/*
 * Create-Socket-Handling.cpp
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

#include "../Headers/Create-Socket-Handling.h"

#include <iostream>

bool tinynetperf::socketProcessing::CreateSocketHandling::InitSocket(int32_t domain,
                                                                     int32_t type,
                                                                     int32_t protocol)
{

    int32_t socket_file_descriptor = -1;

    if (endpoint_layer_init_->CreateSocket(socket_file_descriptor, domain, type,
                                           protocol))
    {
        if (socket_file_descriptor_handler_->SetSocketFileDescriptor(
                socket_file_descriptor))
        {
            /* TODO Chnage std::cout to log file */
            std::cout << "SUCCESS: Socket file descriptor created and set"
                      << std::endl;
            return true;
        }
        else
        {
            /* TODO Chnage std::cout to log file */
            std::cout << "ERROR: Set socket file descriptor failed" << std::endl;
        }
    }
    else
    {
        /* TODO Chnage std::cout to log file */
        std::cout << "ERROR: Create socket file descriptor failed" << std::endl;
    }

    return false;
}

bool tinynetperf::socketProcessing::CreateSocketHandling::DisposeOfSocket(int32_t action)
{

    int32_t socket_file_descriptor = -1;

    socket_file_descriptor = socket_file_descriptor_handler_->GetSeocketFileDescriptot();

    if (endpoint_layer_init_->CloseSocket(socket_file_descriptor, action))
    {
        /* TODO Chnage std::cout to log file */
        std::cout << "SUCCESS: Socket closed" << std::endl;
        return true;
    }

    /* TODO Chnage std::cout to log file */
    std::cout << "ERROR: Socket close failed" << std::endl;
    return false;
}

int32_t tinynetperf::socketProcessing::CreateSocketHandling::GetSocketFileDescriptor()
{
    return socket_file_descriptor_handler_->GetSeocketFileDescriptot();
}
