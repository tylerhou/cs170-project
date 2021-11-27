#include <algorithm>
#include <iostream>

#include "constants.h"
#include "schedule.h"

void Schedule::trim_selected_suffix() {
  while (selections_.size() > 0 && total_duration_ > kDayLength) {
    const auto task = problem_.tasks()[selections_.back().task_index];
    total_duration_ -= task.duration;
    selections_.pop_back();
  }
}

void Schedule::insert(int position, int task_index) {
  const auto task = problem_.tasks()[task_index];
  selections_.insert(selections_.begin() + position,
                     Selection{.task_index = task_index});
  total_duration_ += task.duration;
  trim_selected_suffix();
}

void Schedule::push_back(int task_index) {
  Schedule::insert(selections_.size(), task_index);
}

void Schedule::remove(int position) {
  const auto selection = selections_[position];
  const auto task = problem_.tasks()[selection.task_index];
  selections_.erase(selections_.begin() + position);
  total_duration_ -= task.duration;
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
  int end_time = 0;
  for (const auto selection : selections_) {
    const auto task = problem_.tasks()[selection.task_index];
    end_time += task.duration;
    profit += problem_.profit_for_task(selection.task_index, end_time);
  }
  return profit;
}
