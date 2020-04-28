/*
 * Endpoint-Layer-Init-Tests.cpp
 *
 *      Author: Janusz Wolak
 */

#include "../../TinyNetPerf/Source/Endpoint-Layer-Init.cpp"

#include <gtest/gtest.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#include <memory>
#include <string>

namespace {
const int32_t kSocketDomainInternetProtocolIpV4 = AF_INET;
const int32_t kSocketTypeDatagram = SOCK_DGRAM;
const int32_t kSocketProtocolType = 0;
const int32_t kInvalidParameter = -1;
int32_t kTestFileDescriptor = -1;
const int32_t kSocketOpenFailed = -1;
}

class EndpointLayerInitTests : public ::testing::Test {
 public:
  EndpointLayerInitTests()
      : socket_communication_domain_validator {
            new tinynetperf::serverudp::SocketCommunicationDomainValidator },
        close_socket_action_validator{new tinynetperf::serverudp::CloseSocketActionValidator},
        socket_type_validator { new tinynetperf::serverudp::SocketTypeValidator },
        close_socket_result_analyzer{new tinynetperf::serverudp::CloseSocketResultAnalyzer},
        create_socket_result_analyzer{new tinynetperf::serverudp::CreateSocketResultAnalyzer},
        endpoint_layer_init { new tinynetperf::serverudp::EndpointLayerInit(
            socket_communication_domain_validator, close_socket_action_validator, socket_type_validator,
            close_socket_result_analyzer, create_socket_result_analyzer) } {}

  std::shared_ptr<tinynetperf::serverudp::ISocketCommunicationDomainValidator> socket_communication_domain_validator;
  std::shared_ptr<tinynetperf::serverudp::ICloseSocketActionValidator> close_socket_action_validator;
  std::shared_ptr<tinynetperf::serverudp::ISocketTypeValidator> socket_type_validator;
  std::shared_ptr<tinynetperf::serverudp::ICloseSocketResultAnalyzer> close_socket_result_analyzer;
  std::shared_ptr<tinynetperf::serverudp::ICreateSocketResultAnalyzer> create_socket_result_analyzer;
  std::unique_ptr<tinynetperf::serverudp::IEndpointLayerInit> endpoint_layer_init;
};

TEST_F(EndpointLayerInitTests, CreateSocketWithProperParameter_AndShouldReturnTrue) {
  ASSERT_TRUE(endpoint_layer_init->CreateSocket(kTestFileDescriptor, kSocketDomainInternetProtocolIpV4, kSocketTypeDatagram, kSocketProtocolType));
}

TEST_F(EndpointLayerInitTests, CreateSocketWithProperParameter_AndFileDescriptorSetToPositiveValue) {
  endpoint_layer_init->CreateSocket(kTestFileDescriptor, kSocketDomainInternetProtocolIpV4, kSocketTypeDatagram, kSocketProtocolType);
  ASSERT_TRUE(kTestFileDescriptor > 0);
}

TEST_F(EndpointLayerInitTests, CreateSocketWithInvalidSocketDomainParameter_AndShouldReturnFalse) {
  ASSERT_FALSE(endpoint_layer_init->CreateSocket(kTestFileDescriptor, kInvalidParameter, kSocketTypeDatagram, kSocketProtocolType));
}

TEST_F(EndpointLayerInitTests, CreateSocketWithInvalidSocketDomainParameter_AndFileDescriptorSetToNegativeValue) {
  endpoint_layer_init->CreateSocket(kTestFileDescriptor, kInvalidParameter, kSocketTypeDatagram, kSocketProtocolType);
  ASSERT_TRUE(kTestFileDescriptor == kSocketOpenFailed);
}

TEST_F(EndpointLayerInitTests, CreateSocketWithInvalidSocketTypeDatagramParameter_AndShouldReturnFalse) {
  ASSERT_FALSE(endpoint_layer_init->CreateSocket(kTestFileDescriptor, kSocketDomainInternetProtocolIpV4, kInvalidParameter, kSocketProtocolType));
}

TEST_F(EndpointLayerInitTests, CreateSocketWithInvalidSocketTypeDatagramParameter_AndFileDescriptorSetToNegativeValue) {
  endpoint_layer_init->CreateSocket(kTestFileDescriptor, kSocketDomainInternetProtocolIpV4, kInvalidParameter, kSocketProtocolType);
  ASSERT_TRUE(kTestFileDescriptor == kSocketOpenFailed);
}

TEST_F(EndpointLayerInitTests, CreateSocketWithInvalidSocketProtocolTypeParameter_AndShouldReturnFalse) {
  ASSERT_FALSE(endpoint_layer_init->CreateSocket(kTestFileDescriptor, kSocketDomainInternetProtocolIpV4, kSocketTypeDatagram, kInvalidParameter));
}

TEST_F(EndpointLayerInitTests, CreateSocketWithInvalidSocketProtocolTypeParameter_AndFileDescriptorSetToNegativeValue) {
  endpoint_layer_init->CreateSocket(kTestFileDescriptor, kSocketDomainInternetProtocolIpV4, kSocketTypeDatagram, kInvalidParameter);
  ASSERT_TRUE(kTestFileDescriptor == kSocketOpenFailed);
}

TEST_F(EndpointLayerInitTests, CreateSocketWithAllInvalideParameters_AndShouldReturnFalse) {
  ASSERT_FALSE(endpoint_layer_init->CreateSocket(kTestFileDescriptor, kInvalidParameter, kInvalidParameter, kInvalidParameter));
}

TEST_F(EndpointLayerInitTests, CreateSocketWithAllInvalideParameters_AndFileDescriptorSetToNegativeValue) {
  endpoint_layer_init->CreateSocket(kTestFileDescriptor, kInvalidParameter, kInvalidParameter, kInvalidParameter);
  ASSERT_TRUE(kTestFileDescriptor == kSocketOpenFailed);
}
