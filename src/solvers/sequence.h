#ifndef SOLVERS_SEQUENCE_H
#define SOLVERS_SEQUENCE_H

#include <vector>

#include "src/schedule.h"

class Sequence {
public:
  Sequence() = default;
  virtual ~Sequence() = default;

  virtual int size() const = 0;
  virtual std::vector<double>::const_iterator begin() const = 0;
  virtual std::vector<double>::const_iterator end() const = 0;
};

class LinearSequence : public Sequence {
public:
  // Unfortunately, writing an iterator is annoying, so we fill a vector.
  // This uses more memory and might be slower, but whatever.
  LinearSequence(double start, double stop, double step) {
    sequence_.reserve((stop - start) / step + 1);
    while (start < stop) {
      sequence_.push_back(start);
      start += step;
    }
  }

  int size() const { return sequence_.size(); }
  std::vector<double>::const_iterator begin() const {
    return sequence_.begin();
  }
  std::vector<double>::const_iterator end() const { return sequence_.end(); }

  std::vector<double> sequence_;
};

class ConstantSequence : public Sequence {
public:
  // Unfortunately, writing an iterator is annoying, so we fill a vector.
  // This uses more memory and might be slower, but whatever.
  ConstantSequence(int constant, int size) {
    sequence_.reserve(size);
    for (int i = 0; i < size; ++i) {
      sequence_.push_back(constant);
    }
  }

  int size() const { return sequence_.size(); }
  std::vector<double>::const_iterator begin() const {
    return sequence_.begin();
  }
  std::vector<double>::const_iterator end() const { return sequence_.end(); }

  std::vector<double> sequence_;
};

// Creates a threshold sequence by generating random schedules and selecting a
// neighbor. Computes the delta in cost, and adds that delta as a threshold.
// See: http://comisef.wikidot.com/tutorial:tathresholds
class SampledSequence : public Sequence {
public:
  template <typename RandomGen>
  SampledSequence(const Problem &problem, int size, RandomGen &g)
      : problem_(problem) {
    Schedule schedule{problem_};
    for (int i = 0; i < size; ++i) {
      schedule.shuffle(g);
      const auto schedule_profit = schedule.selected_profit();
      schedule.permute(g);
      const auto difference =
          std::fabs(schedule_profit - schedule.selected_profit());
      sequence_.push_back(difference);
    }
    std::sort(sequence_.rbegin(), sequence_.rend());
  }

  int size() const { return sequence_.size(); }
  std::vector<double>::const_iterator begin() const {
    return sequence_.begin();
  }
  std::vector<double>::const_iterator end() const { return sequence_.end(); }

private:
  const Problem &problem_;
  std::vector<double> sequence_;
};

#endif
