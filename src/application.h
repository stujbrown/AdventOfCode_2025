#pragma once

namespace aoc
{

    struct Args
    {
        int dayToRun = -1;
    };

    Args parseArgs(int numArgs, const char* args[]);
    void run(const Args& args);

}
