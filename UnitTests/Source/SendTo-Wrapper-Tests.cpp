/*
 * SendTo-Wrapper-Tests.cpp
 *
 *      Author: Janusz Wolak
 */

#include "../../TinyNetPerf/Source/SendTo-Wrapper.cpp"

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

namespace SendToTest
{
const uint32_t kBufferMaxSize = 1024;
const uint16_t kPortNumberNumber = 1505;
std::string kFiveBytesMessageToBeSent = "12345";
} // namespace SendToTest

class SendToWrapperTests : public ::testing::Test
{
public:
    SendToWrapperTests() : send_to_wrapper{
                               new tinynetperf::socketDataHandling::SendToWrapper}
    {
    }

    std::unique_ptr<tinynetperf::socketDataHandling::ISendToWrapper> send_to_wrapper;

    void ReceiverTestThread(socklen_t *received_bytes_number);
    void SenderTestThread(socklen_t *sent_bytes_number);
};

void SendToWrapperTests::ReceiverTestThread(socklen_t *received_bytes_number)
{
    int32_t socket_fd;
    char buffer[SendToTest::kBufferMaxSize];
    struct sockaddr_in server_address, client_address;

    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&server_address, 0, sizeof(server_address));
    memset(&client_address, 0, sizeof(client_address));

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(SendToTest::kPortNumberNumber);

    bind(socket_fd, (const struct sockaddr *)&server_address, sizeof(server_address));

    socklen_t received_bytes_from = 0;

    std::cout << "INFO: Test listener started" << std::endl;

    socklen_t len = sizeof(client_address);

    received_bytes_from = recvfrom(socket_fd, (char *)buffer, SendToTest::kBufferMaxSize,
                                   MSG_WAITALL, (struct sockaddr *)&client_address,
                                   &len);

    *received_bytes_number = received_bytes_from;

    close(socket_fd);
}

void SendToWrapperTests::SenderTestThread(socklen_t *sent_bytes_number)
{
    int socket_fd;
    char buffer[SendToTest::kBufferMaxSize];
    struct sockaddr_in server_address;

    strncpy(buffer,
            (const char *)SendToTest::kFiveBytesMessageToBeSent.c_str(),
            strlen(SendToTest::kFiveBytesMessageToBeSent.c_str()));

    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&server_address, 0, sizeof(server_address));

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SendToTest::kPortNumberNumber);
    server_address.sin_addr.s_addr = INADDR_ANY;

    ssize_t sent_num_bytes = 0;

    sent_num_bytes = send_to_wrapper->SendTo(socket_fd,
                                             buffer,
                                             strlen(buffer),
                                             MSG_CONFIRM,
                                             &server_address);

    *sent_bytes_number = sent_num_bytes;

    std::cout
        << "INFO: Test message sent" << std::endl;

    close(socket_fd);
}

TEST_F(SendToWrapperTests, Test1)
{
    socklen_t received_bytes_number = 0;
    socklen_t sent_bytes_number = 0;

    std::thread t1(&SendToWrapperTests::ReceiverTestThread, this, &received_bytes_number);
    std::thread t2(&SendToWrapperTests::SenderTestThread, this, &sent_bytes_number);

    t1.join();
    t2.join();

    ASSERT_EQ(received_bytes_number, sent_bytes_number);
}
