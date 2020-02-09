#ifndef TERMINAL_SIZE_H
#define TERMINAL_SIZE_H
// https://stackoverflow.com/questions/23369503/get-size-of-terminal-window-rows-columns
#include <sys/ioctl.h> //ioctl() and TIOCGWINSZ
#include <unistd.h> // for STDOUT_FILENO

// Given an in_w by in_h image determine how many columns and rows of text will
// fit to the current terminal screen.
//
// Inputs:
//   in_w  width of input image
//   in_h  height of input image
// Outputs:
//   target_cols  fit-to-screen number of columns
//   target_rows  fit-to-screen number of rows
// Returns true iff could determine screen size
bool terminal_size(
  const int in_w,
  const int in_h,
  int & target_cols, 
  int & target_rows)
{
  // Get size of terminal window
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  // Minus one for the command line
  int nrows = size.ws_row-1;
  int ncols = size.ws_col;

  if(ncols == 0 || nrows == 0)
  {
    target_cols = 80;
    // Let ascii_art figure out the number of rows to use
    target_rows = -1;
    return false;
  }

#include "CourierNewB.h"
  const double aspect_ratio = double(CourierNewB_w)/double(CourierNewB_h);
  target_cols = ncols;
  target_rows = int(double(target_cols)*double(in_h)/double(in_w)*aspect_ratio);
  if(target_rows>nrows)
  {
    target_rows = nrows;
    target_cols = int(double(target_rows)*double(in_w)/double(in_h)/aspect_ratio);
  }
  return true;
}

bool terminal_size(
  int & target_cols, 
  int & target_rows)
{
  // Get size of terminal window
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  // Minus one for the command line
  target_rows = size.ws_row-1;
  target_cols = size.ws_col;
  if(target_cols == 0 || target_rows == 0)
  {
    target_cols = 80;
    // Let ascii_art figure out the number of rows to use
    target_rows = -1;
    return false;
  }
  return true;
}
#endif
