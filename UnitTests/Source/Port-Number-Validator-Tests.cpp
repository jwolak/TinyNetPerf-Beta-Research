/*
 * Port-Number-Validator-Tests.cpp
 *
 *      Author: Janusz Wolak
 */

#include "../../TinyNetPerf/Source/Port-Number-Validator.cpp"

#include <gtest/gtest.h>

#include <memory>
#include <string>

namespace {
const in_port_t kValidPortNumber = 1025;
const in_port_t kInvalidLowPortNumber = 1022;
const in_port_t kInvalidHighPortNumber = 65535;
const in_port_t kZeroPortNumber = 0;
}

class PortNumberValidatorTests: public ::testing::Test {
public:
	PortNumberValidatorTests() :
			port_number_validator {
					new tinynetperf::addressHandling::PortNumberValidator } {
	}

	std::unique_ptr<tinynetperf::addressHandling::IPortNumberValidator> port_number_validator;
};

TEST_F(PortNumberValidatorTests, ProvideValidRangePortNumber_TrueShouldBeReturned) {
	ASSERT_TRUE(port_number_validator->ValidatePortNumber(kValidPortNumber));
}

TEST_F(PortNumberValidatorTests, ProvideInvalidLowRangePortNumber_FalseShouldBeReturned) {
	ASSERT_FALSE(port_number_validator->ValidatePortNumber(kInvalidLowPortNumber));
}

TEST_F(PortNumberValidatorTests, ProvideInvalidHighRangePortNumber_FalseShouldBeReturned) {
	ASSERT_FALSE(port_number_validator->ValidatePortNumber(kInvalidHighPortNumber));
}

TEST_F(PortNumberValidatorTests, ProvideZeroPortNumber_FalseShouldBeReturned) {
	ASSERT_FALSE(port_number_validator->ValidatePortNumber(kZeroPortNumber));
}
