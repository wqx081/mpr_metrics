#include "monitor/registry.h"
#include "monitor/metric.h"

namespace monitor {

Registry* Registry::Instance() {
  // We don't lock in this, but lock in accessors
  static Registry* registry(new Registry);
  return registry;
}

void Registry::AddMetric(const Metric* metric) {
  std::lock_guard<std::mutex> l(mutex_);
  metrics_.insert(metric);
}

std::set<const Metric*> Registry::GetMetrics() const {
  std::lock_guard<std::mutex> l(mutex_);
  return std::set<const Metric *>(metrics_);
}

} // namespace monitor
