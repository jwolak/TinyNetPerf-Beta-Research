/*
 * Address-Socket-Wrapper-Tests.cpp
 *
 *      Author: Janusz Wolak
 */

#include "../../TinyNetPerf/Source/Address-Socket-Wrapper.cpp"

#include <gtest/gtest.h>

#include <memory>
#include <string>

namespace
{
const sa_family_t kTestFamilyAddress = AF_INET;
const in_port_t kTestPortNumber = 1927;
const uint32_t kTestInternetAddress = 2130706433; //127.0.0.1

const sa_family_t kTestFamilyAddressSet = AF_INET6;
const in_port_t kTestPortNumberSet = 7291;
const uint32_t kTestInternetAddressSet = 3232235521; //192.168.0.1
} // namespace

class AddressSocketWrapperTests : public ::testing::Test
{
public:
    AddressSocketWrapperTests() : address_socker_wrapper{new tinynetperf::addressHandling::AddressSocketWrapper} {}

    std::unique_ptr<tinynetperf::addressHandling::AddressSocketWrapper> address_socker_wrapper;
};

TEST_F(AddressSocketWrapperTests, SetAddressFamily_TrueShouldBeReturned)
{
    ASSERT_TRUE(address_socker_wrapper->SetAddressFamily(kTestFamilyAddress));
}

TEST_F(AddressSocketWrapperTests, SetPortNumber_TrueShouldBeReturned)
{
    ASSERT_TRUE(address_socker_wrapper->SetPortNumber(kTestPortNumber));
}

TEST_F(AddressSocketWrapperTests, SetInternetAddress_TrueShouldBeReturned)
{
    ASSERT_TRUE(address_socker_wrapper->SetInternetAddress(kTestInternetAddress));
}

TEST_F(AddressSocketWrapperTests, GetAddressFamily_AddressFamilyShouldBeReturned)
{
    address_socker_wrapper->socket_address_in.sin_family = kTestFamilyAddressSet;
    ASSERT_EQ(address_socker_wrapper->GetAddressFamily(), kTestFamilyAddressSet);
}

TEST_F(AddressSocketWrapperTests, GetPortNumber_PortNumberShouldBeReturned)
{
    address_socker_wrapper->socket_address_in.sin_port = kTestPortNumberSet;
    ASSERT_EQ(address_socker_wrapper->GetPortNumber(), kTestPortNumberSet);
}

TEST_F(AddressSocketWrapperTests, GetInternetAddress_InternetAddressShouldBeReturned)
{
    address_socker_wrapper->socket_address_in.sin_addr.s_addr = kTestInternetAddressSet;
    ASSERT_EQ(address_socker_wrapper->GetInternetAddress(), kTestInternetAddressSet);
}

TEST_F(AddressSocketWrapperTests, GetSocketStructAddressIn_StructAddressInShouldBeReturned)
{
    address_socker_wrapper->socket_address_in.sin_addr.s_addr = kTestInternetAddressSet;
    address_socker_wrapper->socket_address_in.sin_family = kTestFamilyAddress;
    address_socker_wrapper->socket_address_in.sin_port = kTestPortNumber;

    struct sockaddr_in socket_add_in_test = address_socker_wrapper->GetSocketStructAddressIn();

    ASSERT_EQ(socket_add_in_test.sin_addr.s_addr, kTestInternetAddressSet);
    ASSERT_EQ(socket_add_in_test.sin_family, kTestFamilyAddress);
    ASSERT_EQ(socket_add_in_test.sin_port, kTestPortNumber);
}
