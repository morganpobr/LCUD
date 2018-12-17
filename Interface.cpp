//g++ -o main_interface Interface.cpp Cube.cpp Cylinder.cpp Cuboid.cpp Sensors.cpp -L/usr/include/mysql -lmysqlclient -I/usr/include/mysql

/** 
 *  @brief      The implementatio of the Interface program.
 *
 *  @details    This program starts by either loading a pre-existing container, or creates a new one;
 *              it then reads data from the sensor to determind the volume of the fluid in the container.  
 *              We then periodically take an average of the data, and send it to our database.
 * 
 *  @author     Marco Manuel
 *  @author     Vance Gullberg
 *  @author     Morgan O'Brien
 *  @author     Jerry Iu 
 *  @author     Joon Lee
 *  @author     Reid Jackson
 */ 

#include "Interface.h"

ifstream inFile;    // The text file that will contain the container information

// Variables to connect to the MYSQL server
MYSQL mysql,*connection;
//MYSQL_RES result; 
//MYSQL_ROW row;
char * ip = (char*)"127.0.0.1";
char * usr = (char*)"root";
char * pass = (char*)"group10";
char * db = (char*)"group10";

int query_state;    // ? doesn't look like its used

// Global variables that will be used to send data to the database
float avgVolume;    // The average volume of 10 sensor "reads"
float avgDistance;  // The average distance of 10 sensor "reads"
float avgLevel;     // The average level of 10 sensor "reads"
int counter = 0;    // The counter variable, once it reaches 10, we collect the average of the sensor reads


/** 
 *  @brief      The main method of the program
 *
 *  @details    This method first checks to see if there is a text file that contains info on a container. If such a file exists, then
 *              create a container object from that file, otherwise prompt the user to enter information about the container using one 
 *              of the create<shape>() functions. From there use the container object to calculate the volume of the fluid and send the
 *              data to the database using the appropriate <shape>func() functions.
 */ 
int main(){
    string shape;
    inFile.open("data.txt");

    //If the file exists then read from the file
    if(inFile){
        getline(inFile,shape);

        // If the shape of the container is a cube
        if(shape.compare("CUBE") == 0){
            string side;
            getline(inFile,side);
            
            // In case the file exists but the line containing the dimensions is empty, inform the user of the problem and have them enter the info again
            if(side.empty()){
                remove("data.txt");
                cout << "Error in configuration file, pointing you to create a new Cube!" << endl;
                Cube cube = createCube();
                CubeFunc(cube); //The calculation function
            }

            else{
                float s = stof(side);
                Cube cube (s);
                CubeFunc(cube); //The calculation function
            }
            
        }

        // If the shape of the container is a cylinder
        else if(shape.compare("CYLINDER") == 0){
            string radius;
            getline(inFile,radius);
            string height;
            getline(inFile,height);

            // In case the file exists but the line containing the dimensions is empty, inform the user of the problem and have them enter the info again
            if(radius.empty() || height.empty()){
                remove("data.txt");
                cout << "Error in configuration file, pointing you to create a new Cylinder!" << endl;
                Cylinder cylinder = createCylinder();
                CylinderFunc(cylinder); //The calculation function

            }

            else {
                float r = stof(radius);
                float h = stof(height);
                cout << "Set values";
                Cylinder cylinder (r,h);
                cout << "Value Created";   
                CylinderFunc(cylinder); //The calculation function
            }
        }

        // If the shape of the container is a cuboid
        else if (shape.compare("CUBOID") == 0){
            string width;
            getline(inFile,width);
            string length;
            getline(inFile,length);
            string height;
            getline(inFile,height);

            // In case the file exists but the line containing the dimensions is empty, inform the user of the problem and have them enter the info again
            if(width.empty() || length.empty() || height.empty()){
                remove("data.txt");
                cout << "Error in configuration file, pointing you to create a new Cylinder!" << endl;
                Cuboid cuboid = createCuboid();
                CuboidFunc(cuboid); //The calculation function
            }

            else{
                float w = stof(width);
                float l = stof(length);
                float h = stof(height);
                Cuboid cuboid (w,l,h);
                CuboidFunc(cuboid); //The calculation function
            }
            
        }
    }

    //If the file doesn't exist, then have the user enter the info for the container
    else{
        ofstream outFile;
        outFile.open("data.txt");
        string shape;

        //Have the user enter the desired shape they want
        cout << "Please enter the shape of the container" << endl;
        cin >> shape;
        
        //Change the case of all the letters to uppercase
        for (int i=0; i<shape.length(); i++)
            shape[i] = toupper(shape[i]);

        //If the user chose cube
        if(shape.compare("CUBE") == 0){
            Cube cube = createCube();
            float side = cube.getCubeSide();
            outFile << shape + "\n";
            outFile << to_string(side) + "\n";
            outFile.close();
            CubeFunc(cube);
        }

        //If the user chose cylinder
        else if(shape.compare("CYLINDER") == 0){
            Cylinder cylinder = createCylinder();
            float height = cylinder.getCylinderHeight();
            float radius = cylinder.getCylinderRadius();
            outFile << shape + "\n";
            outFile << to_string(radius) + "\n";
            outFile << to_string(height) + "\n";
            outFile.close();
            CylinderFunc(cylinder);
        }

        //If the user chose cuboid
        else if(shape.compare("CUBOID") == 0){
            Cuboid cuboid = createCuboid();
            float length = cuboid.getCuboidLength();
            float width = cuboid.getCuboidWidth();
            float height = cuboid.getCuboidHeight();
            outFile << shape + "\n";
            outFile << to_string(width) + "\n";
            outFile << to_string(length) + "\n";
            outFile << to_string(height) + "\n";
            outFile.close();
            CuboidFunc(cuboid);
        }

        //If the shape is not valid
        else{
            cout << "Invalid shape" << endl;
        }

    }

    return 0;
}

