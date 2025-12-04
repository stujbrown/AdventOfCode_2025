export module aoc:day4;
import std;
import vec2;

static const IntVec2 adjacencyOffsets[8] =
{
    IntVec2 { 0, -1 }, IntVec2{ 1, -1 }, IntVec2{ 1, 0 }, IntVec2{ 1, 1 }, IntVec2{ 0, 1 }, IntVec2{ -1, 1 }, IntVec2{ -1, 0 }, IntVec2{ -1, -1 },
};

class Day4
{
private:
    typedef std::vector<std::string> Rows;
    size_t countMovable(Rows& rows, bool allowRemoval)
    {
        size_t numValid = 0;
        for (int y = 0; y < (int)rows.size(); ++y)
        {
            for (int x = 0; x < (int)rows[y].length(); ++x)
            {
                if (rows[y][x] != '@')
                    continue;

                int adjacentCount = 0;
                for (const IntVec2& offset : adjacencyOffsets)
                {
                    const int otherX = x + offset.x;
                    const int otherY = y + offset.y;
                    if (otherX >= 0 && otherX < rows[y].length() && otherY >= 0 && otherY < rows.size())
                    {
                        if (rows[otherY][otherX] == '@')
                            ++adjacentCount;
                    }
                }

                if (adjacentCount < 4)
                {
                    ++numValid;
                    if (allowRemoval)
                    {
                        rows[y][x] = 'x';
                        x = std::max(x - 2, -1);
                        y = std::max(y - 1, 0);
                    }
                }
            }
        }
        return numValid;
    }

public:
    void run(std::string_view inputFilePath)
    {
        std::ifstream inputFile(inputFilePath.data());
        Rows rows(64);
        for (std::string row; inputFile >> row;)
            rows.push_back(row);

        const size_t numValid = countMovable(rows, false);
        const size_t numValidWithRemovals = countMovable(rows, true);

        std::println("Number of valid rolls: {}", numValid);
        std::println("Number of valid rolls (removals allowed): {}", numValidWithRemovals);
    }
};
