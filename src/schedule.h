#ifndef SRC_SCHEDULE_H_
#define SRC_SCHEDULE_H_

#include <algorithm>
#include <array>
#include <random>
#include <vector>

#include "absl/status/status.h"
#include "absl/types/span.h"

#include "src/constants.h"
#include "src/problem.h"
#include "src/task.h"

class Schedule {
public:
  Schedule(const Problem &problem) : problem_(&problem) {
    selections_.reserve(problem_->tasks().size());
    for (int i = 0; i < problem_->tasks().size(); ++i) {
      selections_.push_back(i);
    }
  }

  Schedule(const Schedule &) = default;
  Schedule &operator=(const Schedule &) = default;
  Schedule(Schedule &&) = default;
  Schedule &operator=(Schedule &&) = default;

  // Swaps the two tasks at the indices.
  void swap_tasks(int first_pos, int second_pos);

  // Returns the current profit for the selected tasks.
  // This iterates through the selected tasks, so it takes linear time.
  // Linear time is fine as we must make a copy to compute the neightbor cost.
  double selected_profit() const;

  std::vector<int>::const_iterator begin() const {
    return selections().begin();
  };
  std::vector<int>::const_iterator end() const { return selections().end(); };
  // Returns an iterator into selections that points to the first uncompleted
  // (i.e. the first task that ends after the deadline).  If we complete all
  // tasks, then the return value is equal to selections().end()
  std::vector<int>::const_iterator first_uncompleted_task() const;
  int completed_tasks_size() const;

  const Problem &problem() const { return *problem_; }

  void set_selections(absl::Span<const int> selections);
  const std::vector<int> &selections() const { return selections_; }

  // Mutates the schedule by randomly shuffling all selections.
  template <typename RandomGen> void shuffle(RandomGen &g) {
    std::shuffle(selections_.begin(), selections_.end(), g);
  }
  // Mutates the schedule to a random neighbor by swapping two tasks.
  template <typename RandomGen> void permute(RandomGen &g) {
    auto last_task = completed_tasks_size() - 1;
    std::uniform_int_distribution<> first_dist(0, last_task);
    std::uniform_int_distribution<> second_dist(0,
                                                problem_->tasks().size() - 1);
    auto first = first_dist(g);
    auto second = second_dist(g);
    swap_tasks(first, second);
  }

  // Mutates the schedule to a random close neighbor by swapping two close
  // tasks.
  template <typename RandomGen> void close_permute(RandomGen &g, int distance) {
    auto last_task = completed_tasks_size() - 1;
    std::uniform_int_distribution<> first_dist(0, last_task);
    auto first = first_dist(g);
    std::uniform_int_distribution<> second_dist(
        std::max(0, first - distance), std::min(last_task, first + distance));
    auto second = second_dist(g);
    swap_tasks(first, second);
  }

  // Mutates the schedule to a random neighbor by inserting a task.
  template <typename RandomGen> void insert_permute(RandomGen &g) {
    auto last_task = completed_tasks_size() - 1;
    std::uniform_int_distribution<> first_dist(0, last_task);
    std::uniform_int_distribution<> second_dist(0,
                                                problem_->tasks().size() - 1);
    auto first = first_dist(g);
    auto second = second_dist(g);
    if (second < first) {
      std::swap(first, second);
    }
    auto task = selections_[second];
    selections_.erase(selections_.begin() + second,
                      selections_.begin() + second + 1);
    selections_.insert(selections_.begin() + first, task);
  }

private:
  const Problem *problem_;

  std::vector<int> selections_;
};

#endif
