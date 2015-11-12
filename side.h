#ifndef SIDE_H
#define SIDE_H


#include <iostream>
#include <string>

typedef struct side {
  int parity;//ie side: 1 is odd and 0 is even
  std::string streetname; // the ending address
  
  // to use an unordered map with a key as the strucct
  bool operator==(const side &other) const {
    return (parity == other.parity && streetname == other.streetname);

  }

} side;

#endif
