#pragma once
#include "instance.hpp"

namespace HCP{

    int default_tour_length(Instance &instance);
    std::pair<size_type, std::vector<size_type>> greedy_tour(Instance &Instance);
    int print_tour(std::vector<size_type>&, Instance &);

} //end namespace HCP