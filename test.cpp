#include <string>
#include <cassert>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "segment.h"
#include "side.h"

using namespace std;

int main (int argc, char * argv[]) {
  //set and open the file and test
  ifstream myfile;
  myfile.open("southbend.map");
  if (!myfile) { cout<<"The file did not open properly good sir" <<endl;}
  
  
  //declare the side and segment
  side Side;
  segment Segment; // whole segment

  //for parsing
  string flags; //represents the N: or R:
  string streetname, suffix; //represents the streetname and the "dr" part
  

  //getting the first side of the street
  myfile >> flags >> streetname>>suffix;
  Side.streetname = streetname + " " + suffix;

  //parsing variables that do not end up in the struct
  string line; // for parsing line by line
  int IDstart, IDend; //for next project apparently
  double mileage; 
 
  while (getline(myfile, line)) {
	//see what the flag is 
    istringstream iss(line);
    iss >> flags; // get the N: or R: so we can proceed
    
    //THE CASE HERE IS THAT NEW STREET NAME: WE JUST NEED TO TAKE THE STREETNAME
    if (!flags.compare("N:")) {
        // remove "N:"
        if (line.size() > 3) { 	
        	//set a new streetname
                Side.streetname = line.substr(3, line.size()); 
                
	}
    }

    //THE WE NEED TO UPDATE START AND ENDPOINT AND PARITY
    else if (!flags.compare("R:")) {
      //1.) Get the variables  
  	iss >> Side.parity >> Segment.starting  >> Segment.ending >> IDstart >> IDend >>  mileage >> Segment.url; 	
        cout << mileage << endl;
	
     // now create keys
    }   
  }
  myfile.close();

}
