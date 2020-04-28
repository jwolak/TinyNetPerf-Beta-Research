/*
 * SocketFileDescriptorHandlerMock.h
 *
 *      Author: Janusz Wolak
 */

#ifndef UNITTESTS_MOCKS_SOCKET_FILE_DESCRIPTOR_HANDLER_MOCK_H_
#define UNITTESTS_MOCKS_SOCKET_FILE_DESCRIPTOR_HANDLER_MOCK_H_


#include "../../TinyNetPerf/Headers/Interfaces/ISocket-File-Descriptor-Handler.h"

#include "gmock/gmock.h"

namespace Mocks {

class SocketFileDescriptorHandlerMock : public tinynetperf::serverudp::ISocketFileDescriptorHandler {
 public:
  MOCK_METHOD(bool, SetSocketFileDescriptor, (int32_t), (override));
  MOCK_METHOD(int32_t, GetSeocketFileDescriptot, (), (override));
};

} /* namespace Mocks */


#endif /* UNITTESTS_MOCKS_SOCKET_FILE_DESCRIPTOR_HANDLER_MOCK_H_ */
