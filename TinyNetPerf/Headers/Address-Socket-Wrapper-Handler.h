/*
 * Address-Socket-Wrapper-Handler.h
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

#ifndef HEADERS_ADDRESS_SOCKET_WRAPPER_HANDLER_H_
#define HEADERS_ADDRESS_SOCKET_WRAPPER_HANDLER_H_

#include "Interfaces/IAddress-Socket-Wrapper-Handler.h"
#include "Address-Socket-Wrapper.h"
#include "Address-Family-Validator.h"
#include "Port-Number-Validator.h"
#include "Address-Validator.h"

#include <memory>

namespace tinynetperf
{
namespace addressHandling
{
class AddressSocketWrapperHandler : public IAddressSocketWrapperHandler
{
public:
    AddressSocketWrapperHandler(
        std::shared_ptr<IAddressSocketWrapper> address_socket_wrapper,
        std::shared_ptr<IAddressFamilyValidator> address_family_validator,
        std::shared_ptr<IPortNumberValidator> port_number_validator,
        std::shared_ptr<IAddressValidator> address_validator)
        : address_socket_wrapper_{address_socket_wrapper},
          address_family_validator_{address_family_validator},
          port_number_validator_{port_number_validator},
          address_validator_{address_validator}
    {
    }

    bool SetSocketAddressInStruct(sa_family_t, in_port_t, std::string &) override;
    struct sockaddr_in GetSocketAddressInStruct() override;

private:
    std::shared_ptr<IAddressSocketWrapper> address_socket_wrapper_;
    std::shared_ptr<IAddressFamilyValidator> address_family_validator_;
    std::shared_ptr<IPortNumberValidator> port_number_validator_;
    std::shared_ptr<IAddressValidator> address_validator_;
};

} /* namespace addressHandling */
} /*namespace tinynetperf */

#endif /* HEADERS_ADDRESS_SOCKET_WRAPPER_HANDLER_H_ */