/**
 *  @brief      Creates a new Cube object from user input.
 *  @return     the created Cube object.
 */
Cube createCube(){
    string input;
    cout << "Please enter the length for the sides of the cube (cm):" << endl;
    cin >> input;
    float side = stof(input);
    Cube cubeObj (side);
    return cubeObj;
}

/**
 *  @brief      Creates a new Cylinder object from user input.
 *  @return     the created Cylinder object.
 */
Cylinder createCylinder(){
    string inputR;
    cout << "Please enter the radius of the cylinder (cm):" << endl;
    cin >> inputR;
    string inputH;
    cout << "Please enter the height of the cylinder (cm):" << endl;
    cin >> inputH;
    float radius = stof(inputR);
    float height = stof(inputH);
    Cylinder cylObj (radius,height);
    return cylObj;    
}

/**
 *  @brief      Creates a new Cuboid object from user input.
 *  @return     the created Cuboid object.
 */
Cuboid createCuboid(){
    string inputW;
    cout << "Please enter the width of the cuboid (cm):" << endl;
    cin >> inputW;
    string inputL;
    cout << "Please enter the length of the cuboid (cm):" << endl;
    cin >> inputL;
    string inputH;
    cout << "Please enter the height of the cuboid (cm):" << endl;
    cin >> inputH;
    float width = stof(inputW);
    float length = stof(inputL);
    float height = stof(inputH);
    Cuboid cuboidObj (width,length,height);
    return cuboidObj;
}

/** 
 *  @brief      Calculates volume data from sensor information and sends average to the database.
 *
 *  @details    This function takes in a Cube object, uses the sensor connected to the container to get the duration and temperature. From
 *              there we calculate the level of the fluid and the volume. Every 10 times the information is calculated, the function averages
 *              this data, creates an SQL query and sends the query to the database.
 * 
 *  @param      c   The Cube container that will be measured 
 */ 
