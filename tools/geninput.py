import random
import sys

def random_input(n):
    print(n)
    for i in range(1, n+1):
        t = random.randint(0, 1440)
        d = random.randint(1, 60)
        p = random.uniform(0, 100)
        print(i, t, d, "{:.3f}".format(p))

if __name__ == "__main__":
    random_input(int(sys.argv[1]))

