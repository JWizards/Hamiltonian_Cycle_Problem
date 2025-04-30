#include "tsp_greedy.hpp"

namespace HCP{

    int default_tour(Instance &instance){
        int tour_length = 0;
        for(size_type i = 0; i < instance.get_dimension(); i++){
            tour_length = tour_length + instance.dist(i,i+1);
        }
        return tour_length;
    }




    int greedy_tour(Instance &instance){
        int greedy_length = 0;

        std::multimap<int, std::tuple<size_type, size_type>> binary_tree;
        for(size_type i = 0; i < instance.get_dimension(); i++){
            for(size_type j = 0; j < instance.get_dimension(); j++){
                binary_tree.insert({instance.dist(i, j), {i, j}});
            }
        }
        
        std::vector<int> visited_degree(instance.get_dimension(), 0);

        for (auto it = binary_tree.begin(); it != binary_tree.end(); ++it) {
            auto weight = it->first;
            auto [i, j] = it->second;

            if(visited_degree[j] < 3 && visited_degree[i] < 3){
                visited_degree[i] += 1;
                visited_degree[j] += 1;
                greedy_length += weight;
            }
        }

        return greedy_length;
    }
}