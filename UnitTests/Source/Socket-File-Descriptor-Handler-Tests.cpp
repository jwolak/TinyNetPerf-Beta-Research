/*
 * SocketFileDescriptorHandlerTests.cpp
 *
 *  Created on: Mar 10, 2020
 *      Author: janusz
 */

#include "../../TinyNetPerf/Source/Socket-File-Descriptor-Handler.cpp"

#include <gtest/gtest.h>

#include <memory>
#include <string>

namespace SockFileDescHandlrTest{
const int32_t kValidFileDescriptor = 100;
const int32_t kInvalidFileDescriptor = -100;
const int32_t kFileDescriptorValue = 10;
const int32_t kFileDescriptorValueNotSet = -1;
}

class SocketFileDescriptorHandlerTests : public ::testing::Test {
 public:
  SocketFileDescriptorHandlerTests()
      : socket_file_descriptor_handler {new tinynetperf::serverudp::SocketFileDescriptorHandler} {}

  std::shared_ptr<tinynetperf::serverudp::SocketFileDescriptorHandler> socket_file_descriptor_handler;
};


TEST_F(SocketFileDescriptorHandlerTests, SetValidFileDescriptor_TrueShouldBeReturned) {
  ASSERT_TRUE(socket_file_descriptor_handler->SetSocketFileDescriptor(SockFileDescHandlrTest::kValidFileDescriptor));
}

TEST_F(SocketFileDescriptorHandlerTests, SetValueOfFileDescriptor_SetValueShouldBeSet) {
  socket_file_descriptor_handler->SetSocketFileDescriptor(SockFileDescHandlrTest::kFileDescriptorValue);
  ASSERT_EQ(socket_file_descriptor_handler->socket_fd_, SockFileDescHandlrTest::kFileDescriptorValue);
}

TEST_F(SocketFileDescriptorHandlerTests, SetInvalidFileDescriptor_FalseShouldBeReturned) {
  ASSERT_FALSE(socket_file_descriptor_handler->SetSocketFileDescriptor(SockFileDescHandlrTest::kInvalidFileDescriptor));
}

TEST_F(SocketFileDescriptorHandlerTests, GetValueOfFileDescriptor_ValueOfFileDescriptorShouldBeReturned) {
  socket_file_descriptor_handler->SetSocketFileDescriptor(SockFileDescHandlrTest::kFileDescriptorValue);
  ASSERT_EQ(socket_file_descriptor_handler->GetSeocketFileDescriptot(), SockFileDescHandlrTest::kFileDescriptorValue);
}

TEST_F(SocketFileDescriptorHandlerTests, TryToSetInvalidFileDescriptor_InvalidFileDescriptorValueShouldBeReturbed) {
  socket_file_descriptor_handler->SetSocketFileDescriptor(SockFileDescHandlrTest::kInvalidFileDescriptor);
  ASSERT_EQ(socket_file_descriptor_handler->GetSeocketFileDescriptot(), SockFileDescHandlrTest::kFileDescriptorValueNotSet);
}
