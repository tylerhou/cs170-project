#include <iostream>

#include "absl/types/span.h"
#include "gtest/gtest.h"

#include "src/parse.h"
#include "src/problem.h"
#include "src/schedule.h"

TEST(Schedule, Swap) {
  std::string input = R"(5
1 100 50 50
2 200 10 75
3 100 50 50
4 400 300 80)";
  std::stringstream in(input);
  std::vector<Task> tasks = ParseInput(in);

  Problem problem{tasks};
  Schedule schedule{problem};

  schedule.set_selections(absl::Span<const int>({3, 2, 1, 0}));
  schedule.swap_tasks(0, 1);

  const double profit = 50 + 80 + 4.9406065819802 + 0.2571805286515;
  EXPECT_DOUBLE_EQ(schedule.selected_profit(), profit);
  EXPECT_EQ(schedule.selections(), absl::Span<const int>({2, 3, 1, 0}));
}
