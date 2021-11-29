#ifndef SOLVERS_THRESHOLD_H_
#define SOLVERS_THRESHOLD_H_

#include <cstdlib>
#include <utility>

#include "src/problem.h"
#include "src/schedule.h"

template <typename Sequence, typename Random, int Rounds> class Threshold {
public:
  Threshold(const Problem &problem, const Sequence &threshold_sequence,
            Random &random)
      : problem_(problem), threshold_sequence_(threshold_sequence),
        random_(random) {}

  Schedule Run(Schedule start) {
    const auto size = problem_.tasks().size();
    for (const auto threshold : threshold_sequence_) {
      for (int i = 0; i < Rounds; ++i) {
        auto first = random_(0, size);
        auto second = random_(0, size);

        Schedule neighbor = start;
        neighbor.swap_tasks(first, second);
        const double improvement =
            neighbor.selected_profit() - start.selected_profit();
        if (improvement > threshold) {
          start = std::move(neighbor);
        }
      }
    }
    return start;
  }

private:
  const Problem &problem_;
  const Sequence &threshold_sequence_;
  Random &random_;
};

class StdRand {
public:
  int operator()(int begin, int end) { return std::rand() % (end - begin) + begin; }
};

template <class T> class StdRandom {
public:
  StdRandom(T &generator) : generator_(generator){};
  int operator()(int begin, int end) { return std::rand() % (end - begin) + begin; }

private:
  T &generator_;
};

#endif
