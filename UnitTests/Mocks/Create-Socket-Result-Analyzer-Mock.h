/*
 * Create-Socket-Result-Analyzer-Mock.h
 *
 *      Author: Janusz Wolak
 */

#ifndef UNITTESTS_MOCKS_CREATE_SOCKET_RESULT_ANALYZER_MOCK_H_
#define UNITTESTS_MOCKS_CREATE_SOCKET_RESULT_ANALYZER_MOCK_H_

#include "../../TinyNetPerf/Headers/Interfaces/ICreate-Socket-Result-Analyzer.h"

#include "gmock/gmock.h"

namespace Mocks {

class CreateSocketResultAnalyzerMock : public tinynetperf::serverudp::ICreateSocketResultAnalyzer {
 public:
  MOCK_METHOD(bool, AnalyzeCreateSocketResult, (int32_t), (override) );
};

} /* namespace Mocks */

#endif /* UNITTESTS_MOCKS_CREATE_SOCKET_RESULT_ANALYZER_MOCK_H_ */
