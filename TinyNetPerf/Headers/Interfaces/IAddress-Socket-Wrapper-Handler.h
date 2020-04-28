/*
 * IAddress-Socket-Wrapper-Handler.h
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

#ifndef HEADERS_INTERFACES_IADDRESS_SOCKET_WRAPPER_HANDLER_H_
#define HEADERS_INTERFACES_IADDRESS_SOCKET_WRAPPER_HANDLER_H_

#include <netinet/in.h>
#include <sys/socket.h>

#include <string>

namespace tinynetperf
{
namespace addressHandling
{
class IAddressSocketWrapperHandler
{
public:
    virtual ~IAddressSocketWrapperHandler() = default;
    virtual bool SetSocketAddressInStruct(sa_family_t, in_port_t, std::string &) = 0;
    virtual struct sockaddr_in GetSocketAddressInStruct() = 0;
};

} /* namespace addressHandling */
} /*namespace tinynetperf */

#endif /* HEADERS_INTERFACES_IADDRESS_SOCKET_WRAPPER_HANDLER_H_ */