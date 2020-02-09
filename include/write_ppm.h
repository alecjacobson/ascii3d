#ifndef WRITE_PPM_H
#define WRITE_PPM_H

#include <vector>
#include <string>

// Write an rgb or grayscale image to a .ppm file.
//
// Inputs:
//   filename  path to .ppm file as string
//   data  width*heigh*num_channels array of image intensity data
//   width  image width (i.e., number of columns)
//   height  image height (i.e., number of rows)
//   num_channels  number of channels (e.g., for rgb 3, for grayscale 1)
// Returns true on success, false on failure (e.g., can't open file)
bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels);

#endif
