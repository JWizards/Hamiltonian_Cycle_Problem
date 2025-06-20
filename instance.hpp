#pragma once

/**
   @file instance.hpp

   @brief This file provides a simple class @c instance to read TSPLIB problem instances.
**/

#include <cstddef> // std::size_t
#include <iosfwd> // std::ostream fwd declare
#include <string>
#include <limits>
#include <vector>
#include <map>
#include <cmath>
#include <cfenv>

namespace HCP // for Hamiltonian Cycle Problem
{
   

   using size_type = std::size_t;
   // Keywords to parse TSPLIB format
   enum Keyword{
         NAME,                
         TYPE,                
         TSP,                 
         ATSP,
         HCP,                
         COMMENT,             
         DIMENSION,           
         EDGE_WEIGHT_TYPE,    
         EUC_2D,              
         CEIL_2D,             
         EXPLICIT,            
         EDGE_WEIGHT_FORMAT,  
         FULL_MATRIX,         
         LOWER_DIAG_ROW,      
         UPPER_DIAG_ROW,      
         UPPER_ROW,
         EDGE_DATA_FORMAT,
         EDGE_LIST,
         ADJ_LIST,           
         EDGE_WEIGHT_SECTION, 
         NODE_COORD_SECTION,
         EDGE_DATA_SECTION,  
         EOFF, //Extra f on EOF,
         NONE // C++ special enumeration can be refered to as '{}'                    
   };

   //Keywords
   const std::map<std::string, Keyword> string_to_Keyword = {
      {"NAME",                 NAME},
      {"TYPE",                 TYPE},
      {"TSP",                  TSP},
      {"ATSP",                 ATSP},
      {"HCP",                  HCP},
      {"COMMENT",              COMMENT},
      {"DIMENSION",            DIMENSION},
      {"EDGE_WEIGHT_TYPE",     EDGE_WEIGHT_TYPE},
      {"EUC_2D",               EUC_2D},
      {"CEIL_2D",              CEIL_2D},
      {"EXPLICIT",             EXPLICIT},
      {"EDGE_WEIGHT_FORMAT",   EDGE_WEIGHT_FORMAT},
      {"FULL_MATRIX",          FULL_MATRIX},
      {"LOWER_DIAG_ROW",       LOWER_DIAG_ROW},
      {"UPPER_DIAG_ROW",       UPPER_DIAG_ROW},
      {"UPPER_ROW",            UPPER_ROW},
      {"EDGE_DATA_FORMAT",     EDGE_DATA_FORMAT},
      {"EDGE_LIST",            EDGE_LIST},
      {"ADJ_LIST",             ADJ_LIST}, 
      {"EDGE_WEIGHT_SECTION",  EDGE_WEIGHT_SECTION},
      {"NODE_COORD_SECTION",   NODE_COORD_SECTION},
      {"EDGE_DATA_SECTION",    EDGE_DATA_SECTION},
      {"EOF",                  EOFF}
  };


/**
   @class Instance
   @brief brief here
   @warning add warning here
**/
   class Instance
   {
   public:
      typedef std::size_t size_type;
      /**
         @brief Creates the Instance from the given file in TSPLIB format.
      **/

      int read_TSPLIB(const std::string &);
      int parse_data(std::ifstream &, HCP::Keyword);
      std::string get_name() const;
      size_type get_dimension() const;
      int dist(size_type, size_type); //cost functions are specified to return integers only
      std::pair<double, double> get_coords(size_type i);

      Instance() = default;
      Instance(const std::string & filename) {read_TSPLIB(filename);}

      friend std::ostream & operator<<(std::ostream & str, Instance const & Instance);
      int print_adjacency_matrix();

   private:
      std::string name = "";
      Keyword type = NONE;
      size_type dimensions = 0;
      Keyword edge_weight_type = NONE;
      Keyword edge_weight_format = NONE;
      Keyword edge_data_format = NONE;
      std::vector<double> coords;
      std::vector<int> explicit_weights;
      std::vector<bool> adjacency_list; //vector<bool> is not a Container and stl algorithms may not work. But it is space efficient improving cache and random access.
      
      int euc_2d(double x, double y, double a, double b);
      int ceil_2d(double x, double y, double a, double b);

   }; // class Instance

//BEGIN: Inline section
   inline std::string Instance::get_name() const {
      return this->name;
   }

   inline size_type Instance::get_dimension() const {
      return this->dimensions;
   }

   inline int Instance::euc_2d(double x, double y, double a, double b){
      std::fesetround(FE_TONEAREST);
      double X = x - a;
      double Y = y - b;
      return std::nearbyint(sqrt((X*X + Y*Y)));
   }

   inline int Instance::ceil_2d(double x, double y, double a, double b){
      std::fesetround(FE_UPWARD);
      double X = x - a;
      double Y = y - b;
      return std::nearbyint(sqrt((X*X + Y*Y)));
   }
   
//END: Inline section
} // namespace ED