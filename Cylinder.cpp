/**
 * @brief Cylinder class methods
 * 
 * @details
 *          This file implements the cylinder class member methods;
 *          It consists of the constructor, and a toString method
 * 
 * @author Jerry Iu
 */
#include "Cylinder.h"
   
/**
 * @brief cylinder constructor
 * 
 * @details
 *          calculates and sets the max volume, shapeid, radius, and height
 * @param radius
 * @param height
 * 
 */
Cylinder::Cylinder(float radius, float height){
    Cradius = radius;
    Cheight = height;
    MaxVolume = 3.14*radius*radius*height;
    ShapeID = "Cylinder";
}

/**
 * @brief cylinder toString method
 * 
 * @details
 *          returns string of maxVolume
 *          
 * @return returns string of data
 * 
 */
std::string Cylinder::to_string(){
    return "Type Cylinder with volume: " + std::to_string(MaxVolume);
}
    