/*
 * CommandLineOptionsParser.cpp
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

#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <getopt.h>


bool tinynetperf::commandlineoptionsparser::CommandLineOptionsParser::ParseCommandLineArguments(int32_t number_of_aruments, char **arguments) {

  uint32_t opt = 0;
  bool result = false;

  while ((opt = getopt(number_of_aruments, arguments, "sch:")) != -1)
    switch(opt)
    {
      case 's':
        std::cout <<" server is enabled"<<std::endl;
        result = true;
        break;
      case 'c':
        std::cout <<" client is enabled"<<std::endl;
        result = true;
        break;
      case 'h':
        command_line_options_help_->PrintAllOptionsHelp();
        result = true;
        break;
      default:
        command_line_options_help_->PrintAllOptionsHelp();
        break;
    }

  return result;
}
