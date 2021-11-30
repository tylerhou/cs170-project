#ifndef SRC_SCHEDULE_H_
#define SRC_SCHEDULE_H_

#include <algorithm>
#include <array>
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

  const Problem &problem() const { return *problem_; }

  void set_selections(absl::Span<const int> selections);
  const std::vector<int> &selections() const { return selections_; }

  template <typename RandomGen> void shuffle(RandomGen &g) {
    std::shuffle(selections_.begin(), selections_.end(), g);
  }

private:
  const Problem *problem_;

  std::vector<int> selections_;
};

#endif
