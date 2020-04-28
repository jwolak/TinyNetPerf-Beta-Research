/*
 * Port-Number-Validator-Mock.h
 *
 *      Author: Janusz Wolak
 */

#ifndef PORT_NUMBER_VALIDATOR_MOCK_H_
#define PORT_NUMBER_VALIDATOR_MOCK_H_

#include "../../TinyNetPerf/Headers/Interfaces/IPort-Number-Validator.h"

#include "gmock/gmock.h"

namespace Mocks {

class PortNumberValidatorMock: public tinynetperf::addressHandling::IPortNumberValidator {
public:
	MOCK_METHOD(bool, ValidatePortNumber, (in_port_t), (override) );
};

} /* namespace Mocks */

#endif /* PORT_NUMBER_VALIDATOR_MOCK_H_ */
