/*
 * Command-Line-Options-Help-Tests.cpp
 *
 *      Author: Janusz Wolak
 */

#include "../../TinyNetPerf/Source/Command-Line-Options-Help.cpp"

#include <gtest/gtest.h>

#include <memory>


namespace commandlineoptionshelptests {

class CommandLineOptionsHelpTests : public ::testing::Test {
 public:
  ~CommandLineOptionsHelpTests() = default;
  CommandLineOptionsHelpTests() : command_line_options_help{ new tinynetperf::commandlineoptionsparser::CommandLineOptionsHelp} {}

  std::unique_ptr<tinynetperf::commandlineoptionsparser::ICommandLineOptionsHelp> command_line_options_help;

};

TEST_F(CommandLineOptionsHelpTests, WhenPrintMethodIsCalled_ThereIsNoThrow) {
  ASSERT_NO_THROW(command_line_options_help->PrintAllOptionsHelp());
}

}/* namespace commandlineoptionshelptests */
