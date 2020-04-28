/*
 * ServerUdp.cpp
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

#include "../Headers/ServerUdp.h"

#include <iostream>

namespace
{
const int32_t kSocketDomain = AF_INET;
const int32_t kSocketType = SOCK_DGRAM;
const int32_t kSocketProtocol = 0;
const size_t kFixedBufferSize = 1024;

const sa_family_t kFamilyAddress = AF_INET;
} // namespace

void tinynetperf::ServerUdp::ServerUdp::StartListening(void *buffer)
{
    if (!socket_bind_handling_->BindSocketWithAddress())
    {
        std::cout << "ERROR: [ServerUdp] Bind socket with address failed" << std::endl;
        return;
    }

    std::cout << "INFO [ServerUdp] Server started listening.." << std::endl;

    ssize_t no_bytes_received = socket_receive_from_handling_->ReceiveFrom(buffer, strlen((char*)buffer), MSG_WAITALL);
    std::cout << "INFO: [ServerUdp] " << no_bytes_received << " bytes received" << std::endl;
}


void tinynetperf::ServerUdp::ServerUdp::StartListeningInLoop(void *buffer)
{
    if (!socket_bind_handling_->BindSocketWithAddress())
    {
        std::cout << "ERROR: [ServerUdp] Bind socket with address failed" << std::endl;
        return;
    }

    std::cout << "INFO [ServerUdp] Server started listening in loop.." << std::endl;

	while (true) {
		ssize_t no_bytes_received = socket_receive_from_handling_->ReceiveFrom(
				buffer, 1024, MSG_WAITALL);
		std::cout << "INFO: [ServerUdp] " << no_bytes_received << " bytes received"
							<< std::endl;
	}
}


bool tinynetperf::ServerUdp::ServerUdp::SetupServer(in_port_t port_no, std::string &inter_address)
{
    /* TODO change all std::cout to log file */
    if (!create_socket_handling_->InitSocket(kSocketDomain, kSocketType, kSocketProtocol))
    {
        std::cout << "ERROR: [ServerUdp] Init socket failed" << std::endl;
        return false;
    }

    if (!address_socket_wrapper_handler_server_->SetSocketAddressInStruct(kFamilyAddress, port_no, inter_address))
    {
        std::cout << "ERROR: [ServerUdp] Set socketsddress_in struct failed" << std::endl;
        return false;
    }

    std::cout << "INFO: [ServerUdp] Udp client set up successfully" << std::endl;
    return true;
}
