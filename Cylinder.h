#ifndef CYLINDER_H
#define CYLINDER_H
#include "Container.h"

/** 
 *  @brief      The Cylinder class.
 *
 *  @details    This class is a child class of the Container class. Since the shape of this Container is a cylinder
 *              the dimensions are radius and height. From this we can determine the max possible volume of the container.
 * 
 *  @author     Jerry Iu
 */      
class Cylinder : public Container{
    private:
        float Cradius, Cheight;
    public:

        Cylinder(float radius, float height);   // The function declaration of the constructor
        ~Cylinder(){;}                          // The destructor method

        std::string to_string();    // Function declaration for the to_string method, which will return a formatted string containing the volume

        /** 
         *  @brief      The getter method for the radius of the cylinder.
         *  @return     the Cradius attribute.
         */
        float getCylinderRadius(){return Cradius;}

        /** 
         *  @brief      The getter method for the height of the cylinder.
         *  @return     the Cheight attribute.
         */
        float getCylinderHeight(){return Cheight;}
};
#endif