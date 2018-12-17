#ifndef CONTAINER_H
#define CONTAINER_H
#include "Sensors.h"

/** 
 *  @brief      The Container class.
 *
 *  @details    This class is the parent class for the containers that will inherit the same basic attributes.
 *              Since each shape that can be utilized will have different ways of calculating volume (in other
 *              words, a cube and a cylinder do not share the same geometric properties), this class will be 
 *              inherited such that each sub-class will have an attributed sensor, a maximum possible volume,
 *              and a string that identifies the specific shape. 
 * 
 *  @author     Vance Gullberg
 */ 
class Container{
    protected:
        Sensors s;
        float MaxVolume;
        std::string ShapeID;
    public:
        Container(){}        // The constructor
        ~Container(){;}     // The destructor method

        /**
         *  @brief      The getter method for the max volume.
         *  @return     the MaxVolume attribute.
         */
        float getMaxVolume(){return MaxVolume;}     

        /**
         *  @brief      The getter method for the type of container.
         *  @return     the ShapeID attribute.
         */
        std::string getShapeID(){return ShapeID;}   

        /** 
         *  @brief      The getter method for the Sensors object attatched to this container.
         *  @return     the Sensors attribute s.
         */
        Sensors returnSensor(){return s;}
};
#endif
