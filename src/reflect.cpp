#include <Eigen/Core>

Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n)
{
  // 
  //         Λ      
  //   Λ     |     /
  //    \    |    /
  // out \   |n  / in
  //      \  |  /
  //       \ | /
  //        \|v
  // ========O========
  // 
  // OR equivalently...
  //
  //         Λ      
  //   Λ     |      
  //    \    |     
  // out \   |n      
  //      \  |   
  //       \ |  
  //        \| 
  // ========O========
  //        /|
  //       / |
  //   in /  | (in⋅n)n
  //     /   |
  //    /    |
  //   v     v
  return in - 2.0*(in.dot(n))*n;
}
