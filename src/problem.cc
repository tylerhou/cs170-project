#include "problem.h"

std::array<double, kEndTimesSize> decay_per_minutes_late() {
  std::array<double, kEndTimesSize> decays;
  double curr = 1;
  for (int i = 0; i < kEndTimesSize; ++i) {
    decays[i] = curr;
    curr *= kDecayPerMinute;
  }
  return decays;
}

std::vector<std::array<double, kEndTimesSize>>
Problem::compute_profit_matrix(const std::vector<Task> &tasks) {
  std::vector<std::array<double, kEndTimesSize>> matrix;
  const auto decay_lookup = decay_per_minutes_late();
  for (const auto task : tasks) {
    std::array<double, kEndTimesSize> decays;
    for (int time = 0; time < kEndTimesSize; ++time) {
      int minutes_late = std::max(time - task.deadline, 0);
      decays[time] = decay_lookup[minutes_late] * task.profit;
    }
    matrix.push_back(decays);
  }
  return matrix;
}
