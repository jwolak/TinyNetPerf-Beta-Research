/*
 * Create-Socket-Result-Analyzer.cpp
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

#include "../Headers/Create-Socket-Result-Analyzer.h"

#include <iostream>

bool tinynetperf::serverudp::CreateSocketResultAnalyzer::AnalyzeCreateSocketResult(
    int32_t create_socket_result) {

  if (create_socket_result < 0) {
    switch (errno) {
      case EACCES:
        std::cout
            << "ERROR: Permission to create a socket of the specified type and/or protocol is denied"
            << std::endl;
        break;
      case EAFNOSUPPORT:
        std::cout
            << "ERROR: The implementation does not support the specified address family"
            << std::endl;
        break;
      case EINVAL:
        std::cout << "ERROR: Unknown protocol, or protocol family not available"
            << std::endl;
        break;
      case EMFILE:
        std::cout
            << "ERROR: The per-process limit on the number of open file descriptors has been reached"
            << std::endl;
        break;
      case ENFILE:
        std::cout
            << "ERROR: The system-wide limit on the total number of open files has been reached"
            << std::endl;
        break;
      case ENOBUFS:
      case ENOMEM:
        std::cout
            << "ERROR: Insufficient memory is available.  The socket cannot be created until sufficient resources are freed"
            << std::endl;
        break;
      case EPROTONOSUPPORT:
        std::cout
            << "ERROR: The protocol type or the specified protocol is not supported within this domain"
            << std::endl;
        break;
      default:
        std::cout << "ERROR: Create socket unknown error occurred" << std::endl;
        break;
    }

    return false;
  }

  std::cout << "SUCCESS: Socket created" << std::endl;
  return true;
}
