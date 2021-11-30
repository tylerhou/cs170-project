#ifndef SOLVERS_THRESHOLD_H_
#define SOLVERS_THRESHOLD_H_

#include <cstdlib>
#include <utility>

#include "glog/logging.h"

#include "src/problem.h"
#include "src/schedule.h"

class Threshold {
public:
  Threshold() = default;
  virtual ~Threshold() = default;

  virtual Schedule Run(Schedule start) = 0;
};

template <typename RandomGen, int Rounds>
class ThresholdImpl : public Threshold {
public:
  ThresholdImpl(const Problem &problem, const Sequence *threshold_sequence,
                RandomGen &random)
      : problem_(problem), threshold_sequence_(threshold_sequence),
        random_(random) {}

  Schedule Run(Schedule start) {
    for (const auto threshold : *threshold_sequence_) {
      DCHECK(threshold >= 0) << "Cannot use negative threshold " << threshold;
      for (int i = 0; i < Rounds; ++i) {
        Schedule neighbor = start;
        neighbor.permute(random_);
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
  RandomGen &random_;
};

#endif
