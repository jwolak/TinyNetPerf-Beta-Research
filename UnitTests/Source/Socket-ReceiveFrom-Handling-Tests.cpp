/*
 * Socket-ReceiveFrom-Handling-Tests.cpp
 *
 *      Author: Janusz Wolak
 */

#include "../../TinyNetPerf/Source/Socket-ReceiveFrom-Handling.cpp"

#include <gtest/gtest.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <memory>
#include <string>

#include <iostream>
#include <utility>
#include <thread>
#include <chrono>

namespace RecvFromTst
{
const int32_t kValidDomain = AF_INET;
const int32_t kValidType = SOCK_DGRAM;
const int32_t kValidProtocol = 0;

const sa_family_t kValidFamilyAddress = AF_INET;
const uint16_t kPortNumberNumber = 1927;
std::string kInternetAddressString = "127.0.0.1";

const uint32_t kBufferMaxSize = 1024;
std::string kFiveBytesMessageToBeSent = "Hello";
const uint32_t kFiveBytesReceived = 5;

} // namespace RecvFromTst

class SocketReceiveFromHandlingTests : public ::testing::Test
{
public:
    SocketReceiveFromHandlingTests() : receive_from_wrapper{new tinynetperf::socketDataHandling::ReceiveFromWrapper},
                                       create_socket_handling{new tinynetperf::socketProcessing::CreateSocketHandling},
                                       address_socket_wrapper{new tinynetperf::addressHandling::AddressSocketWrapper},
                                       address_family_validator{new tinynetperf::addressHandling::AddressFamilyValidator},
                                       port_number_validator{new tinynetperf::addressHandling::PortNumberValidator},
                                       address_validator{new tinynetperf::addressHandling::AddressValidator},
                                       socket_address_wrapper_handler{new tinynetperf::addressHandling::AddressSocketWrapperHandler(
                                           address_socket_wrapper,
                                           address_family_validator,
                                           port_number_validator,
                                           address_validator)},
                                       socket_receive_from_handling{
                                           new tinynetperf::socketDataHandling::SocketReceiveFromHandling(
                                               receive_from_wrapper,
                                               create_socket_handling,
                                               socket_address_wrapper_handler)}
    {
    }

    std::shared_ptr<tinynetperf::socketDataHandling::IReceiveFromWrapper> receive_from_wrapper;
    std::shared_ptr<tinynetperf::socketProcessing::ICreateSocketHandling> create_socket_handling;
    std::shared_ptr<tinynetperf::addressHandling::IAddressSocketWrapper> address_socket_wrapper;
    std::shared_ptr<tinynetperf::addressHandling::IAddressFamilyValidator> address_family_validator;
    std::shared_ptr<tinynetperf::addressHandling::IPortNumberValidator> port_number_validator;
    std::shared_ptr<tinynetperf::addressHandling::IAddressValidator> address_validator;
    std::shared_ptr<tinynetperf::addressHandling::IAddressSocketWrapperHandler> socket_address_wrapper_handler;

    std::unique_ptr<tinynetperf::socketDataHandling::ISocketReceiveFromHandling> socket_receive_from_handling;

    void ReceiverTestThread(socklen_t *received_bytes_number);
    void SenderTestThread();

    void SetUp() override
    {
        create_socket_handling->InitSocket(RecvFromTst::kValidDomain, RecvFromTst::kValidType, RecvFromTst::kValidProtocol);
        socket_address_wrapper_handler->SetSocketAddressInStruct(RecvFromTst::kValidFamilyAddress,
                                                                 RecvFromTst::kPortNumberNumber,
                                                                 RecvFromTst::kInternetAddressString);
    }
};

void SocketReceiveFromHandlingTests::ReceiverTestThread(socklen_t *received_bytes_number)
{
    int32_t socket_fd;
    char buffer[RecvFromTst::kBufferMaxSize];
    struct sockaddr_in server_address;

    socket_fd = create_socket_handling->GetSocketFileDescriptor();
    server_address = socket_address_wrapper_handler->GetSocketAddressInStruct();
    bind(socket_fd, (const struct sockaddr *)&server_address, sizeof(server_address));

    socklen_t received_bytes_from = 0;

    std::cout << "INFO: Test listener started" << std::endl;

    received_bytes_from = socket_receive_from_handling->ReceiveFrom((char *)buffer, RecvFromTst::kBufferMaxSize,
                                                                    MSG_WAITALL);

    *received_bytes_number = received_bytes_from;

    close(socket_fd);
}

void SocketReceiveFromHandlingTests::SenderTestThread()
{
    int socket_fd;
    char buffer[RecvFromTst::kBufferMaxSize];
    struct sockaddr_in server_address;

    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&server_address, 0, sizeof(server_address));

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(RecvFromTst::kPortNumberNumber);
    server_address.sin_addr.s_addr = INADDR_ANY;

    sendto(socket_fd, (const char *)RecvFromTst::kFiveBytesMessageToBeSent.c_str(), strlen(RecvFromTst::kFiveBytesMessageToBeSent.c_str()),
           MSG_CONFIRM, (const struct sockaddr *)&server_address,
           sizeof(server_address));

    std::cout << "INFO: Test message sent" << std::endl;

    close(socket_fd);
}

TEST_F(SocketReceiveFromHandlingTests, ReceiveFrom_FiveBytesSent_FiveBytesShouldBeReceived)
{
    socklen_t received_bytes_number = 0;

    std::thread t1(&SocketReceiveFromHandlingTests::ReceiverTestThread, this, &received_bytes_number);
    std::thread t2(&SocketReceiveFromHandlingTests::SenderTestThread, this);

    t1.join();
    t2.join();

    ASSERT_EQ(received_bytes_number, RecvFromTst::kFiveBytesReceived);
}
