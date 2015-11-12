#include <string>
#include <algorithm>
#include <vector>
#include "street_map.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cassert>

using namespace std;

street_map::street_map (const string &filename) {
  // Fill in your code here.
  //
  readmap(filename);
}

bool street_map::geocode(const string &address, string &url) const {  
    string add =address; 
    side Side = parse(add);
    url =  search(Side);
    if (url.size() > 0 ) return true;

}
string street_map::search(side Side)const  {
  std::unordered_map<side,segment>::const_iterator got = mymap.find (Side);
  if ( got == mymap.end() )
    std::cout << "not found";
  else {
    vector<int> rangeV = got->second.range;
    if(std::lower_bound(rangeV.begin(), rangeV.end(), streetNum) != rangeV.end()) {
      string URL = got->second.url; 	
        return URL;
   } else {
        return "";
   }
   }
}

side street_map::parse(string &add) const {

 string snum;  //string version of the street number
 string rest;
 side Side;
  int num;
  istringstream iss(add);
  iss >> snum; 
  num = stoi(snum);
  if (add.size() > snum.size()) {
    rest = add.substr(snum.size()+1, add.size());
    Side.streetname = rest;
  }
  if ((num%2)==0) {
     Side.parity = 0;
  }
  else {
     Side.parity = 1;
  } 
  return Side;
}
void street_map::parseAddress(std::string add) {

   if (add.size() ==0) return;
// here we parse the address into the street number and the actual address part
  string snum;  //string version of the street number
  string rest;// the rest of the string -> after we take the number out
  int num; // the int version of the street address
  istringstream iss(add);
  iss >> snum; //parse the first part into the number
  num = stoi(snum);  //lets get the number too
  if (add.size() > snum.size()) { //it should be... then we will clip the number part off
    rest = add.substr(snum.size()+1, add.size()); //clip the number off and now rest has the address
    mSide.streetname = rest;  //set the street name
  }
  if ((num%2)==0) { //even
    mSide.parity = 0;
  }
  else {
    mSide.parity = 1;
  }
  streetNum = num;
//now search for the address
search();  

}

// You can add any other functions you want to add.
void street_map::readmap (const string &filename) {
//set and open the file and test
  ifstream myfile;
  myfile.open(filename);

  if (!myfile) { cout << "THE FILE IS NOT OPENED WTF " << endl; }

  //declare the side and segment
  side Side;
  segment Segment;


  //for parsing
  string flags;
  string streetname, suffix;
  int par; // for seeing if the parity changed
  bool street = true; // for determinign when the street address has changed
  //getting the first side of the street
  myfile >> flags >> streetname >> suffix;
  Side.streetname = streetname + " " + suffix;
  
  //parsing variables that do not end up ni the struct
  string line;  //for parsing line by line
  int IDstart, IDend;  //for the next project
  double mileage;

  //READ FILE
  while (getline(myfile, line)) {
  
    // SEE WHAT FLAG IS
    istringstream iss(line);
    iss >> flags;  //get the N: or R: so we can proceed

  //THE CASE THAT THERE IS A NEW STREETNAME
    if (!flags.compare("N:")) {
      //remove "N:"
      street = true;
      if (line.size() > 3) {
        //set a new streetname
        Side.streetname = line.substr(3, line.size()); //trim
      }
    }
  
  //HERE WE UPDATE THE UNORDERED MAP
  else if (!flags.compare("R:")) {
  //1. Get the variables
    iss >> Side.parity >> Segment.starting >> Segment.ending >> IDstart >> IDend >> mileage >> Segment.url;
     if (par != Side.parity || street) { //parity changed
	rangeVec.clear();
        par = Side.parity;
      }
     getRange(Segment.starting, Segment.ending); 
     Segment.range = rangeVec;

   //UNORDERED LIST insert every time new street info
   mymap.insert({Side, Segment});
   street = false; // this can no longer be a new street
   }
 }
 rangeVec.clear(); //clear for good measure
 myfile.close();
}
bool street_map::search()  {
  std::unordered_map<side,segment>::const_iterator got = mymap.find (mSide);
  if ( got == mymap.end() )
    std::cout << "not found";
  else {
    rangeVec = got->second.range;
    if(std::find(rangeVec.begin(), rangeVec.end(), streetNum) != rangeVec.end()) {
      return true; 
   } else {
   	return false; 
   }
   }
}


void street_map::getRange(int i, int j) {
  for (int k = i; k < j; k+=2) {
	rangeVec.push_back(k);
  }
  rangeVec.push_back(j); //just in case to be inclusive

}
