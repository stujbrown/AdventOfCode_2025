export module aoc:day6;
import std.compat;

class Day6
{
public:
    void run(std::string_view inputFilePath)
    {
        std::ifstream inputFile(inputFilePath.data());
        std::string line;
        std::vector<std::vector<std::string>> rows;
        std::vector<std::string> verticalDigits;
        while (std::getline(inputFile, line))
        {
            rows.push_back(std::vector<std::string>());
            const std::vector<std::string> row = std::ranges::views::split(line, ' ') | std::ranges::views::filter([](const auto& c) { return !c.empty(); }) | std::ranges::to<std::vector<std::string>>();
            for (size_t columnIndex = 0; columnIndex < row.size(); ++columnIndex)
                rows.back().push_back(row[columnIndex]);

            verticalDigits.resize(std::max(verticalDigits.size(), line.length() + 1));
            for (size_t pos = 0; pos < line.length(); ++pos)
            {
                if (std::isdigit(line[pos]) != 0)
                    verticalDigits[pos + 1] += line[pos];
            }
        }

        uint64_t grandTotal = 0, grandTotalVertical = 0;
        for (size_t columnIndex = 0; columnIndex < rows[0].size(); ++columnIndex)
        {
            uint64_t total = std::stoll(rows[0][columnIndex]);
            for (size_t rowIndex = 1; rowIndex < rows.size() - 1; ++rowIndex)
            {
                if (rows.back()[columnIndex] == "*")
                    total *= std::stoll(rows[rowIndex][columnIndex]);
                else
                    total += std::stoll(rows[rowIndex][columnIndex]);
            }

            grandTotal += total;
        }

        int opIndex = static_cast<int>(rows[0].size()) - 1;
        uint64_t total = 0;
        for (auto itr = verticalDigits.rbegin(); itr != verticalDigits.rend(); ++itr)
        {
            if (itr->empty())
            {
                grandTotalVertical += total;
                total = 0;
                --opIndex;
            }
            else if (total == 0)
                total = std::stoll(*itr);
            else if (rows.back()[opIndex] == "*")
                total *= std::stoll(*itr);
            else
                total += std::stoll(*itr);
        }

        std::println("Grand total: {}", grandTotal);
        std::println("Grand total for vertical digits: {}", grandTotalVertical);
    }
};
