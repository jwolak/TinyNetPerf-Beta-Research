/*
 * Socket-Bind-Processing.cpp
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

#include "../Headers/Socket-Bind-Processing.h"

#include <iostream>

bool tinynetperf::socketDataHandling::SocketBindProcessing::BindSocket(uint32_t sock_fd)
{
    // /* TODO Change all std::cout to log file */
    int32_t socket_bind_result = -1;
    struct sockaddr_in socket_address_in = address_socket_wrapper_handler_->GetSocketAddressInStruct();

    if (socket_address_in.sin_addr.s_addr == 4294967295 ||
        socket_address_in.sin_family == AF_UNSPEC ||
        socket_address_in.sin_port == 0)
    {
        std::cout << "Invalid parameter of stuct socket_address_in" << std::endl;
        return false;
    }

    socket_bind_result = bind(sock_fd, (const struct sockaddr *)&socket_address_in, sizeof(socket_address_in));

    return socket_bind_result_analyzer_->AnalyzeBindSocketResult(socket_bind_result);
}
