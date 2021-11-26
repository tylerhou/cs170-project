#include <algorithm>
#include <iostream>

#include "constants.h"
#include "schedule.h"

void Schedule::shift_selected_task(int selected_task_index, int shift) {
  auto &selection = selections_[selected_task_index];
  const int old_end_time = selection.end_time;
  const int new_end_time = old_end_time + shift;
  selection.end_time = new_end_time;
}

void Schedule::trim_selected_suffix() {
  auto it = selections_.end() - 1;
  while (it != selections_.begin() && !(it->end_time < kEndTimesSize)) {
    --it;
  }
  selections_.erase(it + 1, selections_.end());
}

void Schedule::trim_selected_prefix() {
  auto it = selections_.begin();
  while (it != selections_.end() && !(it->end_time >= 0)) {
    ++it;
  }
  selections_.erase(selections_.begin(), it);
}

void Schedule::insert(int position, int task_index) {
  const auto task_to_insert = problem_.tasks()[task_index];

  for (int i = position; i < selections_.size(); ++i) {
    shift_selected_task(i, task_to_insert.duration);
  }

  int end_time = task_to_insert.duration;
  if (position > 0) {
    end_time += selections_[position - 1].end_time;
  }
  selections_.insert(selections_.begin() + position,
                     Selection{.task_index = task_index, .end_time = end_time});

  trim_selected_suffix();
  trim_selected_prefix();
}

void Schedule::push_back(int task_index) {
  Schedule::insert(selections_.size(), task_index);
}

void Schedule::remove(int position) {
  const auto selection = selections_[position];
  const auto task_to_remove = problem_.tasks()[selection.task_index];
  for (int i = position + 1; i < selections_.size(); ++i) {
    shift_selected_task(i, -task_to_remove.duration);
  }
  selections_.erase(selections_.begin() + position);
}

void Schedule::pop_back() { Schedule::remove(selections_.size() - 1); }

// Swaps the two tasks at the selected indexes.
void Schedule::swap_tasks(int first_pos, int second_pos) {
  if (first_pos == second_pos) {
    return;
  }
  if (first_pos > second_pos) {
    Schedule::swap_tasks(second_pos, first_pos);
  }

  const int first_task_index = selections_[first_pos].task_index;
  const int second_task_index = selections_[second_pos].task_index;
  // Remove in reverse order and add in order to avoid shifting.
  Schedule::remove(second_pos);
  Schedule::remove(first_pos);
  Schedule::insert(first_pos, second_task_index);
  Schedule::insert(second_pos, first_task_index);
}

double Schedule::selected_profit() const {
  double profit = 0;
  for (const auto selection : selections_) {
    profit +=
        problem_.profit_for_task(selection.task_index, selection.end_time);
  }
  return profit;
}
