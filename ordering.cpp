#include "instance.hpp"
#include "ordering.hpp"

#include <iostream>


namespace HCP
{
    //returns a random step if prev is not adjacent to current.
    size_t Ordering::next_step(size_t current, size_t prev){
        return (prev != neighbour_array[2*current]) ? neighbour_array[2*current] : neighbour_array[2*current + 1];
    }

    //in Ordering (x y ... a b .. x) reverse the segment (b ... x) and map to (b y ... a x ... b) 
    int Ordering::reverse_segment(size_t x, size_t y, size_t a, size_t b){
        //x looses y as a neighbour and gains a
        //y looses x as a neighbour and gains b
        (neighbour_array[2*x] == y)? neighbour_array[2*x] = a : neighbour_array[2*x + 1] = a;
        (neighbour_array[2*y] == x)? neighbour_array[2*y] = b : neighbour_array[2*y + 1] = b;
        //likewise for a and b
        (neighbour_array[2*a] == b)? neighbour_array[2*a] = x : neighbour_array[2*a + 1] = x;
        (neighbour_array[2*b] == a)? neighbour_array[2*b] = y : neighbour_array[2*b + 1] = y;
        return 0;
    }

    Ordering& Ordering::gamma(size_t y, size_t x, size_t a){
        if(y != neighbour_array[2*x] && y != neighbour_array[2*x + 1]){
            std::cout << "ERROR";
            return *this; // fail silently for illegal input
        }

        //calculate 'b' the neighbour of 'a' between 'x' and 'a'
        size_t b = x, next, temp;
        next = this->next_step(x, y); //move in direction opposite to y
        while(next != a){
            temp = next;
            next = this->next_step(next, b);
            b = temp; 
        }

        this->reverse_segment(x , y, a, b);
        return *this; 
    }

    //notation is kept consistent with the paper
    Ordering& Ordering::kappa(size_t x, size_t a, size_t c, size_t d){
        size_t y, e, b, f; //to calculate/detect
        y = e = b = f = -1; //default fail state;
        // xy, ec, ba, fd need to be neighbours in fact our ordering begins from (x ec ab fd yx)

        //illegal input
        if(x == a || x == c || x == d || a == c || a == d || c == d ){
            return *this;
        }


        //In the following two while loops y, e, b, f are calculated.
        bool d_found = false, c_found = false;
        size_t temp, current = x, prev = neighbour_array[2*x + 1];
        while(current != a){
            temp = current;
            current = this->next_step(current, prev);
            prev = temp;

            //checks to make after stepping
            if (current == c){
                c_found = true;
                e = prev;
            }
            if (current == d){
                d_found = true;
                f = next_step(current, prev);
            }
            if (d_found && current == a){
                b = prev;
            }
        }

        if (c_found == d_found){
            return *this; //illegal input
        }

        if (c_found){
            y = neighbour_array[2*x + 1];
        } else if (d_found){
            y = neighbour_array[2*x];
        } else {
            y = neighbour_array[2*x]; //default setting of y- likely not called.
        }
        
        //calculate elements to find on other half of ordering
        current = x; prev = neighbour_array[2*x];
        while(current != a){
            temp = current;
            current = this->next_step(current, prev);
            prev = temp;

            //checks to make after stepping
            if (current == c){
                e = prev;
            }
            if (current == d){
                d_found = true;
                f = next_step(current, prev);
            }
            if (d_found && current == a){
                b = prev;
            }
        }


        //the following function is created anonymously since it invalidates the graph structure if only called once.
        auto replace_neighbour = [this](size_t pos, size_t neigh_to_replace, size_t new_neighbour){
            if(neighbour_array[2*pos] == neigh_to_replace){
                neighbour_array[2*pos] = new_neighbour; 
            }
            else if (neighbour_array[2*pos + 1] == neigh_to_replace) {
                neighbour_array[2*pos + 1] = new_neighbour;
            } else {
                return 1; //indicate failure if function call was invalid.
            }
            return 0;
        };

        //Now we perform the transformation
        //x looses y and gains a as a neighbour and etc.
        replace_neighbour(x, y, a);
        replace_neighbour(c, e, d);
        //the following transformations are affected if segment (b..f) is empty- here our calculations will result in b = d and f = a
        if (b != d && f != a){ 
            replace_neighbour(y, x, f);
            replace_neighbour(e, c, b);
            replace_neighbour(a, b, x);
            replace_neighbour(b, a, e);
            replace_neighbour(f, d, y);
            replace_neighbour(d, f, c); 
        } else {
            replace_neighbour(e, c, y);
            replace_neighbour(a, d, x);
            replace_neighbour(d, a, c);
            replace_neighbour(y ,x, e);
        }
        return *this;
    }

    int Ordering::print_ordering(){
        size_t prev, current, temp;

        current = 0;
        prev = neighbour_array[2*current + 1];

        do{
            std::cout << current << " ";
            temp = current;
            current = this->next_step(current, prev);
            prev = temp;
        } while (current != 0);

        std::cout << "\n";
        return 0;
    }

    int Ordering::print_neighbours(size_t current){
        std::cout << neighbour_array[2*current] << " " << neighbour_array[2*current + 1] << "\n";
        return 0;
    }
} // namespace HCP
