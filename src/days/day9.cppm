export module aoc:day9;
import std.compat;
import vec2;


class Day9
{

    static const int BoxLeftX = 0, BoxRightX = 1, BoxTopY = 2, BoxBottomY = 3;
    typedef std::array<int, 4> Box;

    inline uint64_t area(const Box& box)
    {
        return (std::llabs(box[BoxRightX] - box[BoxLeftX]) + 1) * (std::llabs(box[BoxBottomY] - box[BoxTopY]) + 1); // Inclusive of border
    }

    bool intersectsBox(const Point& lineStart, const Point& lineEnd, const Box& box)
    {
        const IntVec2 lineDir(lineEnd - lineStart);
        if (lineDir.x != 0) // Is horizontal
        {
            if (lineStart.y > box[BoxTopY] && lineStart.y < box[BoxBottomY]) // if line is within box y range
            {
                const int minX = std::min(lineStart.x, lineEnd.x);
                const int maxX = std::max(lineStart.x, lineEnd.x);

                if ((minX > box[BoxLeftX] && minX < box[BoxRightX]) || 
                    (maxX > box[BoxLeftX] && maxX < box[BoxRightX]) ||
                    (minX <= box[BoxLeftX] && maxX >= box[BoxRightX]))
                    return true;
            }
        }
        else
        {
            if (lineStart.x > box[BoxLeftX] && lineStart.x < box[BoxRightX])
            {
                const int minY = std::min(lineStart.y, lineEnd.y);
                const int maxY = std::max(lineStart.y, lineEnd.y);

                if ((minY > box[BoxTopY] && minY < box[BoxBottomY]) ||
                    (maxY > box[BoxTopY] && maxY < box[BoxBottomY]) ||
                    (minY <= box[BoxTopY] && maxY >= box[BoxBottomY]))
                    return true;
            }
        }

        return false;
    }

public:
    void run(std::string_view inputFilePath)
    {
        std::vector<Point> redTiles;
        std::set<Box> boxesAdded;

        std::ifstream inputFile(inputFilePath.data());
        int x, y;
        char delim;
        while (inputFile >> x >> delim >> y)
            redTiles.push_back(Point{ x, y });

        std::vector<std::pair<Box, uint64_t>> boxesByArea;
        for (size_t i = 0; i < redTiles.size(); ++i)
        {
            for (size_t j = i + 1; j < redTiles.size(); ++j)
            {
                const Box box{ std::min(redTiles[i].x, redTiles[j].x), std::max(redTiles[i].x, redTiles[j].x), std::min(redTiles[i].y, redTiles[j].y), std::max(redTiles[i].y, redTiles[j].y) };
                if (!boxesAdded.contains(box))
                {
                    boxesAdded.insert(box);
                    boxesByArea.push_back(std::make_pair(box, area(box)));
                }
            }
        }

        std::sort(boxesByArea.begin(), boxesByArea.end(), [](const std::pair<Box, uint64_t>& a, const std::pair<Box, uint64_t>& b) {
            return a.second > b.second;
        });

        std::println("Largest area: {}", area(boxesByArea[0].first));

        for (const auto& boxAndArea : boxesByArea)
        {
            bool isIntersected = false;
            for (size_t i = 0, j = redTiles.size() - 1; i < redTiles.size(); j = i, ++i)
            {
                const Point vertA = redTiles[i];
                const Point vertB = redTiles[j];
                if (intersectsBox(vertA, vertB, boxAndArea.first))
                {
                    isIntersected = true;
                    break;
                }
            }

            if (!isIntersected)
            {
                std::println("Largest area using red & green: {}", area(boxAndArea.first));
                break;
            }
        }
    }
};
