#ifndef SCHEDULE_H_
#define SCHEDULE_H_

#include <array>
#include <vector>

#include "absl/types/span.h"
#include "absl/status/status.h"

#include "constants.h"
#include "problem.h"
#include "task.h"

class Schedule {
public:
  Schedule(const Problem &problem) : problem_(problem) {}

  // Swaps the two tasks at the indices.
  void swap_tasks(int first_pos, int second_pos);


  // Returns the current profit for the selected tasks.
  // This iterates through the selected tasks, so it takes linear time.
  // Linear time is fine as we must make a copy to compute the neightbor cost.
  double selected_profit() const;

  const Problem &problem() const { return problem_; }

  absl::Status set_selections(absl::Span<const int> selections) {
      if (selections.size() != problem_.tasks().size()) {
          return absl::InvalidArgumentError("wrong selections size");
      }
      selections_.resize(problem_.tasks().size());
      std::copy(selections.begin(), selections.end(), selections_.begin());
      return absl::OkStatus();
  }
  const std::vector<int> &selections() const { return selections_; }

private:
  const Problem &problem_;

  std::vector<int> selections_;
};

#endif
