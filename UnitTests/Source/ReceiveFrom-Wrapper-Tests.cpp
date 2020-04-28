/*
 * ReceiveFrom-Wrapper-Tests.cpp
 *
 *      Author: Janusz Wolak
 */

#include "../../TinyNetPerf/Source/ReceiveFrom-Wrapper.cpp"

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

namespace
{
const uint32_t kBufferMaxSize = 1024;
const uint16_t kPortNumberNumber = 1505;
std::string kFiveBytesMessageToBeSent = "Hello";
const uint32_t kFiveBytesReceived = 5;
const uint32_t kTenBytesReceived = 5;
} // namespace

class ReceiveFromWrapperTests : public ::testing::Test
{
public:
    ReceiveFromWrapperTests() : receive_from_wrapper{
                                    new tinynetperf::socketDataHandling::ReceiveFromWrapper}
    {
    }

    std::unique_ptr<tinynetperf::socketDataHandling::IReceiveFromWrapper> receive_from_wrapper;

    void ReceiverTestThread(socklen_t *received_bytes_number);
    void SenderTestThread();
};

void ReceiveFromWrapperTests::ReceiverTestThread(socklen_t *received_bytes_number)
{
    int32_t socket_fd;
    char buffer[kBufferMaxSize];
    struct sockaddr_in server_address, client_address;

    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&server_address, 0, sizeof(server_address));
    memset(&client_address, 0, sizeof(client_address));

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(kPortNumberNumber);

    bind(socket_fd, (const struct sockaddr *)&server_address, sizeof(server_address));

    socklen_t received_bytes_from = 0;

    std::cout << "INFO: Test listener started" << std::endl;

    received_bytes_from = receive_from_wrapper->RecvFrom(socket_fd, (char *)buffer, kBufferMaxSize,
                                                         MSG_WAITALL, &client_address);

    *received_bytes_number = received_bytes_from;

    close(socket_fd);
}

void ReceiveFromWrapperTests::SenderTestThread()
{
    int socket_fd;
    char buffer[kBufferMaxSize];
    struct sockaddr_in server_address;

    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&server_address, 0, sizeof(server_address));

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(kPortNumberNumber);
    server_address.sin_addr.s_addr = INADDR_ANY;

    sendto(socket_fd, (const char *)kFiveBytesMessageToBeSent.c_str(), strlen(kFiveBytesMessageToBeSent.c_str()),
           MSG_CONFIRM, (const struct sockaddr *)&server_address,
           sizeof(server_address));

    std::cout << "INFO: Test message sent" << std::endl;

    close(socket_fd);
}

TEST_F(ReceiveFromWrapperTests, RecvFrom_FiveBytesSent_FiveBytesShouldBeReceived)
{
    socklen_t received_bytes_number = 0;

    std::thread t1(&ReceiveFromWrapperTests::ReceiverTestThread, this, &received_bytes_number);
    std::thread t2(&ReceiveFromWrapperTests::SenderTestThread, this);

    t1.join();
    t2.join();

    ASSERT_EQ(received_bytes_number, kFiveBytesReceived);
}
