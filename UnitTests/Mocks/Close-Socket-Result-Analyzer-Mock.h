/*
 * Close-Socket-Result-Analyzer-Mock.h
 *
 *      Author: Janusz Wolak
 */

#ifndef UNITTESTS_MOCKS_CLOSE_SOCKET_RESULT_ANALYZER_MOCK_H_
#define UNITTESTS_MOCKS_CLOSE_SOCKET_RESULT_ANALYZER_MOCK_H_

#include "../../TinyNetPerf/Headers/Interfaces/IClose-Socket-Result-Analyzer.h"

#include "gmock/gmock.h"

namespace Mocks {

class CloseSocketResultAnalyzerMock : public tinynetperf::serverudp::ICloseSocketResultAnalyzer {
 public:
  MOCK_METHOD(bool, AnalyzeCloseSocketResult, (int32_t), (override) );
};

} /* namespace Mocks */

#endif /* UNITTESTS_MOCKS_CLOSE_SOCKET_RESULT_ANALYZER_MOCK_H_ */
