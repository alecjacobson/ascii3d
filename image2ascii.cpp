#include "ascii_art.h"
#include "terminal_size.h"
// https://stackoverflow.com/questions/23369503/get-size-of-terminal-window-rows-columns
#include <sys/ioctl.h> //ioctl() and TIOCGWINSZ
#include <unistd.h> // for STDOUT_FILENO
#include <iostream>
#include <cstdio>

void print_image(
  unsigned char * in_pixels,
  int in_w,
  int in_h,
  int in_n)
{
  printf("input is %d by %d by %d \n",in_w,in_h,in_n);
  for(int i = 0;i<in_h;i++)
  {
    for(int j = 0;j<in_w;j++)
    {
      for(int c = 0;c<in_n;c++)
      {
        printf("%03d",in_pixels[c+in_n*(j+in_w*i)]);
      }
      printf(" ");
    }
    printf("\n");
  }
}

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

int main(int argc, char *argv[])
{
  // Read test image
  int in_w,in_h,in_n;
  unsigned char *in_pixels = stbi_load(argv[1], &in_w, &in_h, &in_n, 0);
  if(in_pixels == NULL) {
    return EXIT_FAILURE;
  }
  if(in_n>1)
  {
    // Convert to grayscale (in place)
    assert(in_n>=3);
    for(int i = 0;i<in_h;i++)
    {
      for(int j = 0;j<in_w;j++)
      {
        for(int c = 0;c<in_n;c++)
        {
          in_pixels[j+in_w*i] = 
            0.2126*in_pixels[0+in_n*(j+in_w*i)]+
            0.7152*in_pixels[1+in_n*(j+in_w*i)]+
            0.0722*in_pixels[2+in_n*(j+in_w*i)];
        }
      }
    }
  }


  unsigned char * out_pixels;
  int out_w,out_h;
  unsigned char * resize_pixels;
  int resize_w,resize_h;
  char * out_ascii;

  int target_cols;
  int target_rows;
  terminal_size(in_w,in_h,target_cols,target_rows);

  int out_cols,out_rows;
  ascii_art(
    in_pixels,in_w,in_h, target_cols,target_rows,
    &resize_pixels,&resize_w,&resize_h,
    &out_ascii, &out_cols,&out_rows,&out_pixels,&out_w,&out_h);
  //printf("out_ascii: %d by %d\n",out_cols,out_rows);

  for(int i = 0;i<out_rows;i++)
  {
    for(int j = 0;j<out_cols;j++)
    {
      printf("%c",out_ascii[j+out_cols*i]);
    }
    printf("\n");
  }

  stbi_write_png("resize.png", resize_w, resize_h, 1, resize_pixels, 0);
  stbi_write_png("out.png", out_w, out_h, 1, out_pixels, 0);


  stbi_image_free(in_pixels);
  delete[] out_pixels;
  delete[] resize_pixels;
  delete[] out_ascii;
}
