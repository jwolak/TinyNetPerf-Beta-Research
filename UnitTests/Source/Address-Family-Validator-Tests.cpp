/*
 * Address-Family-Validator-Tests.cpp
 *
 *      Author: Janusz Wolak
 */

#include "../../TinyNetPerf/Source/Address-Family-Validator.cpp"

#include <gtest/gtest.h>

#include <memory>
#include <string>

namespace {
const sa_family_t kInternetProtocolIpv4 = AF_INET;
const sa_family_t kUnknownFamily = AF_UNSPEC;
}

class AddressFamilyValidatorTests: public ::testing::Test {
public:
	AddressFamilyValidatorTests() :
			address_family_validator {
					new tinynetperf::addressHandling::AddressFamilyValidator } {
	}

	std::unique_ptr<tinynetperf::addressHandling::IAddressFamilyValidator> address_family_validator;
};

TEST_F(AddressFamilyValidatorTests, SetInternetProtocolIp4_TrueIsReturned) {
	ASSERT_TRUE(
			address_family_validator->ValidateFamilyAddress(
					kInternetProtocolIpv4));
}

TEST_F(AddressFamilyValidatorTests, SetUnknownFamily_FalseIsReturned) {
	ASSERT_FALSE(
			address_family_validator->ValidateFamilyAddress(kUnknownFamily));
}
