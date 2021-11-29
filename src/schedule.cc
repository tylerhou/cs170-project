#include <algorithm>
#include <iostream>

#include "constants.h"
#include "schedule.h"

// Swaps the two tasks at the selected indexes.
void Schedule::swap_tasks(int first_pos, int second_pos) {
    std::swap(selections_[first_pos], selections_[second_pos]);
}

double Schedule::selected_profit() const {
  double profit = 0;
  int end_time = 0;
  for (const auto selection : selections_) {
    const auto task = problem().tasks()[selection];
    end_time += task.duration;
    profit += problem().profit_for_task(selection, end_time);
  }
  return profit;
}
