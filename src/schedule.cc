#include <algorithm>
#include <iostream>

#include "glog/logging.h"

#include "src/constants.h"
#include "src/schedule.h"

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

std::vector<int>::const_iterator Schedule::first_uncompleted_task() const {
  int end_time = 0;
  std::vector<int>::const_iterator it;
  for (it = selections().begin(); it != selections().end(); ++it) {
    const auto task = problem().tasks()[*it];
    end_time += task.duration;
    if (end_time > kDayLength) {
      break;
    }
  }
  return it;
}

int Schedule::completed_tasks_size() const {
  return std::distance(selections().begin(), first_uncompleted_task());
}

void Schedule::set_selections(absl::Span<const int> selections) {
  DCHECK(selections.size() == selections_.size())
      << "Given selections size " << selections.size()
      << "differs from number of tasks " << selections_.size();
  std::copy(selections.begin(), selections.end(), selections_.begin());
}
