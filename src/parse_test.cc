#include <iostream>

#include "gtest/gtest.h"

#include "parse.h"
#include "task.h"

TEST(ParseInput, Parse) {
  std::cout << "In test";
  std::string input = R"(5
1 100 20 5.317
2 200 10 3.285
3 300 20 84.229
4 400 1 28.302
5 1 1 90.192)";
  std::stringstream in(input);
  std::vector<Task> tasks = ParseInput(in);

  EXPECT_EQ(tasks.size(), 5);
  EXPECT_EQ(tasks[0].deadline, 100);
  EXPECT_EQ(tasks[1].deadline, 200);
  EXPECT_EQ(tasks[4].deadline, 1);

  EXPECT_EQ(tasks[0].duration, 20);
  EXPECT_EQ(tasks[1].duration, 10);
  EXPECT_EQ(tasks[4].duration, 1);

  EXPECT_FLOAT_EQ(tasks[0].profit, 5.317);
  EXPECT_FLOAT_EQ(tasks[1].profit, 3.285);
  EXPECT_FLOAT_EQ(tasks[4].profit, 90.192);
}
