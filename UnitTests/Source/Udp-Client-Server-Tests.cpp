/*
 * Udp-Client-Server-Tests.cpp
 *
 *      Author: Janusz Wolak
 */

#include "../../TinyNetPerf/Source/ServerUdp.cpp"
#include "../../TinyNetPerf/Source/ClientUdp.cpp"

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

namespace udpClientServerTests
{
const int32_t kValidDomain = AF_INET;
const int32_t kValidType = SOCK_DGRAM;
const int32_t kValidProtocol = 0;

const sa_family_t kValidFamilyAddress = AF_INET;
std::string kInternetAddressString = "127.0.0.1";

const uint32_t kBufferMaxSize = 1024;
const uint16_t kPortNumberNumber = 1505;
std::string kFiveBytesMessageToBeSent = "12345";

const uint32_t kBufferMaxSize2 = 1024;
} // namespace udpClientServerTests

class UdpClientServerTests : public ::testing::Test
{
public:
    UdpClientServerTests() : client_udp{new tinynetperf::serverudp::ClientUdp},
                             server_udp{new tinynetperf::ServerUdp::ServerUdp}
    {
    }

    std::unique_ptr<tinynetperf::serverudp::IClientUdp> client_udp;
    std::unique_ptr<tinynetperf::ServerUdp::IServerUdp> server_udp;

    void
    SetUp() override
    {
        client_udp->SetupClient(udpClientServerTests::kPortNumberNumber, udpClientServerTests::kInternetAddressString);
        server_udp->SetupServer(udpClientServerTests::kPortNumberNumber, udpClientServerTests::kInternetAddressString);
    }

    void TearDown() override
    {
    }

    void ReceiverTestThread(void *received_bytes);
    void SenderTestThread(void *sent_bytes);
};

void UdpClientServerTests::ReceiverTestThread(void *received_bytes)
{
    char buffer[udpClientServerTests::kBufferMaxSize2];
    server_udp->StartListening((char *)buffer);

    strcpy((char *)received_bytes, buffer);
}

void UdpClientServerTests::SenderTestThread(void *sent_bytes)
{
    char buffer[udpClientServerTests::kBufferMaxSize2];
    strncpy(buffer,
            (const char *)udpClientServerTests::kFiveBytesMessageToBeSent.c_str(),
            strlen(udpClientServerTests::kFiveBytesMessageToBeSent.c_str()));

    client_udp->StartSending((char *)buffer);
    strcpy((char *)sent_bytes, buffer);
}

TEST_F(UdpClientServerTests, CreateClientAndServer_ShouldBeSentAndReceiveTheSameMessage)
{
    char received_bytes[udpClientServerTests::kBufferMaxSize2];
    char sent_bytes[udpClientServerTests::kBufferMaxSize2];

    std::thread t1(&UdpClientServerTests::ReceiverTestThread, this, &received_bytes);
    std::thread t2(&UdpClientServerTests::SenderTestThread, this, &sent_bytes);

    t1.join();
    t2.join();

    ASSERT_STREQ(received_bytes, sent_bytes);
}
