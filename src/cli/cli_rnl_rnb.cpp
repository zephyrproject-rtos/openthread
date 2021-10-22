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

#include "cli_rnl_rnb.hpp"

#include <openthread/message.h>

#include "cli/cli.hpp"
#include "common/encoding.hpp"

namespace ot {
namespace Cli {

constexpr RnlRnb::Command RnlRnb::sCommands[];

RnlRnb::RnlRnb(Interpreter &aInterpreter)
    : mInterpreter(aInterpreter)
{

}

otError RnlRnb::ProcessHelp(Arg aArgs[])
{
    otError error = OT_ERROR_NONE;

    VerifyOrExit(aArgs[0].IsEmpty(), error = OT_ERROR_INVALID_ARGS);

    for (const Command &command : sCommands)
    {
        mInterpreter.OutputLine(command.mName);
    }

exit:
    return error;
}

otError RnlRnb::ProcessVersion(Arg aArgs[])
{
    otError error;

    if (aArgs[0].IsEmpty())
    {
        mInterpreter.OutputLine("%s", otPlatRadioRnlRnbGetVersion(mInterpreter.mInstance));

        error = OT_ERROR_NONE;
    }
    else
    {
        error = OT_ERROR_INVALID_ARGS;
    }

    return error;
}

otError RnlRnb::ProcessStatus(Arg aArgs[])
{
    otError error;
    uint16_t receiveLength;
    char hexString[2*OPENTHREAD_CONFIG_CLI_MAX_LINE_LENGTH+1];
    char *ptr = hexString;

    if (aArgs[0].IsEmpty())
    {
        SuccessOrExit(error = otPlatRadioRnlRnbGetStatus(mInterpreter.mInstance, mReceiveBuffer, &receiveLength));

        for (uint8_t i=0; i<receiveLength; i++)
        {
            ptr += sprintf(ptr, "%02X", mReceiveBuffer[i]);
        }

        mInterpreter.OutputLine("%s", hexString);
    }
    else
    {
        error = OT_ERROR_INVALID_ARGS;
    }

exit:
    return error;
}

otError RnlRnb::ProcessSendRequest(Arg aArgs[])
{
    otError error = OT_ERROR_INVALID_ARGS;
    uint16_t receiveLength;

    VerifyOrExit(!aArgs[0].IsEmpty(), error = OT_ERROR_INVALID_ARGS);
    VerifyOrExit(!aArgs[1].IsEmpty(), error = OT_ERROR_INVALID_ARGS);

    if (aArgs[2].IsEmpty())
    {
        SuccessOrExit(error = aArgs[0].ParseAsUint16(receiveLength));
        SuccessOrExit(error = aArgs[1].ParseAsHexString(mReceiveBuffer, receiveLength));

        error = otPlatRadioRnlRnbSendRequest(mInterpreter.mInstance, mReceiveBuffer, receiveLength);
    }

exit:
    return error;
}

otError RnlRnb::Process(Arg aArgs[])
{
    otError        error = OT_ERROR_INVALID_ARGS;
    const Command *command;

    if (aArgs[0].IsEmpty())
    {
        IgnoreError(ProcessHelp(aArgs));
        ExitNow();
    }

    command = Utils::LookupTable::Find(aArgs[0].GetCString(), sCommands);
    VerifyOrExit(command != nullptr, error = OT_ERROR_INVALID_COMMAND);

    error = (this->*command->mHandler)(aArgs + 1);

exit:
    return error;
}

} // namespace Cli
} // namespace ot
