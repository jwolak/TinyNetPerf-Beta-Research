/*
 * Socket-SendTo-Handling-Tests.cpp
 *
 *      Author: Janusz Wolak
 */

#include "../../TinyNetPerf/Source/Socket-SendTo-Handling.cpp"

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

namespace SendToHndlTest
{
const int32_t kValidDomain = AF_INET;
const int32_t kValidType = SOCK_DGRAM;
const int32_t kValidProtocol = 0;

const sa_family_t kValidFamilyAddress = AF_INET;
std::string kInternetAddressString = "127.0.0.1";

const uint32_t kBufferMaxSize = 1024;
const uint16_t kPortNumberNumber = 1505;
std::string kFiveBytesMessageToBeSent = "12345";
} // namespace SendToHndlTest

class SocketSendToHandlingTests : public ::testing::Test
{
public:
    SocketSendToHandlingTests() : send_to_wrapper{
                                      new tinynetperf::socketDataHandling::SendToWrapper},
                                create_socket_handling{new tinynetperf::socketProcessing::CreateSocketHandling},
                                address_socket_wrapper{new tinynetperf::addressHandling::AddressSocketWrapper},
                                address_family_validator{new tinynetperf::addressHandling::AddressFamilyValidator},
                                port_number_validator{new tinynetperf::addressHandling::PortNumberValidator},
                                address_validator{new tinynetperf::addressHandling::AddressValidator},
                                socket_address_wrapper_handler{new tinynetperf::addressHandling::AddressSocketWrapperHandler(
                                      address_socket_wrapper,
                                      address_family_validator,
                                      port_number_validator,
                                      address_validator
                                  )},
                                socket_send_to_handling{new tinynetperf::socketDataHandling::SocketSendToHandling(send_to_wrapper, create_socket_handling, socket_address_wrapper_handler)}
    {
    }

    std::shared_ptr<tinynetperf::socketDataHandling::ISendToWrapper> send_to_wrapper;
    std::shared_ptr<tinynetperf::socketProcessing::ICreateSocketHandling> create_socket_handling;
    std::shared_ptr<tinynetperf::addressHandling::IAddressSocketWrapper> address_socket_wrapper;
    std::shared_ptr<tinynetperf::addressHandling::IAddressFamilyValidator> address_family_validator;
    std::shared_ptr<tinynetperf::addressHandling::IPortNumberValidator> port_number_validator;
    std::shared_ptr<tinynetperf::addressHandling::IAddressValidator> address_validator;
    std::shared_ptr<tinynetperf::addressHandling::IAddressSocketWrapperHandler> socket_address_wrapper_handler;
    std::unique_ptr<tinynetperf::socketDataHandling::ISocketSendToHandling> socket_send_to_handling;

    void SetUp() override {
        create_socket_handling->InitSocket(SendToHndlTest::kValidDomain, SendToHndlTest::kValidType, SendToHndlTest::kValidProtocol);
        socket_address_wrapper_handler->SetSocketAddressInStruct(SendToHndlTest::kValidFamilyAddress,
                                                                 SendToHndlTest::kPortNumberNumber,
                                                                 SendToHndlTest::kInternetAddressString);
    }

    void ReceiverTestThread(socklen_t *received_bytes_number);
    void SenderTestThread(socklen_t *sent_bytes_number);
};

void SocketSendToHandlingTests::ReceiverTestThread(socklen_t *received_bytes_number)
{
    int32_t socket_fd;
    char buffer[SendToHndlTest::kBufferMaxSize];
    struct sockaddr_in server_address, client_address;

    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&server_address, 0, sizeof(server_address));
    memset(&client_address, 0, sizeof(client_address));

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(SendToHndlTest::kPortNumberNumber);

    bind(socket_fd, (const struct sockaddr *)&server_address, sizeof(server_address));

    socklen_t received_bytes_from = 0;

    std::cout << "INFO: Test listener started" << std::endl;

    socklen_t len = sizeof(client_address);

    received_bytes_from = recvfrom(socket_fd, (char *)buffer, SendToHndlTest::kBufferMaxSize,
                                   MSG_WAITALL, (struct sockaddr *)&client_address,
                                   &len);

    *received_bytes_number = received_bytes_from;

    close(socket_fd);
}

void SocketSendToHandlingTests::SenderTestThread(socklen_t *sent_bytes_number)
{
    int socket_fd;
    char buffer[SendToHndlTest::kBufferMaxSize];

    strncpy(buffer,
            (const char *)SendToHndlTest::kFiveBytesMessageToBeSent.c_str(),
            strlen(SendToHndlTest::kFiveBytesMessageToBeSent.c_str()));

    ssize_t sent_num_bytes = 0;
    sent_num_bytes = socket_send_to_handling->SendTo(buffer, strlen(buffer), MSG_CONFIRM);

    *sent_bytes_number = sent_num_bytes;
    std::cout
        << "INFO: Test message sent" << std::endl;

    close(socket_fd);
}

TEST_F(SocketSendToHandlingTests, SendTo_SentFiveBytes_FiveBytesShouldBeReceived)
{
    socklen_t received_bytes_number = 0;
    socklen_t sent_bytes_number = 0;

    std::thread t1(&SocketSendToHandlingTests::ReceiverTestThread, this, &received_bytes_number);
    std::thread t2(&SocketSendToHandlingTests::SenderTestThread, this, &sent_bytes_number);

    t1.join();
    t2.join();

    ASSERT_EQ(received_bytes_number, sent_bytes_number);
}
