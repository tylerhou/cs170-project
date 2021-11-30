import random
from collections import Counter, deque

class Selector:
    def __init__(self, inputs):
        self.inputs = inputs
        self.outstanding = Counter()
        self.outstanding_queue = deque()
        self.completed = Counter()

    def _total_counts(self):
        return self.outstanding + self.completed

    def select(self):
        """Picks an input according to some priority and returns it."""

def main(inputs, outputs, port):
    parsed_inputs = {}
    for size, file in traverse(inputs):
        key = (size, file)
        parsed_inputs[key] = parse.read_input_file(
            os.path.join(inputs, size, file + ".in"))

def handler():


if __name__ == "__main__":
    import sys
    inputs, outputs, port = *sys.argv[1:]
    main(inputs, outputs, port)
