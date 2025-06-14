/**
   @class Instance
   @brief brief here
   @warning add warning here
**/

#include <limits>
#include <vector>
#include "instance.hpp"

namespace HCP
{
    /**
    @class Instance
    @brief brief here
        @warning add warning here
    **/
    class Ordering 
    {
    public:
        
        size_t next_step(size_t, size_t); // Ordering is direction agnostic, so current and previous has to be supplied to define the next step.
        Ordering& gamma(size_t y, size_t x, size_t a);
        Ordering& kappa(size_t x, size_t a, size_t c, size_t d);
        Ordering(const HCP::Instance &graph_instance) : graph(graph_instance) {
            neighbour_array.resize(graph_instance.get_dimension()*2);
            for(size_t i = 0; i < graph_instance.get_dimension(); i++){
                neighbour_array[2*i] = (i + 1)%graph_instance.get_dimension();
                neighbour_array[2*i + 1] = (i - 1) + ((i == 0)?graph_instance.get_dimension():0);
            }
        }
        int print_ordering();
        int print_neighbours(size_t);
    private:
        const Instance &graph;
        std::vector<size_t> neighbour_array; // neighbour_array[2*i] and neighbour_array[2*i + 1] are the neighbours of i in the ordering/circular graph (circular)

        int reverse_segment(size_t, size_t, size_t, size_t);
    };    
} // namespace HCP
