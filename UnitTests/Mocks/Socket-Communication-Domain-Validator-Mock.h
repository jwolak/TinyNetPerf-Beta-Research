/*
 * Socket-Communication-Domain-Validator-Mock.h
 *
 *      Author: Janusz Wolak
 */

#ifndef UNITTESTS_MOCKS_SOCKET_COMMUNICATION_DOMAIN_VALIDATOR_MOCK_H_
#define UNITTESTS_MOCKS_SOCKET_COMMUNICATION_DOMAIN_VALIDATOR_MOCK_H_


#include "../../TinyNetPerf/Headers/Interfaces/ISocket-Communication-Domain-Validator.h"

#include "gmock/gmock.h"

namespace Mocks {

class SocketCommunicationDomainValidatorMock : public tinynetperf::serverudp::ISocketCommunicationDomainValidator {
 public:
  MOCK_METHOD(bool, ValidateCommunicationDomain, (int32_t), (override) );
};

} /* namespace Mocks */


#endif /* UNITTESTS_MOCKS_SOCKET_COMMUNICATION_DOMAIN_VALIDATOR_MOCK_H_ */
