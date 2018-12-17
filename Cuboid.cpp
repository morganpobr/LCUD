/**
 * @brief Cuboid class methods
 * 
 * @details
 *          This file implements the cuboid class member methods;
 *          It consists of the constructor, and a toString method
 * 
 * @author Reid Jackson
 */
#include "Cuboid.h"
   
/**
 * @brief cuboid constructor
 * 
 * @details
 *          calculates and sets the max volume, shapeid, and width, length, and height
 * @param width Width of Cuboid
 * @param length Length of cuboid
 * @param height Heigth of Cuboid
 * 
 */
Cuboid::Cuboid(float width,float length,float height){
    Cwidth = width;
    Clength = length;
    Cheight = height;

    MaxVolume = width*length*height;
    ShapeID = "Cuboid";
}

/**
 * @brief cuboid toString method
 * 
 * @details
 *          returns string of maxVolume
 *          
 * @return returns string of data
 * 
 */
std::string Cuboid::to_string(){
    return "Type Cuboid with volume: " + std::to_string(MaxVolume);
}