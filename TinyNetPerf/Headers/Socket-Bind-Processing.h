/*
 * Socket-Bind-Processing.h
 *
 *      Author: Janusz Wolak
 */

/*-
 * Copyright (c) 2020 Janusz Wolak
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#ifndef HEADERS_SOCKET_BIND_PROCESSING_H_
#define HEADERS_SOCKET_BIND_PROCESSING_H_

#include "Interfaces/ISocket-Bind-Processing.h"
#include "Socket-Bind-Result-Analyzer.h"

namespace tinynetperf
{
namespace socketDataHandling
{
class SocketBindProcessing : public ISocketBindProcessing
{
public:
    SocketBindProcessing(
        std::shared_ptr<ISocketBindResultAnalyzer> socket_bind_result_analyzer,
        std::shared_ptr<addressHandling::IAddressSocketWrapperHandler> address_socket_wrapper_handler)
        : socket_bind_result_analyzer_{socket_bind_result_analyzer},
          address_socket_wrapper_handler_{address_socket_wrapper_handler}
    {
    }

    bool BindSocket(uint32_t) override;

private:
    std::shared_ptr<ISocketBindResultAnalyzer> socket_bind_result_analyzer_;
    std::shared_ptr<addressHandling::IAddressSocketWrapperHandler> address_socket_wrapper_handler_;
};
} /* namespace socketDataHandling */

} /* namespace tinynetperf */

#endif /* HEADERS_SOCKET_BIND_PROCESSING_H_ */
