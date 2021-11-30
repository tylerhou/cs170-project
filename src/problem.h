#ifndef SRC_PROBLEM_H_
#define SRC_PROBLEM_H_

#include <array>
#include <vector>

#include "src/constants.h"
#include "src/task.h"

class Problem {
public:
  static constexpr auto EndTimesSize = kDayLength + 1;

  Problem(std::vector<Task> tasks)
      : tasks_(std::move(tasks)),
        profit_matrix_(Problem::compute_profit_matrix(tasks_)) {}

  static std::vector<std::array<double, EndTimesSize>>
  compute_profit_matrix(const std::vector<Task> &tasks);

  const std::vector<Task> &tasks() const { return tasks_; }

  const double profit_for_task(int task_index, int end_time) const {
    if (0 <= end_time && end_time < EndTimesSize) {
      return profit_matrix_[task_index][end_time];
    }
    return 0;
  }

private:
  const std::vector<Task> tasks_;
  const std::vector<std::array<double, EndTimesSize>> profit_matrix_;
};

#endif
