#ifndef SCHEDULE_H_
#define SCHEDULE_H_

#include <array>
#include <vector>

#include "constants.h"
#include "problem.h"
#include "task.h"

class Schedule {
public:
  Schedule(const Problem &problem) : problem_(problem) {}

  // Inserts the task at the position.
  // If inserting the task causes tasks to be completed after the end of the
  // day, then we remove those tasks from the schedule.
  void insert(int position, int task_index);
  // Removes the task from the schedule.
  void remove(int position);

  // Swaps the two tasks at the indices.
  void swap_tasks(int first_pos, int second_pos);

  // Appends the selected task.
  void push_back(int task_index);
  // Removes the last selected task.
  void pop_back();

  // Returns the current profit for the selected tasks.
  // This iterates through the selected tasks, so it takes linear time.
  // We could update a cached version on every insertion, but that does the
  // same amount of work (assuming selected_profit() isn't needlessly
  // re-called), and we might accumulate floating-point errors.
  double selected_profit() const;

  const Problem &problem() const { return problem_; }

  struct Selection {
    int task_index; // Index of the selected task in the tasks_ vector.
  };
  const std::vector<Selection> &selections() const { return selections_; }

private:
  // Trims tasks that end after the day ends.
  void trim_selected_suffix();

  const Problem &problem_;

  std::vector<Selection> selections_;
  int total_duration_ = 0;
};

inline bool operator==(const Schedule::Selection &lhs,
                       const Schedule::Selection &rhs) {
  return lhs.task_index == rhs.task_index;
}

#endif
