/*
 * Socket-Bind-Result-Analyzer-Tests.cpp
 *
 *      Author: Janusz Wolak
 */

#include "../../TinyNetPerf/Source/Socket-Bind-Result-Analyzer.cpp"

#include <gtest/gtest.h>

#include <memory>
#include <string>

namespace sockBindResultTests
{
const int32_t kBindSocketPositiveResult = 0;
const int32_t kBindSocketNegativeResult = -1;
} // namespace sockBindResultTests

class SocketBindResultAnalyzerTests : public ::testing::Test
{
public:
    SocketBindResultAnalyzerTests() : socket_bind_result_analyzer{new tinynetperf::socketDataHandling::SocketBindResultAnalyzer}
    {
    }

    std::unique_ptr<tinynetperf::socketDataHandling::ISocketBindResultAnalyzer> socket_bind_result_analyzer;
};

TEST_F(SocketBindResultAnalyzerTests, BindSockePositiveResult_TrueShouldBeReturned)
{
    ASSERT_TRUE(socket_bind_result_analyzer->AnalyzeBindSocketResult(sockBindResultTests::kBindSocketPositiveResult));
}

TEST_F(SocketBindResultAnalyzerTests, BindSockeNegativeResult_FalseShouldBeReturned)
{
    ASSERT_FALSE(socket_bind_result_analyzer->AnalyzeBindSocketResult(sockBindResultTests::kBindSocketNegativeResult));
}
