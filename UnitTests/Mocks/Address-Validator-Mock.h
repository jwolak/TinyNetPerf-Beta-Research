/*
 * Address-Validator-Mock.h
 *
 *      Author: Janusz Wolak
 */

#ifndef ADDRESS_VALIDATOR_MOCK_H_
#define ADDRESS_VALIDATOR_MOCK_H_

#include "../../TinyNetPerf/Headers/Interfaces/IAddress-Validator.h"

#include "gmock/gmock.h"

namespace Mocks {

class AddressValidatorMock: public tinynetperf::addressHandling::IAddressValidator {
public:
	MOCK_METHOD(bool, ValidateAddress, (const char *), (override) );
};

} /* namespace Mocks */

#endif /* ADDRESS_VALIDATOR_MOCK_H_ */
