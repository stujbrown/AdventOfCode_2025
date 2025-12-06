export module aoc:day3;
import std;

class Day3
{
public:
    size_t calcJoltageRecursive(std::string_view bankView, int digitsRemaining)
    {
        if (digitsRemaining == 0)
            return 0;

        --digitsRemaining;
        const auto largestItr = std::max_element(bankView.begin(), bankView.begin() + bankView.length() - digitsRemaining);

        return (((*largestItr) - '0') * (size_t)std::pow(10, digitsRemaining)) +
            calcJoltageRecursive(std::string_view(largestItr + 1, bankView.end()), digitsRemaining);
    }

    void run(std::string_view inputFilePath)
    {
        size_t limitedTotalJoltage = 0, totalJoltage = 0;
        std::ifstream inputFile(inputFilePath.data());
        for (std::string bank; inputFile >> bank;)
        {
            limitedTotalJoltage += calcJoltageRecursive(bank, 2);
            totalJoltage += calcJoltageRecursive(bank, 12);
        }

        std::println("Total joltage (2 batteries): {}", limitedTotalJoltage);
        std::println("Total joltage (12 batteries): {}", totalJoltage);
    }
};
