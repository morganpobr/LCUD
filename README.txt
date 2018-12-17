CS3307 Project Group 10
LCUD - Low Cost Ultrasonic Device
README:


What the LCUD is:

The LCUD is a low-cost, accurate (to 1 mL) ultrasonic and temperature sensor system to remotely measure and track the volume of substances in containers anywhere. An ultrasonic sensor and a temperature sensor are attached to an Arduino microcontroller, which sends readings to a raspberry pi (or any linux computer). The algorithm to compute distance from the sensor to the surface and to compute the volume of a liquid or solid in 3 different container shapes is implemented via our class system in C++. An apache server runs on the pi and we insert the results into a mySQL database using C++. Our interface queries the database which is also on the pi and dynamically displays the measurements as well as the date and time. The measurements on the interface are live and refresh every 15 seconds. //The interface also features a sensor-container setup wizard and a GUI display.


How to run and use the LCUD:

Our Pi must be used (as it has a server and database running on it) with the Arduino and sensors connected. The interface can be seen at the pi’s IP address e.g.: 
192.168.x.x/test/group10/LCUD_Project or can be seen from any internet connection via tunnel using ngrok.io. Then click the “Set Up” button and input the dimensions of your container. To complile the code run g++ -o main_interface Interface.cpp Cube.cpp Cylinder.cpp Cuboid.cpp Sensors.cpp -L/usr/include/mysql -lmysqlclient -I/usr/include/mysql . The code can then be run with ./Interface_main. The interface will automatically refresh every 15 seconds.


How to read the results:

Duration: The time it takes for the ultrasonic particle to bounce off the surface and return to the sensor.
Temperature: Room temperature in degrees celsius.
Distance: Distance from sensor to surface.
Volume: Volume of substance in container
Current Level: Height of substance level.
Percent Full: Amount in % of container that is full.
Shape: Shape of the container.
Date and Time: Current date and time.



Group Members:

Vance Gullberg
Morgan O’Brien
Jerry Iu
Reid Jackson
Joon Lee
Marco Manuel
