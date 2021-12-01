#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

#include "gflags/gflags.h"
#include "glog/logging.h"

#include "src/parse.h"
#include "src/problem.h"
#include "src/solvers/sequence.h"
#include "src/solvers/threshold.h"

constexpr auto kIterations = 500;
constexpr auto kSampleSequenceSize = 100 * 1000;

int main(int argc, char *argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);
  Problem problem{ParseInput(std::cin)};
  if (problem.tasks().empty()) {
    return 0;
  }
  std::random_device rd;
  std::mt19937 g(rd());
  /* LinearSequence sequence(-200, 0, 0.01); */
  auto start = std::chrono::high_resolution_clock::now();
  SampledSequence sequence(problem, /*size=*/kSampleSequenceSize, g);
  auto end = std::chrono::high_resolution_clock::now();
  LOG(INFO) << "Generated " << kSampleSequenceSize << " thresholds in "
            << (end - start) / std::chrono::seconds(1) << " seconds";
  ThresholdImpl<std::mt19937, 1> solver{problem, &sequence, g};

  ConstantSequence quench_sequence(/*constant=*/0, /*size=*/10000);
  ThresholdImpl<std::mt19937, 8> quencher{problem, &quench_sequence, g};

  double max_profit = 0;
  Schedule max_schedule{problem};
  for (int i = 0; i < kIterations; ++i) {
    Schedule initial{problem};
    initial.shuffle(g);
    auto result = solver.Run(initial);
    while (true) {
      auto quenched = result;
      quencher.Run(quenched);
      if (quenched.selected_profit() == result.selected_profit()) {
        break;
      }
      result = std::move(quenched);
    }
    auto profit = result.selected_profit();
    LOG(INFO) << "Run " << i << " found schedule with profit " << profit;
    if (profit > max_profit) {
      LOG(INFO) << "Profit was better than previous best profit " << max_profit;
      max_profit = profit;
      max_schedule = result;
    }
  }
  for (auto it = max_schedule.begin();
       it != max_schedule.first_uncompleted_task(); ++it) {
    // Selections are 1-indexed.
    std::cout << *it + 1 << "\n";
  }
}
