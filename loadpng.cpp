#include <iostream>
#include <vector>
#include <cstdlib>
#include "loadpng.h"
#include "lodepng.h"


//Example 1
//Decode from disk to raw pixels with a single function call
std::vector<unsigned char> decodeOneStep(const char* filename, unsigned int *width, unsigned int *height) {
  std::vector<unsigned char> image; //the raw pixels


  //decode
  unsigned error = lodepng::decode(image, width[0], height[0], filename);
//  std::cout<<width<<","<<height<<std::endl;
  std::cout<<width<<","<<height<<std::endl;
  //if there's an error, display it
  if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
  return image;
  //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
}

void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height) {
  //Encode the image
  unsigned error = lodepng::encode(filename, image, width, height);

  //if there's an error, display it
  if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

Matrix *png_read(const char *filename){


    unsigned int *width = nullptr,*height = nullptr;
    width=(unsigned int*)malloc(sizeof(unsigned int));
    height=(unsigned int*)malloc(sizeof(unsigned int));
    width[0]=0;
    height[0]=0;


    std::vector<unsigned char> *image=new std::vector<unsigned char>(width[0]*height[0]*4);

    image[0]=decodeOneStep(filename,width,height);
    Matrix *matrix = nullptr;
    matrix=(Matrix*)malloc(sizeof(Matrix(height[0],width[0]))*4);

    std::vector<float> *red_vector=new std::vector<float>(width[0]*height[0]);
    std::vector<float> *green_vector=new std::vector<float>(width[0]*height[0]);
    std::vector<float> *blue_vector=new std::vector<float>(width[0]*height[0]);
    std::vector<float> *alpha_vector=new std::vector<float>(width[0]*height[0]);
    for (unsigned int i=0;i<image[0].size();i++){
        if (i%4==0){
            red_vector[0][i/4]=image[0][i];
        }else if (i%4==1){
            green_vector[0][i/4]=image[0][i];
        }else if (i%4==2){
            blue_vector[0][i/4]=image[0][i];
        }else if (i%4==3){
            alpha_vector[0][i/4]=image[0][i];
        }
    }
    matrix[0]=Matrix(red_vector[0],height[0],width[0]);
    matrix[1]=Matrix(green_vector[0],height[0],width[0]);
    matrix[2]=Matrix(blue_vector[0],height[0],width[0]);
    matrix[3]=Matrix(alpha_vector[0],height[0],width[0]);
    delete image;
    delete red_vector;
    delete green_vector;
    delete blue_vector;
    delete alpha_vector;
    return matrix;
}

void png_output(const char *filename, Matrix *matrix){
    unsigned int length,colnum,rownum;
    colnum=matrix[0].getcolnum();
    rownum=matrix[0].getrownum();
    length=colnum*rownum*4;
    float **add1,**add2,**add3,**add4;
    add1=matrix[0].getaddress();
    add2=matrix[1].getaddress();
    add3=matrix[2].getaddress();
    add4=matrix[3].getaddress();
    vector<unsigned char> image(length);
    for (unsigned int i=0;i<length;i++){
        if (i%4==0){
            image[i]=(unsigned char)add1[i/4/colnum][(i/4)%colnum];
        }else if (i%4==1){
            image[i]=(unsigned char)add2[i/4/colnum][(i/4)%colnum];
        }else if (i%4==2){
            image[i]=(unsigned char)add3[i/4/colnum][(i/4)%colnum];
        }else if (i%4==3){
            image[i]=(unsigned char)add4[i/4/colnum][(i/4)%colnum];
        }
    }
    encodeOneStep(filename,image,colnum,rownum);
}

unsigned char *png_cache(Matrix *matrix){
    unsigned int length,colnum,rownum;
    colnum=matrix[0].getcolnum();
    rownum=matrix[0].getrownum();
    length=colnum*rownum*4;
    float **add1,**add2,**add3,**add4;
    add1=matrix[0].getaddress();
    add2=matrix[1].getaddress();
    add3=matrix[2].getaddress();
    add4=matrix[3].getaddress();
    unsigned char *image=new unsigned char[length];
    for (unsigned int i=0;i<length;i++){
        if (i%4==0){
            image[i]=(unsigned char)add1[i/4/colnum][(i/4)%colnum];
        }else if (i%4==1){
            image[i]=(unsigned char)add2[i/4/colnum][(i/4)%colnum];
        }else if (i%4==2){
            image[i]=(unsigned char)add3[i/4/colnum][(i/4)%colnum];
        }else if (i%4==3){
            image[i]=(unsigned char)add4[i/4/colnum][(i/4)%colnum];
        }
    }
    return image;
}
