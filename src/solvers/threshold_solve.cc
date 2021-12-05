#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

#include "absl/container/flat_hash_set.h"
#include "gflags/gflags.h"
#include "glog/logging.h"

#include "src/parse.h"
#include "src/problem.h"
#include "src/solvers/sequence.h"
#include "src/solvers/threshold.h"

constexpr auto kIterations = 10;
constexpr auto kSampleSequenceSize = 1000 * 1000;

Schedule greedy_solve(const Problem &problem) {
  std::vector<int> selections;
  absl::flat_hash_set<int> selected;
  int time = 0;
  const auto &tasks = problem.tasks();
  while (selections.size() < tasks.size()) {
    int best_task = -1;
    int best_profit = -1;
    for (int task = 0; task < tasks.size(); ++task) {
      if (selected.find(task) != selected.end())
        continue;
      const int end_time = time + tasks[task].duration;
      const double profit = problem.profit_for_task(task, end_time);
      if (profit > best_profit ||
          (profit == best_profit &&
           tasks[task].deadline < tasks[best_task].deadline)) {
        best_task = task;
        best_profit = profit;
      }
    }
    CHECK(best_task != -1) << "No best task found.";
    selections.push_back(best_task);
    selected.insert(best_task);
    time += tasks[best_task].duration;
  }
  Schedule schedule{problem};
  schedule.set_selections(selections);
  for (auto s : selections) {
    LOG(INFO) << s;
  }
  return schedule;
}

int main(int argc, char *argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);
  Problem problem{ParseInput(std::cin)};
  if (problem.tasks().empty()) {
    return 0;
  }

  std::random_device rd;
  std::mt19937 g(rd());

  auto start = std::chrono::high_resolution_clock::now();
  SampledSequence sequence(problem, /*size=*/kSampleSequenceSize, g);
  auto end = std::chrono::high_resolution_clock::now();
  LOG(INFO) << "Generated " << kSampleSequenceSize << " thresholds in "
            << (end - start) / std::chrono::seconds(1) << " seconds";
  Threshold<std::mt19937, 1> solver{problem, &sequence};

  ConstantSequence quench_sequence(/*constant=*/0, /*size=*/10000);
  Threshold<std::mt19937, 8> quencher{problem, &quench_sequence};

  auto random_permute = [&](Schedule &s) {
    std::uniform_int_distribution<> which(0, 1);
    auto choice = which(g);
    if (choice == 0) {
      s.permute(g);
    } else {
      s.insert_permute(g);
    }
  };
  auto random_close_permute = [&](Schedule &s) { s.close_permute(g, 5); };

  double max_profit = 0;
  Schedule max_schedule{problem};

  auto anneal = [&](Schedule schedule) -> Schedule {
    schedule.shuffle(g);
    return solver.Run(schedule, random_permute);
  };

  auto quench_random = [&](Schedule schedule) -> Schedule {
    while (true) {
      auto quenched = schedule;
      quencher.Run(quenched, random_permute);
      if (quenched.selected_profit() == schedule.selected_profit()) {
        break;
      }
      schedule = std::move(quenched);
    }
    return schedule;
  };

  auto quench_close = [&](Schedule schedule) -> Schedule {
    while (true) {
      auto quenched = schedule;
      quencher.Run(quenched, random_close_permute);
      if (quenched.selected_profit() == schedule.selected_profit()) {
        break;
      }
      schedule = std::move(quenched);
    }
    return schedule;
  };

  auto update = [&](const Schedule &result, std::string label) {
    auto profit = result.selected_profit();
    LOG(INFO) << "Run " << label << " found schedule with profit " << profit;
    if (profit > max_profit) {
      LOG(INFO) << "Profit " << profit
                << " was better than previous best profit " << max_profit;
      max_profit = profit;
      max_schedule = result;
    }
  };

  Schedule inorder{problem};
  update(inorder, "inorder");
  update(quench_close(quench_random(inorder)), "quench inorder");
  update(anneal(inorder), "anneal inorder");

  Schedule greedy_profit{problem};
  std::vector<int> selections = greedy_profit.selections();
  auto tasks = greedy_profit.problem().tasks();
  std::sort(selections.begin(), selections.end(), [&](int f, int s) {
    auto tf = tasks[f], ts = tasks[s];
    LOG(INFO) << f << " " << tf.profit << " " << tf.deadline << " " << s << " "
              << ts.profit << " " << ts.deadline;
    LOG(INFO) << (tf.profit > ts.profit && tf.deadline < ts.deadline);
    if (tf.profit == ts.profit) {
      return tf.deadline < ts.deadline;
    }
    return tf.profit > ts.profit;
  });
  greedy_profit.set_selections(selections);
  update(greedy_profit, "greedy_profit");
  update(quench_close(quench_random(greedy_profit)), "quench greedy_profit");
  update(quench_close(quench_random(anneal(greedy_profit))),
         "anneal greedy_profit");

  Schedule greedy_profit_ratio{problem};
  selections = greedy_profit.selections();
  std::sort(selections.begin(), selections.end(), [&](int f, int s) {
    auto tasks = greedy_profit.problem().tasks();
    auto tf = tasks[f], ts = tasks[s];
    double tf_ratio = tf.profit / tf.duration,
           ts_ratio = ts.profit / ts.duration;
    if (tf_ratio == ts_ratio) {
      return tf.deadline < ts.deadline;
    }
    return tf_ratio > ts_ratio;
  });
  greedy_profit.set_selections(selections);
  update(greedy_profit_ratio, "greedy_profit_ratio");
  update(quench_close(quench_random(greedy_profit_ratio)),
         "quench greedy_profit_ratio");
  update(quench_close(quench_random(anneal(greedy_profit_ratio))),
         "anneal greedy_profit_ratio");

  Schedule greedy = greedy_solve(problem);
  update(greedy, "greedy");
  update(quench_close(quench_random(greedy)), "quench greedy");
  update(quench_close(quench_random(anneal(greedy))), "anneal greedy");

  for (int i = 0; i < kIterations; ++i) {
    Schedule initial{problem};
    auto result = anneal(std::move(initial));
    result = quench_random(std::move(result));
    result = quench_close(std::move(result));
    update(result, std::to_string(i));
  }

  for (const auto selection : max_schedule) {
    // Selections are 1-indexed.
    std::cout << selection + 1 << "\n";
  }
}
