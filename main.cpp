#include "instance.hpp"
#include "tsp_greedy.hpp"
#include "ordering.hpp"

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
   
   HCP::Instance instance(argv[1]); //read TSPLIB and store as instance

   std::cout << "instance has name " << instance.get_name() << "\n";
   std::cout << "instance dimension is " << instance.get_dimension() << "\n";

   std::cout << "instance adjancency list is\n" << "\n";
   instance.print_adjacency_matrix();

   HCP::Ordering ordering(instance);

   std::cout << "\n\n\nNow we print the default ordering\n";
   ordering.print_ordering();

}