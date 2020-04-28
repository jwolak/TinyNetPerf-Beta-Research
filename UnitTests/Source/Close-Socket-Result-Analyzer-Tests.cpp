/*
 * Close-Socket-Result-Analyzer-Tests.cpp
 *
 *      Author: Janusz Wolak
 */

#include "../../TinyNetPerf/Source/Close-Socket-Result-Analyzer.cpp"

#include <gtest/gtest.h>

#include <memory>
#include <string>

namespace SockResultAnalyzerTest {
const int32_t kCloseSocketPositiveResult = 0;
const int32_t kCloseSocketNegativeResult = -1;
}

class CloseSocketResultAnalyzerTests : public ::testing::Test {
 public:
  CloseSocketResultAnalyzerTests()
      : close_socket_result_analyzer {
          new tinynetperf::serverudp::CloseSocketResultAnalyzer } {
  }

  std::unique_ptr<tinynetperf::serverudp::ICloseSocketResultAnalyzer> close_socket_result_analyzer;
};

TEST_F(CloseSocketResultAnalyzerTests, WhenTheCloseSocketResultPositive_TrueShouldBeReturned) {
  ASSERT_TRUE(close_socket_result_analyzer->AnalyzeCloseSocketResult(SockResultAnalyzerTest::kCloseSocketPositiveResult));
}

TEST_F(CloseSocketResultAnalyzerTests, WhenTheCloseSocketResultNegative_FalseShouldBeReturned) {
  ASSERT_FALSE(close_socket_result_analyzer->AnalyzeCloseSocketResult(SockResultAnalyzerTest::kCloseSocketNegativeResult));
}
