#include "src/parse.h"

std::vector<Task> ParseInput(std::istream &in) {
    std::vector<Task> tasks;
    int n;
    if (!(in >> n)) {
        return tasks;
    }
    for (int i = 0; i < n; ++i) {
        Task task;
        if (!(in >> task)) {
            break;
        }
        tasks.push_back(task);
    }
    return tasks;
};
