/*
 * Endpoint-Layer-Init-Mock.h
 *
 *      Author: Janusz Wolak
 */

#ifndef UNITTESTS_MOCKS_ENDPOINT_LAYER_INIT_MOCK_H_
#define UNITTESTS_MOCKS_ENDPOINT_LAYER_INIT_MOCK_H_

#include "../../TinyNetPerf/Headers/Interfaces/IEndpoint-Layer-Init.h"

#include "gmock/gmock.h"

namespace Mocks {

class EndpointLayerInitMock : public tinynetperf::serverudp::IEndpointLayerInit {
 public:
  MOCK_METHOD(bool, CreateSocket, (int32_t&, int32_t, int32_t, int32_t), (override) );
  MOCK_METHOD(bool, CloseSocket, (int32_t, int32_t), (override) );
};

} /* namespace Mocks */



#endif /* UNITTESTS_MOCKS_ENDPOINT_LAYER_INIT_MOCK_H_ */


/*
virtual bool CreateSocket(int32_t&, int32_t, int32_t, int32_t) = 0;
virtual bool CloseSocket(int32_t, int32_t) = 0;*/
