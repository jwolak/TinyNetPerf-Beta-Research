/*
 * Socket-Communication-Domain-Validator-Tests.cpp
 *
 *      Author: Janusz Wolak
 */

#include "../../TinyNetPerf/Source/Socket-Communication-Domain-Validator.cpp"

#include <gtest/gtest.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#include <memory>
#include <string>

namespace {
const int32_t kUnknownSocketDomainType = 14;
}

class SocketCommunicationDomainValidatorTests : public ::testing::Test {
 public:
  SocketCommunicationDomainValidatorTests()
      : socket_communucation_domain_validator {
          new tinynetperf::serverudp::SocketCommunicationDomainValidator } {
  }

  std::unique_ptr<tinynetperf::serverudp::ISocketCommunicationDomainValidator> socket_communucation_domain_validator;
};

TEST_F(SocketCommunicationDomainValidatorTests, WhenInternetProtocolIpV4IsSet_TrueShouldBeReturned) {
  ASSERT_TRUE(socket_communucation_domain_validator->ValidateCommunicationDomain(AF_INET));
}

TEST_F(SocketCommunicationDomainValidatorTests, WhenInternetProtocolIpV6IsSet_TrueShouldBeReturned) {
  ASSERT_TRUE(socket_communucation_domain_validator->ValidateCommunicationDomain(AF_INET6));
}

TEST_F(SocketCommunicationDomainValidatorTests, WhenUnknownDomainTypeSet_FalseShouldBeReturned) {
  ASSERT_FALSE(socket_communucation_domain_validator->ValidateCommunicationDomain(kUnknownSocketDomainType));
}
