#ifndef CUBOID_H
#define CUBOID_H
#include "Container.h"

/** 
 *  @brief      The Cuboid class.
 *
 *  @details    This class is a child class of the Container class. Since the shape of this Container is a cuboid
 *              the dimensions are width, length and height. From this we can determine the max possible volume
 *              of the container.
 * 
 *  @author     Reid Jackson
 */ 
class Cuboid : public Container{
    private:
        float Cwidth,Clength,Cheight;
    public:
        Cuboid(float width,float length,float height);  // The function declaration of the constructor
        ~Cuboid(){;}                                    // The destructor method

        std::string to_string();    // Function declaration for the to_string method, which will return a formatted string containing the volume

        /** 
         *  @brief      The getter method for the width of the cuboid.
         *  @return     the Cwidth attribute.
         */
        float getCuboidWidth(){return Cwidth;}

        /** 
         *  @brief      The getter method for the length of the cuboid.
         *  @return     the Clength attribute.
         */
        float getCuboidLength(){return Clength;}

        /** 
         *  @brief      The getter method for the height of the cuboid.
         *  @return     the Cheight attribute.
         */
        float getCuboidHeight(){return Cheight;}
}; 
#endif