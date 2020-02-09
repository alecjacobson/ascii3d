#ifndef ASCII_ART_H
#define ASCII_ART_H
// Inputs:
//   in_pixels  pointer to grayscale input image
//   in_w  width of input
//   in_h  height of input
//   target_cols  number of columns of output (-1 indicates maintain aspect ratio) 
//   target_rows  number of rows of output (-1 indicates maintain aspect ratio) 
// Outputs:
//   resize_pixels  pointer to grayscale resized input image
//   resize_w  width of resized input
//   resize_h  height of resized input
//   out_ascii  out_cols by out_rows array of ascii characters
//   out_cols  number of output columns (==target_cols, unless target_cols=-1)
//   out_rows  number of output columns (==target_rows, unless target_rows=-1)
//   out_pixels  pointer to grayscale output (using cached text images)
//   out_w  width of output
//   out_h  height of output
void ascii_art(
  const unsigned char * in_pixels,
  const int in_w,
  const int in_h,
  /*const*/ int target_cols,
  /*const*/ int target_rows,
  unsigned char ** resize_pixels,
  int * resize_w,
  int * resize_h,
  char ** out_ascii,
  int * out_cols,
  int * out_rows,
  unsigned char ** out_pixels,
  int * out_w,
  int * out_h);
// Version with assuming pre-allocated output memory and perfect sizes.
void ascii_art(
  const unsigned char * in_pixels,
  const int in_w,
  const int in_h,
  char * out_ascii,
  const int out_cols,
  const int out_rows,
  unsigned char * out_pixels);

#endif
