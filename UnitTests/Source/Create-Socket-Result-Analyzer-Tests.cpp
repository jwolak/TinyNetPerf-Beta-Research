/*
 * Create-Socket-Result-Analyzer-Tests.cpp
 *
 *      Author: Janusz Wolak
 */
#include "../../TinyNetPerf/Source/Create-Socket-Result-Analyzer.cpp"

#include <gtest/gtest.h>

#include <memory>
#include <string>

namespace CreateSockResultAnalyzerTest {
const int32_t kCreateSocketPositiveResult = 0;
const int32_t kCreateSocketNegativeResult = -1;
}

class CreateSocketResultAnalyzerTests : public ::testing::Test {
 public:
  CreateSocketResultAnalyzerTests()
      : create_socket_result_analyzer {
          new tinynetperf::serverudp::CreateSocketResultAnalyzer } {
  }

  std::unique_ptr<tinynetperf::serverudp::ICreateSocketResultAnalyzer> create_socket_result_analyzer;
};

TEST_F(CreateSocketResultAnalyzerTests, WhenTheCreateSocketResultPositive_TrueShouldBeReturned) {
  ASSERT_TRUE(create_socket_result_analyzer->AnalyzeCreateSocketResult(CreateSockResultAnalyzerTest::kCreateSocketPositiveResult));
}

TEST_F(CreateSocketResultAnalyzerTests, WhenTheCreateSocketResultNegative_FalseShouldBeReturned) {
  ASSERT_FALSE(create_socket_result_analyzer->AnalyzeCreateSocketResult(CreateSockResultAnalyzerTest::kCreateSocketNegativeResult));
}

