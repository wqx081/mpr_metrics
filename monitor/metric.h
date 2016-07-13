#ifndef MONITOR_METRIC_H_
#define MONITOR_METRIC_H_

#include <map>
#include <ostream>
#include <set>
#include <string>
#include <vector>

#include "base/macros.h"
#include "monitor/registry.h"

namespace monitor {

// Trait
template<typename... F>
struct NameType {
  typedef const std::string& name;
};

class Metric {
 public:
  typedef std::pair<std::chrono::system_clock::time_point,
                    double> TimestampedValue;
  enum Type {
    COUNTER,
    GAUGE,
    HISTOGRAM,
    SUMMARY,
  };
  
  Type Type() const { return type_; }
  const std::string& Name() const { return name_; }
  const std::vector<std::string>& LabelNames() const { return label_names_; }

  const std::string& LabelName(size_t i) const {
    return label_names_[i]; // Not Check i
  }
  const std::string& Help() const { return help_; }
  bool operator<(const Metric& rhs) const { return name_ < rhs.name_; }
  
  virtual std::map<std::vector<std::string>, TimestampedValue> CurrentValues() const = 0;

 protected:
  Metric(enum Type type, 
         const std::string& name,
         const std::vector<std::string>& label_name,
         const std::string& help) 
    : type_(type),
      name_(name),
      label_names_(label_name),
      help_(help) {
    Registry::Instance()->AddMetric(this);
  }
  
  virtual ~Metric() {}

 private:
  const enum Type type_;
  const std::string name_;
  const std::vector<std::string> label_names_;
  const std::string help_;

  DISALLOW_COPY_AND_ASSIGN(Metric);
};

} // namespace monitor
#endif // MONITOR_METRIC_H_