void CubeFunc(Cube c){
    Sensors s = c.returnSensor();

    //Output information about the sensor and container
    cout<< "Sensor ID: " + s.getSensorID() << endl;
    cout << "Vessel has maximum volume of: " + to_string(c.getMaxVolume()) << endl;
    cout << "This is a " + c.getShapeID() << endl;
    cout << "It has a side of: " + to_string(c.getCubeSide()) << endl;

    //Connect to the database
    mysql_init(&mysql);
    connection = mysql_real_connect(&mysql, ip, usr, pass, db, 0, NULL, 0);

    while(true){
        s.update(); //Get data from the sensor
        //Calculations                                                
        float speedOfSoundM = 331+0.6*s.getTemperature();             
        float speedOfSoundCM = speedOfSoundM*100;                     
        float distance = (s.getDuration()/2/1000000)*speedOfSoundCM;  
        float level = c.getCubeSide() - distance;                     
        float volume = c.getCubeSide()*c.getCubeSide()*level;         

        //In the case that the data retrieved from the sensor is wrong, skip this iteration of the loop
        //This usually occurs when the sensor first starts up or if the sensor is moved
        if(volume >= c.getMaxVolume() || volume < 0){
            continue;
        }
    
        //Output the calculation data
        cout << c.getShapeID()+" Container with a volume of "+ to_string(volume)+" and has a water level of "+to_string(level) <<endl;
        cout <<"\n";

        //Prepare the data to be sent to the database
        avgVolume = avgVolume + volume;
        avgDistance = avgDistance + distance;
        avgLevel = avgLevel + level;
        counter++;

        //After 10 iterations, average the data and send to the MYSQL database
        if(counter == 10){
            avgVolume = avgVolume/counter;
            avgDistance = avgDistance/counter;
            avgLevel = avgLevel/counter;

            //If the connection fails, notify the user
            if (connection==NULL){
                cout<<mysql_error(&mysql)<<endl;
            }

            else{
                //Format the averaged data so that it can be sent as an SQL query
                string q = "INSERT into sensor VALUES ('" + s.getSensorID() + "','" + to_string(s.getDuration()) + "','" + to_string(s.getTemperature()) + "','" + to_string(avgDistance) + "','" + to_string(avgVolume) + "','" + to_string(avgLevel) + "','" + to_string((avgLevel/c.getCubeSide())*100) + "','" + c.getShapeID() + "',CURRENT_TIMESTAMP());";
                const char* query = q.c_str();
                //Send query to database  
                mysql_query(connection,query);        
                if (query_state !=0) {
                    cout << mysql_error(connection) << endl;
                }
                //Notify the user that the query has been sent
                cout << "Sending to db\n" << endl;
            }

            //Reset averaged data and counter
            counter = avgVolume = avgDistance = avgLevel = 0;
            
        }
    
    }
    mysql_close(&mysql);
}

/** 
 *  @brief      Calculates volume data from sensor information and sends average to the database.
 *
 *  @details    This function takes in a Cylinder object, uses the sensor connected to the container to get the duration and temperature. From
 *              there we calculate the level of the fluid and the volume. Every 10 times the information is calculated, the function averages
 *              this data, creates an SQL query and sends the query to the database.
 * 
 *  @param      c   The Cylinder container that will be measured 
 */ 
void CylinderFunc(Cylinder c){
    Sensors s = c.returnSensor();

    //Output information about the sensor and container
    cout<< "Sensor ID: " + s.getSensorID() << endl;
    cout << "Vessel has maximum volume of: " + to_string(c.getMaxVolume()) << endl;
    cout << "This is a " + c.getShapeID() << endl;
    cout << "It has a height, radius of: " << to_string(c.getCylinderHeight()) + " cm, " + to_string(c.getCylinderRadius()) + "cm" << endl;

    //Connect to the database
    mysql_init(&mysql);
    connection = mysql_real_connect(&mysql, ip, usr, pass, db, 0, NULL, 0);

    while(true){
       
        s.update();//Get data from the sensor
        //Calculations
        float speedOfSoundM = 331+0.6*s.getTemperature();
        float speedOfSoundCM = speedOfSoundM*100;
        float distance = (s.getDuration()/2/1000000)*speedOfSoundCM;
        float level = c.getCylinderHeight() - distance;
        float volume = (M_PI * c.getCylinderRadius() * c.getCylinderRadius()) * level;

        //In the case that the data retrieved from the sensor is wrong, skip this iteration of the loop
        //This usually occurs when the sensor first starts up or if the sensor is moved
        if(volume >= c.getMaxVolume() || volume < 0){
            continue;
        }

        //Output the calculation data
        cout << c.getShapeID()+" Container with a volume of "+ to_string(volume)+" and has a water level of "+to_string(level) <<endl;
        cout <<"\n";

        //Prepare the data to be sent to the database
        avgVolume = avgVolume + volume;
        avgDistance = avgDistance + distance;
        avgLevel = avgLevel + level;
        counter++;

        //After 10 iterations, average the data and send to the MYSQL database
        if(counter == 10){
            avgVolume = avgVolume/counter;
            avgDistance = avgDistance/counter;
            avgLevel = avgLevel/counter;

            //If the connection fails, notify the user
            if (connection==NULL){
                cout<<mysql_error(&mysql)<<endl;
            }

            else{
                //Format the averaged data so that it can be sent as an SQL query
                string q = "INSERT into sensor VALUES ('" + s.getSensorID() + "','" + to_string(s.getDuration()) + "','" + to_string(s.getTemperature()) + "','" + to_string(avgDistance) + "','" + to_string(avgVolume) + "','" + to_string(avgLevel) + "','" + to_string((avgLevel/c.getCylinderHeight()) * 100) + "','"  + c.getShapeID() + "',CURRENT_TIMESTAMP());";
                const char* query = q.c_str();  
                //Send query to database 
                mysql_query(connection,query);   
                 
                if (query_state !=0) {
                    cout << mysql_error(connection) << endl;
                }
                //Notify the user that the query has been sent
                cout << "Sending to db\n" << endl;
            }

            //Reset averaged data and counter
            counter = avgVolume = avgDistance = avgLevel = 0;
        }
        
    }
    mysql_close(&mysql);
}

