#include "src/task.h"

std::istream& operator>>(std::istream& in, Task& task) {
    int index;
    in >> index >> task.deadline >> task.duration >> task.profit;
    return in;
}

