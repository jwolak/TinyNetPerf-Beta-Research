/*
 * Address-Socket-Wrapper-Handler-Tests.cpp
 *
 *      Author: Janusz Wolak
 */

#include "../../TinyNetPerf/Source/Address-Socket-Wrapper-Handler.cpp"

#include <gtest/gtest.h>

#include <memory>
#include <string>

namespace sockWrappHanld
{
const sa_family_t kValidFamilyAddress = AF_INET;
const in_port_t kValidPortNumber = 1927;
const uint32_t kValidInternetAddress = 16777343; //127.0.0.1 - byte order inverted

std::string kInternetAddressString = "127.0.0.1";

std::string kInvalidInternetAddressString = "257.0.0.1";
const in_port_t kInvalidPortNumber = 100;
const sa_family_t kInvalidAddressFamily = AF_UNSPEC;

} // namespace sockWrappHanld

class AddressSocketWrapperHandlerTests : public ::testing::Test
{
public:
    AddressSocketWrapperHandlerTests()
        : address_socket_wrapper{new tinynetperf::addressHandling::AddressSocketWrapper},
          address_family_validator{new tinynetperf::addressHandling::AddressFamilyValidator},
          port_number_validator{new tinynetperf::addressHandling::PortNumberValidator},
          address_validator{new tinynetperf::addressHandling::AddressValidator},
          address_socket_handler_wrapper{
              new tinynetperf::addressHandling::AddressSocketWrapperHandler{
                  address_socket_wrapper,
                  address_family_validator,
                  port_number_validator,
                  address_validator}}
    {
    }

    std::shared_ptr<tinynetperf::addressHandling::IAddressSocketWrapper> address_socket_wrapper;
    std::shared_ptr<tinynetperf::addressHandling::IAddressFamilyValidator> address_family_validator;
    std::shared_ptr<tinynetperf::addressHandling::IPortNumberValidator> port_number_validator;
    std::shared_ptr<tinynetperf::addressHandling::IAddressValidator> address_validator;

    std::unique_ptr<tinynetperf::addressHandling::IAddressSocketWrapperHandler> address_socket_handler_wrapper;
};

TEST_F(AddressSocketWrapperHandlerTests, SetSocketAddressFamily_WithAllValidParameters_TrueShouldBeReturned)
{
    ASSERT_TRUE(address_socket_handler_wrapper->SetSocketAddressInStruct(sockWrappHanld::kValidFamilyAddress,
                                                                         sockWrappHanld::kValidPortNumber,
                                                                         sockWrappHanld::kInternetAddressString));
}

TEST_F(AddressSocketWrapperHandlerTests, SetSocketAddressFamily_WitnInvalidAddressFamily_FalseShouldBeReturned)
{
    ASSERT_FALSE(address_socket_handler_wrapper->SetSocketAddressInStruct(sockWrappHanld::kInvalidAddressFamily,
                                                                          sockWrappHanld::kValidPortNumber,
                                                                          sockWrappHanld::kInternetAddressString));
}

TEST_F(AddressSocketWrapperHandlerTests, SetSocketAddressFamily_WitnInvalidPortNumber_FalseShouldBeReturned)
{
    ASSERT_FALSE(address_socket_handler_wrapper->SetSocketAddressInStruct(sockWrappHanld::kValidFamilyAddress,
                                                                          sockWrappHanld::kInvalidPortNumber,
                                                                          sockWrappHanld::kInternetAddressString));
}

TEST_F(AddressSocketWrapperHandlerTests, SetSocketAddressFamily_WitnInvalidAddress_FalseShouldBeReturned)
{
    ASSERT_FALSE(address_socket_handler_wrapper->SetSocketAddressInStruct(sockWrappHanld::kValidFamilyAddress,
                                                                          sockWrappHanld::kValidPortNumber,
                                                                          sockWrappHanld::kInvalidInternetAddressString));
}

TEST_F(AddressSocketWrapperHandlerTests, SetSocketAddressFamily_WithAllInvalidParameters_FalseShouldBeReturned)
{
    ASSERT_FALSE(address_socket_handler_wrapper->SetSocketAddressInStruct(sockWrappHanld::kInvalidAddressFamily,
                                                                          sockWrappHanld::kInvalidPortNumber,
                                                                          sockWrappHanld::kInvalidInternetAddressString));
}

TEST_F(AddressSocketWrapperHandlerTests, GetSocketAddressInStruct_WithAllValidParameters_AddressInStructShouldBeReturned)
{
    struct sockaddr_in test_struct_sockaddr_in;

    address_socket_handler_wrapper->SetSocketAddressInStruct(sockWrappHanld::kValidFamilyAddress,
                                                             sockWrappHanld::kValidPortNumber,
                                                             sockWrappHanld::kInternetAddressString);

    test_struct_sockaddr_in = address_socket_handler_wrapper->GetSocketAddressInStruct();

    ASSERT_EQ(test_struct_sockaddr_in.sin_family, sockWrappHanld::kValidFamilyAddress);
    ASSERT_EQ(test_struct_sockaddr_in.sin_port, htons(sockWrappHanld::kValidPortNumber));
    ASSERT_EQ(test_struct_sockaddr_in.sin_addr.s_addr, sockWrappHanld::kValidInternetAddress);
}
