#pragma once
#include "instance.hpp"

namespace HCP{

    int default_tour(Instance &instance);
    HCP::Tour greedy_tour(Instance &Instance);

} //end namespace HCP