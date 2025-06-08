#include "tsp_greedy.hpp"
#include <algorithm>
#include <iostream>
#include <fstream>

namespace HCP{

    int default_tour_length(Instance &instance){
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

    

    std::pair<size_type, std::vector<size_type>> greedy_tour(Instance &instance){

        //sort directed edges for greedy tour formation
        std::vector<std::pair<size_type, size_type>> sorted_directed_edges;
        for(size_type i = 0; i < instance.get_dimension(); i++){
            for(size_type j = 0; j < instance.get_dimension(); j++){
                sorted_directed_edges.push_back({i, j});
            }
        }

        std::sort(sorted_directed_edges.begin(), sorted_directed_edges.end(),
            [&instance](const std::pair<size_type, size_type>& A, const std::pair<size_type, size_type>& B){
                return instance.dist(A.first, A.second) < instance.dist(B.first, B.second);
            }
        );

        std::vector<size_type> visited_degree(instance.get_dimension(), 0); //track degree of each vertex
        std::vector<std::vector<size_type>> neighbours(instance.get_dimension()); //tracks neighbours of each vertex
        size_type greedy_length = 0;
        
        //greedily find tour
        for (auto it = sorted_directed_edges.begin(); it != sorted_directed_edges.end(); ++it) {
            auto weight = instance.dist(it->first, it->second);
            auto [i, j] = *it;

            if(tourness_not_violated(i, j, instance.get_dimension(), visited_degree)){
                std::cout << "adding " << i << " " << j << std::endl;
                neighbours[i].push_back(j);
                neighbours[j].push_back(i);
                visited_degree[i] += 1;
                visited_degree[j] += 1;
                greedy_length += weight;
            }
        }

        std::vector<size_type> tour_found(instance.get_dimension()); //the tour found returned as a permutation. i.e tour[i] = j means go from city i to city j
        size_type previous_city = -1;
        size_type currently_at = 0;
        size_type next_city;
        for(size_type i = 0; i < instance.get_dimension(); i++){
            next_city = neighbours[currently_at][0] == previous_city? neighbours[currently_at][1] : neighbours[currently_at][0];
            tour_found[currently_at] = next_city;
            previous_city = currently_at;
            currently_at = next_city; 
        }

        
        return {greedy_length, tour_found};
    }

    int print_tour(std::vector<size_type> &tour, Instance &instance){

        std::ofstream fout("output.greedy.tour");
        if(!fout.is_open()){
            std::cerr << "Failed to open 'output.tsp'";
            return 1;
        }

        fout << "NAME : " << instance.get_name() << ".greedy.tour" << '\n';
        fout << "COMMENT : Greedily found tour for " << instance.get_name() << ".tsp" << '\n';
        fout << "TYPE : TOUR" << '\n';
        fout << "DIMENSION : " << tour.size() << '\n';
        fout << "TOUR_SECTION" << '\n';
        
        size_type tour_position = 0;
        for(size_type i = 0; i < tour.size(); i++){
            fout << tour_position + 1 << '\n'; //+1 since tour indexing begins at 1 in TSPLIB files
            tour_position = tour[tour_position];
        }
        fout << "-1\nEOF";
        return 0;
    }
}