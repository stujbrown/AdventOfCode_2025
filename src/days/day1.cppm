export module aoc:day1;
import std;

class Day1
{
public:
    void run(std::string_view inputFilePath)
    {
        std::ifstream inputFile(inputFilePath.data());
        std::string instruction;

        int pos = 50;
        int timesAtZero = 0, timesPassingZero = 0;
        while (inputFile >> instruction && !instruction.empty())
        {
            const int startPos = pos;
            int moveAmount = std::stoi(instruction.substr(1));

            timesPassingZero += moveAmount / 100;
            moveAmount %= 100; // Only move by remainder, to test if partial rotation passes 0

            if (instruction[0] == 'L')
                pos -= moveAmount;
            else
                pos += moveAmount;

            if (startPos != 0 && startPos != 100 && (pos < 0 || pos > 100))
                ++timesPassingZero;

            pos = (pos + 100) % 100;
            if (pos == 0)
                ++timesAtZero;
        }

        std::println("Password: {}", timesAtZero);
        std::println("Password for new protocol: {}", timesAtZero + timesPassingZero);
    }
};
