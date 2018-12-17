/**
 * @brief Sensors class methods
 * 
 * @details
 *          This file implements the Sensors class member methods;
 *          It consists of the constructor, the update function,
 *          and a toString method
 *
 * 
 * @author Vance Gullberg
 * @author Marco Manuel
 * @author Morgan O'Brien
 */
#include "Sensors.h"
   
/**
 * @brief Sensors constructor
 * 
 * @details
 *          sets the sensor ID and the file address attribute
 * 
 * @author Vance Gullberg
 */

Sensors::Sensors(){
	int ID = 0;                       //sensorID;
    SensorID = std::to_string(ID);    //convert int to string
    file = "/dev/ttyACM" + SensorID;  //setting file attribute to directory
}

/**
 * @brief updates sensor data
 * 
 * @details
 *          Reads a line of the file, which consists of duration and temperature,
 *          splits it on the space, and stores it in the respective attributes,
 *          thereby updating the information
 *          
 * 
 * @author Marco Manuel
 * @author Morgan O'Brien
 */
void Sensors::update(){
    std::ifstream inFile;
    //open file
    inFile.open(file);
    //if threres a line, read it and split
    std::string line;
    if (getline(inFile, line)){
        //uses string stream to split the line on the space        
        std::stringstream ss(line);
        std::string duration;
        getline(ss,duration, ' ');
        std::string temperature;
        getline(ss,temperature,' ');

        //if there is data, set attributes accordingly
        if(!duration.empty() && !temperature.empty()){
            SDuration = stof(duration);
            STemperature = stof(temperature);
        }
    }
    inFile.close();
}

/**
 * @brief Sensors toString method
 * 
 * @details
 *          returns string of sensor ID, current duration, and temperature
 *          
 * @return returns string of data
 * 
 * @author Vance Gullberg
 */
std::string Sensors::to_string(){
    return "Sensor number "+SensorID+" currently has duration "+std::to_string(SDuration)+" and temperature "+std::to_string(STemperature);
}