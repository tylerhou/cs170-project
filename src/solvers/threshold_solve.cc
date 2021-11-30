#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

#include "src/parse.h"
#include "src/problem.h"
#include "src/solvers/sequence.h"
#include "src/solvers/threshold.h"

constexpr auto kIterations = 10;

int main() {
  Problem problem{ParseInput(std::cin)};
  if (problem.tasks().empty()) {
      return 0;
  }
  std::random_device rd;
  std::mt19937 g(rd());
  LinearSequence sequence{-200, 0, 0.01, 100};

  StdRandom<std::mt19937> random{g};
  Threshold<LinearSequence, StdRandom<std::mt19937>, 128> solver{
      problem,
      sequence,
      random,
  };

  double max_profit = 0;
  Schedule max_schedule{problem};
  for (int i = 0; i < kIterations; ++i) {
    Schedule initial{problem};
    initial.shuffle(g);
    auto result = solver.Run(initial);
    auto profit = result.selected_profit();
    if (profit > max_profit) {
      max_profit = profit;
      max_schedule = result;
    }
  }
  std::cout << "# Total score: " << max_profit << "\n";
  for (const auto selection : max_schedule.selections()) {
      std::cout << selection << "\n";
  }
}
