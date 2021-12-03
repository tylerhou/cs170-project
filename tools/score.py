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
def compute_profit(tasks, selections, offset=1):
    # selections has 1-indexes
    profit = 0
    time = 0
    for index in selections:
        if not (0 <= index - offset < len(tasks)):
            return 0
        task = tasks[index-offset]
        time += task.duration
        if time > MAX_TIME:
            break
        profit += task.get_benefit(time)
    return profit


from collections import namedtuple
Result = namedtuple("Result", ["profit", "roots"], defaults=[0, []])

def main(inputs, roots):
    parsed_inputs = {}
    for size, file in traverse(inputs):
        key = (size, file)
        parsed_inputs[key] = parse.read_input_file(
            os.path.join(inputs, size, file + ".in"))

    max_profit = defaultdict(Result)
    for root in roots:
        for size, file in traverse(root):
            key = (size, file)
            tasks = parsed_inputs[key]
            selections = parse.read_output_file(
                os.path.join(root, size, file + ".out"))
            max_offset = -1
            for offset in (0, 1):
                profit = compute_profit(tasks, selections, offset)
                if profit == max_profit[key].profit:
                    max_profit[key].roots.append(root)
                    max_offset = offset
                if profit > max_profit[key].profit:
                    max_profit[key] = Result(profit=profit, roots=[root])
                    max_offset = offset

    for key, profit in max_profit.items():
        print(key, profit)


if __name__ == "__main__":
    # score.py inputs outputs
    assert len(sys.argv) >= 3
    inputs = sys.argv[1]
    roots = sys.argv[2:]

    main(inputs, roots)
