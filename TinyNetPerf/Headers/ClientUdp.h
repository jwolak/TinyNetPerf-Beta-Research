/*
 * ClientUdp.h
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

#pragma once
#include "Interfaces/IClientUdp.h"

#include "Address-Socket-Wrapper-Handler.h"
#include "Create-Socket-Handling.h"
#include "Socket-Bind-Handling.h"
#include "Socket-ReceiveFrom-Handling.h"
#include "Socket-SendTo-Handling.h"

namespace tinynetperf
{
namespace serverudp
{

class ClientUdp : public IClientUdp
{
public:
    ClientUdp() : create_socket_handling_{new socketProcessing::CreateSocketHandling},
                  address_socket_wrapper_server_{new addressHandling::AddressSocketWrapper},
                  address_family_validator_{new addressHandling::AddressFamilyValidator},
                  port_number_validator_{new addressHandling::PortNumberValidator},
                  address_validator_{new addressHandling::AddressValidator},
                  address_socket_wrapper_handler_server_{
                      new addressHandling::AddressSocketWrapperHandler(address_socket_wrapper_server_,
                                                                       address_family_validator_,
                                                                       port_number_validator_,
                                                                       address_validator_)},
                  address_socket_wrapper_client_{new addressHandling::AddressSocketWrapper},
                  socket_bind_result_analyzer_{new socketDataHandling::SocketBindResultAnalyzer},
                  socket_bind_processing_{new socketDataHandling::SocketBindProcessing(
                      socket_bind_result_analyzer_,
                      address_socket_wrapper_handler_server_)},
                  socket_bind_handling_{new socketDataHandling::SocketBindHandling(
                      create_socket_handling_,
                      address_socket_wrapper_handler_server_,
                      socket_bind_processing_)},
                  receive_from_wrapper_{new socketDataHandling::ReceiveFromWrapper},
                  socket_receive_from_handling_{new socketDataHandling::SocketReceiveFromHandling(
                      receive_from_wrapper_,
                      create_socket_handling_,
                      address_socket_wrapper_handler_server_)},
                  sendto_wrapper_{new socketDataHandling::SendToWrapper},
                  socket_send_to_handling_{new socketDataHandling::SocketSendToHandling(
                      sendto_wrapper_,
                      create_socket_handling_,
                      address_socket_wrapper_handler_server_)}
    {
    }

    ~ClientUdp() {
        create_socket_handling_->DisposeOfSocket(SHUT_RDWR);
    }

    void StartSending(void *) override;
    void StartSendingInLoop(void *) override;
    bool SetupClient(in_port_t, std::string &) override;

private:
    std::shared_ptr<socketProcessing::ICreateSocketHandling> create_socket_handling_;

    std::shared_ptr<addressHandling::IAddressSocketWrapper> address_socket_wrapper_server_;
    std::shared_ptr<addressHandling::IAddressFamilyValidator> address_family_validator_;
    std::shared_ptr<addressHandling::IPortNumberValidator> port_number_validator_;
    std::shared_ptr<addressHandling::IAddressValidator> address_validator_;
    std::shared_ptr<addressHandling::IAddressSocketWrapperHandler> address_socket_wrapper_handler_server_;
    std::shared_ptr<addressHandling::IAddressSocketWrapper> address_socket_wrapper_client_;
    std::shared_ptr<socketDataHandling::ISocketBindResultAnalyzer> socket_bind_result_analyzer_;
    std::shared_ptr<socketDataHandling::ISocketBindProcessing> socket_bind_processing_;
    std::shared_ptr<socketDataHandling::ISocketBindHandling> socket_bind_handling_;
    std::shared_ptr<socketDataHandling::IReceiveFromWrapper> receive_from_wrapper_;
    std::shared_ptr<socketDataHandling::ISocketReceiveFromHandling> socket_receive_from_handling_;
    std::shared_ptr<socketDataHandling::ISendToWrapper> sendto_wrapper_;
    std::shared_ptr<socketDataHandling::ISocketSendToHandling> socket_send_to_handling_;
};
} // namespace serverudp
} // namespace tinynetperf
