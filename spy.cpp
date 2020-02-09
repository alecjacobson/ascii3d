
#include "ascii_art.h"
#include "terminal_size.h"
#include <igl/read_triangle_mesh.h>
#include <igl/cotmatrix.h>
#include <iostream>
#include <cstdio>

void spy(
  const Eigen::SparseMatrix<double> & L,
  const int w,
  const int h,
  Eigen::Matrix<unsigned char,Eigen::Dynamic,Eigen::Dynamic, Eigen::RowMajor> & S)
{
  Eigen::MatrixXd Sd = Eigen::MatrixXd::Zero(h,w);
  // Iterate over outside of A
  for(int k=0; k<L.outerSize(); ++k)
  {
    // Iterate over inside
    for(Eigen::SparseMatrix<double>::InnerIterator it (L,k); it; ++it)
    {
      Sd(it.row()*h/L.rows(),it.col()*w/L.cols()) = 1;
    }
  }
  const double m = Sd.maxCoeff();
  S = (255.0 - Sd.array()*255.0/m).cast<unsigned char>();
};



int main(int argc, char *argv[])
{
  Eigen::MatrixXd V;
  Eigen::MatrixXi F;
  igl::read_triangle_mesh(argv[1],V,F);
  Eigen::SparseMatrix<double> L;
  igl::cotmatrix(V,F,L);

  int target_cols;
  int target_rows;
  terminal_size(L.cols(),L.rows(),target_cols,target_rows);
  Eigen::Matrix<unsigned char,Eigen::Dynamic,Eigen::Dynamic, Eigen::RowMajor> S;

#include "CourierNewB.h"
  spy(L,target_cols*CourierNewB_w,target_rows*CourierNewB_h,S);

  //unsigned char * out_pixels = new unsigned char[S.cols() * S.rows()];
  char * out_ascii = new char[target_cols * target_rows];

  ascii_art(S.data(),S.cols(),S.rows(),out_ascii,target_cols,target_rows,NULL);

  for(int i = 0;i<target_rows;i++)
  {
    for(int j = 0;j<target_cols;j++)
    {
      printf("%c",out_ascii[j+target_cols*i]);
    }
    printf("\n");
  }

  delete[] out_ascii;
}
