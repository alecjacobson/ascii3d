#include "ascii_art.h"
#include "terminal_size.h"
//#include "Camera.h"
//#include <igl/read_triangle_mesh.h>
//
//
//int main(int argc, char *argv[])
//{
//  Eigen::MatrixXd V;
//  Eigen::MatrixXi F;
//  igl::read_triangle_mesh(argv[1],V,F);
//
//  const Eigen::RowVector3d center = 
//    0.5*(V.colwise().maxCoeff() + V.colwise().minCoeff());
//  V.rowwise() -= center;
//  V /= V.rowwise().norm().maxCoeff();
//
//  Camera camera;
//  e = Eigen::RowVector3d(0,0,3);
//  
//}

#include "Object.h"
#include "Camera.h"
#include "Light.h"
#include "read_json.h"
#include "write_ppm.h"
#include "viewing_ray.h"
#include "raycolor.h"
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <vector>
#include <iostream>
#include <memory>
#include <limits>
#include <functional>

// https://stackoverflow.com/questions/421860/capture-characters-from-standard-input-without-waiting-for-enter-to-be-pressed
#include <unistd.h>
#include <termios.h>
char getch() 
{
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

int main(int argc, char * argv[])
{
  Camera camera;
  std::vector< std::shared_ptr<Object> > objects;
  std::vector< std::shared_ptr<Light> > lights;
  {
    std::string path = argv[1];
    std::string extension;
    {
      std::string dir,base,file;
      igl::pathinfo(path,dir,base,extension,file);
    }
    if(extension == "json")
    {
      // Read a camera and scene description from given .json file
      read_json(
        argc<=1?"../data/sphere-and-plane.json":argv[1],
        camera,
        objects,
        lights);
    }else
    {

      
      // Otherwise, assume it's a mesh format
      std::shared_ptr<TriangleSoup> soup(new TriangleSoup());
      if(!igl::read_triangle_mesh(path,soup->V,soup->F)) { return EXIT_FAILURE; }
      const Eigen::RowVector3d center = 
        0.5*(soup->V.colwise().maxCoeff() + soup->V.colwise().minCoeff());
      soup->V.rowwise() -= center;
      soup->V /= 2.0*soup->V.rowwise().norm().maxCoeff();
      igl::per_vertex_normals(soup->V,soup->F,soup->N);
      //igl::per_face_normals(soup->V,soup->F,soup->N);
      soup->ei.init(soup->V.cast<float>(),soup->F);
      objects.push_back(soup);
      // Default lights and floor and materials and camera
      std::shared_ptr<Plane> plane(new Plane());
      plane->point = soup->V.colwise().minCoeff().transpose();
      plane->normal = Eigen::Vector3d(0,1,0);
      objects.push_back(plane);
      std::shared_ptr<Material> plane_mat(new Material());
      plane_mat->ka = Eigen::Vector3d(0.7,0.7,0.7);
      plane_mat->kd = Eigen::Vector3d(0.2,0.2,0.2);
      plane_mat->ks = Eigen::Vector3d(0.0,0.0,0.0);
      plane_mat->km = Eigen::Vector3d(0.0,0.0,0.0);
      plane_mat->phong_exponent = 20;
      plane->material = plane_mat;
      std::shared_ptr<Material> soup_mat(new Material());
      soup_mat->ka = Eigen::Vector3d(0.1,0.1,0.1);
      soup_mat->kd = Eigen::Vector3d(0.3,0.3,0.3);
      soup_mat->ks = Eigen::Vector3d(0.8,0.8,0.8);
      soup_mat->km = Eigen::Vector3d(0.0,0.0,0.0);
      soup_mat->phong_exponent = 1000;
      soup->material = soup_mat;
      const Eigen::MatrixXd light_directions = 
        (Eigen::MatrixXd(3,3)<<0,-0.4,-1,-0.2,-0.2,-1,0.2,-0.2,-1).finished();
      for(int l = 0;l<light_directions.rows();l++)
      {
        std::shared_ptr<DirectionalLight> light(new DirectionalLight());
        light->I = Eigen::Vector3d(1,1,1);
        light->d = light_directions.row(l).transpose();
        lights.push_back(light);
      }
      camera.e = Eigen::Vector3d(0,0,6);
      camera.v = Eigen::Vector3d(0,1,0);
      camera.w = -Eigen::Vector3d(0,0,-1);
      camera.u = camera.v.cross(camera.w);
      camera.height = 0.5;
      camera.d = 3;
    }
  }

#include "CourierNewB.h"
  int target_cols,target_rows;
  terminal_size(target_cols,target_rows);

  Eigen::Matrix<unsigned char,Eigen::Dynamic,Eigen::Dynamic, Eigen::RowMajor> 
    S(target_rows*CourierNewB_h,target_cols*CourierNewB_w);
  camera.width = camera.height*S.cols()/S.rows();
  
  char * out_ascii = new char[target_cols * target_rows];

  const auto draw_frame = [&]()
  {
    // For each pixel (i,j)
    for(unsigned i=0; i<S.rows(); ++i) 
    {
      for(unsigned j=0; j<S.cols(); ++j)
      {
        // Set background color
        Eigen::Vector3d rgb(1,1,1);

        // Compute viewing ray
        Ray ray;
        viewing_ray(camera,i,j,S.cols(),S.rows(),ray);
        
        // Shoot ray and collect color
        raycolor(ray,1.0,objects,lights,0,rgb);

        // Write double precision color into image
        auto clamp = [](double s){ return std::max(std::min(s,1.0),0.0);};
        S(i,j) = 
          0.2126*255.0*clamp(rgb(0))+
          0.7152*255.0*clamp(rgb(1))+
          0.0722*255.0*clamp(rgb(2));
      }
    }

    stbi_write_png("out.png", S.cols(), S.rows(), 1, S.data(), 0);
    // Write ascii starting at top of page
    printf("\033[0;0H");
    ascii_art(S.data(),S.cols(),S.rows(),out_ascii,target_cols,target_rows,NULL);
    for(int i = 0;i<target_rows;i++)
    {
      for(int j = 0;j<target_cols;j++)
      {
        printf("%c",out_ascii[j+target_cols*i]);
      }
      printf("\n");
    }
  };

  const auto orbit = [&](double angle, const Eigen::Vector3d & axis)
  {
    camera.e = (Eigen::AngleAxisd(angle,axis)*camera.e).eval();
    camera.u = (Eigen::AngleAxisd(angle,axis)*camera.u).eval();
    camera.v = (Eigen::AngleAxisd(angle,axis)*camera.v).eval();
    camera.w = (Eigen::AngleAxisd(angle,axis)*camera.w).eval();
    for(auto light : lights)
    {
      std::shared_ptr<DirectionalLight>  dir_light = std::dynamic_pointer_cast<DirectionalLight> (light);
      if(dir_light)
      {
        dir_light->d = (Eigen::AngleAxisd(angle,axis)*dir_light->d).eval();
      }
    }

  };

  while(true)
  {
    draw_frame();
    bool exit = false;
    const char key = getch();
    switch(key)
    {
      case 'Q':
      case 'q':
        exit = true;
        break;
      case 'h':
        orbit( 1./60.*M_PI,Eigen::Vector3d::UnitY());
        break;                                                  
      case 'l':                                                 
        orbit(-1./60.*M_PI,Eigen::Vector3d::UnitY());
        break;
      case 'j':
        orbit(-1./60.*M_PI,camera.u);
        break;
      case 'k':
        orbit( 1./60.*M_PI,camera.u);
        break;
      case 'J':
        camera.e *= 0.80;
        break;
      case 'K':
        camera.e *= 1.25;
        break;
      default:
        printf("Unknown key: %c (%d)\n",key,int(key));
        break;
    }
    if(exit) break;
  }
  

  delete[] out_ascii;
}
