/*
 * Create-Socket-Handling-Tests.cpp
 *
 *      Author: Janusz Wolak
 */

#include "../../TinyNetPerf/Source/Create-Socket-Handling.cpp"

#include <gtest/gtest.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#include <memory>
#include <string>

namespace socketHandlingTests {
const int32_t kValidDomain = AF_INET;
const int32_t kValidType = SOCK_DGRAM;
const int32_t kValidProtocol = 0;
const int32_t kInvalidParameter = -1;
const int32_t kValidCloseAction = 1;
}

class CreateSocketHandlingTests : public ::testing::Test {
 public:
  CreateSocketHandlingTests()
      : socket_communication_validator_ {
            new tinynetperf::serverudp::SocketCommunicationDomainValidator },
        close_socket_action_validator_ {
            new tinynetperf::serverudp::CloseSocketActionValidator },
        socket_type_validator_ { new tinynetperf::serverudp::SocketTypeValidator },
        close_socket_result_analyzer_ {
            new tinynetperf::serverudp::CloseSocketResultAnalyzer },
        create_socket_result_analyzer_ {
            new tinynetperf::serverudp::CreateSocketResultAnalyzer },
        endpoint_layer_init_ { new tinynetperf::serverudp::EndpointLayerInit {
            socket_communication_validator_, close_socket_action_validator_,
            socket_type_validator_, close_socket_result_analyzer_,
            create_socket_result_analyzer_ } },
        socket_file_descriptor_handler {
            new tinynetperf::serverudp::SocketFileDescriptorHandler },
        create_socket_handling { new tinynetperf::socketProcessing::CreateSocketHandling() } {
  }

  std::shared_ptr<tinynetperf::serverudp::ISocketCommunicationDomainValidator> socket_communication_validator_;
  std::shared_ptr<tinynetperf::serverudp::ICloseSocketActionValidator> close_socket_action_validator_;
  std::shared_ptr<tinynetperf::serverudp::ISocketTypeValidator> socket_type_validator_;
  std::shared_ptr<tinynetperf::serverudp::ICloseSocketResultAnalyzer> close_socket_result_analyzer_;
  std::shared_ptr<tinynetperf::serverudp::ICreateSocketResultAnalyzer> create_socket_result_analyzer_;
  std::shared_ptr<tinynetperf::serverudp::IEndpointLayerInit> endpoint_layer_init_;
  std::shared_ptr<tinynetperf::serverudp::ISocketFileDescriptorHandler> socket_file_descriptor_handler;

  std::shared_ptr<tinynetperf::socketProcessing::ICreateSocketHandling> create_socket_handling;
};

TEST_F(CreateSocketHandlingTests, ServerUdpInitedWithValidDomainIpV4_ValidType_ValidProtocol_AndTrueShouldBeReturned) {
  ASSERT_TRUE(create_socket_handling->InitSocket(socketHandlingTests::kValidDomain, socketHandlingTests::kValidType, socketHandlingTests::kValidProtocol));
}

TEST_F(CreateSocketHandlingTests, ServerUdpInitedWith_InvalidDomain_ValidType_ValidProtocol_AndFalseShouldBeReturned) {
  ASSERT_FALSE(create_socket_handling->InitSocket(socketHandlingTests::kInvalidParameter, socketHandlingTests::kValidType, socketHandlingTests::kValidProtocol));
}

TEST_F(CreateSocketHandlingTests, ServerUdpInitedWith_ValidDomain_InvalidType_ValidProtocol_AndFalseShouldBeReturned) {
  ASSERT_FALSE(create_socket_handling->InitSocket(socketHandlingTests::kValidDomain, socketHandlingTests::kInvalidParameter, socketHandlingTests::kValidProtocol));
}

TEST_F(CreateSocketHandlingTests, ServerUdpInitedWith_ValidDomain_ValidType_InvalidProtocol_AndFalseShouldBeReturned) {
  ASSERT_FALSE(create_socket_handling->InitSocket(socketHandlingTests::kValidDomain, socketHandlingTests::kValidType, socketHandlingTests::kInvalidParameter));
}

TEST_F(CreateSocketHandlingTests, ServerUdpInitedWith_InvalidDomain_InvalidType_ValidProtocol_AndFalseShouldBeReturned) {
  ASSERT_FALSE(create_socket_handling->InitSocket(socketHandlingTests::kInvalidParameter, socketHandlingTests::kInvalidParameter, socketHandlingTests::kValidProtocol));
}

TEST_F(CreateSocketHandlingTests, ServerUdpInitedWith_ValidDomain_InvalidType_InvalidProtocol_AndFalseShouldBeReturned) {
  ASSERT_FALSE(create_socket_handling->InitSocket(socketHandlingTests::kValidDomain, socketHandlingTests::kInvalidParameter, socketHandlingTests::kInvalidParameter));
}

TEST_F(CreateSocketHandlingTests, ServerUdpInitedWith_InvalidDomain_InvalidType_InvalidProtocol_AndFalseShouldBeReturned) {
  ASSERT_FALSE(create_socket_handling->InitSocket(socketHandlingTests::kInvalidParameter, socketHandlingTests::kInvalidParameter, socketHandlingTests::kInvalidParameter));
}

/* Tear Down Tests */
TEST_F(CreateSocketHandlingTests, DISABLED_ServerTearDownWith_ValidCloseAction_TrueReturned) {
  /* not possible to pass without mock */
  ASSERT_TRUE(create_socket_handling->DisposeOfSocket(socketHandlingTests::kValidCloseAction));
}

TEST_F(CreateSocketHandlingTests, ServerTearDownWith_InvalidCloseAction_FalseReturned) {
  ASSERT_FALSE(create_socket_handling->DisposeOfSocket(socketHandlingTests::kInvalidParameter));
}

/* GetSocketFileDescriptor Tests */
TEST_F(CreateSocketHandlingTests, GetSocketFileDescriptor_DefaultInitedFileDescriptorReturned) {
  ASSERT_TRUE(create_socket_handling->GetSocketFileDescriptor() == -1);
}


