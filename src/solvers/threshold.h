#ifndef SOLVERS_THRESHOLD_H_
#define SOLVERS_THRESHOLD_H_

#include <cstdlib>
#include <utility>

#include "glog/logging.h"

#include "src/problem.h"
#include "src/schedule.h"

template <typename RandomGen, int Rounds>
class Threshold {
public:
  Threshold(const Problem &problem, const Sequence *threshold_sequence)
      : problem_(problem), threshold_sequence_(threshold_sequence) {}

  template <typename F>
  Schedule Run(Schedule start, F permute) {
    for (const auto threshold : *threshold_sequence_) {
      DCHECK(threshold >= 0) << "Cannot use negative threshold " << threshold;
      for (int i = 0; i < Rounds; ++i) {
        Schedule neighbor = start;
        permute(neighbor);
        const double improvement =
            neighbor.selected_profit() - start.selected_profit();
        DVLOG(2) << "Neighbor has improvment " << improvement;
        if (improvement > -threshold) {
          DVLOG(2) << "Improvement better than threshold " << threshold;
          start = std::move(neighbor);
        } else {
          DVLOG(2) << "Improvement worse than threshold " << threshold;
        }
      }
    }
    return start;
  }

private:
  const Problem &problem_;
  const Sequence *threshold_sequence_;
};

#endif
