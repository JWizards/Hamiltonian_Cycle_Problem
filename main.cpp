#include "instance.hpp"
#include <iostream>


/**
   @file main.cpp

   @brief This file wraps the TSPLIB solving functionality into a command line tool. 
**/




HCP::Tour find_greedy_tour(HCP::Instance instance);
HCP::size_type default_tour(HCP::Instance instance);


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
   
   std::cout << "Default tour length:" << default_tour(instance) << std::endl;
   HCP::Tour greedy_tour = find_greedy_tour(instance);
   std::cout << "Outputting found tour to output.TSP" << std::endl;
   greedy_tour.print_into(""); 
}