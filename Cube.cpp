/**
 * @brief Cube class methods
 * 
 * @details
 *          This file implements the cube class member methods;
 *          It consists of the constructor, and a toString method
 *
 * 
 * @author Marco Manuel
 */
#include "Cube.h"
   
/**
 * @brief cube constructor
 * 
 * @details
 *          calculates and sets the max volume, shapeid, and side
 * @param side Side of cube.
 * 
 * @author Marco Manuel
 */
Cube::Cube(float s){
    MaxVolume = s*s*s;
    ShapeID = "Cube";
    side  = s;
}

/**
 * @brief cube toString method
 * 
 * @details
 *          returns string of maxVolume and side
 *          
 * @return returns string of data
 * 
 * @author Marco Manuel
 */
std::string Cube::to_string(){
    return "Type cube with volume: " + std::to_string(MaxVolume) + " and side: " + std::to_string(side);
}

