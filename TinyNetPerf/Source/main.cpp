/*
 * main.cpp
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

#include "../Headers/Command-Line-Options-Parser.h"

#include "../Headers/ServerUdp.h"
#include "../Headers/ClientUdp.h"

#include <memory>
#include <getopt.h>
#include <unistd.h>
#include <iostream>


int main(int argc, char *argv[]) {
	int opt;
	char buffer[1024];
	std::string address_parameter;
	uint16_t port_num_parameter = 0;
	uint32_t bytes_number_to_be_sent = 1;

	strcpy(buffer, "test");

	std::unique_ptr<tinynetperf::serverudp::IClientUdp> client_udp;
	std::unique_ptr<tinynetperf::ServerUdp::IServerUdp> server_udp;


	while ((opt = getopt(argc, argv, "a:p:n:sch")) != -1) {
		switch (opt) {
			case 'a':
				address_parameter = optarg;
				break;
			case 'p':
				port_num_parameter = atoi(optarg);
				break;
			case 'n':
				bytes_number_to_be_sent = atoi(optarg);
				memset(buffer, 's', bytes_number_to_be_sent);
				break;
			case 's':
				server_udp.reset(new tinynetperf::ServerUdp::ServerUdp);
				server_udp->SetupServer(port_num_parameter, address_parameter);
				server_udp->StartListeningInLoop(buffer);
				break;
			case 'c':
				client_udp.reset(new tinynetperf::serverudp::ClientUdp);
				client_udp->SetupClient(port_num_parameter, address_parameter);
				client_udp->StartSendingInLoop(buffer);
				break;
			case 'h':
			default:
				std::cout<<"\nHelp:"<<std::endl;
				std::cout<<"Use: -s for Server mode"<<std::endl;
				std::cout<<"Use: -c for Client mode"<<std::endl;
				std::cout<<"Use: -a for target IP address"<<std::endl;
				std::cout<<"Use: -p for listening/send port number"<<std::endl;
				std::cout<<"Use: -n for number of bytes to be sent"<<std::endl;
				std::cout<<"\nExample Client: -a 127.0.0.1 -p 5000 -n 100 -c"<<std::endl;
				std::cout<<"Example Server: -a 127.0.0.1 -p 5000 -s\n"<<std::endl;
				break;
		}
	}

	return 0;
}
