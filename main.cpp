// https://stackoverflow.com/questions/23369503/get-size-of-terminal-window-rows-columns
#include <sys/ioctl.h> //ioctl() and TIOCGWINSZ
#include <unistd.h> // for STDOUT_FILENO
#include <iostream>
#include <cstdio>

#include <Eigen/Core>
// Inputs:
//   Z  height by width target grayscale image
//   nrows  number of rows of output (-1 indicates maintain aspect ratio) 
//   ncols  number of columns of output (-1 indicates maintain aspect ratio) 
// Outputs:
void ascii_art(
  const Eigen::Matrix<unsigned char,Eigen::Dynamic,Eigen::Dynamic> & Z,
  const int nrows,
  const int ncols,
  Eigen::Matrix<unsigned char,Eigen::Dynamic,Eigen::Dynamic> & ascii,
  Eigen::Matrix<unsigned char,Eigen::Dynamic,Eigen::Dynamic> & ZZ)
{
}

int main(int argc, char *argv[])
{
  // Get size of terminal window
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  int nrows = size.ws_row;
  int ncols = size.ws_col;
  printf("Terminal is %d by %d\n",ncols,nrows);




}
