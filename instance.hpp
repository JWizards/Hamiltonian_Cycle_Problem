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

namespace HCP // for Hamiltonian Cycle Problem
{

   using size_type = std::size_t;
   // Keywords to parse TSPLIB format
   enum Keyword{
         NAME,                
         TYPE,                
         TSP,                 
         ATSP,                
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
         EDGE_WEIGHT_SECTION, 
         NODE_COORD_SECTION,  
         EOFF, //Extra f on EOF,
         NONE // C++ special enumeration can be refered to as '{}'                    
   };

   //Keywords
   const std::map<std::string, Keyword> m = {
      {"NAME",                 NAME},
      {"TYPE",                 TYPE},
      {"TSP",                  TSP},
      {"ATSP",                 ATSP},
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
      {"EDGE_WEIGHT_SECTION",  EDGE_WEIGHT_SECTION},
      {"NODE_COORD_SECTION",   NODE_COORD_SECTION},
      {"EOF",                  EOFF}
  };


   class Tour {
      public:
         int print_into(const std::string &filename);
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
      static int read_TSPLIB(const std::string & filename, Instance &);
      static int parse_data(std::ifstream &ifs, Instance &instance);
      std::string get_name() const;
      size_type get_coords() const;
      size_type get_dimension() const;

      Instance() = default;

      friend std::ostream & operator<<(std::ostream & str, Instance const & Instance);
   private:
      std::string name = "";
      HCP::Keyword type = NONE;
      size_type dimensions = 0;
      Keyword edge_weight_type = NONE;
      Keyword edge_weight_format = NONE; 
      std::vector<double> coords;
      std::vector<int> explicit_weights;
   }; // class Instance

   //BEGIN: Inline section
   inline std::string Instance::get_name() const {
      return this->name;
   }

   inline size_type Instance::get_coords() const {
      return this->coords.size();
   }

   inline size_type Instance::get_dimension() const {
      return this->dimensions;
   }


//END: Inline section
} // namespace ED