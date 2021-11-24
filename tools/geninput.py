import random
import sys
import solver
from solver import Task


DEADLINE = 1440
def generate_random(n):
    for i in range(1, n+1):
        t = random.randint(0, DEADLINE)
        d = random.randint(8, 17)
        p = random.uniform(60, 90)
        yield Task(i, duration=d, deadline=t, profit=p)


def pseudorandom_partition(t, n):
    """Partitions the number t into n parts.

    This is not unbiased, but probably works for our use case.
    https://stackoverflow.com/a/10287192
    """
    partitions = [0 for _ in range(n)]
    for _ in range(t):
        partitions[random.randrange(n)] += 1
    return partitions


def generate_solution(n, t):
    """Creates n tasks that can all be scheduled, one after the other
    that take t time."""
    time = 0
    for duration in pseudorandom_partition(t, n):
        time += duration
        # Pick a high profit so that we are penalized if we miss any task.
        yield Task(1, duration, time, random.uniform(85, 100))


def wiggle_deadlines(tasks):
    """Given a sequence of tasks, wiggle deadlines so that it is harder to solve."""
    for task in tasks:
        # Bias the deadline shift to later rather than earlier. That way we
        # lose as few points as possible.
        if random.random() > 0.5:
            deadline = task.deadline + random.uniform(0, task.duration)
        else:
            deadline = task.deadline - random.uniform(0, task.deadline / 20)
        deadline = max(min(deadline, 1440), 0)

        yield Task(task.index, task.duration, round(deadline), task.profit)


def print_tasks(tasks, out=sys.stdout):
    tasks = list(tasks)
    print(len(tasks), file=out)
    for i, task in enumerate(tasks):
        print(i+1, task.deadline, task.duration, "{:.3f}".format(task.profit), file=out)

def reindex_tasks(tasks):
    for i, task in enumerate(tasks):
        yield Task(i, duration=task.duration, deadline=task.deadline, profit=task.profit)


if __name__ == "__main__":
    solution_length = int(sys.argv[1])
    random_length = int(sys.argv[2])
    tasks = list(wiggle_deadlines(generate_solution(solution_length, DEADLINE)))
    tasks += list(generate_random(random_length))
    tasks = list(reindex_tasks(tasks))
    random.shuffle(tasks)

    new_indexes = [0] * solution_length
    for i, task in enumerate(tasks):
        new_index = i+1
        if task.index < solution_length:
            new_indexes[task.index] = new_index

    with open(f"{solution_length + random_length}.in", "w") as f:
        print_tasks(tasks, out=f)

    with open(f"{solution_length + random_length}.out", "w") as f:
        for i in new_indexes:
            print(i, file=f)

    chosen = []
    for index in new_indexes:
        chosen.append(tasks[index-1])

    print(solver.total_profit(chosen, 1440, solver.linear_decaying_profit))
    # print(sorted(solver.force_solve(tasks, DEADLINE).items(), reverse=True)[0][0])
    # print(sorted(solver.force_solve(tasks, DEADLINE).items(), reverse=True)[0][1][0])
    # print_tasks(generate_random(int(sys.argv[1])))
