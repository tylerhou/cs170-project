#include "problem.h"

std::array<double, Problem::EndTimesSize> decay_per_minutes_late() {
  std::array<double, Problem::EndTimesSize> decays;
  double curr = 1;
  for (int i = 0; i < Problem::EndTimesSize; ++i) {
    decays[i] = curr;
    curr *= kDecayPerMinute;
  }
  return decays;
}

std::vector<std::array<double, Problem::EndTimesSize>>
Problem::compute_profit_matrix(const std::vector<Task> &tasks) {
  std::vector<std::array<double, EndTimesSize>> matrix;
  const auto decay_lookup = decay_per_minutes_late();
  for (const auto task : tasks) {
    std::array<double, EndTimesSize> decays;
    for (int time = 0; time < EndTimesSize; ++time) {
      int minutes_late = std::max(time - task.deadline, 0);
      decays[time] = decay_lookup[minutes_late] * task.profit;
    }
    matrix.push_back(decays);
  }
  return matrix;
}
