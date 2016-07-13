#ifndef MONITOR_COUNTER_H_
#define MONITOR_COUNTER_H_

#include <gflags/gflags.h>
#include <memory>
#include <mutex>
#include <string>

#include "base/macros.h"
#include "monitor/labelled_values.h"
#include "monitor/metric.h"

namespace monitor {

// A metric which can only increase (e.g. total_requests_served).
template <typename... LabelTypes>
class Counter : public Metric {
 public:
  static Counter<LabelTypes...>* New(
      const std::string& name,
      const typename NameType<LabelTypes>::name&... label_names,
      const std::string& help);

  void Increment(const LabelTypes&... labels);

  void IncrementBy(const LabelTypes&... labels, double amount);

  double Get(const LabelTypes&... labels) const;

  std::map<std::vector<std::string>, Metric::TimestampedValue> CurrentValues()
      const override;

 private:
  Counter(const std::string& name,
          const typename NameType<LabelTypes>::name&... label_names,
          const std::string& help);

  LabelledValues<LabelTypes...> values_;

  DISALLOW_COPY_AND_ASSIGN(Counter);
};


// static
template <typename... LabelTypes>
Counter<LabelTypes...>* Counter<LabelTypes...>::New(
    const std::string& name,
    const typename NameType<LabelTypes>::name&... label_names,
    const std::string& help) {
  return new Counter(name, label_names..., help);
}


template <typename... LabelTypes>
Counter<LabelTypes...>::Counter(
    const std::string& name,
    const typename NameType<LabelTypes>::name&... label_names,
    const std::string& help)
    : Metric(COUNTER, name, {label_names...}, help),
      values_(name, label_names...) {
}


template <typename... LabelTypes>
void Counter<LabelTypes...>::Increment(const LabelTypes&... labels) {
  values_.Increment(labels...);
}


template <typename... LabelTypes>
void Counter<LabelTypes...>::IncrementBy(const LabelTypes&... labels,
                                         double amount) {
  values_.IncrementBy(labels..., amount);
}


template <typename... LabelTypes>
double Counter<LabelTypes...>::Get(const LabelTypes&... labels) const {
  return values_.Get(labels...);
}


template <typename... LabelTypes>
std::map<std::vector<std::string>, Metric::TimestampedValue>
Counter<LabelTypes...>::CurrentValues() const {
  return values_.CurrentValues();
}


}  // namespace monitor 

#endif  // MONITOR_COUNTER_H_
