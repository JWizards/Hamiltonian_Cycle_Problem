#include "instance.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace HCP{


    //parsing related functions


    Keyword catch_keyword(std::string a){
        Keyword keyword = NONE;
        try
        {
            keyword = m.at(a);
        }
        catch(const std::exception& e){ }
        return keyword;
    }

    int interpret_line(std::stringstream &ss, std::string & word){
        ss >> word;
        if (word == ":"){
            ss >> word;
            return 0;
        } else 
        return 1;
    }

    int Instance::parse_data(std::ifstream &ifs, Instance &instance){
        std::string a, b, c;
        
        if(instance.edge_weight_type == EXPLICIT){
            while(ifs >> a){
                if(catch_keyword(a) != EOF and stoi(a) != -1){ 
                    instance.explicit_weights.push_back(stoi(a));
                }
            }
        } else {
            while(ifs >> a >> b >> c){
                if(catch_keyword(a) != EOF){
                    instance.coords.push_back(stod(b));
                    instance.coords.push_back(stod(c));
                }
            }
        }
        return 0;
    }


//read TSPLIB function
    int Instance::read_TSPLIB(const std::string & filename, Instance &instance){
        std::ifstream file_stream(filename);
        if (!file_stream.is_open())
           throw std::runtime_error("Could not open input file.");
        
        // some local variables to support parsing of the file
        std::stringstream line_stream;
        std::string key_string, value_string;
        std::string line;

        while(getline(file_stream, line)){
            line_stream.clear();
            line_stream.str(line); //stream the line
            line_stream >> key_string;

            //handle differently formatted problem files.
            if(key_string.back() == ':'){
                line_stream >> value_string;
                key_string.pop_back();
            } else {
                interpret_line(line_stream, value_string);
            }

            Keyword keyword = catch_keyword(key_string);
            switch(keyword){
                case NAME:
                    instance.name = value_string;
                break;
                case TYPE:
                    instance.type = catch_keyword(value_string);
                    break;
                case DIMENSION:
                    instance.dimensions = stoi(value_string);
                    break;
                case EDGE_WEIGHT_TYPE:
                    instance.edge_weight_type = catch_keyword(value_string);
                    break;
                case EDGE_WEIGHT_FORMAT:
                    instance.edge_weight_format = catch_keyword(value_string);
                    break;
                case EDGE_WEIGHT_SECTION:
                    parse_data(file_stream, instance);
                    break;
                case NODE_COORD_SECTION:
                    parse_data(file_stream, instance);
                    break;
                case EOFF:
                case COMMENT: //do nothing
                default:
                    break;    
                // std::cout << "unrecognized keyword: " << word << "\n"; //do nothing 
            }
        }

        return 0;
    }

    // distance related functions

    std::tuple<double, double> Instance::get_coords(size_type i){
        return {this->coords[2*i], this->coords[2*i+1]} ;
    }


    int Instance::dist(size_type i, size_type j){
        i = i % this->dimensions;
        j = j % this->dimensions;
        
        auto[a, b] = this->get_coords(i);
        auto[x, y] = this->get_coords(j);

        auto d = this->dimensions;
        auto at = d*i + j;

        switch(this->edge_weight_type){
            case EUC_2D:
                return euc_2d(a, b, x, y);
                break;
            case CEIL_2D:
                return ceil_2d(a, b, x, y);
                break;
            case EXPLICIT:
                
                switch(this->edge_weight_format){
                    case FULL_MATRIX:
                        at = d*i + j;
                        return this->explicit_weights[at];
                        break;
                    case LOWER_DIAG_ROW:
                        if (j > i){
                            auto temp = j;
                            j = i;
                            i = temp;
                        }
                        at = d*i + j;
                        return this->explicit_weights[at];
                        break;
                    case UPPER_DIAG_ROW:
                        if (i > j){
                            auto temp = j;
                            j = i;
                            i = temp;
                        }
                        at = d*i + j;
                        return this->explicit_weights[at];
                        break;
                    case UPPER_ROW:
                        if (i == j)
                            return 0;
                        if (j < i){
                            auto temp = j;
                            j = i;
                            i = temp;
                        }
                        at = d*i + j;
                        return this->explicit_weights[at];
                        break;
                    
                    default:
                    break;
                }
                break;
            default:
                break;   
        }
        return std::numeric_limits<int>::max();
    }
} //namespace HCP

