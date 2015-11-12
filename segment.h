#ifndef SEGMENT_H
#define SEGMENT_H


#include <iostream>
#include <string>
#include <vector>
typedef struct segment {
  int starting; // the starting address
  int ending; // the ending address
  std::string url;
  std::vector<int> range; // the range of starting and ending addresses 

} segment;

#endif
