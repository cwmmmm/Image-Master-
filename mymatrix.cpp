#include "mymatrix.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;


Matrix::Matrix(){
    col_num = 1;     // enter by row by row order
    row_num = 1;
    address=(float**)malloc(sizeof(float*)*row_num);
    for (unsigned int i=0;i<row_num;i++){
        address[i]=(float*)malloc(sizeof(float)*(col_num+1));
    }
    for (unsigned int i=0;i<row_num;i++){
        for (unsigned int j=0;j<col_num+1;j++){
            if (j!=col_num){
                address[i][j]=0;
            }else{
            address[i][j]='\0';}
        }
    }
};

float **Matrix::getaddress(){
    return address;
}

unsigned int Matrix::getcolnum(){
    return col_num;
}
unsigned int Matrix::getrownum(){
    return row_num;
}

void Matrix::freeMatrix(){
    for(unsigned int i=0;i<row_num;i++){
        free(address[i]);
    }
    free(address);
}


Matrix:: Matrix(vector<vector<int>> &vec){
    col_num=vec[0].size();
    row_num=vec.size();
    address=(float**)malloc(sizeof(float*)*row_num);
    for (unsigned int i=0;i<row_num;i++){
        address[i]=(float*)malloc(sizeof(float)*(col_num+1));
    }
    for (unsigned int i=0;i<row_num;i++){
        for (unsigned int j=0;j<col_num+1;j++){
            if (j!=col_num){
                address[i][j]=(float)vec[i][j];

            }else{
            address[i][j]='\0';};
        }
    }

}

Matrix:: Matrix(vector<vector<float>> &vec){
    col_num=vec[0].size();
    row_num=vec.size();
    address=(float**)malloc(sizeof(float*)*row_num);
    for (unsigned int i=0;i<row_num;i++){
        address[i]=(float*)malloc(sizeof(float)*(col_num+1));
    }
    for (unsigned int i=0;i<row_num;i++){
        for (unsigned int j=0;j<col_num+1;j++){
            if (j!=col_num){
                address[i][j]=vec[i][j];

            }else{
            address[i][j]='\0';};
        }
    }
}

Matrix::Matrix(vector<float> &vec, unsigned int rownum, unsigned int colnum){
    col_num=colnum;
    row_num=rownum;
    address=(float**)malloc(sizeof(float*)*row_num);
    for (unsigned int i=0;i<row_num;i++){
        address[i]=(float*)malloc(sizeof(float)*(col_num+1));
    }
    for (unsigned int i=0;i<row_num*col_num;i++){
        address[i/col_num][i%col_num]=vec[i];
    }
}

Matrix::Matrix(unsigned int rownum, unsigned int colnum){
    col_num=colnum;
    row_num=rownum;
    address=(float**)malloc(sizeof(float*)*row_num);
    for (unsigned int i=0;i<row_num;i++){
        address[i]=(float*)malloc(sizeof(float)*(col_num+1));
    }
    for (unsigned int i=0;i<row_num;i++){
        for (unsigned int j=0;j<col_num+1;j++){
            if (j!=col_num){
                address[i][j]=0;

            }else{
            address[i][j]='\0';};
        }
    }
}

Matrix::Matrix(string symbol, unsigned int n){
    col_num=n;
    row_num=n;
    address=(float**)malloc(sizeof(float*)*row_num);
    for (unsigned int i=0;i<row_num;i++){
        address[i]=(float*)malloc(sizeof(float)*(col_num+1));
    }
    // dimension = {row_num, col_num};

    if (symbol == "one"){
        for (unsigned int i = 0 ; i < row_num; i++){
            for (unsigned int j = 0 ; j< col_num; j++){
                if(i == j) {
                    address[i][j] = 1 ;
                //    cout<<"hhh"<<address[i][j]<<endl ;
                } if(i!= j){
                    address[i][j] = 0 ;
                } ;
            };
        };
    };

    if (symbol == "zero"){
        for (unsigned int i = 0 ; i < row_num; i++){
            for (unsigned int j = 0 ; j< col_num; j++){
                    address[i][j] = 0 ;
                } ;
            };
        };
  };



