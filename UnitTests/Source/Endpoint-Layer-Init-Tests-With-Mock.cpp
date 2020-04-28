/*
 * Endpoint-Layer-Init-Tests-With-Mock.cpp
 *
 *      Author: Janusz Wolak
 */

#include "../Mocks/Socket-Communication-Domain-Validator-Mock.h"
#include "../Mocks/Socket-Type-Validator-Mock.h"
#include "../Mocks/Close-Socket-Action-Validator-Mock.h"
#include "../Mocks/Close-Socket-Result-Analyzer-Mock.h"
#include "../Mocks/Create-Socket-Result-Analyzer-Mock.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#include <memory>
#include <string>

using ::testing::Return;
using ::testing::_;

namespace {
const int32_t kValidFileDescriptor = 100;
const int32_t kInvalidFileDescriptor = -100;
const int32_t kValidAction = 0;
const int32_t kInvalidAction = 3;
}

class EndpointLayerInitTestsWithMock : public ::testing::Test {
 public:
  EndpointLayerInitTestsWithMock()
      : socket_communucation_domain_validator_mock {
            new Mocks::SocketCommunicationDomainValidatorMock },
        close_socke_action_validator_mock {
            new Mocks::CloseSocketActionValidatorMock },
        socket_type_validator_mock { new Mocks::SocketTypeValidatorMock },
        close_socket_result_anylyzer_mock {
            new Mocks::CloseSocketResultAnalyzerMock },
        create_socket_result_anylyzer_mock {
            new Mocks::CreateSocketResultAnalyzerMock },
        endpoint_layer_init { new tinynetperf::serverudp::EndpointLayerInit(
            socket_communucation_domain_validator_mock,
            close_socke_action_validator_mock, socket_type_validator_mock,
            close_socket_result_anylyzer_mock,
            create_socket_result_anylyzer_mock) } {
  }

  std::shared_ptr<Mocks::SocketCommunicationDomainValidatorMock> socket_communucation_domain_validator_mock;
  std::shared_ptr<Mocks::CloseSocketActionValidatorMock> close_socke_action_validator_mock;
  std::shared_ptr<Mocks::SocketTypeValidatorMock> socket_type_validator_mock;
  std::shared_ptr<Mocks::CloseSocketResultAnalyzerMock> close_socket_result_anylyzer_mock;
  std::shared_ptr<Mocks::CreateSocketResultAnalyzerMock> create_socket_result_anylyzer_mock;
  std::unique_ptr<tinynetperf::serverudp::IEndpointLayerInit> endpoint_layer_init;
};

TEST_F(EndpointLayerInitTestsWithMock, CreateSocketWithValidCommunicationDomain_AndShouldReturnTrue) {
  EXPECT_CALL(*socket_communucation_domain_validator_mock, ValidateCommunicationDomain(_)).WillOnce(Return(true));
  EXPECT_CALL(*socket_type_validator_mock, ValidateSocketType(_)).WillOnce(Return(true));
  EXPECT_CALL(*close_socke_action_validator_mock, ValidateCloseSocketActionType(_)).Times(0);
  EXPECT_CALL(*create_socket_result_anylyzer_mock, AnalyzeCreateSocketResult(_)).WillOnce(Return(true));
  ASSERT_TRUE(endpoint_layer_init->CreateSocket(kTestFileDescriptor, kSocketDomainInternetProtocolIpV4, kSocketTypeDatagram, kSocketProtocolType));
}

TEST_F(EndpointLayerInitTestsWithMock, CreateSocketWithInvalidCommunicationDomain_AndShouldReturnFalse) {
  EXPECT_CALL(*socket_communucation_domain_validator_mock, ValidateCommunicationDomain(_)).WillOnce(Return(false));
  EXPECT_CALL(*socket_type_validator_mock, ValidateSocketType(_)).Times(0);
  EXPECT_CALL(*close_socke_action_validator_mock, ValidateCloseSocketActionType(_)).Times(0);
  ASSERT_FALSE(endpoint_layer_init->CreateSocket(kTestFileDescriptor, kSocketDomainInternetProtocolIpV4, kSocketTypeDatagram, kSocketProtocolType));
}

