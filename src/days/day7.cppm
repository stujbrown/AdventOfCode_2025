export module aoc:day7;
import std;
import vec2;

class Day7
{
public:
    void run(std::string_view inputFilePath)
    {
        struct Particle
        {
            IntVec2 pos{};
            size_t timesEncountered = 0;
        };

        std::ifstream inputFile(inputFilePath.data());
        std::string line;
        std::getline(inputFile, line);

        int rowIndex = 0;
        size_t numSplits = 0;
        std::vector<Particle> particles;
        particles.push_back(Particle{ .pos = IntVec2 {static_cast<int>(line.find('S')), 0 }, .timesEncountered = 1 });
        std::set<IntVec2> splitRecords;

        while (std::getline(inputFile, line))
        {
            ++rowIndex;
            for (int particlePos = 0; particlePos < line.length(); ++particlePos)
            {
                particlePos = static_cast<int>(line.find_first_of('^', particlePos));
                if (particlePos == static_cast<int>(std::string::npos))
                    break;

                for (int particleIndex = 0; particleIndex < static_cast<int>(particles.size()); ++particleIndex)
                {
                    if (particles[particleIndex].pos.x == particlePos && particles[particleIndex].pos.y < rowIndex)
                    {
                        size_t timesEncountered = particles[particleIndex].timesEncountered;
                        particles.erase(particles.begin() + particleIndex);
                        --particleIndex;

                        static const int offsets[2]{ -1, 1 };
                        for (const int offset : offsets)
                        {
                            auto existing = std::find_if(particles.begin(), particles.end(), [particlePos, offset](const Particle& a) { return a.pos.x == particlePos + offset; });
                            if (existing == particles.end())
                                particles.push_back(Particle{ .pos = IntVec2{ particlePos + offset, rowIndex }, .timesEncountered = timesEncountered });
                            else
                                existing->timesEncountered += timesEncountered;
                        }

                        if (!splitRecords.contains(IntVec2{ particlePos, rowIndex }))
                        {
                            splitRecords.insert(IntVec2{ particlePos, rowIndex });
                            ++numSplits;
                        }
                    }
                }
            }
        }

        size_t total = 0;
        for (const auto& entry : particles)
            total += (entry.timesEncountered);
        std::println("Num splits: {}", numSplits);
        std::println("Num permutations: {}", total);
    }
};
