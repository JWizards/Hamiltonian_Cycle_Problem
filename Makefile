HCP: 
	g++ -std=c++20 -pedantic -Wall -Wextra -Werror -o main main.cpp instance.cpp tsp_greedy.cpp ordering.cpp -O3	

local: local.cpp
	g++ -std=c++20 -pedantic -Wall -Wextra -Werror -o local local.cpp -O3

debug: 
	g++ -std=c++20 -pedantic -Wall -Wextra -Werror -o main main.cpp instance.cpp tsp_greedy.cpp ordering.cpp -O3	-g
