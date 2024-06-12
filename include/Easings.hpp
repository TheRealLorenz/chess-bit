#include <cmath>

namespace easings {

inline double easeOutCubic(double x) { return 1 - std::pow(1 - x, 3); }

}  // namespace easings