TEST_F(EndpointLayerInitTestsWithMock, CreateSocketWithValidCommunicationDomainAndInvalidTypeDatagram_AndShouldReturnFalse) {
  EXPECT_CALL(*socket_communucation_domain_validator_mock, ValidateCommunicationDomain(_)).WillOnce(Return(true));
  EXPECT_CALL(*socket_type_validator_mock, ValidateSocketType(_)).WillOnce(Return(false));
  EXPECT_CALL(*close_socke_action_validator_mock, ValidateCloseSocketActionType(_)).Times(0);
  ASSERT_FALSE(endpoint_layer_init->CreateSocket(kTestFileDescriptor, kSocketDomainInternetProtocolIpV4, kInvalidParameter, kSocketProtocolType));
}

TEST_F(EndpointLayerInitTestsWithMock, CreateSocketWithInvalidCommunicationDomainAndInvalidTypeDatagram_AndShouldReturnFalse) {
  EXPECT_CALL(*socket_communucation_domain_validator_mock, ValidateCommunicationDomain(_)).WillOnce(Return(false));
  EXPECT_CALL(*socket_type_validator_mock, ValidateSocketType(_)).Times(0);
  EXPECT_CALL(*close_socke_action_validator_mock, ValidateCloseSocketActionType(_)).Times(0);
  ASSERT_FALSE(endpoint_layer_init->CreateSocket(kTestFileDescriptor, kSocketDomainInternetProtocolIpV4, kInvalidParameter, kSocketProtocolType));
}

TEST_F(EndpointLayerInitTestsWithMock, CreateSocketWithInvalidCommunicationDomainAndInvalidSocketProtocolType_AndShouldReturnFalse) {
  EXPECT_CALL(*socket_communucation_domain_validator_mock, ValidateCommunicationDomain(_)).WillOnce(Return(false));
  EXPECT_CALL(*socket_type_validator_mock, ValidateSocketType(_)).Times(0);
  EXPECT_CALL(*close_socke_action_validator_mock, ValidateCloseSocketActionType(_)).Times(0);
  ASSERT_FALSE(endpoint_layer_init->CreateSocket(kTestFileDescriptor, kSocketDomainInternetProtocolIpV4, kSocketTypeDatagram, kInvalidParameter));
}

TEST_F(EndpointLayerInitTestsWithMock, CreateSocketWithValidCommunicationDomainAndInvalidSocketProtocolType_AndShouldReturnFalse) {
  EXPECT_CALL(*socket_communucation_domain_validator_mock, ValidateCommunicationDomain(_)).WillOnce(Return(true));
  EXPECT_CALL(*socket_type_validator_mock, ValidateSocketType(_)).WillOnce(Return(true));
  EXPECT_CALL(*close_socke_action_validator_mock, ValidateCloseSocketActionType(_)).Times(0);
  ASSERT_FALSE(endpoint_layer_init->CreateSocket(kTestFileDescriptor, kSocketDomainInternetProtocolIpV4, kSocketTypeDatagram, kInvalidParameter));
}

TEST_F(EndpointLayerInitTestsWithMock, CreateSocketWithValidCommunicationDomainAndInvalidOtherParameters_AndShouldReturnFalse) {
  EXPECT_CALL(*socket_communucation_domain_validator_mock, ValidateCommunicationDomain(_)).WillOnce(Return(true));
  EXPECT_CALL(*socket_type_validator_mock, ValidateSocketType(_)).WillOnce(Return(false));
  EXPECT_CALL(*close_socke_action_validator_mock, ValidateCloseSocketActionType(_)).Times(0);
  ASSERT_FALSE(endpoint_layer_init->CreateSocket(kTestFileDescriptor, kSocketDomainInternetProtocolIpV4, kInvalidParameter, kInvalidParameter));
}

