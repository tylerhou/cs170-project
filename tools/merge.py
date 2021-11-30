from solver import total_profit
import sys
import enum
import os
import os.path
import parse


class Size(enum.Enum):
    SMALL = enum.auto()
    MEDIUM = enum.auto()
    LARGE = enum.auto()


def traverse(root):
    for size_dir in os.listdir(root):
        for file in os.listdir(os.path.join(root, size_dir)):
            file = file.removesuffix(".in")
            file = file.removesuffix(".out")
            yield (size_dir, file)


def profit(tasks, selected):
    # selected has 1-indexes
    profit = 0
    time = 0
    for index in selected:
        # TODO(tylerhou): Switch to 1 indexes
        task = tasks[index]
        time += task.duration
        profit += task.get_benefit(time)
    return profit


def main(inputs, roots):
    parsed_inputs = {}
    for size, file in traverse(inputs):
        parsed_inputs[(size, file)] = parse.read_input_file(
            os.path.join(inputs, size, file + ".in"))

    for root in roots:
        for size, file in traverse(root):
            tasks = parsed_inputs[(size, file)]
            selected = parse.read_output_file(os.path.join(root, size, file + ".out"))
            print(file, profit(tasks, selected))
            # TODO(tylerhou): Finish


if __name__ == "__main__":
    inputs = sys.argv[1]
    dirs = sys.argv[2:]
    main(inputs, dirs)
