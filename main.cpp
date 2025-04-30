#include "instance.hpp"
#include "tsp_greedy.hpp"
#include <iostream>


/**
   @file main.cpp

   @brief This file wraps the TSPLIB solving functionality into a command line tool. 
**/







int main(int argc, char** argv)
{
   if (argc != 2)
   {
      std::cerr << "Wrong number of arguments. Program call: <program_name> <input_graph>" << std::endl;
      return EXIT_FAILURE;
   }
   
   HCP::Instance instance;
   HCP::Instance::read_TSPLIB(argv[1], instance);

   std::cout << "instance has name " << instance.get_name() << "\n";
   std::cout << "number of coords is " << instance.get_coords() << "\n";
   std::cout << "instance dimension is " << instance.get_dimension() << "\n";
   
   std::cout << "Default tour length: " << default_tour(instance) << std::endl;
   std::cout << "Greedy Tour lenght: " << greedy_tour(instance) << std::endl;
}