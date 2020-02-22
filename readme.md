# Welcome To FlightGear Simulator Interpreter!
Interpreter for flight gear simulator:
 - This program interpret a text to a code that run the flight gear simulator.
  
 - The commands to fly the airplane is in the "fly.txt" and "fly_with_func.txt" file.
  
 - The following program supports functions, therefore you can run it with fly_with_func file.
  
 - You can compile this program by using the following command:
   "g++ -std=c++11 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread"
   and run it with the command "./a.out file_name" whereas file_name is the name of the text file you
   would like to interpret, for example fly_with_func.txt.
  
 - You should reside the text files along side the main.cpp file (and all the others).
  
 - Moreover, you should open the flightgear simulator and click on: settings->additional settings and write
   the following lines in order to open & conncect to the correct port of open server, port & IP of the connect server:
   --generic=socket,out,10,127.0.0.1,5400,tcp,generic_small   
   --telnet=socket,in,10,127.0.0.1,5402,tcp

 - In addition, you should reside the "generic_small.xml" file in the protocol folder under data of 
   the simulator code (wherever you downloaded it to).
   please make sure that you run the program before entering the simulator to enable right connection flow.
  
Key Features:
1) Sending and Recieving data via socket connection.
2) Multi-Threading implementation.
3) Usage of C++ STL, I/O, Mutex libraries.
4) Usage of OOP Design Patterns: Singleton, Composite Command.
5) Organized work using Github repository.

Link to the project in GitHub:
https://github.com/adi-cohen/flightsimulatorexc

Authors:
Adi Cohen & Yaron Sofer,
BIU University, Israel.

# Have a nice flight!