string Matrix::toString(){
    string result = "[";
    for (unsigned int i = 0 ; i < row_num; i++){
        for (unsigned int j = 0 ; j < col_num; j++){
            result = result + to_string(address[i][j]);
            if (j!=col_num-1){
            result = result + "," ;}
            else{if (i!=row_num-1){
                    result+=";";}
            }
        };
        if (i!=row_num-1){
            result+="\n";
        }else{
            result += "]";
        }
    }
    return  result;
};

Matrix operator+(Matrix m1,Matrix m2){
    Matrix m(m1.row_num,m1.col_num);
    if (m1.row_num!=m2.row_num || m1.col_num!=m2.col_num){
        cout<<"m1 do not have same column or row number with m2"<<endl;
    }else{

        for (unsigned int i=0;i<m1.row_num;i++){
            for (unsigned int j=0;j<m1.col_num;j++){
                m.address[i][j]=m1.address[i][j]+m2.address[i][j];
        }
    }}
    return m;
}

Matrix operator-(Matrix m1,Matrix m2){
    Matrix m(m1.row_num,m1.col_num);
    if (m1.row_num!=m2.row_num || m1.col_num!=m2.col_num){
        cout<<"m1 do not have same column or row number with m2"<<endl;
    }else{

        for (unsigned int i=0;i<m1.row_num;i++){
            for (unsigned int j=0;j<m1.col_num;j++){
                m.address[i][j]=m1.address[i][j]-m2.address[i][j];
        }
    }}
    return m;
}

Matrix operator*(Matrix m1,Matrix m2){
    Matrix m(m1.row_num,m2.col_num);
    if (m1.col_num!=m2.row_num){
        cout<<"m1 can not multiply with m2"<<endl;
    }else{
        for (unsigned int i=0;i<m1.row_num;i++){
            for (unsigned int j=0;j<m2.col_num;j++){
                for (unsigned int k=0;k<m2.row_num;k++){
                    m.address[i][j]=m1.address[i][k]*m2.address[k][j]+m.address[i][j];
                }

        }
    }}
    return m;
}


bool operator==(Matrix m1,Matrix m2){
    if (m1.col_num!=m2.col_num || m1.row_num!=m2.row_num){
        return 0;
    }else{
        for (unsigned int i=0;i<m1.row_num;i++){
            for (unsigned int j=0;j<m1.col_num;j++){
                // TODO
                if (~equal(m1.address[i][j],m2.address[i][j])){
                    return 0;}}}}
    return 1;
}

bool operator!=(Matrix m1,Matrix m2){
    if (!(m1==m2)){
        return 1;
    }else{
        return 0;}
}

Matrix operator^(Matrix m, int p){
    if (m.row_num!=m.col_num){
        cout<<"m is not square matrix"<<endl;
        return m;
    }else{
    if (p!=0){
        Matrix result=m.assign();
        if (p>1){
        while (p>1){
            result=result*m;
            p--;
        }
        return result;
        }else {return result;}}                                   //Needs inverse
    else{
        Matrix result("one",m.row_num);
        return result;
    }}
}


Matrix point_multiply(Matrix m1,Matrix m2){
    unsigned int rownum1=m1.getrownum();
    unsigned int colnum1=m1.getcolnum();
    unsigned int rownum2=m2.getrownum();
    unsigned int colnum2=m2.getcolnum();
    float **add1=m1.getaddress();
    float **add2=m2.getaddress();
    Matrix m(rownum1,colnum1);
    float **addm=m.getaddress();
    if (rownum1!=rownum2 || colnum1!=colnum2){
        cout<<"m1 do not have same column or row number with m2"<<endl;
    }else{
        for (unsigned int i=0;i<rownum1;i++){
            for (unsigned int j=0;j<colnum1;j++){
                addm[i][j]=add1[i][j]*add2[i][j];
        }
    }}
    return m;
}

Matrix point_square(Matrix m, int p){
    unsigned int rownum=m.getrownum();
    unsigned int colnum=m.getcolnum();
    float **add=m.getaddress();
    Matrix result=m.assign();
    float **addr=result.getaddress();
    for (unsigned int i=0;i<rownum;i++){
        for (unsigned int j=0;j<colnum;j++){
            for (int k=0;k<p-1;k++){
                addr[i][j]=add[i][j]*addr[i][j];
            }
         }}
    return result;
}

