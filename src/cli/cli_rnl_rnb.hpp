/*
 *  Copyright (c) 2021, RedNodeLabs.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 *   This file implements a simple CLI for the RNL RNB service.
 */

#ifndef CLI_RNL_RNB_HPP_
#define CLI_RNL_RNB_HPP_

#include "openthread-core-config.h"

#include "utils/lookup_table.hpp"
#include "utils/parse_cmdline.hpp"

namespace ot {
namespace Cli {

class Interpreter;

/**
 * This class implements the CLI-based RNL RNB module.
 *
 */
class RnlRnb
{
public:
    typedef Utils::CmdLineParser::Arg Arg;

    /**
     * Constructor
     *
     * @param[in]  aInterpreter  The CLI interpreter.
     *
     */
    explicit RnlRnb(Interpreter &aInterpreter);

    /**
     * This method interprets a list of CLI arguments.
     *
     * @param[in]  aArgs        An array of command line arguments.
     *
     */
    otError Process(Arg aArgs[]);

private:
    struct Command
    {
        const char *mName;
        otError (RnlRnb::*mHandler)(Arg aArgs[]);
    };

    otError ProcessHelp(Arg aArgs[]);
    otError ProcessVersion(Arg aArgs[]);
    otError ProcessSendRequest(Arg aArgs[]);

    static constexpr Command sCommands[] = {
        {"help", &RnlRnb::ProcessHelp},
        {"sendrequest", &RnlRnb::ProcessSendRequest},
        {"version", &RnlRnb::ProcessVersion},
    };

    static_assert(Utils::LookupTable::IsSorted(sCommands), "Command Table is not sorted");

    Interpreter &mInterpreter;
    uint8_t     mReceiveBuffer[OPENTHREAD_CONFIG_CLI_MAX_LINE_LENGTH];
};

} // namespace Cli
} // namespace ot

#endif // CLI_RNL_RNB_HPP_
