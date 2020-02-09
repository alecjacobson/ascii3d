#include "ascii_art.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb/stb_image_resize.h"


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
  int * out_h)
{
#include "CourierNewB.h"
  const double aspect_ratio = double(CourierNewB_w)/double(CourierNewB_h);
  if(target_rows == -1)
  {
    assert(target_cols > 0);
    target_rows = int(double(target_cols)*double(in_h)/double(in_w)*aspect_ratio);
  }
  else if(target_cols == -1)
  {
    assert(target_rows > 0);
    target_cols = int(double(target_rows)*double(in_w)/double(in_h)/aspect_ratio);
  }
  *resize_w = target_cols*CourierNewB_w;
  *resize_h = target_rows*CourierNewB_h;

  *resize_pixels = new unsigned char[*resize_w* *resize_h];
  // Resize input to be perfectly the correct size
  stbir_resize_uint8(
    in_pixels,in_w,in_h,0,
    *resize_pixels,*resize_w,*resize_h,0,1);

  *out_w = *resize_w;
  *out_h = *resize_h;
  *out_pixels = new unsigned char[*out_w* *out_h];

  *out_cols = target_cols;
  *out_rows = target_rows;
  *out_ascii = new char[*out_cols * *out_rows];
  return ascii_art(
    *resize_pixels,*resize_w,*resize_h,
    *out_ascii,*out_cols,*out_rows,*out_pixels);
}

void ascii_art(
  const unsigned char * resize_pixels,
  const int resize_w,
  const int resize_h,
  char * out_ascii,
  const int out_cols,
  const int out_rows,
  unsigned char * out_pixels)
{
#include "CourierNewB.h"
  typedef int Scalar;
  const Scalar MAX_ERR = 255*255*CourierNewB_h*CourierNewB_w;
  // Loop over window)s
  // ut
  for(int y = 0;y < out_rows;y++)
  {
    for(int x = 0;x < out_cols;x++)
    {
      Scalar best_err = MAX_ERR;
      int best_z = -1;
      for(int z = 0;z<CourierNewB_count;z++)
      {
        Scalar cur_err = 0;
        // loop within pixels of window
        for(int ci = 0;ci < CourierNewB_h;ci++)
        {
          for(int cj = 0;cj < CourierNewB_w;cj++)
          {
            const int i = ci + y*CourierNewB_h;
            const int j = cj + x*CourierNewB_w;
            unsigned char r = resize_pixels[j + resize_w*i];
            unsigned char c = CourierNewB[z][ci][cj];
            // L2
            cur_err += (r-c)*(r-c);
            // L1
            //cur_err += abs(r-c);
          }
        }
        if(cur_err < best_err)
        {
          best_err = cur_err;
          best_z = z;
        }
      }
      assert(best_z>=0);
      out_ascii[x+out_cols*y] = CourierNewB_str[best_z];
      // loop within pixels of window
      for(int ci = 0;ci < CourierNewB_h;ci++)
      {
        for(int cj = 0;cj < CourierNewB_w;cj++)
        {
          const int i = ci + y*CourierNewB_h;
          const int j = cj + x*CourierNewB_w;
          unsigned char c = CourierNewB[best_z][ci][cj];
          if(out_pixels) out_pixels[j + resize_w*i] = c; 
        }
      }
    }
  }
}
