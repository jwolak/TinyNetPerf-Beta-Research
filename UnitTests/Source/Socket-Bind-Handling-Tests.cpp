/*
 * Socket-Bind-Handling-Tests.cpp
 *
 *      Author: Janusz Wolak
 */

#include "../../TinyNetPerf/Source/Socket-Bind-Handling.cpp"

#include <gtest/gtest.h>

#include <memory>
#include <string>

namespace bindTests
{
/* Init Socket */
const int32_t kValidDomain = AF_INET;
const int32_t kValidType = SOCK_DGRAM;
const int32_t kValidProtocol = 0;
const int32_t kInvalidParameter = -1;
const int32_t kValidCloseAction = 1;

/* Socket Address In */
const sa_family_t kAddressFamilyTest = AF_INET;
const sa_family_t kAddressFamilyUnspecified = AF_UNSPEC;

std::string kValidAddress = "127.0.0.1";
std::string kInvalidAddress = "256.168.0.0";
std::string kMalformedAddress = "@@@127.@.0.1";

const in_port_t kValidPortNumber = 1025;
const in_port_t kInvalidLowPortNumber = 1022;
const in_port_t kInvalidHighPortNumber = 65535;
const in_port_t kZeroPortNumber = 0;

const uint32_t kUnsignedIntIpAddress = 1510058176;
} // namespace bindTests

class SocketBindHandlingTests : public ::testing::Test
{
public:
    SocketBindHandlingTests()
        : create_socket_handling{new tinynetperf::socketProcessing::CreateSocketHandling},
          address_socket_wrapper{new tinynetperf::addressHandling::AddressSocketWrapper},
          address_family_validator{new tinynetperf::addressHandling::AddressFamilyValidator},
          port_number_validator{new tinynetperf::addressHandling::PortNumberValidator},
          address_validator{new tinynetperf::addressHandling::AddressValidator},
          address_socket_wrapper_handler{new tinynetperf::addressHandling::AddressSocketWrapperHandler(
              address_socket_wrapper,
              address_family_validator,
              port_number_validator,
              address_validator)},
          socket_bind_result_analyzer{new tinynetperf::socketDataHandling::SocketBindResultAnalyzer},
          socket_bind_processing{new tinynetperf::socketDataHandling::SocketBindProcessing(socket_bind_result_analyzer, address_socket_wrapper_handler)},
          socket_bind_handling{
              new tinynetperf::socketDataHandling::SocketBindHandling{create_socket_handling,
                                                                      address_socket_wrapper_handler,
                                                                      socket_bind_processing}}

    {
    }

    std::shared_ptr<tinynetperf::socketProcessing::ICreateSocketHandling> create_socket_handling;
    std::shared_ptr<tinynetperf::addressHandling::IAddressSocketWrapper> address_socket_wrapper;
    std::shared_ptr<tinynetperf::addressHandling::IAddressFamilyValidator> address_family_validator;
    std::shared_ptr<tinynetperf::addressHandling::IPortNumberValidator> port_number_validator;
    std::shared_ptr<tinynetperf::addressHandling::IAddressValidator> address_validator;
    std::shared_ptr<tinynetperf::addressHandling::IAddressSocketWrapperHandler> address_socket_wrapper_handler;
    std::shared_ptr<tinynetperf::socketDataHandling::ISocketBindResultAnalyzer> socket_bind_result_analyzer;
    std::shared_ptr<tinynetperf::socketDataHandling::ISocketBindProcessing> socket_bind_processing;

    std::unique_ptr<tinynetperf::socketDataHandling::ISocketBindHandling> socket_bind_handling;
};

TEST_F(SocketBindHandlingTests, BindSocketWithAddress_AllValidParameters_TrueShouldBeReturned)
{
    create_socket_handling->InitSocket(bindTests::kValidDomain, bindTests::kValidType, bindTests::kValidProtocol);
    address_socket_wrapper_handler->SetSocketAddressInStruct(bindTests::kAddressFamilyTest, bindTests::kValidPortNumber, bindTests::kValidAddress);
    ASSERT_TRUE(socket_bind_handling->BindSocketWithAddress());
}

TEST_F(SocketBindHandlingTests, BindSocketWithAddress_AllInvalidParameters_FalseShouldBeReturned)
{
    create_socket_handling->InitSocket(bindTests::kInvalidParameter, bindTests::kInvalidParameter, bindTests::kInvalidParameter);
    address_socket_wrapper_handler->SetSocketAddressInStruct(bindTests::kAddressFamilyUnspecified, bindTests::kZeroPortNumber, bindTests::kInvalidAddress);
    ASSERT_FALSE(socket_bind_handling->BindSocketWithAddress());
}

