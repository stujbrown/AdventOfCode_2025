export module aoc;

import std.compat;

import :day1;
import :day2;
import :day3;
import :day4;
import :day5;
import :day6;
import :day7;
import :day8;
import :day9;
import :day10;
import :day11;
import :day12;
import :day13;
import :day14;
import :day15;
import :day16;
import :day17;
import :day18;
import :day19;
import :day20;
import :day21;
import :day22;
import :day23;
import :day24;
import :day25;

namespace aoc
{
    export struct Args
    {
        int dayToRun = -1;
    };

    export Args parseArgs(int numArgs, const char* args[])
    {
        int dayToRun = -1;
        if (numArgs > 1)
        {
            dayToRun = atoi(args[1]);
        }
        return Args{ .dayToRun = dayToRun };
    }

    export void run(const Args& args);
}

module : private;

namespace aoc
{
    template<typename T>
    concept RunnableDay = requires(T t, std::string_view inputFilePath)
    {
        { t.run(inputFilePath) };
    };

    template<typename TDay> requires RunnableDay<TDay>
    void runDay(std::string_view inputFilePath)
    {
        TDay day;
        day.run(inputFilePath);
    }

    void run(const Args& args)
    {
        int dayToRun = args.dayToRun;
        if (dayToRun <= 0)
        {
            std::cout << "Run day: ";
            std::cin >> dayToRun;
            std::cout << std::endl;
        }


        const auto startTime = std::chrono::high_resolution_clock::now();

#define INVOKE_DAY(number) case number: runDay<Day##number>("inputs/day"#number".txt"); break;
        switch (dayToRun)
        {
            INVOKE_DAY(1);
            INVOKE_DAY(2);
            INVOKE_DAY(3);
            INVOKE_DAY(4);
            INVOKE_DAY(5);
            INVOKE_DAY(6);
            INVOKE_DAY(7);
            INVOKE_DAY(8);
            INVOKE_DAY(9);
            INVOKE_DAY(10);
            INVOKE_DAY(11);
            INVOKE_DAY(12);
            INVOKE_DAY(13);
            INVOKE_DAY(14);
            INVOKE_DAY(15);
            INVOKE_DAY(16);
            INVOKE_DAY(17);
            INVOKE_DAY(18);
            INVOKE_DAY(19);
            INVOKE_DAY(20);
            INVOKE_DAY(21);
            INVOKE_DAY(22);
            INVOKE_DAY(23);
            INVOKE_DAY(24);
            INVOKE_DAY(25);

        default:
            std::cout << "Invalid day\n";
        }

        const auto endTime = std::chrono::high_resolution_clock::now();
        const auto duration = endTime - startTime;
        std::println("\nCompleted in {}ms ({}ns)", std::chrono::duration_cast<std::chrono::milliseconds>(duration).count(), std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count());
        std::cout << std::endl;
    }

}
