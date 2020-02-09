#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  assert(
    (num_channels == 3 || num_channels ==1 ) &&
    ".ppm only supports RGB or grayscale images");
  std::ofstream s(filename);
  if(!s.is_open())
  {
    std::cerr<<"Failed to open "<<filename<<std::endl;
    return false;
  }
  switch(num_channels)
  {
    case 3:
    {
      s<<"P3\n"<<
        width <<" "<<height <<"\n"<<
        255<<"\n";
      break;
    }
    case 1:
    {
      s<<"P2\n"<<
        width <<" "<<height <<"\n"<<
        255<<"\n";
      break;
    }
  }
  for(unsigned i=0; i<height; ++i) 
  {
    for(unsigned j=0; j<width; ++j)
    {
      for(unsigned c=0; c<num_channels; ++c)
      {
        s<<(int) data[c+ num_channels*(j + width*i)]<<" ";
      }
    }
    s<<"\n";
  }
  return true;
}