Matrix Matrix::Mask(Matrix mask){
    unsigned int colnum=mask.getcolnum();
    unsigned int rownum=mask.getrownum();
    Matrix m(row_num-rownum+1,col_num-colnum+1);
    float **add=m.getaddress();
    float **addm=mask.getaddress();
    for (unsigned int i=0;i<row_num-rownum+1;i++){
        for (unsigned int j=0;j<col_num-colnum+1;j++){
            for (unsigned int k=0;k<rownum;k++){
                for (unsigned int l=0;l<colnum;l++){
                    add[i][j]=add[i][j]+addm[k][l]*address[k+i][l+j];
                }
            }
        }
    }
    return m;
}

Matrix Matrix::assign(){
    Matrix m(row_num,col_num);
    for (unsigned int i=0;i<row_num;i++){
            for (unsigned int j=0;j<col_num;j++){
                    m.address[i][j]=address[i][j];
                }
        }
    return m;
}

Complex * Matrix::transform_to_long_vector(){

    unsigned int lenght = col_num * row_num ;
    Complex *vec = new Complex[lenght] ;
    float **addr=this->getaddress();
    for (unsigned int i=0;i<row_num;i++){
        for (unsigned int j=0;j<col_num;j++){
            vec[i*col_num + j] = double(addr[i][j]) ; // get the double type of the original matrix
         }};
    return vec ;
};

Matrix Matrix::trans(){
    Matrix m(col_num,row_num);
    for (unsigned int i=0;i<row_num;i++){
            for (unsigned int j=0;j<col_num;j++){
                    m.address[j][i]=address[i][j];
                }
        }
    return m;}



ostream & operator<<(std::ostream & os, Matrix m){
    return os<<m.toString();
};

float Matrix::mean(){
    float sum=0;
    float total_dim = col_num * row_num ;
    for (unsigned int i = 0 ; i < row_num ; i ++){
        for (unsigned int j = 0; j < col_num ; j++){
            sum= sum + address[i][j] ;
            // cout<<"sum is : "<<sum<<endl ;
            };

        };
    return  sum/total_dim ;


};                  // return the mean value of the matrix
float Matrix::maximum(){
    float comp = address[0][0] ;

    for (unsigned int i = 0 ; i < row_num ; i ++){
        for (unsigned int j = 0; j < col_num ; j++){
            if (address[i][j]>comp){
                comp = address[i][j] ;

            };

        };

};
    return  comp  ;
};

float Matrix::minimum(){
    float comp = address[0][0] ;

    for (unsigned int i = 0 ; i < row_num ; i ++){
        for (unsigned int j = 0; j < col_num ; j++){
            if (address[i][j]<comp){
                comp = address[i][j] ;

            };

        };

};
     return  comp  ;
};

float Matrix::norm(){
    float sum=0;
    float total_dim = col_num * row_num ;
    for (unsigned int i = 0 ; i < row_num ; i ++){
        for (unsigned int j = 0; j < col_num ; j++){
            sum= sum + ((address[i][j])*(address[i][j])) ;
            // cout<<"sum is : "<<sum<<endl ;
            };

        };
    return  sum/total_dim ;
};

Matrix Matrix::inv(){

   // First needed to check whether the determinant of the matrix is 0 or not, if it's 0, if it is not 0 then to calculate the invertible matrix
    // considering the order n csae
    Matrix result = Matrix(row_num,col_num);
    cout<<"\n\nInverse of matrix is: \n";
    for(unsigned int i = 0; i < col_num; i++){
        for(unsigned int j = 0; j < 3; j++)
            cout<<((address[(j+1)%3][(i+1)%3] * address[(j+2)%3][(i+2)%3]) - (address[(j+1)%3][(i+2)%3] * address[(j+2)%3][(i+1)%3]))/det()<<"\t";

        cout<<"\n";
    };

    int n = col_num ;
    for(int i=0;i<n;i++)
    {
       for(int j=n;j<2*n;j++)
       {
           if(i==j-n)
              result.address[i][j]=1;
          else
              result.address[i][j]=0;
        }
    }
    for(int i=0;i<n;i++)
    {
       int t=result.address[i][i];
       for(int j=i;j<2*n;j++)
           result.address[i][j]=result.address[i][j]/t;
       for(int j=0;j<n;j++)
       {
          if(i!=j)
          {
             t=result.address[j][i];
             for(int k=0;k<2*n;k++)
                 result.address[j][k]=result.address[j][k]-t*result.address[i][k];
           }
       }
    }

    for(int i=0;i<n;i++)
    {
       for(int j=n;j<2*n;j++)
          cout<<"\t"<<result.address[i][j];
       cout<<"\n";
     }
    return result ;

};

