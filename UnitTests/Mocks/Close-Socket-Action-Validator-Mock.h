/*
 * Close-Socket-Action-Validator-Mock.h
 *
 *      Author: Janusz Wolak
 */

#ifndef UNITTESTS_MOCKS_CLOSE_SOCKET_ACTION_VALIDATOR_MOCK_H_
#define UNITTESTS_MOCKS_CLOSE_SOCKET_ACTION_VALIDATOR_MOCK_H_


#include "../../TinyNetPerf/Headers/Interfaces/IClose-Socket-Action-Validator.h"

#include "gmock/gmock.h"

namespace Mocks {

class CloseSocketActionValidatorMock : public tinynetperf::serverudp::ICloseSocketActionValidator {
 public:
  MOCK_METHOD(bool, ValidateCloseSocketActionType, (int32_t), (override) );
};

} /* namespace Mocks */


#endif /* UNITTESTS_MOCKS_CLOSE_SOCKET_ACTION_VALIDATOR_MOCK_H_ */
