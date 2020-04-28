/*
 * Socket-Type-Validator-Mock.h
 *
 *      Author: Janusz Wolak
 */

#ifndef UNITTESTS_MOCKS_SOCKET_TYPE_VALIDATOR_MOCK_H_
#define UNITTESTS_MOCKS_SOCKET_TYPE_VALIDATOR_MOCK_H_


#include "../../TinyNetPerf/Headers/Interfaces/ISocket-Type-Validator.h"

#include "gmock/gmock.h"

namespace Mocks {

class SocketTypeValidatorMock : public tinynetperf::serverudp::ISocketTypeValidator {
 public:
  MOCK_METHOD(bool, ValidateSocketType, (int32_t), (override) );
};

} /* namespace Mocks */


#endif /* UNITTESTS_MOCKS_SOCKET_TYPE_VALIDATOR_MOCK_H_ */
