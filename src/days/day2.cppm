export module aoc:day2;
import std;

class Day2
{
public:
    void run(std::string_view inputFilePath)
    {
        std::ifstream inputFile(inputFilePath.data());
        std::string line;
        size_t invalidTotal = 0, invalidTotal2 = 0;
        while (std::getline(inputFile, line, ',') && !line.empty())
        {
            auto&& split = std::ranges::views::split(line, '-') | std::ranges::to<std::vector<std::string>>();
            const size_t start = std::stoll(split[0]);
            const size_t end = std::stoll(split[1]);

            for (size_t value = start; value < end + 1; ++value)
            {
                const std::string valueStr = std::to_string(value);
                if (valueStr.length() % 2 == 0)
                {
                    const std::string_view pattern(valueStr.data(), valueStr.length() / 2);
                    if (std::string_view(valueStr.data() + valueStr.length() / 2, valueStr.length() / 2) == pattern)
                        invalidTotal += value;
                }

                for (size_t patternEndIndex = 1; patternEndIndex < valueStr.length(); ++patternEndIndex)
                {
                    const std::string_view pattern(valueStr.data(), patternEndIndex);
                    bool isMatch = true;
                    for (size_t matchStartIndex = pattern.length(); matchStartIndex < valueStr.length(); matchStartIndex += pattern.length())
                    {
                        if (std::string_view(valueStr.data() + matchStartIndex, pattern.length()) != pattern)
                        {
                            isMatch = false;
                            break;
                        }
                    }

                    if (isMatch)
                    {
                        invalidTotal2 += value;                         
                        break;
                    }
                }
            }
        }

        std::println("Invalid ID total (Two repeats): {}", invalidTotal);
        std::println("Invalid ID total (Multiple repeats): {}", invalidTotal2);
    }
};