TEST_F(SocketBindHandlingTests, BindSocketWithAddress_InvalidSocketDomain_FalseShouldBeReturned)
{
    create_socket_handling->InitSocket(bindTests::kInvalidParameter, bindTests::kValidType, bindTests::kValidProtocol);
    address_socket_wrapper_handler->SetSocketAddressInStruct(bindTests::kAddressFamilyTest, bindTests::kValidPortNumber, bindTests::kValidAddress);
    ASSERT_FALSE(socket_bind_handling->BindSocketWithAddress());
}

TEST_F(SocketBindHandlingTests, BindSocketWithAddress_InvalidSocketType_FalseShouldBeReturned)
{
    create_socket_handling->InitSocket(bindTests::kValidDomain, bindTests::kInvalidParameter, bindTests::kValidProtocol);
    address_socket_wrapper_handler->SetSocketAddressInStruct(bindTests::kAddressFamilyTest, bindTests::kValidPortNumber, bindTests::kValidAddress);
    ASSERT_FALSE(socket_bind_handling->BindSocketWithAddress());
}

TEST_F(SocketBindHandlingTests, BindSocketWithAddress_InvalidSocketProtocol_FalseShouldBeReturned)
{
    create_socket_handling->InitSocket(bindTests::kValidDomain, bindTests::kValidType, bindTests::kInvalidParameter);
    address_socket_wrapper_handler->SetSocketAddressInStruct(bindTests::kAddressFamilyTest, bindTests::kValidPortNumber, bindTests::kValidAddress);
    ASSERT_FALSE(socket_bind_handling->BindSocketWithAddress());
}

TEST_F(SocketBindHandlingTests, BindSocketWithAddress_InvalidAddressFamily_FalseShouldBeReturned)
{
    create_socket_handling->InitSocket(bindTests::kValidDomain, bindTests::kValidType, bindTests::kValidProtocol);
    address_socket_wrapper_handler->SetSocketAddressInStruct(bindTests::kAddressFamilyUnspecified, bindTests::kValidPortNumber, bindTests::kValidAddress);
    ASSERT_FALSE(socket_bind_handling->BindSocketWithAddress());
}

TEST_F(SocketBindHandlingTests, BindSocketWithAddress_InvalidAddress_FalseShouldBeReturned)
{
    create_socket_handling->InitSocket(bindTests::kValidDomain, bindTests::kValidType, bindTests::kValidProtocol);
    address_socket_wrapper_handler->SetSocketAddressInStruct(bindTests::kAddressFamilyTest, bindTests::kValidPortNumber, bindTests::kInvalidAddress);
    ASSERT_FALSE(socket_bind_handling->BindSocketWithAddress());
}

TEST_F(SocketBindHandlingTests, BindSocketWithAddress_MalformedAddress_FalseShouldBeReturned)
{
    create_socket_handling->InitSocket(bindTests::kValidDomain, bindTests::kValidType, bindTests::kValidProtocol);
    address_socket_wrapper_handler->SetSocketAddressInStruct(bindTests::kAddressFamilyTest, bindTests::kValidPortNumber, bindTests::kMalformedAddress);
    ASSERT_FALSE(socket_bind_handling->BindSocketWithAddress());
}

TEST_F(SocketBindHandlingTests, BindSocketWithAddress_InvalidlowPortNumber_FalseShuouldBeReturned)
{
    create_socket_handling->InitSocket(bindTests::kValidDomain, bindTests::kValidType, bindTests::kValidProtocol);
    address_socket_wrapper_handler->SetSocketAddressInStruct(bindTests::kAddressFamilyTest, bindTests::kInvalidLowPortNumber, bindTests::kValidAddress);
    ASSERT_FALSE(socket_bind_handling->BindSocketWithAddress());
}

TEST_F(SocketBindHandlingTests, BindSocketWithAddress_InvalidHighPortNumber_FalseShuouldBeReturned)
{
    create_socket_handling->InitSocket(bindTests::kValidDomain, bindTests::kValidType, bindTests::kValidProtocol);
    address_socket_wrapper_handler->SetSocketAddressInStruct(bindTests::kAddressFamilyTest, bindTests::kInvalidHighPortNumber, bindTests::kValidAddress);
    ASSERT_FALSE(socket_bind_handling->BindSocketWithAddress());
}

TEST_F(SocketBindHandlingTests, BindSocketWithAddress_InvalidZeroPortNumber_FalseShuouldBeReturned)
{
    create_socket_handling->InitSocket(bindTests::kValidDomain, bindTests::kValidType, bindTests::kValidProtocol);
    address_socket_wrapper_handler->SetSocketAddressInStruct(bindTests::kAddressFamilyTest, bindTests::kZeroPortNumber, bindTests::kValidAddress);
    ASSERT_FALSE(socket_bind_handling->BindSocketWithAddress());
}
