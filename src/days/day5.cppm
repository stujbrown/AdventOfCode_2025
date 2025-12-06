export module aoc:day5;
import std.compat;

class Day5
{
public:
    void run(std::string_view inputFilePath)
    {
        typedef std::pair<uint64_t, uint64_t> IntPair;
        std::ifstream inputFile(inputFilePath.data());
        std::string line;
        std::vector<IntPair> freshRanges;
        while (inputFile >> line && line.contains('-'))
        {
            const std::vector<std::string> range = std::ranges::views::split(line, '-') | std::ranges::to<std::vector<std::string>>();
            freshRanges.push_back(std::make_pair(std::stoll(range[0]), std::stoll(range[1])));
        }

        std::sort(freshRanges.begin(), freshRanges.end(), [](IntPair a, IntPair b) { return a.first < b.first; });
        for (auto itr = freshRanges.begin(); itr != freshRanges.end(); ++itr)
        {
            bool hasRemoved = false;
            for (auto otherItr = itr + 1; otherItr != freshRanges.end();)
            {
                if (otherItr->first <= itr->second)
                {
                    itr->second = std::max(itr->second, otherItr->second);
                    otherItr = freshRanges.erase(otherItr);
                }
                else
                    ++otherItr;
            }
        }

        uint64_t numFresh = 0, numFreshInRanges = 0;
        do
        {
            const uint64_t ingredient = std::stoll(line);
            for (size_t i = 0; i < freshRanges.size(); ++i)
            {
                if (ingredient >= freshRanges[i].first && ingredient <= freshRanges[i].second)
                {
                    ++numFresh;
                    break;
                }
            }
        } while (inputFile >> line && !line.empty());

        for (size_t i = 0; i < freshRanges.size(); ++i)
            numFreshInRanges += (freshRanges[i].second + 1) - freshRanges[i].first;

        std::println("Total fresh: {}", numFresh);
        std::println("Total fresh in ranges: {}", numFreshInRanges);
    }
};
