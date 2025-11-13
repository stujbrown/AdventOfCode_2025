@echo off

for /l %%x in (1, 1, 25) do (

	if NOT EXIST src/days/day%%x.cppm (
		(
			echo export module aoc:day%%x;
			echo import std;
			echo:
			echo class Day%%x
			echo {
			echo public:
			echo     void run(std::string_view inputFilePath^)
			echo     {
			echo         (void^)inputFilePath;
			echo     }
			echo };
		) > src/days/day%%x.cppm
	)

	if NOT EXIST inputs/day%%x.txt (
		echo: > inputs/day%%x.txt
	)
)
