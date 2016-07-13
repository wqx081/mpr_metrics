#include "monitor/gauge.h"

#include <glog/logging.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

namespace monitor {

class MyGauge : public ::testing::Test {
 protected:
  template <class... LabelTypes>
  const std::string& GetName(const Metric& m) {
    return m.Name();
  }

  template <class... LabelTypes>
  const std::vector<std::string>& GetLabelNames(const Metric& m) {
    return m.LabelNames();
  }

  template <class... LabelTypes>
  std::string GetHelp(const Metric& m) {
    return m.Help();
  }
};


TEST_F(MyGauge, TestGaugeName) {
  std::unique_ptr<Gauge<>> gauge(Gauge<>::New("name", "help"));
  EXPECT_EQ("name", GetName(*gauge));
}

} // namespace monitor
