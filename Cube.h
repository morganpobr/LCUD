#ifndef CUBE_H
#define CUBE_H
#include "Container.h" 

/** 
 *  @brief      The Cube class.
 *
 *  @details    This class is a child class of the Container class. Since the shape of this Container is a cube
 *              the only measurement we require is side length. From this we can determine the max possible volume
 *              of the container.
 * 
 *  @author     Marco Manuel
 */ 
class Cube : public Container{
    private:
        float side;
    public:
        Cube(float s);  // The function declaration of the constructor
        ~Cube(){;}      // The destructor method

        std::string to_string();            // Function declaration for the to_string method, which will return a formatted string containing the volume and side lengths 

        /** 
         *  @brief      The getter method for the side length of the cube.
         *  @return     the side attribute.
         */
        float getCubeSide(){return side;}
};
#endif
