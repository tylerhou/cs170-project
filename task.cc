#include "task.h"

std::istream& operator>>(std::istream& in, Task& task) {
    int index, deadline, duration;
    float profit;
    in >> index >> deadline >> duration >> profit;
    task.index = index;
    task.deadline = deadline;
    task.duration = duration;
    task.profit = profit;
    return in;
}

