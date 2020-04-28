/*
 * Socket-Bind-Processing-Tests.cpp
 *
 *      Author: Janusz Wolak
 */

#include "../../TinyNetPerf/Source/Socket-Bind-Processing.cpp"
#include "../../TinyNetPerf/Headers/Socket-Bind-Result-Analyzer.h"
#include "../../TinyNetPerf/Headers/Address-Socket-Wrapper-Handler.h"

#include <gtest/gtest.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <memory>
#include <string>

namespace sockBindTests
{
const sa_family_t kValidAddressFamily = AF_INET;
const in_port_t kValidPortNumber = 1027;

const int32_t kTestSocketType = SOCK_DGRAM;
const int32_t kTestSocketProtocol = 0;
const uint32_t kTestSocketNetworkAddress = INADDR_ANY;
const uint32_t kLoopbackAddresInBinaryOrder = 2130706433; /* 127.0.0.1 */
std::string kStringIpAddress = "127.0.0.1";
std::string kStringAnyAddress = "0.0.0.0";

} // namespace sockBindTests

class SocketBindProcessingTests : public ::testing::Test
{
public:
    SocketBindProcessingTests()
        : address_socket_wrapper{new tinynetperf::addressHandling::AddressSocketWrapper},
          address_family_validator{new tinynetperf::addressHandling::AddressFamilyValidator},
          port_number_validator{new tinynetperf::addressHandling::PortNumberValidator},
          address_validator{new tinynetperf::addressHandling::AddressValidator},
          address_socket_wrapper_handler{new tinynetperf::addressHandling::AddressSocketWrapperHandler(
              address_socket_wrapper,
              address_family_validator,
              port_number_validator,
              address_validator)},
          socket_bind_result_analyzer{new tinynetperf::socketDataHandling::SocketBindResultAnalyzer},
          socket_bind_processing{new tinynetperf::socketDataHandling::SocketBindProcessing(socket_bind_result_analyzer, address_socket_wrapper_handler)}
    {
    }

    std::shared_ptr<tinynetperf::addressHandling::IAddressSocketWrapper> address_socket_wrapper;
    std::shared_ptr<tinynetperf::addressHandling::IAddressFamilyValidator> address_family_validator;
    std::shared_ptr<tinynetperf::addressHandling::IPortNumberValidator> port_number_validator;
    std::shared_ptr<tinynetperf::addressHandling::IAddressValidator> address_validator;
    std::shared_ptr<tinynetperf::addressHandling::IAddressSocketWrapperHandler> address_socket_wrapper_handler;

    std::shared_ptr<tinynetperf::socketDataHandling::ISocketBindResultAnalyzer> socket_bind_result_analyzer;
    std::unique_ptr<tinynetperf::socketDataHandling::ISocketBindProcessing> socket_bind_processing;

    std::shared_ptr<struct sockaddr_in> socket_address_in;
    std::shared_ptr<struct sockaddr> socket_address;
};

TEST_F(SocketBindProcessingTests, BindWithIpv4Address_TrueShouldBeReturned)
{
    int32_t socket_fd = socket(sockBindTests::kValidAddressFamily,
                               sockBindTests::kTestSocketType,
                               sockBindTests::kTestSocketProtocol);

    address_socket_wrapper_handler->SetSocketAddressInStruct(
        sockBindTests::kValidAddressFamily,
        sockBindTests::kValidPortNumber,
        sockBindTests::kStringIpAddress);

    ASSERT_TRUE(socket_bind_processing->BindSocket(socket_fd));

    shutdown(socket_fd, SHUT_RDWR);
}

TEST_F(SocketBindProcessingTests, DISABLED_BindWithAnyAddress_TrueShouldBeReturned)
{
    int32_t socket_fd = socket(sockBindTests::kValidAddressFamily,
                               sockBindTests::kTestSocketType,
                               sockBindTests::kTestSocketProtocol);

    address_socket_wrapper_handler->SetSocketAddressInStruct(
        sockBindTests::kValidAddressFamily,
        sockBindTests::kValidPortNumber,
        sockBindTests::kStringAnyAddress);

    ASSERT_TRUE(socket_bind_processing->BindSocket(socket_fd));

    shutdown(socket_fd, SHUT_RDWR);
}
