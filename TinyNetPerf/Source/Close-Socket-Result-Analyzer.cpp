/*
 * Close-Socket-Result-Analyzer.cpp
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

#include "../Headers/Close-Socket-Result-Analyzer.h"
#include <iostream>

bool tinynetperf::serverudp::CloseSocketResultAnalyzer::AnalyzeCloseSocketResult(int32_t close_socket_result) {

  /* TODO change std::cout to log file */
  if (close_socket_result == -1) {
    switch (errno) {
      case EBADF:
        std::cout<<"ERROR Socket argument is not a valid file descriptor"<<std::endl;
        return false;
      case EINVAL:
        std::cout<<"ERROR Action argument is invalid"<<std::endl;
        return false;
      case ENOTCONN:
        std::cout<<"ERROR Socket is not connected"<<std::endl;
        return false;
      case ENOTSOCK:
        std::cout<<"ERROR Socket argument does not refer to a socket"<<std::endl;
        return false;
      case ENOBUFS:
        std::cout<<"ERROR Insufficient resources were available in the system to perform the operation"<<std::endl;
        return false;
      default:
        std::cout<<"ERROR Close socket unknown error occurred"<<std::endl;
        return false;
    }
  }

  std::cout<<"SUCCESS: Socket closed"<<std::endl;
  return true;
}

