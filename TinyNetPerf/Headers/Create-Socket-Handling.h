/*
 * Create-Socket-Handling.h
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

#ifndef HEADERS_CREATE_SOCKET_HANDLING_H_
#define HEADERS_CREATE_SOCKET_HANDLING_H_

#include "Interfaces/ICreate-Socket-Handling.h"
#include "Endpoint-Layer-Init.h"
#include "Socket-Communication-Domain-Validator.h"
#include "Socket-Type-Validator.h"
#include "Close-Socket-Action-Validator.h"
#include "Socket-File-Descriptor-Handler.h"

namespace tinynetperf
{
namespace socketProcessing
{
class CreateSocketHandling : public ICreateSocketHandling
{
    /* #TODO Change serverudp:: namespace */
public:
    CreateSocketHandling()
        : socket_communication_validator_{new serverudp::SocketCommunicationDomainValidator},
          close_socket_action_validator_{new serverudp::CloseSocketActionValidator},
          socket_type_validator_{new serverudp::SocketTypeValidator},
          close_socket_result_analyzer_{new serverudp::CloseSocketResultAnalyzer},
          create_socket_result_analyzer_{new serverudp::CreateSocketResultAnalyzer},
          endpoint_layer_init_{new serverudp::EndpointLayerInit(socket_communication_validator_,
                                                                close_socket_action_validator_, socket_type_validator_, 
                                                                close_socket_result_analyzer_, create_socket_result_analyzer_)},
          socket_file_descriptor_handler_{new serverudp::SocketFileDescriptorHandler}
    {
    }

    bool InitSocket(int32_t, int32_t, int32_t) override;
    bool DisposeOfSocket(int32_t) override;
    int32_t GetSocketFileDescriptor() override;

private:
    /* #TODO Change serverudp:: namespace */
    std::shared_ptr<serverudp::ISocketCommunicationDomainValidator> socket_communication_validator_;
    std::shared_ptr<serverudp::ICloseSocketActionValidator> close_socket_action_validator_;
    std::shared_ptr<serverudp::ISocketTypeValidator> socket_type_validator_;
    std::shared_ptr<serverudp::ICloseSocketResultAnalyzer> close_socket_result_analyzer_;
    std::shared_ptr<serverudp::ICreateSocketResultAnalyzer> create_socket_result_analyzer_;
    std::shared_ptr<serverudp::IEndpointLayerInit> endpoint_layer_init_;
    std::shared_ptr<serverudp::ISocketFileDescriptorHandler> socket_file_descriptor_handler_;
};

} // namespace socketProcessing
} /* namespace tinynetperf */

#endif /* HEADERS_CREATE_SOCKET_HANDLING_H_ */