float Matrix::det(){
    float determinant = 0;
    //finding determinant
    for(unsigned int i = 0; i < col_num; i++){
     //   for (unsigned int j = 0 ; j < col_num ; i++){
        determinant = determinant + (address[0][i] * (address[1][(i+1)%3] * address[2][(i+2)%3] - address[1][(i+2)%3] * address[2][(i+1)%3]));
//}
};
    return determinant ;
}

bool equal(float a, float b){
    if ((a-b<float(0.000001) && a-b>=0) || (b-a<float(0.000001) && b-a>=0)){
        return 1;
    }else {
        return 0;
    }
}

float *Matrix::operator[](unsigned int p){
    return address[p];
}


Matrix *assign(Matrix *m){
     Matrix *new_m= new Matrix[4];
     new_m[0]=m[0].assign();
     new_m[1]=m[1].assign();
     new_m[2]=m[2].assign();
     new_m[3]=m[3].assign();
     return new_m;
}

void fft(Complex_Array& x)
{
    size_t N = x.size();
    if (N>1)
    {

        //split elements into even and odd
        Complex_Array even = x[slice(0, N / 2, 2)];
        Complex_Array odd = x[slice(1, N / 2, 2)];

        //apply the recursive function
        fft(even);
        fft(odd);

        //blend both array together
        for (size_t i = 0; i<N / 2; i++)
        {
            Complex t = polar(1.0, -2 * PI*i / N)*odd[i];
            x[i] = even[i] + t;
            x[i + N / 2] = even[i] - t;
        }
    }
}

//concealed recursive function implementing the IFFT based on Cooley/Tukey algorithm. in-place. input array is overwritten.
void _ifft(Complex_Array& x)
{
    size_t N = x.size();
    if (N>1)
    {
        //split elements into even and odd
        Complex_Array even = x[slice(0, N / 2, 2)];
        Complex_Array odd = x[slice(1, N / 2, 2)];

        //apply the recursive function
        _ifft(even);
        _ifft(odd);

        //blend both array together
        for (size_t i = 0; i<N / 2; i++)
        {
            //positive angle instead of negative angle
            Complex t = polar(1.0, 2 * PI*i / N)*odd[i];
            x[i] = even[i] + t;
            x[i + N / 2] = even[i] - t;
        }
    }
}

void ifft(Complex_Array& x)
{
    //call the concealed _ifft function
    _ifft(x);

    size_t N = x.size();
    //loop and divide all elements by N
    for (size_t i = 0; i<N; i++)
    {
        x[i] = x[i] / (double)N;
    }
}

