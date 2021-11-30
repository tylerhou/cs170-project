from solver import total_profit
import sys
import enum
import os
import os.path
import parse
from collections import defaultdict

def traverse(root):
    for size_dir in os.listdir(root):
        for file in os.listdir(os.path.join(root, size_dir)):
            file = file.removesuffix(".in")
            file = file.removesuffix(".out")
            yield (size_dir, file)


MAX_TIME = 1440
def compute_profit(tasks, selections):
    # selections has 1-indexes
    profit = 0
    time = 0
    for index in selections:
        task = tasks[index-1]
        time += task.duration
        if time > MAX_TIME:
            break
        profit += task.get_benefit(time)
    return profit


def selection_prefix(tasks, selections):
    time = 0
    prefix = []
    for index in selections:
        task = tasks[index-1]
        time += task.duration
        if time > MAX_TIME:
            break
        prefix.append(index)
    return prefix


def main(inputs, roots, output):
    parsed_inputs = {}
    for size, file in traverse(inputs):
        key = (size, file)
        parsed_inputs[key] = parse.read_input_file(
            os.path.join(inputs, size, file + ".in"))

    max_profit = defaultdict(int)
    max_selections = {}
    for root in roots:
        for size, file in traverse(root):
            key = (size, file)
            tasks = parsed_inputs[key]
            selections = parse.read_output_file(
                os.path.join(root, size, file + ".out"))
            profit = compute_profit(tasks, selections)
            if profit > max_profit[key]:
                max_profit[key] = profit
                max_selections[key] = selections

    for (size, file) in max_selections:
        key = (size, file)
        dirname = os.path.join(output, size)
        # Fragile if the directory gets created in between,
        # but whatever.
        if not os.path.exists(dirname):
            os.makedirs(dirname)
        selections = max_selections[key]
        selections = selection_prefix(parsed_inputs[key], selections)
        parse.write_output_file(os.path.join(
            output, size, file + ".out"), selections)


if __name__ == "__main__":
    # merge.py inputs roots... output
    assert len(sys.argv) >= 4
    inputs = sys.argv[1]
    roots = sys.argv[2:-1]
    output = sys.argv[-1]
    main(inputs, roots, output)
