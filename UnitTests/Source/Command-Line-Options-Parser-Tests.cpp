/*
 * Command-Line-Options-Parser-Tests.cpp
 *
 *      Author: Janusz Wolak
 */

#include "../../TinyNetPerf/Source/Command-Line-Options-Parser.cpp"

#include <gtest/gtest.h>

#include <memory>
#include <string>


namespace commandlineoptionsparsertests {

namespace {
const uint32_t kNumberOfArgumentsSetToZero = 0;
const uint32_t kNumberOfArgumentsSetToOne = 1;
const uint32_t kNumberOfArgumentsSetToTwo = 2;
char* kTestProgramName = "TestAppName";
char* kDummyCommandLineArgument[] = {kTestProgramName, "-s"};
char* kEmptyCommandLineArgument[] = {kTestProgramName};
char* kEnableServerModeArgument[] = {kTestProgramName, "-s"};
char* kEnableClientModeArgument[] = {kTestProgramName, "-c"};
char* kEnableHelpModeArgument[] = {kTestProgramName, "h"};
}

class CommandLineOptionsParserTests : public ::testing::Test {
 public:
  CommandLineOptionsParserTests() : command_line_options_parser{new tinynetperf::commandlineoptionsparser::CommandLineOptionsParser} {};

 public:
  std::unique_ptr<tinynetperf::commandlineoptionsparser::ICommandLineOptionsParser> command_line_options_parser;
};

TEST_F(CommandLineOptionsParserTests, WhenNumberOfArgumentsEqualZero_ShouldReturnFalse) {
  ASSERT_FALSE(command_line_options_parser->ParseCommandLineArguments(kNumberOfArgumentsSetToZero, kDummyCommandLineArgument));
}

TEST_F(CommandLineOptionsParserTests, WhenListOfArgumentsIsEmpty_ShouldReturnFalse) {
  ASSERT_FALSE(command_line_options_parser->ParseCommandLineArguments(kNumberOfArgumentsSetToOne, kEmptyCommandLineArgument));
}

TEST_F(CommandLineOptionsParserTests, WhenListOfArgumentsIsNotEmptyAndValid_ShouldReturnTrue) {
  ASSERT_TRUE(command_line_options_parser->ParseCommandLineArguments(kNumberOfArgumentsSetToTwo, kDummyCommandLineArgument));
}

TEST_F(CommandLineOptionsParserTests, DISABLED_WhenArgumentsIsToEnableServer_ShouldReturnTrue) {
  ASSERT_TRUE(command_line_options_parser->ParseCommandLineArguments(kNumberOfArgumentsSetToTwo, kEnableServerModeArgument));
}

TEST_F(CommandLineOptionsParserTests, DISABLED_WhenArgumentsIsToEnableClient_ShouldReturnTrue) {
  ASSERT_TRUE(command_line_options_parser->ParseCommandLineArguments(kNumberOfArgumentsSetToTwo, kEnableClientModeArgument));
}

TEST_F(CommandLineOptionsParserTests, DISABLED_WhenArgumentsIsToEnableHelp_ShouldReturnTrue) {
  ASSERT_TRUE(command_line_options_parser->ParseCommandLineArguments(kNumberOfArgumentsSetToTwo, kEnableHelpModeArgument));
}

} /* commandlineoptionsparsertests */

