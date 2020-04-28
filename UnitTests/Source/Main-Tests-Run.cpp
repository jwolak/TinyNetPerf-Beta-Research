#include "Command-Line-Options-Parser-Tests.cpp"
#include "Command-Line-Options-Help-Tests.cpp"
#include "Endpoint-Layer-Init-Tests.cpp"
#include "Socket-Communication-Domain-Validator-Tests.cpp"
#include "Endpoint-Layer-Init-Tests-With-Mock.cpp"
#include "Socket-Type-Validator-Tests.cpp"
#include "Close-Socket-Action-Validator-Tests.cpp"
#include "Socket-File-Descriptor-Handler-Tests.cpp"
#include "Close-Socket-Result-Analyzer-Tests.cpp"
#include "Create-Socket-Result-Analyzer-Tests.cpp"
#include "Address-Validator-Tests.cpp"
#include "Address-Family-Validator-Tests.cpp"
#include "Port-Number-Validator-Tests.cpp"
#include "Socket-Bind-Handling-Tests.cpp"
#include "Socket-ReceiveFrom-Handling-Tests.cpp"
#include "Create-Socket-Handling-Tests.cpp"
#include "Socket-Bind-Processing-Tests.cpp"
#include "Socket-Bind-Result-Analyzer-Tests.cpp"
#include "Address-Socket-Wrapper-Tests.cpp"
#include "Address-Socket-Wrapper-Handler-Tests.cpp"
#include "Address-Socket-Wrapper-Handler-Tests-With-Mocks.cpp"
#include "Socket-Bind-Handling-Tests-With-Mocks.cpp"
#include "Socket-Bind-Processing-Tests-With-Mocks.cpp"
#include "ReceiveFrom-Wrapper-Tests.cpp"
#include "Socket-SendTo-Handling-Tests.cpp"
#include "SendTo-Wrapper-Tests.cpp"
#include "Udp-Client-Server-Tests.cpp"

#include <gtest/gtest.h>
#include "gmock/gmock.h"


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