/** 
 *  @brief      Calculates volume data from sensor information and sends average to the database.
 *
 *  @details    This function takes in a Cuboid object, uses the sensor connected to the container to get the duration and temperature. From
 *              there we calculate the level of the fluid and the volume. Every 10 times the information is calculated, the function averages
 *              this data, creates an SQL query and sends the query to the database.
 * 
 *  @param      c   The Cuboid container that will be measured 
 */ 
void CuboidFunc(Cuboid c){
    Sensors s = c.returnSensor();

    //Output information about the sensor and container
    cout << "Sensor ID: " + s.getSensorID() << endl;
    cout << "Vessel has maximum volume of: " + to_string(c.getMaxVolume()) << endl;
    cout << "This is a " + c.getShapeID() << endl;
    cout << "It has a height, width and length of: " << to_string(c.getCuboidHeight()) + " cm, " + to_string(c.getCuboidWidth()) + " cm, " + to_string(c.getCuboidLength()) + "cm" << endl;

    //Connect to the database
    mysql_init(&mysql);
    connection = mysql_real_connect(&mysql, ip, usr, pass, db, 0, NULL, 0);

    while(true){
        s.update();//Get data from the sensor
        //Calculations
        float speedOfSoundM = 331+0.6*s.getTemperature();
        float speedOfSoundCM = speedOfSoundM*100;
        float distance = (s.getDuration()/2/1000000)*speedOfSoundCM;
        float level = c.getCuboidHeight() - distance;
        float volume = c.getCuboidLength() * c.getCuboidWidth() * level;

        //In the case that the data retrieved from the sensor is wrong, skip this iteration of the loop
        //This usually occurs when the sensor first starts up or if the sensor is moved
        if(volume >= c.getMaxVolume() || volume < 0){
            continue;
        }

        //Output the calculation data
        cout << c.getShapeID()+" Container with a volume of "+ to_string(volume)+" cm cubed and has a water level of "+to_string(level) <<endl;
        cout <<"\n";

        //Prepare the data to be sent to the database
        avgVolume = avgVolume + volume;
        avgDistance = avgDistance + distance;
        avgLevel = avgLevel + level;
        counter++;

        //After 10 iterations, average the data and send to the MYSQL database
        if(counter == 10){
            avgVolume = avgVolume/counter;
            avgDistance = avgDistance/counter;
            avgLevel = avgLevel/counter;

            //If the connection fails, notify the user
            if (connection==NULL){
                cout<<mysql_error(&mysql)<<endl;
            }

            else{
                //Format the averaged data so that it can be sent as an SQL query
                string q = "INSERT into sensor VALUES ('" + s.getSensorID() + "','" + to_string(s.getDuration()) + "','" + to_string(s.getTemperature()) + "','" + to_string(avgDistance) + "','" + to_string(avgVolume) + "','" + to_string(avgLevel) + "','" + to_string((avgLevel/c.getCuboidHeight())*100) + "','"  + c.getShapeID() + "', CURRENT_TIMESTAMP());";
                const char* query = q.c_str();   
                //Send query to database 
                mysql_query(connection,query);
                if (query_state !=0) {
                    cout << mysql_error(connection) << endl;
                }

                //Notify the user that the query has been sent
                cout << "Sending to db\n" << endl;
            }

            //Reset averaged data and counter
            counter = avgVolume = avgDistance = avgLevel = 0;
        }
    }
    mysql_close(&mysql);
}