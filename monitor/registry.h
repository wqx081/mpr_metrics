// Author: wangqx@mpreader.com (Wang Qixiang)
//
#ifndef MONITOR_REGISTRY_H_
#define MONITOR_REGISTRY_H_
#include <mutex> // C++11
#include <set>
#include <sstream>

#include "base/macros.h"

namespace monitor {


class Metric;

class Registry {
 public:
  static Registry* Instance();
  
  void AddMetric(const Metric* metric);
  std::set<const Metric *> GetMetrics() const;

 private:
  Registry() = default;
  
  mutable std::mutex mutex_;
  std::set<const Metric *> metrics_;

  DISALLOW_COPY_AND_ASSIGN(Registry);
};

} // namespace monitor
#endif // MONITOR_REGISTRY_H_
