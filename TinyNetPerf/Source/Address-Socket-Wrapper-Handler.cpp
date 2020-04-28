/*
 * Address-Socket-Wrapper-Handler.cpp
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

#include "../Headers/Address-Socket-Wrapper-Handler.h"

#include <arpa/inet.h>
#include <iostream>

bool tinynetperf::addressHandling::AddressSocketWrapperHandler::SetSocketAddressInStruct(sa_family_t addr_family, in_port_t port_no, std::string &inter_address)
{
    /* TODO Change all std::cout to log file */
    if (!address_family_validator_->ValidateFamilyAddress(addr_family))
    {
        std::cout << "ERROR: Invalid socket address family" << std::endl;
        return false;
    }

    if (!port_number_validator_->ValidatePortNumber(port_no))
    {
        std::cout << "ERROR: Invalid port number" << std::endl;
        return false;
    }

    if (!address_validator_->ValidateAddress(inter_address.c_str()))
    {
        std::cout << "ERROR: Invalid internet address" << std::endl;
        return false;
    }

    if (!address_socket_wrapper_->SetAddressFamily(addr_family))
    {
        std::cout << "ERROR: Set address family failed" << std::endl;
        return false;
    }

    if (!address_socket_wrapper_->SetPortNumber(port_no))
    {
        std::cout << "ERROR: Set port number failed" << std::endl;
        return false;
    }

    /* TODO inet_pton-  To be wrapped */
    struct sockaddr_in serv_addr;
    inet_pton(addr_family, inter_address.c_str(), &serv_addr.sin_addr);
    /* ****** */

    if (!address_socket_wrapper_->SetInternetAddress(serv_addr.sin_addr.s_addr))
    {
        std::cout << "ERROR: Set internet address failed" << std::endl;
        return false;
    }

    std::cout << "SUCCESS: AddressIn struct set" << std::endl;
    return true;
}

struct sockaddr_in tinynetperf::addressHandling::AddressSocketWrapperHandler::GetSocketAddressInStruct()
{
    return address_socket_wrapper_->GetSocketStructAddressIn();
}
