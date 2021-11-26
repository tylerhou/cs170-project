#ifndef TASK_H_
#define TASK_H_

#include <iostream>

class Task {
public:
  Task(int deadline, int duration, float profit)
      : deadline(deadline), duration(duration), profit(profit) {}

  Task() = default;

  friend std::istream &operator>>(std::istream &in, Task &task);

  int index = 0, deadline = 0, duration = 0;
  float profit = 0;
};

#endif
