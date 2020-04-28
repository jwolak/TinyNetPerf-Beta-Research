/*
 * Address-Socket-Wrapper.cpp
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

#include "../Headers/Address-Socket-Wrapper.h"

bool tinynetperf::addressHandling::AddressSocketWrapper::SetAddressFamily(sa_family_t address_family)
{
    socket_address_in.sin_family = address_family;
    return true;
}

bool tinynetperf::addressHandling::AddressSocketWrapper::SetPortNumber(in_port_t port_num)
{
    socket_address_in.sin_port = htons(port_num);
    return true;
}

bool tinynetperf::addressHandling::AddressSocketWrapper::SetInternetAddress(uint32_t internet_address)
{
    socket_address_in.sin_addr.s_addr = internet_address;
    return true;
}

sa_family_t tinynetperf::addressHandling::AddressSocketWrapper::GetAddressFamily()
{
    return socket_address_in.sin_family;
}

in_port_t tinynetperf::addressHandling::AddressSocketWrapper::GetPortNumber()
{
    return socket_address_in.sin_port;
}

uint32_t tinynetperf::addressHandling::AddressSocketWrapper::GetInternetAddress()
{
    return socket_address_in.sin_addr.s_addr;
}

struct sockaddr_in tinynetperf::addressHandling::AddressSocketWrapper::GetSocketStructAddressIn()
{
    return socket_address_in;
}
