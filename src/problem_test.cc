#include <iostream>

#include "gtest/gtest.h"

#include "src/problem.h"
#include "src/parse.h"

TEST(Problem, ProfitForTask) {
  std::string input = R"(5
1 100 50 50
2 200 10 75)";
  std::stringstream in(input);
  std::vector<Task> tasks = ParseInput(in);

  Problem problem{tasks};

  EXPECT_EQ(problem.profit_for_task(0, 0), 50);
  EXPECT_EQ(problem.profit_for_task(0, 50), 50);
  EXPECT_EQ(problem.profit_for_task(0, 100), 50);

  EXPECT_DOUBLE_EQ(problem.profit_for_task(0, 101), 49.157184231745482);
  EXPECT_DOUBLE_EQ(problem.profit_for_task(0, 150), 21.370746597436334);
  EXPECT_DOUBLE_EQ(problem.profit_for_task(0, 300), 1.668663498016306);
  EXPECT_DOUBLE_EQ(problem.profit_for_task(0, 1440), 6.3935447105762268e-09);

  EXPECT_EQ(problem.profit_for_task(0, -1), 0);
  EXPECT_EQ(problem.profit_for_task(0, 2000), 0);

  EXPECT_EQ(problem.profit_for_task(1, 0), 75);
  EXPECT_EQ(problem.profit_for_task(1, 50), 75);
  EXPECT_EQ(problem.profit_for_task(1, 100), 75);
  EXPECT_EQ(problem.profit_for_task(1, 200), 75);

  EXPECT_DOUBLE_EQ(problem.profit_for_task(1, 201), 73.735776347618227);
  EXPECT_DOUBLE_EQ(problem.profit_for_task(1, 250), 32.056119896154506);
  EXPECT_DOUBLE_EQ(problem.profit_for_task(1, 400), 2.502995247024459);
  EXPECT_DOUBLE_EQ(problem.profit_for_task(1, 1440), 5.2496891088524894e-08);

  EXPECT_EQ(problem.profit_for_task(1, -1), 0);
  EXPECT_EQ(problem.profit_for_task(1, 2000), 0);
}
