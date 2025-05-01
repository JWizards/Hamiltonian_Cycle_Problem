#include "tsp_greedy.hpp"
#include <iostream>

namespace HCP{

    int default_tour(Instance &instance){
        int tour_length = 0;
        for(size_type i = 0; i < instance.get_dimension(); i++){
            tour_length = tour_length + instance.dist(i,i+1);
        }
        return tour_length;
    }


    bool tourness_not_violated(size_type i, size_type j, size_type dimensions, std::vector<size_type> &visited_degree){
        static size_type count_visited = 0;
        bool given_edge_completes_a_loop = visited_degree[i] == 1 && visited_degree[j] == 1;
        bool allowed_to_complete_loop = (count_visited == dimensions);
        bool can_add_edge = (visited_degree[i] < 2) && (visited_degree[j] < 2) && i != j;

        if((can_add_edge && (allowed_to_complete_loop || !given_edge_completes_a_loop))){
            if(visited_degree[i] == 0)
                count_visited++;
            if(visited_degree[j] == 0)
                count_visited++;
            return true;
        }

        return false;  
    }

    int greedy_tour(Instance &instance){
        //sort the edges in ascending order
        std::multimap<int, std::tuple<size_type, size_type>> binary_tree;
        for(size_type i = 0; i < instance.get_dimension(); i++){
            for(size_type j = 0; j < instance.get_dimension(); j++){
                binary_tree.insert({instance.dist(i, j), {i, j}});
            }
        }
        
        std::vector<size_type> visited_degree(instance.get_dimension(), 0);
        int greedy_length = 0;
        
        //greedily find tour
        for (auto it = binary_tree.begin(); it != binary_tree.end(); ++it) {
            auto weight = it->first;
            auto [i, j] = it->second;

            if(tourness_not_violated(i, j, instance.get_dimension(), visited_degree)){

                visited_degree[i] += 1;
                visited_degree[j] += 1;
                greedy_length += weight;
            }
        }

        return greedy_length;
    }
}