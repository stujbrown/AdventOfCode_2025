export module aoc:day8;
import std;
import vec3;

namespace
{
    inline double distance(const IntVec3& lhs, const IntVec3& rhs)
    {
        const double dX = double(rhs.x) - double(lhs.x);
        const double dY = double(rhs.y) - double(lhs.y);
        const double dZ = double(rhs.z) - double(lhs.z);
        return std::sqrt(dX * dX + dY * dY + dZ * dZ);
    }
}

class Day8
{
public:
    void run(std::string_view inputFilePath)
    {
        typedef std::set<IntVec3> Circuit;

        std::set<std::shared_ptr<Circuit>> circuits;
        std::vector<IntVec3> allNodes;
        std::map<IntVec3, std::shared_ptr<Circuit>> positionToCircuit; // Maps a node position to the circuit it belongs to

        std::ifstream inputFile(inputFilePath.data());
        int x, y, z;
        char delim;
        while (inputFile >> x >> delim >> y >> delim >> z)
        {
            const IntVec3 position{ x, y, z };
            auto&& circuit = std::shared_ptr<Circuit>(new Circuit);
            circuits.insert(circuit);
            allNodes.push_back(position);
            circuit->insert(position);
            positionToCircuit[position] = circuit;
        }

        // Calc distances for all pairs
        std::vector<std::tuple<IntVec3, IntVec3, float>> pairsAndDistances;
        for (size_t i = 0; i < allNodes.size(); ++i)
        {
            for (size_t j = i + 1; j < allNodes.size(); ++j)
            {
                const float dist = distance(allNodes[i], allNodes[j]);
                pairsAndDistances.push_back(std::make_tuple(allNodes[i], allNodes[j], dist));
            }
        }
        std::sort(pairsAndDistances.begin(), pairsAndDistances.end(), [](const std::tuple<IntVec3, IntVec3, float>& a, const std::tuple<IntVec3, IntVec3, float>& b) {
            return std::get<2>(a) > std::get<2>(b); });


        const size_t iterationsForPart1 = 1000;
        size_t iteration = 0;
        size_t largestCircuitVal = 0, finalConnectionVal = 0;
        while (largestCircuitVal == 0 || finalConnectionVal == 0)
        {
            ++iteration;
            if (largestCircuitVal == 0 && iteration == iterationsForPart1 + 1)
            {
                std::vector<size_t> sizes;
                for (auto itr = circuits.begin(); itr != circuits.end(); ++itr)
                    sizes.push_back(itr->get()->size());

                std::sort(sizes.begin(), sizes.end(), std::greater<size_t>());
                largestCircuitVal = sizes[0] * sizes[1] * sizes[2];
            }

            const std::pair<IntVec3, IntVec3> closestPair(std::get<0>(pairsAndDistances.back()), std::get<1>(pairsAndDistances.back()));
            pairsAndDistances.pop_back();

            // Merge circuits
            const std::shared_ptr<Circuit> circuitA = positionToCircuit[closestPair.first];
            const std::shared_ptr<Circuit> circuitB = positionToCircuit[closestPair.second];
            if (circuitA == circuitB)
                continue;

            for (const IntVec3& node : *circuitB)
                circuitA->insert(node);

            const std::shared_ptr<Circuit> oldCircuit = positionToCircuit[closestPair.second];
            circuits.erase(oldCircuit);

            for (auto itr = positionToCircuit.begin(); itr != positionToCircuit.end(); ++itr)
            {
                if (itr->second == oldCircuit)
                    itr->second = positionToCircuit[closestPair.first];
            }

            if (finalConnectionVal == 0 && circuits.size() == 1)
                finalConnectionVal = static_cast<size_t>(closestPair.first.x) * static_cast<size_t>(closestPair.second.x);
        }

        std::println("Largest circuit value: {}", largestCircuitVal);
        std::println("Final connection value: {}", finalConnectionVal);
    }
};
