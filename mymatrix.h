#ifndef MYMATRIX_H
#define MYMATRIX_H

#include <iostream>
#include "string"
#include <vector>
#include <cstdlib>
#include <complex>
#include <valarray>
#include <math.h>
using namespace std ;


// PI constant
const double PI = 3.14192653589793238460;
//using type complex due to the nature of the FFT function. double for higher precision
typedef complex<double> Complex;
//using valarray because its easier to deal with in the recursive function (creating subsets)
typedef valarray<Complex> Complex_Array;

void fft(Complex_Array& x) ;
void _ifft(Complex_Array& x) ;
void ifft(Complex_Array& x) ;

struct Point{
    int x ;
    int y ;
};

void sortPoints(vector<Point> & arr);

class Matrix{
public:

    Matrix(); // m * n matrix
    void freeMatrix();
    Matrix(unsigned int rownum, unsigned int colnum);
    Matrix(vector<vector<int>> &vec);
    Matrix(vector<vector<float>> &vec);
    Matrix(vector<float> &vec, unsigned int rownum, unsigned int colnum);
    float **getaddress();
    unsigned int getcolnum();
    unsigned int getrownum();
    std::string toString();
    float mean();                       // return the mean value of the matrix
    float maximum();
    float minimum();
    float norm();
    Matrix(std::string symbol,  unsigned int n);
    float det();
    void subMatrix(int );
    Matrix Mask(Matrix mask);
   // Matrix(std::string symbol,  unsigned int n); // special matrix like I , O matrix
   /* ~Matrix();

    int norm() ;                      // return the norm of the matrix
    std::vector<int> size(Matrix m);  // return the size of the matrix
    int mean();                       // return the mean value of the matrix
    int maximum();
    int minimum();
    std::string toString();

    int getEntry(std::vector<int> index) ;    // retunr the entry by index
    int setEntry(std::vector<int> index, int element);  // reset the entry
    std::vector<int> getRow(int row);                   // get a row
    std::vector<int> getColumn(int col);                // get a column

    std::vector<std::vector<int>> eigenvector();
    std::vector<int> eigenvalue();


    friend std::ostream & operator<<(std::ostream &os, Matrix M);
    //friend std::istream & operator>>(std::istream &os, Matrix M);*/
    Matrix trans();                             // return the transposed matrix
    friend Matrix operator+(Matrix m1,Matrix m2);   // +
    friend Matrix operator-(Matrix m1,Matrix m2);    // -
    friend Matrix operator*(Matrix m1,Matrix m2);
  //  friend Matrix operator/(Matrix m1,Matrix m2);
    friend bool operator==(Matrix m1,Matrix m2); // ==
    friend bool operator!=(Matrix m1,Matrix m2);// !=

    friend Matrix operator^(Matrix m, int p);

    float *operator[](unsigned int p);

    friend std::ostream & operator<<(std::ostream &os, Matrix M);
    Matrix assign();
    Matrix inv();
    Matrix eigenVector() ;
    Matrix eigenValue() ;
    Complex * transform_to_long_vector();
    Matrix perspectiveProject(vector<Point> vec) ;
   // friend bool operator!=(float a, float b) ;

private:
    unsigned int row_num=1;
    unsigned int col_num=1;
    float **address = nullptr;


};

Matrix operator+(Matrix m1,Matrix m2);   // +
Matrix operator-(Matrix m1,Matrix m2);    // -
Matrix operator*(Matrix m1,Matrix m2);   // *
Matrix operator/(Matrix m1,Matrix m2);
bool operator==(Matrix m1,Matrix m2); // ==
bool operator!=(Matrix m1,Matrix m2);
Matrix operator^(Matrix m, int p);
Matrix point_multiply(Matrix m1,Matrix m2);
Matrix point_square(Matrix m, int p);

bool equal(float a, float b);

Matrix *assign(Matrix *m);

class PerspectiveTransform{
public:
   // PerspectiveTransform() ;
    PerspectiveTransform(float inA11, float inA21, float inA31, float inA12,
                         float inA22, float inA32, float inA13, float inA23, float inA33);
    //~PerspectiveTransform();
    void transformPoints(vector<int> &points) ;
    PerspectiveTransform buildAdjoint()  ;
    PerspectiveTransform times(PerspectiveTransform other) ;

private:
    float a11;
    float a12;
    float a13;
    float a21;
    float a22;
    float a23;
    float a31;
    float a32;
    float a33;

};

PerspectiveTransform quadrilateralToQuadrilateral(float x0, float y0, float x1, float y1,
                                                  float x2, float y2, float x3, float y3, float x0p, float y0p, float x1p, float y1p, float x2p, float y2p,
                                                  float x3p, float y3p);

PerspectiveTransform squareToQuadrilateral(float x0, float y0, float x1, float y1, float x2,float y2, float x3, float y3)  ;
PerspectiveTransform quadrilateralToSquare(float x0, float y0, float x1, float y1, float x2,float y2, float x3, float y3) ;



#endif // MYMATRIX_H
