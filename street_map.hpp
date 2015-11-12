#ifndef STREET_MAP_HPP
#define STREET_MAP_HPP

#include <string>
#include <unordered_map>
#include "segment.h"
#include "side.h"
#include <vector>


//for hash stuff
template <class T>
inline void hash_combine(std::size_t& seed, const T& v)
{
  std::hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

namespace std {
  template <>
  struct hash<side> {
    std::size_t operator() (side const& p) const {
      std::size_t h = std::hash<string>()(p.streetname);
      hash_combine(h, p.parity);
      return h;
    }
  };
}
//////////// above was for using hash as a key ////////////////////////////////////////////////


class street_map {

public:

  // You need to write implementations of these functions in street_map.cpp.

  // Constructor.
  // `filename` is the pathname of a file with the format described in pg4.pdf.

  explicit street_map (const std::string &filename);

  // Geocodes an address.
  // Input argument:
  //   `address` is an address of the form "1417 E Wayne St"
  // Return value:
  //   `true` if address is found, `false` if address is not found
  // Output argument:
  //   `url` is the URL of an image displaying the street segment
  //   containing the address.

  bool geocode(std::string &address, std::string &url) const;
  void readmap(std::string &filename); // helper function of the constructor that will read in the map
  void parseAddress(std::string add); // for parsing the address
  bool search(); // searches for the address
  void getRange(int, int);//definig a vector of ranges
private:

  // Add any other member variables and functions you want.

  // The main data structure must have a type of the form:
 std::unordered_multimap<side, segment> mymap;
 //I will define right here the number of the current address to search for
 //and the street name
 int streetNum;
 std::string streetName;
 side mSide; //member side variable
 std::vector<int> rangeVec; // range vector
};


#endif
