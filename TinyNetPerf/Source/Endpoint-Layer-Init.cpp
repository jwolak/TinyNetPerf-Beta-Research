/*
 * EndpointLayerInit.cpp
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

#include "../Headers/Endpoint-Layer-Init.h"

#include <sys/types.h>
#include <sys/socket.h>

#include <errno.h>
#include <iostream>

namespace {
constexpr int32_t kWrongNegativeFileDescriptorValue = -1;
}

bool tinynetperf::serverudp::EndpointLayerInit::CreateSocket(
    int32_t& file_descriptor, int32_t communication_domain, int32_t socket_type,
    int32_t protocol_type) {

  if (socket_communication_validator_->ValidateCommunicationDomain(
      communication_domain) == false) {
    /* TODO change std::cout to log file */
    std::cout << "ERROR socket communication domain is invalid" << std::endl;
    file_descriptor = kWrongNegativeFileDescriptorValue;
    return false;
  }

  if (socket_type_validator_->ValidateSocketType(
      socket_type) == false) {
    /* TODO change std::cout to log file */
    std::cout << "ERROR socket type is invalid" << std::endl;
    file_descriptor = kWrongNegativeFileDescriptorValue;
    return false;
  }

  file_descriptor = socket(communication_domain, socket_type, protocol_type);

  return create_socket_result_analyzer_->AnalyzeCreateSocketResult(file_descriptor);
}

bool tinynetperf::serverudp::EndpointLayerInit::CloseSocket(int32_t socket,
                                                            int32_t action) {
  int32_t result = -1;

  /* TODO change std::cout to log file */
  if (!close_socket_action_validator_->ValidateCloseSocketActionType(action)) {
    std::cout<<"ERROR Close socket action type is invalid"<<std::endl;
    return false;
  }

  result = shutdown(socket, action);

  return close_socket_result_analyzer_->AnalyzeCloseSocketResult(result);
}

