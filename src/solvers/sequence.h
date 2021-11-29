#ifndef SOLVERS_SEQUENCE_H
#define SOLVERS_SEQUENCE_H

#include <vector>

class LinearSequence {
public:
  // Unfortunately, writing an iterator is annoying, so we fill a vector.
  // This uses more memory and might be slower, but whatever.
  LinearSequence(double start, double stop, double step, int quench) {
    sequence_.reserve((stop - start) / step + quench + 1);
    while (start < stop) {
      sequence_.push_back(start);
      start += step;
    }
    for (int i = 0; i < quench; ++i) {
        sequence_.push_back(0);
    }
  }

  const auto begin() const { return sequence_.begin(); }
  const auto end() const { return sequence_.end(); }

  std::vector<double> sequence_;
};

#endif