TEST_F(EndpointLayerInitTestsWithMock, CreateSocketWithInvalidCommunicationDomainAndInvalidOtherParameters_AndShouldReturnFalse) {
  EXPECT_CALL(*socket_communucation_domain_validator_mock, ValidateCommunicationDomain(_)).WillOnce(Return(true));
  EXPECT_CALL(*socket_type_validator_mock, ValidateSocketType(_)).WillOnce(Return(false));
  EXPECT_CALL(*close_socke_action_validator_mock, ValidateCloseSocketActionType(_)).Times(0);
  ASSERT_FALSE(endpoint_layer_init->CreateSocket(kTestFileDescriptor, kInvalidParameter, kInvalidParameter, kInvalidParameter));
}

/* Close Socket tests */

TEST_F(EndpointLayerInitTestsWithMock, CloseSocketWithValidActionAndValidFileDescriptor_AndTrueShouldBeReturned) {
  EXPECT_CALL(*socket_communucation_domain_validator_mock, ValidateCommunicationDomain(_)).Times(0);
  EXPECT_CALL(*socket_type_validator_mock, ValidateSocketType(_)).Times(0);
  EXPECT_CALL(*close_socke_action_validator_mock, ValidateCloseSocketActionType(_)).WillOnce(Return(true));
  EXPECT_CALL(*close_socket_result_anylyzer_mock, AnalyzeCloseSocketResult(_)).WillOnce(Return(true));
  ASSERT_TRUE(endpoint_layer_init->CloseSocket(kValidFileDescriptor, kValidAction));
}

TEST_F(EndpointLayerInitTestsWithMock, CloseSocketWithInalidActionAndValidFileDescriptor_AndFalseShouldBeReturned) {
  EXPECT_CALL(*socket_communucation_domain_validator_mock, ValidateCommunicationDomain(_)).Times(0);
  EXPECT_CALL(*socket_type_validator_mock, ValidateSocketType(_)).Times(0);
  EXPECT_CALL(*close_socket_result_anylyzer_mock, AnalyzeCloseSocketResult(_)).Times(0);
  EXPECT_CALL(*close_socke_action_validator_mock, ValidateCloseSocketActionType(_)).WillOnce(Return(false));
  ASSERT_FALSE(endpoint_layer_init->CloseSocket(kValidFileDescriptor, kInvalidAction));
}

TEST_F(EndpointLayerInitTestsWithMock, CloseSocketWithValidActionAndInvalidFileDescriptor_AndTrueShouldBeReturned) {
  EXPECT_CALL(*socket_communucation_domain_validator_mock, ValidateCommunicationDomain(_)).Times(0);
  EXPECT_CALL(*socket_type_validator_mock, ValidateSocketType(_)).Times(0);
  EXPECT_CALL(*close_socke_action_validator_mock, ValidateCloseSocketActionType(_)).WillOnce(Return(true));
  EXPECT_CALL(*close_socket_result_anylyzer_mock, AnalyzeCloseSocketResult(_)).WillOnce(Return(false));
  ASSERT_FALSE(endpoint_layer_init->CloseSocket(kInvalidFileDescriptor, kValidAction));
}

TEST_F(EndpointLayerInitTestsWithMock, CloseSocketWithInvalidActionAndInvalidFileDescriptor_AndTrueShouldBeReturned) {
  EXPECT_CALL(*socket_communucation_domain_validator_mock, ValidateCommunicationDomain(_)).Times(0);
  EXPECT_CALL(*socket_type_validator_mock, ValidateSocketType(_)).Times(0);
  EXPECT_CALL(*close_socke_action_validator_mock, ValidateCloseSocketActionType(_)).WillOnce(Return(false));
  EXPECT_CALL(*close_socket_result_anylyzer_mock, AnalyzeCloseSocketResult(_)).Times(0);
  ASSERT_FALSE(endpoint_layer_init->CloseSocket(kInvalidFileDescriptor, kInvalidAction));
}
