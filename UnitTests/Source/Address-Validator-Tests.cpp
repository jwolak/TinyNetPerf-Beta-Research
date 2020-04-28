/*
 * Address-Validator-Tests.cpp
 *
 *      Author: Janusz Wolak
 */

#include "../../TinyNetPerf/Source/Address-Validator.cpp"

#include <gtest/gtest.h>

#include <memory>
#include <string>

namespace {
const std::string kValidAddress = "127.0.0.1";
const std::string kInvalidAddress = "256.168.0.0";
const std::string kMalformedAddress = "@@@127.@.0.1";

/* const std::string kInvalidAddress = "192.168.0.0";
 * TODO When network address is provided - address is VALLID...need to be handled in other way*/
}

class AddressValidatorTests: public ::testing::Test {
public:
	AddressValidatorTests() :
			address_validator {
					new tinynetperf::addressHandling::AddressValidator } {
	}

	std::unique_ptr<tinynetperf::addressHandling::IAddressValidator> address_validator;
};

TEST_F(AddressValidatorTests, ValidAddressInserted_TrueShouldBeReturned) {
	ASSERT_TRUE(address_validator->ValidateAddress(kValidAddress.c_str()));
}

TEST_F(AddressValidatorTests, InvalidAddressInserted_FalseShouldBeReturned) {
	ASSERT_FALSE(address_validator->ValidateAddress(kInvalidAddress.c_str()));
}

TEST_F(AddressValidatorTests, MalformedAddressInserted_FalseShouldBeReturned) {
	ASSERT_FALSE(address_validator->ValidateAddress(kMalformedAddress.c_str()));
}
