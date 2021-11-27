#include <iostream>

#include "gtest/gtest.h"

#include "parse.h"
#include "problem.h"
#include "schedule.h"

using Selection = Schedule::Selection;

TEST(Schedule, PushBack) {
  std::string input = R"(5
1 100 50 50
2 200 10 75
3 100 50 50
4 400 300 80)";
  std::stringstream in(input);
  std::vector<Task> tasks = ParseInput(in);

  Problem problem{tasks};
  Schedule schedule{problem};

  schedule.push_back(0);
  EXPECT_EQ(schedule.selected_profit(), 50);

  schedule.push_back(1);
  EXPECT_EQ(schedule.selected_profit(), 125);

  schedule.push_back(2);
  EXPECT_DOUBLE_EQ(schedule.selected_profit(), 125 + 42.1832408298192);

  EXPECT_EQ(schedule.selections(),
            std::vector<Selection>({
                Selection{.task_index = 0},
                Selection{.task_index = 1},
                Selection{.task_index = 2},
            }));
}

TEST(Schedule, PopBack) {
  std::string input = R"(5
1 100 50 50
2 200 10 75
3 100 50 50
4 400 300 80)";
  std::stringstream in(input);
  std::vector<Task> tasks = ParseInput(in);

  Problem problem{tasks};
  Schedule schedule{problem};

  schedule.push_back(0);
  schedule.push_back(1);
  schedule.push_back(2);
  schedule.pop_back();

  EXPECT_EQ(schedule.selected_profit(), 125);
  EXPECT_EQ(schedule.selections(),
            std::vector<Selection>({
                Selection{.task_index = 0},
                Selection{.task_index = 1},
            }));
}

TEST(Schedule, Insert) {
  std::string input = R"(5
1 100 50 50
2 200 10 75
3 100 50 50
4 400 300 80)";
  std::stringstream in(input);
  std::vector<Task> tasks = ParseInput(in);

  Problem problem{tasks};
  Schedule schedule{problem};

  schedule.push_back(0);
  schedule.push_back(1);
  schedule.insert(1, 2);

  EXPECT_EQ(schedule.selected_profit(), 175);
  EXPECT_EQ(schedule.selections(),
            std::vector<Selection>({
                Selection{.task_index = 0},
                Selection{.task_index = 2},
                Selection{.task_index = 1},
            }));
}

TEST(Schedule, Remove) {
  std::string input = R"(5
1 100 50 50
2 200 10 75
3 100 50 50
4 400 300 80)";
  std::stringstream in(input);
  std::vector<Task> tasks = ParseInput(in);

  Problem problem{tasks};
  Schedule schedule{problem};

  schedule.push_back(0);
  schedule.push_back(1);
  schedule.insert(1, 2);

  EXPECT_EQ(schedule.selected_profit(), 175);
  EXPECT_EQ(schedule.selections(),
            std::vector<Selection>({
                Selection{.task_index = 0},
                Selection{.task_index = 2},
                Selection{.task_index = 1},
            }));
}

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

  schedule.push_back(3);
  schedule.push_back(2);
  schedule.push_back(1);
  schedule.swap_tasks(0, 1);

  EXPECT_DOUBLE_EQ(schedule.selected_profit(), 50 + 80 + 4.9406065819802);
  EXPECT_EQ(schedule.selections(),
            std::vector<Selection>({
                Selection{.task_index = 2},
                Selection{.task_index = 3},
                Selection{.task_index = 1},
            }));
}

TEST(Schedule, Copy) {
  std::string input = R"(5
1 100 50 50
2 200 10 75
3 100 50 50
4 400 300 80)";
  std::stringstream in(input);
  std::vector<Task> tasks = ParseInput(in);

  Problem problem{tasks};
  Schedule schedule{problem};

  schedule.push_back(0);
  schedule.push_back(1);

  Schedule schedule_copy{schedule};
  schedule.pop_back();

  EXPECT_EQ(schedule_copy.selected_profit(), 125);
  EXPECT_EQ(schedule_copy.selections(),
            std::vector<Selection>({
                Selection{.task_index = 0},
                Selection{.task_index = 1},
            }));

  EXPECT_EQ(schedule.selected_profit(), 50);
  EXPECT_EQ(schedule.selections(),
            std::vector<Selection>({
                Selection{.task_index = 0},
            }));
}