Matrix Matrix::perspectiveProject(vector<Point> vec) {
    int img_height = this->row_num;
    int img_width = this->col_num;


     float dx3 = vec[0].x - vec[1].x + vec[2].x - vec[3].x;
     float dy3 =vec[0].y - vec[1].y + vec[2].y - vec[3].y;

     //
     float a11, a12, a13 , a21, a22, a23, a31, a32, a33 ;






     if (dx3 == 0.0f && dy3 == 0.0f) {



    a11 = vec[1].x -vec[0].x ;
    a12 = vec[2].x -vec[1].x ;
    a13 = vec[0].x ;
    a21 = vec[1].y -vec[0].y ;
    a22 = vec[2].y -vec[1].y ;
    a23 = vec[0].y  ;
    a31 = 0.0f ;
    a32 = 0.0f ;
    a33 = 1.0f ;


     }
     else {
       float dx1 = vec[1].x - vec[2].x;
       float dx2 = vec[3].x - vec[2].x;
       float dy1 = vec[1].y - vec[2].y;
       float dy2 = vec[3].y - vec[2].y;
       float denominator_hhh = dx1 * dy2 - dx2 * dy1;
       float fake_a13 = (dx3 * dy2 - dx2 * dy3) / denominator_hhh;
       float fake_a23 = (dx1 * dy3 - dx3 * dy1) / denominator_hhh;


        a11 = vec[1].x -vec[0].x + fake_a13*vec[1].x; //
        a12 = vec[3].x -vec[0].x + fake_a23*vec[3].x ; //
        a13 = vec[0].x ;//
        a21 = vec[1].y -vec[0].y +fake_a13*vec[1].y ;
        a22 = vec[3].y -vec[0].y + fake_a23*vec[3].y ;
        a23 = vec[0].y  ;
        a31 = fake_a13 ;
        a32 = fake_a23 ;
        a33 = 1.0f ;}



       // get the whole transform  Q to S
        float A11 = a22 * a33 - a23 * a32 ;
        float A12 =  a23 * a31 - a21 * a33 ;
        float A13 =  a21 * a32 - a22 * a31 ;
        float A21 = a13 * a32 - a12 * a33 ;
        float A22 = a11 * a33 - a13 * a31 ;
        float A23 = a12 * a31 - a11 * a32 ;
        float A31 = a12 * a23 - a13 * a22 ;
        float A32 = a13 * a21 - a11 * a23 ;
        float A33 = a11 * a22 - a12 * a21 ;


        vector<Point> points ;
        for (int i =0 ; i <img_height ; i++){
            for (int j = 0 ; j <img_width ; j++){
                Point pt  ;
                pt.x = j ;
                pt.y = i ;
                points.push_back(pt) ;
            }

          };

        int max = points.size() ;
        for (int i = 0; i < max ; i+= 1){
            float x = points[i].x ;
            float y = points[i].y ;
            float denominator = A13 * x + A23 * y + A33 ;
            points[i].x = (A11*x + A21 * y + A31) / denominator;
            points[i].y = (A12 *x + A22 * y + A32) / denominator ;

        };

        Matrix img_trans = this->trans() ;
        // remember to free this pointor

        for (int i = 0 ; i < img_height; i++){
            float * t = img_trans.getaddress()[i] ;
            for (int j = 0 ; j < img_width ; j++){
                int tmp = i*img_width + j ;
                int x = points[tmp].x ;
                int y = points[tmp].y ;
                if (x< 0 || x>(img_width -1) || y<0 || y> (img_height -1)){continue;};
                float * p = this->getaddress()[y] ;
                t[j*3] = p[x*3] ;
                t[j*3 + 1] = p[x*3 + 1] ;
                t[j*3 + 2] = p[x*3 + 2] ;


            }

        };


        return  img_trans ;

     // now make it a matrix copfactor


};

/*
PerspectiveTransform::PerspectiveTransform(){
    this->a11 = 0 ;
     this->a12 = 0 ;
     this->a13 = 0 ;
     this->a21 = 0 ;
     this->a22 = 0 ;
     this->a23 = 0 ;
     this->a31 = 0 ;
     this->a32 = 0 ;
     this->a33 = 0 ;
};*/

PerspectiveTransform::PerspectiveTransform(float inA11, float inA21,
                                           float inA31, float inA12,
                                           float inA22, float inA32,
                                           float inA13, float inA23,
                                           float inA33) :
  a11(inA11), a12(inA12), a13(inA13), a21(inA21), a22(inA22), a23(inA23), a31(inA31), a32(inA32), a33(inA33) {} ;


PerspectiveTransform quadrilateralToQuadrilateral(float x0, float y0, float x1, float y1,
    float x2, float y2, float x3, float y3, float x0p, float y0p, float x1p, float y1p, float x2p, float y2p,
    float x3p, float y3p) {
  PerspectiveTransform qToS = quadrilateralToSquare(x0, y0, x1, y1, x2, y2, x3, y3);
  PerspectiveTransform sToQ = squareToQuadrilateral(x0p, y0p, x1p, y1p, x2p, y2p, x3p, y3p);
  return sToQ.times(qToS);
}  ;


PerspectiveTransform squareToQuadrilateral(float x0, float y0, float x1, float y1, float x2,
    float y2, float x3, float y3) {
  float dx3 = x0 - x1 + x2 - x3;
  float dy3 = y0 - y1 + y2 - y3;
  if (dx3 == 0.0f && dy3 == 0.0f) {
    PerspectiveTransform result(PerspectiveTransform(x1 - x0, x2 - x1, x0, y1 - y0, y2 - y1, y0, 0.0f,
                                     0.0f, 1.0f));
    return result;
  } else {
    float dx1 = x1 - x2;
    float dx2 = x3 - x2;
    float dy1 = y1 - y2;
    float dy2 = y3 - y2;
    float denominator = dx1 * dy2 - dx2 * dy1;
    float a13 = (dx3 * dy2 - dx2 * dy3) / denominator;
    float a23 = (dx1 * dy3 - dx3 * dy1) / denominator;
    PerspectiveTransform result(PerspectiveTransform(x1 - x0 + a13 * x1, x3 - x0 + a23 * x3, x0, y1 - y0
                                     + a13 * y1, y3 - y0 + a23 * y3, y0, a13, a23, 1.0f));
    return result;
  }
}

