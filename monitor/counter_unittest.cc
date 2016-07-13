#include "monitor/counter.h"

#include <glog/logging.h>
#include <gtest/gtest.h>
#include <memory>


namespace monitor {

class MyCounter : public ::testing::Test {
 protected:
  template<typename... LabelTypes>
  const std::string& GetName(const Metric& m) {
    return m.Name();
  }
  template<typename... LabelTypes>
  const std::vector<std::string>& GetLabelNames(const Metric& m) {
    return m.LabelNames();
  }
  template<typename... LabelTypes>
  const std::string& GetHelp(const Metric& m) {
    return m.Help();
  }
};

TEST_F(MyCounter, CounterName) {
  std::unique_ptr<Counter<>> counter(Counter<>::New("name", "help"));
  EXPECT_EQ("name", GetName(*counter));
}

TEST_F(MyCounter, CounterLabelNamesEmpty) {
  std::unique_ptr<Counter<>> counter(Counter<>::New("name", "help"));
  EXPECT_TRUE(GetLabelNames(*counter).empty());
}

} // namespace monitor
