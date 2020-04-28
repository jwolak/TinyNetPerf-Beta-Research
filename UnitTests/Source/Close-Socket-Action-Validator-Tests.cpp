/*
 * Close-Socket-Action-Validator-Tests.cpp
 *
 *      Author: Janusz Wolak
 */

#include "../../TinyNetPerf/Source/Close-Socket-Action-Validator.cpp"

#include <gtest/gtest.h>

#include <memory>
#include <string>

namespace {
const int32_t kStopReceivingDataForThisSocketAction = 0;
const int32_t kStopTryingToTransmitDataFromThisSocketAction = 1;
const int32_t kStopBothReceptionAndTransmissionAction = 2;
const int32_t kUnknownAction = 3;
}

class CloseSocketActionValidatorTests : public ::testing::Test {
 public:
  CloseSocketActionValidatorTests()
      : close_socket_action_validator { new tinynetperf::serverudp::CloseSocketActionValidator } {
  }

  std::unique_ptr<tinynetperf::serverudp::ICloseSocketActionValidator> close_socket_action_validator;
};

TEST_F(CloseSocketActionValidatorTests, WhenStopReceivingDataForThisSocketActionIsSet_TrueShouldBeReturned) {
  ASSERT_TRUE(close_socket_action_validator->ValidateCloseSocketActionType(kStopReceivingDataForThisSocketAction));
}

TEST_F(CloseSocketActionValidatorTests, WhenStopTryingToTransmitDataFromThisSocketActionIsSet_TrueShouldBeReturned) {
  ASSERT_TRUE(close_socket_action_validator->ValidateCloseSocketActionType(kStopTryingToTransmitDataFromThisSocketAction));
}

TEST_F(CloseSocketActionValidatorTests, WhenStopBothReceptionAndTransmissionActionIsSet_TrueShouldBeReturned) {
  ASSERT_TRUE(close_socket_action_validator->ValidateCloseSocketActionType(kStopBothReceptionAndTransmissionAction));
}

TEST_F(CloseSocketActionValidatorTests, WhenUnknownActionIsSet_FalseShouldBeReturned) {
  ASSERT_FALSE(close_socket_action_validator->ValidateCloseSocketActionType(kUnknownAction));
}
