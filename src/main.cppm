import aoc;
import std;

int main(int argc, const char* argv[])
{
    try 
    {
        aoc::run(aoc::parseArgs(argc, argv));
    } 
    catch (const std::exception& e)
    {
        std::cout << "\nUnhandled exception: " << e.what() << std::endl;
    }

#if _WIN32
    system("pause");
#endif

    return 0;
}
