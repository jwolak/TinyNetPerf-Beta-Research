/*
 * Socket-Bind-Result-Analyzer.cpp
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

#include "../Headers/Socket-Bind-Result-Analyzer.h"
#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>

bool tinynetperf::socketDataHandling::SocketBindResultAnalyzer::AnalyzeBindSocketResult(int32_t bind_result)
{
    /* TODO change std::cout to log file */
    if (bind_result == -1)
    {
        switch (errno)
        {
        case EACCES:
            std::cout << "ERROR: [EACCES] Address is protected, and the user is not the superuser" << std::endl;
            return false;
        case EADDRINUSE:
            std::cout << "ERROR: [EADDRINUSE] Given address is already in use" << std::endl;
            return false;
        case EBADF:
            std::cout << "ERROR: [EBADF] Ivalid file descriptor" << std::endl;
            return false;
        case EINVAL:
            std::cout << "ERROR: [EINVAL] Socket is already bound to an address" << std::endl;
            return false;
        case ENOTSOCK:
            std::cout << "ERROR: [ENOTSOCK] File descriptor sockfd does not refer to a socket" << std::endl;
            return false;
        case EADDRNOTAVAIL:
            std::cout << "ERROR: [EADDRNOTAVAIL] Nonexistent interface was requested or the requested address was not local" << std::endl;
            return false;
        case EFAULT:
            std::cout << "ERROR: [EFAULT] Address points outside the user's accessible address space" << std::endl;
            return false;
        case ELOOP:
            std::cout << "ERROR: [ELOOP] Too many symbolic links were encountered in resolving address" << std::endl;
            return false;
        case ENAMETOOLONG:
            std::cout << "ERROR: [ENAMETOOLONG] Address is too long" << std::endl;
            return false;
        case ENOENT:
            std::cout << "ERROR: [ENOENT] Component in the directory prefix of the socket pathname does not exist" << std::endl;
            return false;
        case ENOMEM:
            std::cout << "ERROR: [ENOMEM] Insufficient kernel memory was available" << std::endl;
            return false;
        case ENOTDIR:
            std::cout << "ERROR: [ENOTDIR] Component of the path prefix is not a directory" << std::endl;
            return false;
        case EROFS:
            std::cout << "ERROR: [EROFS] socket inode would reside on a read-only filesystem" << std::endl;
            return false;
        default:
            std::cout << "ERROR Close socket unknown error occurred" << std::endl;
            return false;
        }
    }
    std::cout << "SUCCESS: Socket binded" << std::endl;
    return true;
}