PerspectiveTransform quadrilateralToSquare(float x0, float y0, float x1, float y1, float x2,
    float y2, float x3, float y3) {
  // Here, the adjoint serves as the inverse:
  return squareToQuadrilateral(x0, y0, x1, y1, x2, y2, x3, y3).buildAdjoint();
}

PerspectiveTransform PerspectiveTransform::buildAdjoint() {
  // Adjoint is the transpose of the cofactor matrix:
  PerspectiveTransform result(PerspectiveTransform(a22 * a33 - a23 * a32, a23 * a31 - a21 * a33, a21 * a32
                                   - a22 * a31, a13 * a32 - a12 * a33, a11 * a33 - a13 * a31, a12 * a31 - a11 * a32, a12 * a23 - a13 * a22,
                                   a13 * a21 - a11 * a23, a11 * a22 - a12 * a21));
  return result;
}

PerspectiveTransform PerspectiveTransform::times(PerspectiveTransform other) {
  PerspectiveTransform result(PerspectiveTransform(a11 * other.a11 + a21 * other.a12 + a31 * other.a13,
                                   a11 * other.a21 + a21 * other.a22 + a31 * other.a23, a11 * other.a31 + a21 * other.a32 + a31
                                   * other.a33, a12 * other.a11 + a22 * other.a12 + a32 * other.a13, a12 * other.a21 + a22
                                   * other.a22 + a32 * other.a23, a12 * other.a31 + a22 * other.a32 + a32 * other.a33, a13
                                   * other.a11 + a23 * other.a12 + a33 * other.a13, a13 * other.a21 + a23 * other.a22 + a33
                                   * other.a23, a13 * other.a31 + a23 * other.a32 + a33 * other.a33));
  return result;
}

void PerspectiveTransform::transformPoints(vector<int> &points) {
    int max = points.size();
    for (int i = 0; i < max; i += 2) {
      float x = points[i];
      float y = points[i + 1];
      float denominator = a13 * x + a23 * y + a33;
      points[i] = (a11 * x + a21 * y + a31) / denominator;
      points[i + 1] = (a12 * x + a22 * y + a32) / denominator;
    }
  }  ;

void sortPoints( vector<Point> &  arr)
    {

    // first sorting y, then sorting x

    int A[8][2]={arr[0].x,arr[0].y,arr[1].x,arr[1].y,arr[2].x,arr[2].y,arr[3].x,arr[3].y};
    int n = 4 ;
    int i,j,k;
    int t;
    for(i=0;i<n-1;++i)
    {
        k=i;
        for(j=i+1;j<n;++j)
        {
            if(A[k][1]>A[j][1])
                k=j;
        }
        if(k!=i)
        {
            for(j=0;j<2;++j)
            {
                t=A[k][j];
                A[k][j]=A[i][j];
                A[i][j]=t;
            }
        }
    }

    // now it sort according to y priority
    //if (A[0][0]>=){

    // }

    int tmp1 ;
    int tmp2 ;
    if (A[0][0] > A[1][0]){
        tmp1 = A[0][0];
        tmp2 = A[0][1];
        A[0][0] = A[1][0] ;
        A[0][1] = A[1][1] ;

        A[1][0] = tmp1 ;
        A[1][1] = tmp2 ;

    };
    if (A[2][0] > A[3][0]){
        tmp1 = A[2][0];
        tmp2 = A[2][1];
        A[2][0] = A[3][0] ;
        A[2][1] = A[3][1] ;

        A[3][0] = tmp1 ;
        A[3][1] = tmp2 ;

    };

    arr[0].x = A[0][0] ;
     arr[0].y = A[0][1] ;
      arr[1].x = A[1][0] ;
       arr[1].y = A[1][1] ;
        arr[2].x = A[2][0] ;
         arr[2].y = A[2][1] ;
          arr[3].x = A[3][0] ;
           arr[3].y = A[3][1] ;
};
