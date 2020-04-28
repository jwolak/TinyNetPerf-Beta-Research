/*
 * Socket-Type-Validator-Tests.cpp
 *
 *      Author: Janusz Wolak
 */

#include "../../TinyNetPerf/Source/Socket-Type-Validator.cpp"

#include <gtest/gtest.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#include <memory>
#include <string>

namespace {
const int32_t kUnknownSocketType = -2;
}

class SocketTypeValidatorTests : public ::testing::Test {
 public:
  SocketTypeValidatorTests()
      : socket_type_validator { new tinynetperf::serverudp::SocketTypeValidator } {
  }

  std::unique_ptr<tinynetperf::serverudp::ISocketTypeValidator> socket_type_validator;
};


TEST_F(SocketTypeValidatorTests, WhenSocketTypeIsSockStream_TrueShouldBeReturned) {
  ASSERT_TRUE(socket_type_validator->ValidateSocketType(SOCK_STREAM));
}

TEST_F(SocketTypeValidatorTests, WhenSocketTypeIsSockDgram_TrueShouldBeReturned) {
  ASSERT_TRUE(socket_type_validator->ValidateSocketType(SOCK_DGRAM));
}

TEST_F(SocketTypeValidatorTests, WhenSocketTypeIsSockSeqpacket_TrueShouldBeReturned) {
  ASSERT_TRUE(socket_type_validator->ValidateSocketType(SOCK_SEQPACKET));
}

TEST_F(SocketTypeValidatorTests, WhenSocketTypeIsSockRaw_TrueShouldBeReturned) {
  ASSERT_TRUE(socket_type_validator->ValidateSocketType(SOCK_RAW));
}

TEST_F(SocketTypeValidatorTests, WhenSocketTypeIsSockRdm_TrueShouldBeReturned) {
  ASSERT_TRUE(socket_type_validator->ValidateSocketType(SOCK_RDM));
}

TEST_F(SocketTypeValidatorTests, WhenSocketTypeIsSockNonblock_TrueShouldBeReturned) {
  ASSERT_TRUE(socket_type_validator->ValidateSocketType(SOCK_NONBLOCK));
}

TEST_F(SocketTypeValidatorTests, WhenSocketTypeIsSockCloexec_TrueShouldBeReturned) {
  ASSERT_TRUE(socket_type_validator->ValidateSocketType(SOCK_CLOEXEC));
}

TEST_F(SocketTypeValidatorTests, WhenSocketTypeIsUnknown_FalseShouldBeReturned) {
  ASSERT_FALSE(socket_type_validator->ValidateSocketType(kUnknownSocketType));
}
