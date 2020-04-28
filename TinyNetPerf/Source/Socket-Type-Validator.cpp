/*
 * Socket-Type-Validator.cpp
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

#include "../Headers/Socket-Type-Validator.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#include <iostream>

bool tinynetperf::serverudp::SocketTypeValidator::ValidateSocketType(
    int32_t socket_type) {

  /* TODO change std::cout to log file */
  switch (socket_type) {
    case SOCK_STREAM:
      std::cout << "Set based byte streams socket type" << std::endl;
      return true;
    case SOCK_DGRAM:
      std::cout << "Set the datagrams socket type" << std::endl;
      return true;
    case SOCK_SEQPACKET:
      std::cout << "Set the sequenced socket type" << std::endl;
      return true;
    case SOCK_RAW:
      std::cout << "Set the raw network protocol access socket type"
          << std::endl;
      return true;
    case SOCK_RDM:
      std::cout << "Set the reliable datagram layer socket type" << std::endl;
      return true;
    case SOCK_NONBLOCK:
      std::cout << "Set the O_NONBLOCK socket type" << std::endl;
      return true;
    case SOCK_CLOEXEC:
      std::cout << "Set the close-on-exec socket type" << std::endl;
      return true;
    default:
      std::cout << "Unknown socket type" << std::endl;
      return false;
  }
}

