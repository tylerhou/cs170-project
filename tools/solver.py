from collections import namedtuple, defaultdict
from itertools import permutations

Task = namedtuple("Task", ["index", "duration", "deadline", "profit"])

tasks = [
    Task(1, 30, 100, 10),
    Task(2, 40, 100, 20),
    Task(3, 15, 100, 5),
    Task(4, 20, 100, 30),
    Task(5, 25, 100, 15),
]

def total_profit(tasks, max_time, profit_fn):
    time = profit = 0
    for t in tasks:
        time += t.duration
        if time > max_time:
            break
        profit += profit_fn(time, t)
    return profit

def linear_decaying_profit(time, task):
    """Computes linearly decaying profit.

    >>> linear_decaying_profit(100, Task(0, 50, 100, 50))
    50
    >>> linear_decaying_profit(100, Task(0, 40, 120, 50))
    50
    >>> linear_decaying_profit(100, Task(0, 30, 90, 50))
    40
    >>> linear_decaying_profit(100, Task(0, 20, 50, 50))
    0
    """
    s = max(0, time - task.deadline)
    return max(0, task.profit - s)

def cutoff_profit(time, task):
    """Only receive profit if the task is completed before the deadline.

    >>> linear_decaying_profit(100, Task(0, 50, 100, 50))
    50
    >>> linear_decaying_profit(100, Task(0, 40, 120, 50))
    50
    >>> linear_decaying_profit(100, Task(0, 30, 90, 50))
    40
    >>> linear_decaying_profit(100, Task(0, 20, 50, 50))
    0
    """
    if time <= task.deadline:
        return task.profit
    return 0

def force_solve(tasks, time):
    profits_to_tasks = defaultdict(list)
    for n in range(len(tasks) + 1):
        for p in permutations(tasks, n):
            profit = total_profit(p, time, cutoff_profit)
            profits_to_tasks[profit].append(p)
    return profits_to_tasks

def greedy_profit_solve(tasks):
    return sorted(tasks, key=lambda t: t.profit, reverse=True)

def greedy_deadline_solve(tasks):
    return sorted(tasks, key=lambda t: t.deadline)

tasks = [
    Task(1, 30, 30, 10),
    Task(2, 30, 31, 20),
]
print(total_profit(greedy_profit_solve(tasks), 100, linear_decaying_profit))
print(total_profit(greedy_deadline_solve(tasks), 100, linear_decaying_profit))

# for profit, tasks in sorted(force_solve(tasks, time=100).items()):
#     print(profit)
#     for task in tasks:
#         print("\t", task)
