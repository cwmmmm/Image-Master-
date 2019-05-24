#include "operation.h"
#include "mymatrix.h"
#include "math.h"
#include <QString>
#include <stack>
#include <queue>
#include <array>

QString fileName;
QString savefileName;
Matrix *image_Matrix;
stack<Matrix*> image_cache;
stack<Matrix*> undo_cache;
Matrix *new_image;
float scale_value=1;

void brightness_adjustment(int value){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    new_image=assign(image_cache.top());
    unsigned int row=new_image[0].getrownum();
    unsigned int col=new_image[0].getcolnum();
    float **red,**gre,**blu,**new_red,**new_gre,**new_blu;
    red=image_cache.top()[0].getaddress();
    gre=image_cache.top()[1].getaddress();
    blu=image_cache.top()[2].getaddress();
    new_red=new_image[0].getaddress();
    new_gre=new_image[1].getaddress();
    new_blu=new_image[2].getaddress();
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            if (red[i][j]+value>255){
                new_red[i][j]=255;
            }else if (red[i][j]+value<0){
                new_red[i][j]=0;
            }else{
                new_red[i][j]=red[i][j]+value;
            }
            if (gre[i][j]+value>255){
                new_gre[i][j]=255;
            }else if (gre[i][j]+value<0){
                new_gre[i][j]=0;
            }else{
                new_gre[i][j]=gre[i][j]+value;
            }
            if (blu[i][j]+value>255){
                new_blu[i][j]=255;
            }else if (blu[i][j]+value<0){
                new_blu[i][j]=0;
            }else{
                new_blu[i][j]=blu[i][j]+value;
            }
        }
    }
}

void contrast_adjustment(int value){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }


    unsigned int row=image_cache.top()[0].getrownum();
    unsigned int col=image_cache.top()[0].getcolnum();
    new_image=new Matrix[4];
    new_image[0]=Matrix(row,col);
    new_image[1]=Matrix(row,col);
    new_image[2]=Matrix(row,col);
    new_image[3]=Matrix(row,col);
    float **red,**gre,**blu;
    red=image_cache.top()[0].getaddress();
    gre=image_cache.top()[1].getaddress();
    blu=image_cache.top()[2].getaddress();
    Matrix *gray=new Matrix(row,col);
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            gray[0][i][j]=float(0.3)*red[i][j]+float(0.59)*gre[i][j]+float(0.11)*blu[i][j];
        }
    }
    float gray_ave,contrast;
    if (value<0){
        contrast=float(2.55)*(255*float(255)/float(255-value)-255);
    }else{
        contrast=float(2.55)*float(value);
    }
    gray_ave=gray[0].mean();
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            new_image[0][i][j]=red[i][j]+(red[i][j]-gray_ave)*contrast/255;
            new_image[1][i][j]=gre[i][j]+(gre[i][j]-gray_ave)*contrast/255;
            new_image[2][i][j]=blu[i][j]+(blu[i][j]-gray_ave)*contrast/255;
            if (new_image[0][i][j]>255){
                new_image[0][i][j]=255;
            }else if (new_image[0][i][j]<0){
                new_image[0][i][j]=0;
            }
            if (new_image[1][i][j]>255){
                new_image[1][i][j]=255;
            }else if (new_image[1][i][j]<0){
                new_image[1][i][j]=0;
            }
            if (new_image[2][i][j]>255){
                new_image[2][i][j]=255;
            }else if (new_image[2][i][j]<0){
                new_image[2][i][j]=0;
            }
            new_image[3][i][j]=image_cache.top()[3][i][j];
        }
    }
}

void satuationAdjustment(int increment_255){
    double increment_norm;
    increment_norm = double(increment_255)/100;
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    new_image=assign(image_cache.top());
    unsigned int row=new_image[0].getrownum();
    unsigned int col=new_image[0].getcolnum();
    float **red,**gre,**blu,**new_red,**new_gre,**new_blu;
    red=image_cache.top()[0].getaddress();
    gre=image_cache.top()[1].getaddress();
    blu=image_cache.top()[2].getaddress();
    new_red=new_image[0].getaddress();
    new_gre=new_image[1].getaddress();
    new_blu=new_image[2].getaddress();
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            double rgbMax = fmax (fmax(double(red[i][j]), double(gre[i][j])),double(blu[i][j]));
            double rgbMin = fmin (fmin(double(red[i][j]), double(gre[i][j])),double(blu[i][j]));
            double delta = (rgbMax - rgbMin)/255;
            if (delta > 0){
                double value = (rgbMax + rgbMin)/255;
                double L = value/2;
                double S;
                if (L > 0.5){
                    S = delta/(2-value);
                }
                else {
                    S = delta/value;
                }
                double alpha;
                if (increment_norm > 0){
                    if (increment_norm + S >= 1){
                        alpha = S;
                    }
                    else {
                        alpha = 1 - increment_norm;
                    }
                    alpha = 1/alpha - 1;
                    new_red[i][j] = red[i][j] + int((double(red[i][j]) - L * 255) * alpha);
                    new_gre[i][j] = gre[i][j] + int((double(gre[i][j]) - L * 255) * alpha);
                    new_blu[i][j] = blu[i][j] + int((double(blu[i][j]) - L * 255) * alpha);
                }
                else {
                    alpha = increment_norm;
                    new_red[i][j] = int(L * 255) + int((double(red[i][j]) - L * 255) * (1+alpha));
                    new_gre[i][j] = int(L * 255) + int((double(gre[i][j]) - L * 255) * (1+alpha));
                    new_blu[i][j] = int(L * 255) + int((double(blu[i][j]) - L * 255) * (1+alpha));
                }
            }
        }
    }
}

void alpha_adjustment(int value){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    new_image=assign(image_cache.top());
    unsigned int row=new_image[0].getrownum();
    unsigned int col=new_image[0].getcolnum();
    float **alp,**new_alp;
    alp=image_cache.top()[3].getaddress();
    new_alp=new_image[3].getaddress();
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            new_alp[i][j]=alp[i][j]*(1-value/float(100));
        }
    }
}

void black_white(){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    new_image=assign(image_cache.top());
    unsigned int row=new_image[0].getrownum();
    unsigned int col=new_image[0].getcolnum();
    float **red,**gre,**blu,**new_red,**new_gre,**new_blu;
    red=image_cache.top()[0].getaddress();
    gre=image_cache.top()[1].getaddress();
    blu=image_cache.top()[2].getaddress();
    new_red=new_image[0].getaddress();
    new_gre=new_image[1].getaddress();
    new_blu=new_image[2].getaddress();
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            float grey=red[i][j]*float(0.299)+gre[i][j]*float(0.587)+blu[i][j]*float(0.114);
            int black=int(grey/32)*32;
            new_red[i][j]=black;
            new_gre[i][j]=black;
            new_blu[i][j]=black;
        }
    }
}

void grey_level(){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    new_image=assign(image_cache.top());
    unsigned int row=new_image[0].getrownum();
    unsigned int col=new_image[0].getcolnum();
    float **red,**gre,**blu,**new_red,**new_gre,**new_blu;
    red=image_cache.top()[0].getaddress();
    gre=image_cache.top()[1].getaddress();
    blu=image_cache.top()[2].getaddress();
    new_red=new_image[0].getaddress();
    new_gre=new_image[1].getaddress();
    new_blu=new_image[2].getaddress();
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            float grey=red[i][j]*float(0.299)+gre[i][j]*float(0.587)+blu[i][j]*float(0.114);
            new_red[i][j]=grey;
            new_gre[i][j]=grey;
            new_blu[i][j]=grey;
        }
    }
}

void keepRed(){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    new_image=assign(image_cache.top());
    unsigned int row=new_image[0].getrownum();
    unsigned int col=new_image[0].getcolnum();
    float **new_gre,**new_blu;
    new_gre=new_image[1].getaddress();
    new_blu=new_image[2].getaddress();
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            new_gre[i][j]=0;
            new_blu[i][j]=0;
        }
    }
}

void keepGreen(){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    new_image=assign(image_cache.top());
    unsigned int row=new_image[0].getrownum();
    unsigned int col=new_image[0].getcolnum();
    float **new_red,**new_blu;
    new_red=new_image[0].getaddress();
    new_blu=new_image[2].getaddress();
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            new_red[i][j]=0;
            new_blu[i][j]=0;
        }
    }
}

void keepBlue(){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    new_image=assign(image_cache.top());
    unsigned int row=new_image[0].getrownum();
    unsigned int col=new_image[0].getcolnum();
    float **new_red,**new_gre;
    new_red=new_image[0].getaddress();
    new_gre=new_image[1].getaddress();
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            new_red[i][j]=0;
            new_gre[i][j]=0;
        }
    }
}

void reduceRed(){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    new_image=assign(image_cache.top());
    unsigned int row=new_image[0].getrownum();
    unsigned int col=new_image[0].getcolnum();
    float **new_red;
    new_red=new_image[0].getaddress();
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            new_red[i][j]=0;
        }
    }
}

void reduceGreen(){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    new_image=assign(image_cache.top());
    unsigned int row=new_image[0].getrownum();
    unsigned int col=new_image[0].getcolnum();
    float **new_gre;
    new_gre=new_image[1].getaddress();
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            new_gre[i][j]=0;
        }
    }
}

void reduceBlue(){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    new_image=assign(image_cache.top());
    unsigned int row=new_image[0].getrownum();
    unsigned int col=new_image[0].getcolnum();
    float **new_blu;
    new_blu=new_image[2].getaddress();
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            new_blu[i][j]=0;
        }
    }
}

void invertColor(){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    new_image=assign(image_cache.top());
    unsigned int row=new_image[0].getrownum();
    unsigned int col=new_image[0].getcolnum();
    float **new_red,**new_gre,**new_blu,**red,**gre,**blu;
    red=image_cache.top()[0].getaddress();
    gre=image_cache.top()[1].getaddress();
    blu=image_cache.top()[2].getaddress();
    new_red=new_image[0].getaddress();
    new_gre=new_image[1].getaddress();
    new_blu=new_image[2].getaddress();
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            new_red[i][j]=255-red[i][j];
            new_gre[i][j]=255-gre[i][j];
            new_blu[i][j]=255-blu[i][j];
        }
    }
}

void rgb_adjustment(int red_change,int gre_change,int blu_change){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    new_image=assign(image_cache.top());
    unsigned int row=new_image[0].getrownum();
    unsigned int col=new_image[0].getcolnum();
    float **red,**gre,**blu,**new_red,**new_gre,**new_blu;
    red=image_cache.top()[0].getaddress();
    gre=image_cache.top()[1].getaddress();
    blu=image_cache.top()[2].getaddress();
    new_red=new_image[0].getaddress();
    new_gre=new_image[1].getaddress();
    new_blu=new_image[2].getaddress();
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            if (red[i][j]+red_change>255){
                new_red[i][j]=255;
            }else if (red[i][j]+red_change<0){
                new_red[i][j]=0;
            }else {
                new_red[i][j]=red[i][j]+red_change;
            }
            if (gre[i][j]+gre_change>255){
                new_gre[i][j]=255;
            }else if (gre[i][j]+gre_change<0){
                new_gre[i][j]=0;
            }else {
                new_gre[i][j]=gre[i][j]+gre_change;
            }
            if (blu[i][j]+blu_change>255){
                new_blu[i][j]=255;
            }else if (blu[i][j]+blu_change<0){
                new_blu[i][j]=0;
            }else {
                new_blu[i][j]=blu[i][j]+blu_change;
            }
        }
    }
}

void rotate_Right90(){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    new_image=new Matrix[4];
    unsigned int row=image_cache.top()[0].getrownum();
    unsigned int col=image_cache.top()[0].getcolnum();
    new_image[0]=Matrix(col,row);
    new_image[1]=Matrix(col,row);
    new_image[2]=Matrix(col,row);
    new_image[3]=Matrix(col,row);
    float **red,**gre,**blu,**alp,**new_red,**new_gre,**new_blu,**new_alp;
    red=image_cache.top()[0].getaddress();
    gre=image_cache.top()[1].getaddress();
    blu=image_cache.top()[2].getaddress();
    alp=image_cache.top()[3].getaddress();
    new_red=new_image[0].getaddress();
    new_gre=new_image[1].getaddress();
    new_blu=new_image[2].getaddress();
    new_alp=new_image[3].getaddress();
    for (unsigned int i=0;i<col;i++){
        for (unsigned int j=0;j<row;j++){
            new_red[i][j]=red[row-j-1][i];
            new_gre[i][j]=gre[row-j-1][i];
            new_blu[i][j]=blu[row-j-1][i];
            new_alp[i][j]=alp[row-j-1][i];
        }
    }
}

void rotate_180(){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    new_image=new Matrix[4];
    unsigned int row=image_cache.top()[0].getrownum();
    unsigned int col=image_cache.top()[0].getcolnum();
    new_image[0]=Matrix(row,col);
    new_image[1]=Matrix(row,col);
    new_image[2]=Matrix(row,col);
    new_image[3]=Matrix(row,col);
    float **red,**gre,**blu,**alp,**new_red,**new_gre,**new_blu,**new_alp;
    red=image_cache.top()[0].getaddress();
    gre=image_cache.top()[1].getaddress();
    blu=image_cache.top()[2].getaddress();
    alp=image_cache.top()[3].getaddress();
    new_red=new_image[0].getaddress();
    new_gre=new_image[1].getaddress();
    new_blu=new_image[2].getaddress();
    new_alp=new_image[3].getaddress();
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            new_red[i][j]=red[row-i-1][col-j-1];
            new_gre[i][j]=gre[row-i-1][col-j-1];
            new_blu[i][j]=blu[row-i-1][col-j-1];
            new_alp[i][j]=alp[row-i-1][col-j-1];
        }
    }
}

void rotate_Left90(){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    new_image=new Matrix[4];
    unsigned int row=image_cache.top()[0].getrownum();
    unsigned int col=image_cache.top()[0].getcolnum();
    new_image[0]=Matrix(col,row);
    new_image[1]=Matrix(col,row);
    new_image[2]=Matrix(col,row);
    new_image[3]=Matrix(col,row);
    float **red,**gre,**blu,**alp,**new_red,**new_gre,**new_blu,**new_alp;
    red=image_cache.top()[0].getaddress();
    gre=image_cache.top()[1].getaddress();
    blu=image_cache.top()[2].getaddress();
    alp=image_cache.top()[3].getaddress();
    new_red=new_image[0].getaddress();
    new_gre=new_image[1].getaddress();
    new_blu=new_image[2].getaddress();
    new_alp=new_image[3].getaddress();
    for (unsigned int i=0;i<col;i++){
        for (unsigned int j=0;j<row;j++){
            new_red[i][j]=red[j][col-i-1];
            new_gre[i][j]=gre[j][col-i-1];
            new_blu[i][j]=blu[j][col-i-1];
            new_alp[i][j]=alp[j][col-i-1];
        }
    }
}

void custom_rotation(int value){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    float pi=float(3.1415926);
    float degree=float(value)/float(180)*pi;
    unsigned int row=image_cache.top()[0].getrownum();
    unsigned int col=image_cache.top()[0].getcolnum();
    float x1,x2,x3,x4;
    float y1,y2,y3,y4;
    x1=0;y1=0;
    x2=(col-1)*cos(degree)+(row-1)*sin(degree);
    y2=(row-1)*cos(degree)-(col-1)*sin(degree);
    x3=(col-1)*cos(degree);y3=-(float(col)-1)*sin(degree);
    x4=(row-1)*sin(degree);y4=(row-1)*cos(degree);
    float y_max=(((y1>y2)?y1:y2)>((y3>y4)?y3:y4))?((y1>y2)?y1:y2):((y3>y4)?y3:y4);
    float x_max=(((x1>x2)?x1:x2)>((x3>x4)?x3:x4))?((x1>x2)?x1:x2):((x3>x4)?x3:x4);
    float y_min=(((y1<y2)?y1:y2)<((y3<y4)?y3:y4))?((y1<y2)?y1:y2):((y3<y4)?y3:y4);
    float x_min=(((x1<x2)?x1:x2)<((x3<x4)?x3:x4))?((x1<x2)?x1:x2):((x3<x4)?x3:x4);
    unsigned int new_row;
    new_row=int(y_max)-int(y_min);
    unsigned int new_col;
    new_col=int(x_max)-int(x_min);
    new_image=new Matrix[4];
    new_image[0]=Matrix(new_row+1,new_col+1);
    new_image[1]=Matrix(new_row+1,new_col+1);
    new_image[2]=Matrix(new_row+1,new_col+1);
    new_image[3]=Matrix(new_row+1,new_col+1);
    int x;
    int y;
    for (unsigned int i=0;i<new_row+1;i++){
        for (unsigned int j=0;j<new_col+1;j++){
            x=int((j+x_min)*cos(degree)-float(i+y_min)*sin(degree));
            y=int((j+x_min)*sin(degree)+float(i+y_min)*cos(degree));
            if (x>=0 && x<col && y>=0 && y<row){
                new_image[3][i][j]=image_cache.top()[3][y][x];
                new_image[0][i][j]=image_cache.top()[0][y][x];
                new_image[1][i][j]=image_cache.top()[1][y][x];
                new_image[2][i][j]=image_cache.top()[2][y][x];
            }else{
                new_image[3][i][j]=0;
                new_image[0][i][j]=0;
                new_image[1][i][j]=0;
                new_image[2][i][j]=0;
            }
        }
    }

}

void mirror_Horizontal(){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    new_image=new Matrix[4];
    unsigned int row=image_cache.top()[0].getrownum();
    unsigned int col=image_cache.top()[0].getcolnum();
    new_image[0]=Matrix(row,col);
    new_image[1]=Matrix(row,col);
    new_image[2]=Matrix(row,col);
    new_image[3]=Matrix(row,col);
    float **red,**gre,**blu,**alp,**new_red,**new_gre,**new_blu,**new_alp;
    red=image_cache.top()[0].getaddress();
    gre=image_cache.top()[1].getaddress();
    blu=image_cache.top()[2].getaddress();
    alp=image_cache.top()[3].getaddress();
    new_red=new_image[0].getaddress();
    new_gre=new_image[1].getaddress();
    new_blu=new_image[2].getaddress();
    new_alp=new_image[3].getaddress();
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            new_red[i][j]=red[i][col-j-1];
            new_gre[i][j]=gre[i][col-j-1];
            new_blu[i][j]=blu[i][col-j-1];
            new_alp[i][j]=alp[i][col-j-1];
        }
    }
}

void mirror_Vertical(){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    new_image=new Matrix[4];
    unsigned int row=image_cache.top()[0].getrownum();
    unsigned int col=image_cache.top()[0].getcolnum();
    new_image[0]=Matrix(row,col);
    new_image[1]=Matrix(row,col);
    new_image[2]=Matrix(row,col);
    new_image[3]=Matrix(row,col);
    float **red,**gre,**blu,**alp,**new_red,**new_gre,**new_blu,**new_alp;
    red=image_cache.top()[0].getaddress();
    gre=image_cache.top()[1].getaddress();
    blu=image_cache.top()[2].getaddress();
    alp=image_cache.top()[3].getaddress();
    new_red=new_image[0].getaddress();
    new_gre=new_image[1].getaddress();
    new_blu=new_image[2].getaddress();
    new_alp=new_image[3].getaddress();
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            new_red[i][j]=red[row-i-1][j];
            new_gre[i][j]=gre[row-i-1][j];
            new_blu[i][j]=blu[row-i-1][j];
            new_alp[i][j]=alp[row-i-1][j];
        }
    }
}

void lowSharpen(){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    unsigned int row=image_cache.top()[0].getrownum();
    unsigned int col=image_cache.top()[0].getcolnum();
    new_image=new Matrix[4];
    vector<float> mask_vector={1,-3,1,-3,9,-3,1,-3,1};
    Matrix mask(mask_vector,3,3);
    unsigned int edge=(3-1)/2;
    Matrix *tem=new Matrix[3];
    tem[0]=Matrix(row+2*edge,col+2*edge);
    tem[1]=Matrix(row+2*edge,col+2*edge);
    tem[2]=Matrix(row+2*edge,col+2*edge);
    for (unsigned int i=0;i<row+2*edge;i++){
        for (unsigned int j=0;j<col+2*edge;j++){
            if (i<edge || i>row+edge-1 || j<edge || j>col+edge-1){
                if (i<edge){
                    if (j<edge){
                        tem[0][i][j]=image_cache.top()[0][0][0];
                        tem[1][i][j]=image_cache.top()[1][0][0];
                        tem[2][i][j]=image_cache.top()[2][0][0];
                    }else if (j>col+edge-1){
                        tem[0][i][j]=image_cache.top()[0][0][col-1];
                        tem[1][i][j]=image_cache.top()[1][0][col-1];
                        tem[2][i][j]=image_cache.top()[2][0][col-1];
                    }
                }else if (i>row+edge-1){
                    if (j<edge){
                        tem[0][i][j]=image_cache.top()[0][row-1][0];
                        tem[1][i][j]=image_cache.top()[1][row-1][0];
                        tem[2][i][j]=image_cache.top()[2][row-1][0];
                    }else if (j>col+edge-1){
                        tem[0][i][j]=image_cache.top()[0][row-1][col-1];
                        tem[1][i][j]=image_cache.top()[1][row-1][col-1];
                        tem[2][i][j]=image_cache.top()[2][row-1][col-1];
                    }
                }
            }else{
                tem[0][i][j]=image_cache.top()[0][i-edge][j-edge];
                tem[1][i][j]=image_cache.top()[1][i-edge][j-edge];
                tem[2][i][j]=image_cache.top()[2][i-edge][j-edge];
            }
        }
    }
    new_image[0]=tem[0].Mask(mask);
    new_image[1]=tem[1].Mask(mask);
    new_image[2]=tem[2].Mask(mask);
    new_image[3]=Matrix(row,col);
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            if (new_image[0][i][j]>255){
                new_image[0][i][j]=255;
            }else if (new_image[0][i][j]<0){
                new_image[0][i][j]=0;
            }
            if (new_image[1][i][j]>255){
                new_image[1][i][j]=255;
            }else if (new_image[1][i][j]<0){
                new_image[1][i][j]=0;
            }
            if (new_image[2][i][j]>255){
                new_image[2][i][j]=255;
            }else if (new_image[2][i][j]<0){
                new_image[2][i][j]=0;
            }
            new_image[3][i][j]=image_cache.top()[3][i][j];
        }
     }
    tem[0].freeMatrix();
    tem[1].freeMatrix();
    tem[2].freeMatrix();
    delete [] tem;
}


void highSharpen(){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    unsigned int row=image_cache.top()[0].getrownum();
    unsigned int col=image_cache.top()[0].getcolnum();
    new_image=new Matrix[4];
    vector<float> mask_vector={-1,-1,-1,-1,9,-1,-1,-1,-1};
    Matrix mask(mask_vector,3,3);
    unsigned int edge=(3-1)/2;
    Matrix *tem=new Matrix[3];
    tem[0]=Matrix(row+2*edge,col+2*edge);
    tem[1]=Matrix(row+2*edge,col+2*edge);
    tem[2]=Matrix(row+2*edge,col+2*edge);
    for (unsigned int i=0;i<row+2*edge;i++){
        for (unsigned int j=0;j<col+2*edge;j++){
            if (i<edge || i>row+edge-1 || j<edge || j>col+edge-1){
                if (i<edge){
                    if (j<edge){
                        tem[0][i][j]=image_cache.top()[0][0][0];
                        tem[1][i][j]=image_cache.top()[1][0][0];
                        tem[2][i][j]=image_cache.top()[2][0][0];
                    }else if (j>col+edge-1){
                        tem[0][i][j]=image_cache.top()[0][0][col-1];
                        tem[1][i][j]=image_cache.top()[1][0][col-1];
                        tem[2][i][j]=image_cache.top()[2][0][col-1];
                    }
                }else if (i>row+edge-1){
                    if (j<edge){
                        tem[0][i][j]=image_cache.top()[0][row-1][0];
                        tem[1][i][j]=image_cache.top()[1][row-1][0];
                        tem[2][i][j]=image_cache.top()[2][row-1][0];
                    }else if (j>col+edge-1){
                        tem[0][i][j]=image_cache.top()[0][row-1][col-1];
                        tem[1][i][j]=image_cache.top()[1][row-1][col-1];
                        tem[2][i][j]=image_cache.top()[2][row-1][col-1];
                    }
                }
            }else{
                tem[0][i][j]=image_cache.top()[0][i-edge][j-edge];
                tem[1][i][j]=image_cache.top()[1][i-edge][j-edge];
                tem[2][i][j]=image_cache.top()[2][i-edge][j-edge];
            }
        }
    }
    new_image[0]=tem[0].Mask(mask);
    new_image[1]=tem[1].Mask(mask);
    new_image[2]=tem[2].Mask(mask);
    new_image[3]=Matrix(row,col);
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            if (new_image[0][i][j]>255){
                new_image[0][i][j]=255;
            }else if (new_image[0][i][j]<0){
                new_image[0][i][j]=0;
            }
            if (new_image[1][i][j]>255){
                new_image[1][i][j]=255;
            }else if (new_image[1][i][j]<0){
                new_image[1][i][j]=0;
            }
            if (new_image[2][i][j]>255){
                new_image[2][i][j]=255;
            }else if (new_image[2][i][j]<0){
                new_image[2][i][j]=0;
            }
            new_image[3][i][j]=image_cache.top()[3][i][j];
        }
     }
    tem[0].freeMatrix();
    tem[1].freeMatrix();
    tem[2].freeMatrix();
    delete [] tem;
}

void sharpeness_adjustment(int value){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    unsigned int row=image_cache.top()[0].getrownum();
    unsigned int col=image_cache.top()[0].getcolnum();
    new_image=new Matrix[4];
    vector<float> mask_vector(9);
    for (unsigned int i=0;i<9;i++){
        if (i==4){
            mask_vector[i]=8*value+50;
        }else{
            mask_vector[i]=-value;
        }
    }
    Matrix mask(mask_vector,3,3);
    unsigned int edge=(3-1)/2;
    Matrix *tem=new Matrix[3];
    tem[0]=Matrix(row+2*edge,col+2*edge);
    tem[1]=Matrix(row+2*edge,col+2*edge);
    tem[2]=Matrix(row+2*edge,col+2*edge);
    for (unsigned int i=0;i<row+2*edge;i++){
        for (unsigned int j=0;j<col+2*edge;j++){
            if (i<edge || i>row+edge-1 || j<edge || j>col+edge-1){
                if (i<edge){
                    if (j<edge){
                        tem[0][i][j]=image_cache.top()[0][0][0];
                        tem[1][i][j]=image_cache.top()[1][0][0];
                        tem[2][i][j]=image_cache.top()[2][0][0];
                    }else if (j>col+edge-1){
                        tem[0][i][j]=image_cache.top()[0][0][col-1];
                        tem[1][i][j]=image_cache.top()[1][0][col-1];
                        tem[2][i][j]=image_cache.top()[2][0][col-1];
                    }
                }else if (i>row+edge-1){
                    if (j<edge){
                        tem[0][i][j]=image_cache.top()[0][row-1][0];
                        tem[1][i][j]=image_cache.top()[1][row-1][0];
                        tem[2][i][j]=image_cache.top()[2][row-1][0];
                    }else if (j>col+edge-1){
                        tem[0][i][j]=image_cache.top()[0][row-1][col-1];
                        tem[1][i][j]=image_cache.top()[1][row-1][col-1];
                        tem[2][i][j]=image_cache.top()[2][row-1][col-1];
                    }
                }
            }else{
                tem[0][i][j]=image_cache.top()[0][i-edge][j-edge];
                tem[1][i][j]=image_cache.top()[1][i-edge][j-edge];
                tem[2][i][j]=image_cache.top()[2][i-edge][j-edge];
            }
        }
    }
    new_image[0]=tem[0].Mask(mask);
    new_image[1]=tem[1].Mask(mask);
    new_image[2]=tem[2].Mask(mask);
    new_image[3]=Matrix(row,col);
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            new_image[0][i][j]/=50;
            new_image[1][i][j]/=50;
            new_image[2][i][j]/=50;
            if (new_image[0][i][j]>255){
                new_image[0][i][j]=255;
            }else if (new_image[0][i][j]<0){
                new_image[0][i][j]=0;
            }
            if (new_image[1][i][j]>255){
                new_image[1][i][j]=255;
            }else if (new_image[1][i][j]<0){
                new_image[1][i][j]=0;
            }
            if (new_image[2][i][j]>255){
                new_image[2][i][j]=255;
            }else if (new_image[2][i][j]<0){
                new_image[2][i][j]=0;
            }
            new_image[3][i][j]=image_cache.top()[3][i][j];
        }
     }
    tem[0].freeMatrix();
    tem[1].freeMatrix();
    tem[2].freeMatrix();
    delete [] tem;
}

void lowReduce(){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    unsigned int row=image_cache.top()[0].getrownum();
    unsigned int col=image_cache.top()[0].getcolnum();
    float **red,**gre,**blu;
    red=image_cache.top()[0].getaddress();
    gre=image_cache.top()[1].getaddress();
    blu=image_cache.top()[2].getaddress();
    new_image=new Matrix[4];
    new_image[0]=Matrix(row,col);
    new_image[1]=Matrix(row,col);
    new_image[2]=Matrix(row,col);
    new_image[3]=Matrix(row,col);
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            if (i!=0 && i!=row-1){
                if (j!=0 && j!=col-1){
                    for (unsigned int k=0;k<3;k++){
                        for (unsigned int l=0;l<3;l++){
                            new_image[0][i][j]+=red[i+k-1][j+l-1];
                            new_image[1][i][j]+=gre[i+k-1][j+l-1];
                            new_image[2][i][j]+=blu[i+k-1][j+l-1];
                        }
                    }
                    new_image[0][i][j]/=9;
                    new_image[1][i][j]/=9;
                    new_image[2][i][j]/=9;
                }else{
                    new_image[0][i][j]=red[i][j];
                    new_image[1][i][j]=gre[i][j];
                    new_image[2][i][j]=blu[i][j];
                }
            }else{
                new_image[0][i][j]=red[i][j];
                new_image[1][i][j]=gre[i][j];
                new_image[2][i][j]=blu[i][j];
            }
            new_image[3][i][j]=image_cache.top()[3][i][j];
        }
     }
}

void highReduce(){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    unsigned int row=image_cache.top()[0].getrownum();
    unsigned int col=image_cache.top()[0].getcolnum();
    Matrix mask(5,5);
    for (unsigned int i=0;i<5;i++){
        for (unsigned int j=0;j<5;j++){
            mask[i][j]=1;
        }
    }
    new_image=new Matrix[4];
    unsigned int edge=(5-1)/2;
    Matrix *tem=new Matrix[3];
    tem[0]=Matrix(row+2*edge,col+2*edge);
    tem[1]=Matrix(row+2*edge,col+2*edge);
    tem[2]=Matrix(row+2*edge,col+2*edge);
    for (unsigned int i=0;i<row+2*edge;i++){
        for (unsigned int j=0;j<col+2*edge;j++){
            if (i<edge || i>row+edge-1 || j<edge || j>col+edge-1){
                if (i<edge){
                    if (j<edge){
                        tem[0][i][j]=image_cache.top()[0][0][0];
                        tem[1][i][j]=image_cache.top()[1][0][0];
                        tem[2][i][j]=image_cache.top()[2][0][0];
                    }else if (j>col+edge-1){
                        tem[0][i][j]=image_cache.top()[0][0][col-1];
                        tem[1][i][j]=image_cache.top()[1][0][col-1];
                        tem[2][i][j]=image_cache.top()[2][0][col-1];
                    }
                }else if (i>row+edge-1){
                    if (j<edge){
                        tem[0][i][j]=image_cache.top()[0][row-1][0];
                        tem[1][i][j]=image_cache.top()[1][row-1][0];
                        tem[2][i][j]=image_cache.top()[2][row-1][0];
                    }else if (j>col+edge-1){
                        tem[0][i][j]=image_cache.top()[0][row-1][col-1];
                        tem[1][i][j]=image_cache.top()[1][row-1][col-1];
                        tem[2][i][j]=image_cache.top()[2][row-1][col-1];
                    }
                }
            }else{
                tem[0][i][j]=image_cache.top()[0][i-edge][j-edge];
                tem[1][i][j]=image_cache.top()[1][i-edge][j-edge];
                tem[2][i][j]=image_cache.top()[2][i-edge][j-edge];
            }
        }
    }
    new_image[0]=tem[0].Mask(mask);
    new_image[1]=tem[1].Mask(mask);
    new_image[2]=tem[2].Mask(mask);
    new_image[3]=Matrix(row,col);
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            new_image[0][i][j]/=25;
            new_image[1][i][j]/=25;
            new_image[2][i][j]/=25;
            if (new_image[0][i][j]>255){
                new_image[0][i][j]=255;
            }else if (new_image[0][i][j]<0){
                new_image[0][i][j]=0;
            }
            if (new_image[1][i][j]>255){
                new_image[1][i][j]=255;
            }else if (new_image[1][i][j]<0){
                new_image[1][i][j]=0;
            }
            if (new_image[2][i][j]>255){
                new_image[2][i][j]=255;
            }else if (new_image[2][i][j]<0){
                new_image[2][i][j]=0;
            }
            new_image[3][i][j]=image_cache.top()[3][i][j];
        }
     }
    tem[0].freeMatrix();
    tem[1].freeMatrix();
    tem[2].freeMatrix();
    delete [] tem;
}

void custom_reduce(int value){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    unsigned int row=image_cache.top()[0].getrownum();
    unsigned int col=image_cache.top()[0].getcolnum();
    unsigned int value1=(unsigned int)(value*2+1);
    Matrix mask(value1,value1);
    for (unsigned int i=0;i<value1;i++){
        for (unsigned int j=0;j<value1;j++){
            mask[i][j]=1;
        }
    }
    new_image=new Matrix[4];
    unsigned int edge=(value1-1)/2;
    Matrix *tem=new Matrix[3];
    tem[0]=Matrix(row+2*edge,col+2*edge);
    tem[1]=Matrix(row+2*edge,col+2*edge);
    tem[2]=Matrix(row+2*edge,col+2*edge);
    for (unsigned int i=0;i<row+2*edge;i++){
        for (unsigned int j=0;j<col+2*edge;j++){
            if (i<edge || i>row+edge-1 || j<edge || j>col+edge-1){
                if (i<edge){
                    if (j<edge){
                        tem[0][i][j]=image_cache.top()[0][0][0];
                        tem[1][i][j]=image_cache.top()[1][0][0];
                        tem[2][i][j]=image_cache.top()[2][0][0];
                    }else if (j>col+edge-1){
                        tem[0][i][j]=image_cache.top()[0][0][col-1];
                        tem[1][i][j]=image_cache.top()[1][0][col-1];
                        tem[2][i][j]=image_cache.top()[2][0][col-1];
                    }
                }else if (i>row+edge-1){
                    if (j<edge){
                        tem[0][i][j]=image_cache.top()[0][row-1][0];
                        tem[1][i][j]=image_cache.top()[1][row-1][0];
                        tem[2][i][j]=image_cache.top()[2][row-1][0];
                    }else if (j>col+edge-1){
                        tem[0][i][j]=image_cache.top()[0][row-1][col-1];
                        tem[1][i][j]=image_cache.top()[1][row-1][col-1];
                        tem[2][i][j]=image_cache.top()[2][row-1][col-1];
                    }
                }
            }else{
                tem[0][i][j]=image_cache.top()[0][i-edge][j-edge];
                tem[1][i][j]=image_cache.top()[1][i-edge][j-edge];
                tem[2][i][j]=image_cache.top()[2][i-edge][j-edge];
            }
        }
    }
    new_image[0]=tem[0].Mask(mask);
    new_image[1]=tem[1].Mask(mask);
    new_image[2]=tem[2].Mask(mask);
    new_image[3]=Matrix(row,col);
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            new_image[0][i][j]/=(value1*value1);
            new_image[1][i][j]/=(value1*value1);
            new_image[2][i][j]/=(value1*value1);
            if (new_image[0][i][j]>255){
                new_image[0][i][j]=255;
            }else if (new_image[0][i][j]<0){
                new_image[0][i][j]=0;
            }
            if (new_image[1][i][j]>255){
                new_image[1][i][j]=255;
            }else if (new_image[1][i][j]<0){
                new_image[1][i][j]=0;
            }
            if (new_image[2][i][j]>255){
                new_image[2][i][j]=255;
            }else if (new_image[2][i][j]<0){
                new_image[2][i][j]=0;
            }
            new_image[3][i][j]=image_cache.top()[3][i][j];
        }
     }
    tem[0].freeMatrix();
    tem[1].freeMatrix();
    tem[2].freeMatrix();
    delete [] tem;
}

vector<int> count_red(){
    vector<int> red_statistic(256);
    unsigned int row=image_cache.top()[0].getrownum();
    unsigned int col=image_cache.top()[0].getcolnum();
    float **red;
    red=image_cache.top()[0].getaddress();
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            int index=int(red[i][j]);
            red_statistic[index]+=1;
        }
    }
    return red_statistic;
}

vector<int> count_green(){
    vector<int> gre_statistic(256);
    unsigned int row=image_cache.top()[0].getrownum();
    unsigned int col=image_cache.top()[0].getcolnum();
    float **gre;
    gre=image_cache.top()[1].getaddress();
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            int index=int(gre[i][j]);
            gre_statistic[index]+=1;
        }
    }
    return gre_statistic;
}

vector<int> count_blue(){
    vector <int> blu_statistic(256);
    unsigned int row=image_cache.top()[0].getrownum();
    unsigned int col=image_cache.top()[0].getcolnum();
    float **blu;
    blu=image_cache.top()[2].getaddress();
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            int index=int(blu[i][j]);
            blu_statistic[index]+=1;
        }
    }
    return blu_statistic;
}

void Cut(int x, int y, int width, int height){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    new_image=new Matrix[4];
    new_image[0]=Matrix(height,width);
    new_image[1]=Matrix(height,width);
    new_image[2]=Matrix(height,width);
    new_image[3]=Matrix(height,width);
    float **red,**gre,**blu,**alp,**new_red,**new_gre,**new_blu,**new_alp;
    red=image_cache.top()[0].getaddress();
    gre=image_cache.top()[1].getaddress();
    blu=image_cache.top()[2].getaddress();
    alp=image_cache.top()[3].getaddress();
    new_red=new_image[0].getaddress();
    new_gre=new_image[1].getaddress();
    new_blu=new_image[2].getaddress();
    new_alp=new_image[3].getaddress();
    for (unsigned int i=0;i<height;i++){
        for (unsigned int j=0;j<width;j++){
            new_red[i][j]=red[y+i][x+j];
            new_gre[i][j]=gre[y+i][x+j];
            new_blu[i][j]=blu[y+i][x+j];
            new_alp[i][j]=alp[y+i][x+j];
        }
    }
}

void verticaledge(){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    unsigned int row=image_cache.top()[0].getrownum();
    unsigned int col=image_cache.top()[0].getcolnum();
    vector<float> mask_vector={-1,0,1,-2,0,2,-1,0,1};
    Matrix mask(mask_vector,3,3);
    new_image=new Matrix[4];
    unsigned int edge=(3-1)/2;
    Matrix *tem=new Matrix[3];
    tem[0]=Matrix(row+2*edge,col+2*edge);
    tem[1]=Matrix(row+2*edge,col+2*edge);
    tem[2]=Matrix(row+2*edge,col+2*edge);
    for (unsigned int i=0;i<row+2*edge;i++){
        for (unsigned int j=0;j<col+2*edge;j++){
            if (i<edge || i>row+edge-1 || j<edge || j>col+edge-1){
                if (i<edge){
                    if (j<edge){
                        tem[0][i][j]=image_cache.top()[0][0][0];
                        tem[1][i][j]=image_cache.top()[1][0][0];
                        tem[2][i][j]=image_cache.top()[2][0][0];
                    }else if (j>col+edge-1){
                        tem[0][i][j]=image_cache.top()[0][0][col-1];
                        tem[1][i][j]=image_cache.top()[1][0][col-1];
                        tem[2][i][j]=image_cache.top()[2][0][col-1];
                    }
                }else if (i>row+edge-1){
                    if (j<edge){
                        tem[0][i][j]=image_cache.top()[0][row-1][0];
                        tem[1][i][j]=image_cache.top()[1][row-1][0];
                        tem[2][i][j]=image_cache.top()[2][row-1][0];
                    }else if (j>col+edge-1){
                        tem[0][i][j]=image_cache.top()[0][row-1][col-1];
                        tem[1][i][j]=image_cache.top()[1][row-1][col-1];
                        tem[2][i][j]=image_cache.top()[2][row-1][col-1];
                    }
                }
            }else{
                tem[0][i][j]=image_cache.top()[0][i-edge][j-edge];
                tem[1][i][j]=image_cache.top()[1][i-edge][j-edge];
                tem[2][i][j]=image_cache.top()[2][i-edge][j-edge];
            }
        }
    }
    new_image[0]=tem[0].Mask(mask);
    new_image[1]=tem[1].Mask(mask);
    new_image[2]=tem[2].Mask(mask);
    new_image[3]=Matrix(row,col);
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            if (new_image[0][i][j]>255){
                new_image[0][i][j]=255;
            }else if (new_image[0][i][j]<0){
                new_image[0][i][j]=0;
            }
            if (new_image[1][i][j]>255){
                new_image[1][i][j]=255;
            }else if (new_image[1][i][j]<0){
                new_image[1][i][j]=0;
            }
            if (new_image[2][i][j]>255){
                new_image[2][i][j]=255;
            }else if (new_image[2][i][j]<0){
                new_image[2][i][j]=0;
            }
            new_image[3][i][j]=image_cache.top()[3][i][j];
        }
     }
    tem[0].freeMatrix();
    tem[1].freeMatrix();
    tem[2].freeMatrix();
    delete [] tem;
}

void horizontaledge(){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    unsigned int row=image_cache.top()[0].getrownum();
    unsigned int col=image_cache.top()[0].getcolnum();
    vector<float> mask_vector={-1,-2,-1,0,0,0,1,2,1};
    Matrix mask(mask_vector,3,3);
    new_image=new Matrix[4];
    unsigned int edge=(3-1)/2;
    Matrix *tem=new Matrix[3];
    tem[0]=Matrix(row+2*edge,col+2*edge);
    tem[1]=Matrix(row+2*edge,col+2*edge);
    tem[2]=Matrix(row+2*edge,col+2*edge);
    for (unsigned int i=0;i<row+2*edge;i++){
        for (unsigned int j=0;j<col+2*edge;j++){
            if (i<edge || i>row+edge-1 || j<edge || j>col+edge-1){
                if (i<edge){
                    if (j<edge){
                        tem[0][i][j]=image_cache.top()[0][0][0];
                        tem[1][i][j]=image_cache.top()[1][0][0];
                        tem[2][i][j]=image_cache.top()[2][0][0];
                    }else if (j>col+edge-1){
                        tem[0][i][j]=image_cache.top()[0][0][col-1];
                        tem[1][i][j]=image_cache.top()[1][0][col-1];
                        tem[2][i][j]=image_cache.top()[2][0][col-1];
                    }
                }else if (i>row+edge-1){
                    if (j<edge){
                        tem[0][i][j]=image_cache.top()[0][row-1][0];
                        tem[1][i][j]=image_cache.top()[1][row-1][0];
                        tem[2][i][j]=image_cache.top()[2][row-1][0];
                    }else if (j>col+edge-1){
                        tem[0][i][j]=image_cache.top()[0][row-1][col-1];
                        tem[1][i][j]=image_cache.top()[1][row-1][col-1];
                        tem[2][i][j]=image_cache.top()[2][row-1][col-1];
                    }
                }
            }else{
                tem[0][i][j]=image_cache.top()[0][i-edge][j-edge];
                tem[1][i][j]=image_cache.top()[1][i-edge][j-edge];
                tem[2][i][j]=image_cache.top()[2][i-edge][j-edge];
            }
        }
    }
    new_image[0]=tem[0].Mask(mask);
    new_image[1]=tem[1].Mask(mask);
    new_image[2]=tem[2].Mask(mask);
    new_image[3]=Matrix(row,col);
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            if (new_image[0][i][j]>255){
                new_image[0][i][j]=255;
            }else if (new_image[0][i][j]<0){
                new_image[0][i][j]=0;
            }
            if (new_image[1][i][j]>255){
                new_image[1][i][j]=255;
            }else if (new_image[1][i][j]<0){
                new_image[1][i][j]=0;
            }
            if (new_image[2][i][j]>255){
                new_image[2][i][j]=255;
            }else if (new_image[2][i][j]<0){
                new_image[2][i][j]=0;
            }
            new_image[3][i][j]=image_cache.top()[3][i][j];
        }
     }
    tem[0].freeMatrix();
    tem[1].freeMatrix();
    tem[2].freeMatrix();
    delete [] tem;
}

void contour(){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    unsigned int row=image_cache.top()[0].getrownum();
    unsigned int col=image_cache.top()[0].getcolnum();
    vector<float> mask_vector={-1,-1,-1,-1,8,-1,-1,-1,-1};
    Matrix mask(mask_vector,3,3);
    new_image=new Matrix[4];
    unsigned int edge=(3-1)/2;
    Matrix *tem=new Matrix[3];
    tem[0]=Matrix(row+2*edge,col+2*edge);
    tem[1]=Matrix(row+2*edge,col+2*edge);
    tem[2]=Matrix(row+2*edge,col+2*edge);
    for (unsigned int i=0;i<row+2*edge;i++){
        for (unsigned int j=0;j<col+2*edge;j++){
            if (i<edge || i>row+edge-1 || j<edge || j>col+edge-1){
                if (i<edge){
                    if (j<edge){
                        tem[0][i][j]=image_cache.top()[0][0][0];
                        tem[1][i][j]=image_cache.top()[1][0][0];
                        tem[2][i][j]=image_cache.top()[2][0][0];
                    }else if (j>col+edge-1){
                        tem[0][i][j]=image_cache.top()[0][0][col-1];
                        tem[1][i][j]=image_cache.top()[1][0][col-1];
                        tem[2][i][j]=image_cache.top()[2][0][col-1];
                    }
                }else if (i>row+edge-1){
                    if (j<edge){
                        tem[0][i][j]=image_cache.top()[0][row-1][0];
                        tem[1][i][j]=image_cache.top()[1][row-1][0];
                        tem[2][i][j]=image_cache.top()[2][row-1][0];
                    }else if (j>col+edge-1){
                        tem[0][i][j]=image_cache.top()[0][row-1][col-1];
                        tem[1][i][j]=image_cache.top()[1][row-1][col-1];
                        tem[2][i][j]=image_cache.top()[2][row-1][col-1];
                    }
                }
            }else{
                tem[0][i][j]=image_cache.top()[0][i-edge][j-edge];
                tem[1][i][j]=image_cache.top()[1][i-edge][j-edge];
                tem[2][i][j]=image_cache.top()[2][i-edge][j-edge];
            }
        }
    }
    new_image[0]=tem[0].Mask(mask);
    new_image[1]=tem[1].Mask(mask);
    new_image[2]=tem[2].Mask(mask);
    new_image[3]=Matrix(row,col);
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            if (new_image[0][i][j]>255){
                new_image[0][i][j]=255;
            }else if (new_image[0][i][j]<0){
                new_image[0][i][j]=0;
            }
            if (new_image[1][i][j]>255){
                new_image[1][i][j]=255;
            }else if (new_image[1][i][j]<0){
                new_image[1][i][j]=0;
            }
            if (new_image[2][i][j]>255){
                new_image[2][i][j]=255;
            }else if (new_image[2][i][j]<0){
                new_image[2][i][j]=0;
            }
            new_image[0][i][j]=255-new_image[0][i][j];
            new_image[1][i][j]=255-new_image[1][i][j];
            new_image[2][i][j]=255-new_image[2][i][j];
            new_image[3][i][j]=image_cache.top()[3][i][j];
        }
     }
    tem[0].freeMatrix();
    tem[1].freeMatrix();
    tem[2].freeMatrix();
    delete [] tem;
}


void brownness(){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    unsigned int row=image_cache.top()[0].getrownum();
    unsigned int col=image_cache.top()[0].getcolnum();
    new_image=new Matrix[4];
    new_image[0]=Matrix(row,col);
    new_image[1]=Matrix(row,col);
    new_image[2]=Matrix(row,col);
    new_image[3]=Matrix(row,col);
    float **red,**gre,**blu;
    red=image_cache.top()[0].getaddress();
    gre=image_cache.top()[1].getaddress();
    blu=image_cache.top()[2].getaddress();
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            new_image[0][i][j]=float(0.293)*red[i][j]+float(0.769)*gre[i][j]+float(0.189)*blu[i][j];
            new_image[1][i][j]=float(0.349)*red[i][j]+float(0.686)*gre[i][j]+float(0.168)*blu[i][j];
            new_image[2][i][j]=float(0.272)*red[i][j]+float(0.534)*gre[i][j]+float(0.131)*blu[i][j];
            new_image[3][i][j]=image_cache.top()[3][i][j];
            if (new_image[0][i][j]>255){
                new_image[0][i][j]=255;
            }else if (new_image[0][i][j]<0){
                new_image[0][i][j]=0;
            }
            if (new_image[1][i][j]>255){
                new_image[1][i][j]=255;
            }else if (new_image[1][i][j]<0){
                new_image[1][i][j]=0;
            }
            if (new_image[2][i][j]>255){
                new_image[2][i][j]=255;
            }else if (new_image[2][i][j]<0){
                new_image[2][i][j]=0;
            }
        }
    }
}

void frost_glass(){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    unsigned int row=image_cache.top()[0].getrownum();
    unsigned int col=image_cache.top()[0].getcolnum();
    new_image=new Matrix[4];
    new_image[0]=Matrix(row,col);
    new_image[1]=Matrix(row,col);
    new_image[2]=Matrix(row,col);
    new_image[3]=Matrix(row,col);
    float **red,**gre,**blu;
    red=image_cache.top()[0].getaddress();
    gre=image_cache.top()[1].getaddress();
    blu=image_cache.top()[2].getaddress();
    unsigned int random;
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            if (i>0 && i<row-1 && j>0 &&j<col-1){
                random=rand()%9;
                new_image[0][i][j]=red[i+random/3-1][j+random%3-1];
                new_image[1][i][j]=gre[i+random/3-1][j+random%3-1];
                new_image[2][i][j]=blu[i+random/3-1][j+random%3-1];
                if (new_image[0][i][j]>255){
                    new_image[0][i][j]=255;
                }else if (new_image[0][i][j]<0){
                    new_image[0][i][j]=0;
                }
                if (new_image[1][i][j]>255){
                    new_image[1][i][j]=255;
                }else if (new_image[1][i][j]<0){
                    new_image[1][i][j]=0;
                }
                if (new_image[2][i][j]>255){
                    new_image[2][i][j]=255;
                }else if (new_image[2][i][j]<0){
                    new_image[2][i][j]=0;
                }
            }
            new_image[3][i][j]=image_cache.top()[3][i][j];
        }
    }
}

void embossment(){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    unsigned int row=image_cache.top()[0].getrownum();
    unsigned int col=image_cache.top()[0].getcolnum();
    vector<float> mask_vector={-1,0,0,0,1,0,0,0,0};
    Matrix mask(mask_vector,3,3);
    new_image=new Matrix[4];
    unsigned int edge=(3-1)/2;
    Matrix *tem=new Matrix[3];
    tem[0]=Matrix(row+2*edge,col+2*edge);
    tem[1]=Matrix(row+2*edge,col+2*edge);
    tem[2]=Matrix(row+2*edge,col+2*edge);
    for (unsigned int i=0;i<row+2*edge;i++){
        for (unsigned int j=0;j<col+2*edge;j++){
            if (i<edge || i>row+edge-1 || j<edge || j>col+edge-1){
                if (i<edge){
                    if (j<edge){
                        tem[0][i][j]=image_cache.top()[0][0][0];
                        tem[1][i][j]=image_cache.top()[1][0][0];
                        tem[2][i][j]=image_cache.top()[2][0][0];
                    }else if (j>col+edge-1){
                        tem[0][i][j]=image_cache.top()[0][0][col-1];
                        tem[1][i][j]=image_cache.top()[1][0][col-1];
                        tem[2][i][j]=image_cache.top()[2][0][col-1];
                    }
                }else if (i>row+edge-1){
                    if (j<edge){
                        tem[0][i][j]=image_cache.top()[0][row-1][0];
                        tem[1][i][j]=image_cache.top()[1][row-1][0];
                        tem[2][i][j]=image_cache.top()[2][row-1][0];
                    }else if (j>col+edge-1){
                        tem[0][i][j]=image_cache.top()[0][row-1][col-1];
                        tem[1][i][j]=image_cache.top()[1][row-1][col-1];
                        tem[2][i][j]=image_cache.top()[2][row-1][col-1];
                    }
                }
            }else{
                tem[0][i][j]=image_cache.top()[0][i-edge][j-edge];
                tem[1][i][j]=image_cache.top()[1][i-edge][j-edge];
                tem[2][i][j]=image_cache.top()[2][i-edge][j-edge];
            }
        }
    }
    new_image[0]=tem[0].Mask(mask);
    new_image[1]=tem[1].Mask(mask);
    new_image[2]=tem[2].Mask(mask);
    new_image[3]=Matrix(row,col);
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            new_image[0][i][j]=128-new_image[0][i][j];
            new_image[1][i][j]=128-new_image[1][i][j];
            new_image[2][i][j]=128-new_image[2][i][j];
            if (new_image[0][i][j]>255){
                new_image[0][i][j]=255;
            }else if (new_image[0][i][j]<0){
                new_image[0][i][j]=0;
            }
            if (new_image[1][i][j]>255){
                new_image[1][i][j]=255;
            }else if (new_image[1][i][j]<0){
                new_image[1][i][j]=0;
            }
            if (new_image[2][i][j]>255){
                new_image[2][i][j]=255;
            }else if (new_image[2][i][j]<0){
                new_image[2][i][j]=0;
            }
            new_image[3][i][j]=image_cache.top()[3][i][j];
        }
     }
    tem[0].freeMatrix();
    tem[1].freeMatrix();
    tem[2].freeMatrix();
    delete [] tem;
}

void lowsmooth(){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    unsigned int row=image_cache.top()[0].getrownum();
    unsigned int col=image_cache.top()[0].getcolnum();
    vector<float> mask_vector={1,1,1,1,5,1,1,1,1};
    Matrix mask(mask_vector,3,3);
    new_image=new Matrix[4];
    unsigned int edge=(3-1)/2;
    Matrix *tem=new Matrix[3];
    tem[0]=Matrix(row+2*edge,col+2*edge);
    tem[1]=Matrix(row+2*edge,col+2*edge);
    tem[2]=Matrix(row+2*edge,col+2*edge);
    for (unsigned int i=0;i<row+2*edge;i++){
        for (unsigned int j=0;j<col+2*edge;j++){
            if (i<edge || i>row+edge-1 || j<edge || j>col+edge-1){
                if (i<edge){
                    if (j<edge){
                        tem[0][i][j]=image_cache.top()[0][0][0];
                        tem[1][i][j]=image_cache.top()[1][0][0];
                        tem[2][i][j]=image_cache.top()[2][0][0];
                    }else if (j>col+edge-1){
                        tem[0][i][j]=image_cache.top()[0][0][col-1];
                        tem[1][i][j]=image_cache.top()[1][0][col-1];
                        tem[2][i][j]=image_cache.top()[2][0][col-1];
                    }
                }else if (i>row+edge-1){
                    if (j<edge){
                        tem[0][i][j]=image_cache.top()[0][row-1][0];
                        tem[1][i][j]=image_cache.top()[1][row-1][0];
                        tem[2][i][j]=image_cache.top()[2][row-1][0];
                    }else if (j>col+edge-1){
                        tem[0][i][j]=image_cache.top()[0][row-1][col-1];
                        tem[1][i][j]=image_cache.top()[1][row-1][col-1];
                        tem[2][i][j]=image_cache.top()[2][row-1][col-1];
                    }
                }
            }else{
                tem[0][i][j]=image_cache.top()[0][i-edge][j-edge];
                tem[1][i][j]=image_cache.top()[1][i-edge][j-edge];
                tem[2][i][j]=image_cache.top()[2][i-edge][j-edge];
            }
        }
    }
    new_image[0]=tem[0].Mask(mask);
    new_image[1]=tem[1].Mask(mask);
    new_image[2]=tem[2].Mask(mask);
    new_image[3]=Matrix(row,col);
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            new_image[0][i][j]/=13;
            new_image[1][i][j]/=13;
            new_image[2][i][j]/=13;
            if (new_image[0][i][j]>255){
                new_image[0][i][j]=255;
            }else if (new_image[0][i][j]<0){
                new_image[0][i][j]=0;
            }
            if (new_image[1][i][j]>255){
                new_image[1][i][j]=255;
            }else if (new_image[1][i][j]<0){
                new_image[1][i][j]=0;
            }
            if (new_image[2][i][j]>255){
                new_image[2][i][j]=255;
            }else if (new_image[2][i][j]<0){
                new_image[2][i][j]=0;
            }
            new_image[3][i][j]=image_cache.top()[3][i][j];
        }
     }
    tem[0].freeMatrix();
    tem[1].freeMatrix();
    tem[2].freeMatrix();
    delete [] tem;
}

void highsmooth(){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    unsigned int row=image_cache.top()[0].getrownum();
    unsigned int col=image_cache.top()[0].getcolnum();
    vector<float> mask_vector={1,1,1,1,1,1,5,5,5,1,1,5,44,5,1,1,5,5,5,1,1,1,1,1,1};
    Matrix mask(mask_vector,5,5);
    new_image=new Matrix[4];
    unsigned int edge=(5-1)/2;
    Matrix *tem=new Matrix[3];
    tem[0]=Matrix(row+2*edge,col+2*edge);
    tem[1]=Matrix(row+2*edge,col+2*edge);
    tem[2]=Matrix(row+2*edge,col+2*edge);
    for (unsigned int i=0;i<row+2*edge;i++){
        for (unsigned int j=0;j<col+2*edge;j++){
            if (i<edge || i>row+edge-1 || j<edge || j>col+edge-1){
                if (i<edge){
                    if (j<edge){
                        tem[0][i][j]=image_cache.top()[0][0][0];
                        tem[1][i][j]=image_cache.top()[1][0][0];
                        tem[2][i][j]=image_cache.top()[2][0][0];
                    }else if (j>col+edge-1){
                        tem[0][i][j]=image_cache.top()[0][0][col-1];
                        tem[1][i][j]=image_cache.top()[1][0][col-1];
                        tem[2][i][j]=image_cache.top()[2][0][col-1];
                    }
                }else if (i>row+edge-1){
                    if (j<edge){
                        tem[0][i][j]=image_cache.top()[0][row-1][0];
                        tem[1][i][j]=image_cache.top()[1][row-1][0];
                        tem[2][i][j]=image_cache.top()[2][row-1][0];
                    }else if (j>col+edge-1){
                        tem[0][i][j]=image_cache.top()[0][row-1][col-1];
                        tem[1][i][j]=image_cache.top()[1][row-1][col-1];
                        tem[2][i][j]=image_cache.top()[2][row-1][col-1];
                    }
                }
            }else{
                tem[0][i][j]=image_cache.top()[0][i-edge][j-edge];
                tem[1][i][j]=image_cache.top()[1][i-edge][j-edge];
                tem[2][i][j]=image_cache.top()[2][i-edge][j-edge];
            }
        }
    }
    new_image[0]=tem[0].Mask(mask);
    new_image[1]=tem[1].Mask(mask);
    new_image[2]=tem[2].Mask(mask);
    new_image[3]=Matrix(row,col);
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            new_image[0][i][j]/=100;
            new_image[1][i][j]/=100;
            new_image[2][i][j]/=100;
            if (new_image[0][i][j]>255){
                new_image[0][i][j]=255;
            }else if (new_image[0][i][j]<0){
                new_image[0][i][j]=0;
            }
            if (new_image[1][i][j]>255){
                new_image[1][i][j]=255;
            }else if (new_image[1][i][j]<0){
                new_image[1][i][j]=0;
            }
            if (new_image[2][i][j]>255){
                new_image[2][i][j]=255;
            }else if (new_image[2][i][j]<0){
                new_image[2][i][j]=0;
            }
            new_image[3][i][j]=image_cache.top()[3][i][j];
        }
     }
    tem[0].freeMatrix();
    tem[1].freeMatrix();
    tem[2].freeMatrix();
    delete [] tem;
}
Matrix mas(Matrix original, Matrix mask){
    unsigned int colnum=mask.getcolnum();
    unsigned int rownum=mask.getrownum();
    unsigned int row_num = original.getrownum();
    unsigned int col_num = original.getcolnum();

    Matrix m(row_num,col_num);
    float **add=m.getaddress();
    float **addm=mask.getaddress();
    unsigned int indentation = (colnum-1)/2;
    for (unsigned int i=indentation;i<row_num-indentation;i++){
        for (unsigned int j=indentation;j<col_num-indentation;j++){
            for (unsigned int k=0;k<rownum;k++){
                for (unsigned int l=0;l<colnum;l++){
                    add[i][j] = add[i][j] + addm[k][l]*original[i-indentation+k][j-indentation+l];
                }
            }
        }
    }
    return m;
}


void EdgeDetection(float higher_valve){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    new_image=assign(image_cache.top());
    unsigned int row=new_image[0].getrownum();
    unsigned int col=new_image[0].getcolnum();
    float **red,**gre,**blu,**new_red,**new_gre,**new_blu;
    red=image_cache.top()[0].getaddress();
    gre=image_cache.top()[1].getaddress();
    blu=image_cache.top()[2].getaddress();
    new_red=new_image[0].getaddress();
    new_gre=new_image[1].getaddress();
    new_blu=new_image[2].getaddress();
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            float Grey=red[i][j]*float(0.299)+gre[i][j]*float(0.587)+blu[i][j]*float(0.114);
            new_red[i][j] = Grey;
        }
    }
    float Edge = 255;
    float NonEdge = 0;
    float UnknownEdge = 128;
    float lower_valve = higher_valve/2;

    vector <float> gauss = {1/float(273),4/float(273),7/float(273),4/float(273),1/float(273),4/float(273),16/float(273),26/float(273),
                           16/float(273),4/float(273),7/float(273),26/float(273),41/float(273),26/float(273),7/float(273),4/float(273),
                           16/float(273),26/float(273),16/float(273),4/float(273),1/float(273),4/float(273),7/float(273),4/float(273),
                           1/float(273)};

    Matrix Gauss_Matrix(gauss,5,5);
    Matrix grey = mas(new_image[0],Gauss_Matrix);

    vector <float> sobel_x = {-1,0,1,-2,0,2,-1,0,1};
    vector <float> sobel_y = {1,2,1,0,0,0,-1,-2,-1};

    Matrix sobel_matrix_x_axis(sobel_x,3,3);
    Matrix sobel_matrix_y_axis(sobel_y,3,3);

    Matrix x_gradient = mas(grey,sobel_matrix_x_axis);
    Matrix y_gradient = mas(grey,sobel_matrix_y_axis);

    Matrix A = point_square(x_gradient,2);
    Matrix B = point_square(y_gradient,2);
    Matrix gradient = A + B;
    Matrix gradient_direction(row,col);

    for (unsigned int i = 0;i < row;i++){
        for (unsigned int j=0;j < col;j++){
            gradient[i][j] = sqrt(gradient[i][j]);
        }
    }

    for (unsigned int i=1;i<row-1;i++){
        for (unsigned int j=1;j<col-1;j++){
            gradient_direction[i][j] = y_gradient[i][j]/x_gradient[i][j];
        }
    }

    for (unsigned int i=1;i<row-1;i++){
        for (unsigned int j=1;j<col-1;j++){
            float upper_edge;
            float lower_edge;
            float x = gradient_direction[i][j];
            if (gradient_direction[i][j] >= 1){
                upper_edge = gradient[i-1][j] + 1/x*(gradient[i-1][j+1] - gradient[i-1][j]);
                lower_edge = gradient[i+1][j] + 1/x*(gradient[i+1][j-1] - gradient[i+1][j]);
            }else if (gradient_direction[i][j] <= -1){
                upper_edge = gradient[i-1][j] + (-1/x)*(gradient[i-1][j-1]-gradient[i-1][j]);
                lower_edge = gradient[i+1][j] + (-1/x)*(gradient[i+1][j+1] - gradient[i+1][j]);
            }else if (gradient_direction[i][j] < 1 && gradient_direction[i][j] > 0){
                upper_edge = gradient[i+1][j] + x*(gradient[i+1][j+1] - gradient[i+1][j]);
                lower_edge = gradient[i-1][j] + x*(gradient[i-1][j-1] - gradient[i-1][j]);
            }else{
                upper_edge = gradient[i-1][j] - x*(gradient[i-1][j-1] - gradient[i-1][j]);
                lower_edge = gradient[i+1][j] - x*(gradient[i+1][j+1] - gradient[i+1][j]);
            }
            if (gradient[i][j] < upper_edge || gradient[i][j] < lower_edge){
                gradient[i][j] = 0;
            }
            if (gradient[i][j] > higher_valve){
                gradient[i][j] = Edge;
            }else if (gradient[i][j] < lower_valve){
                gradient[i][j] = NonEdge;
            }
            else{
                gradient[i][j] = UnknownEdge;
            }
        }
    }

    stack <vector<unsigned int>> *S = new stack <vector<unsigned int>>;
    queue <vector<unsigned int>> *Q = new queue <vector<unsigned int>>;
    bool connected = false;
    Matrix map_matrix(row,col);

    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            if (equal(gradient[i][j], UnknownEdge)){
                S->push(vector<unsigned int> {i,j});
                Q->push(vector<unsigned int> {i,j});
                map_matrix[i][j] = 1;
                while (!S->empty()){
                    vector <unsigned int> top = S->top();
                    if (top[0] == 0 || top[0] == row || top[1] == 0 || top[1] == col){
                        S->pop();
                    }
                    else{
                        if (equal(gradient[top[0] - 1][top[1] - 1],UnknownEdge) && equal(map_matrix[top[0] - 1][top[1] - 1] , 0)){
                            S->push(vector<unsigned int> {top[0] - 1,top[1] - 1});
                            Q->push(vector<unsigned int> {top[0] - 1,top[1] - 1});
                            map_matrix[top[0] - 1][top[1] - 1] = 1;
                        }else if(equal(gradient[top[0] - 1][top[1]],UnknownEdge) && equal(map_matrix[top[0] - 1][top[1]], 0)){
                            S->push(vector<unsigned int> {top[0] - 1,top[1]});
                            Q->push(vector<unsigned int> {top[0] - 1,top[1]});
                            map_matrix[top[0] - 1][top[1]] = 1;
                        }else if(equal(gradient[top[0] - 1][top[1] + 1], UnknownEdge) && equal(map_matrix[top[0] - 1][top[1] + 1], 0)){
                            S->push(vector<unsigned int> {top[0] - 1,top[1] + 1});
                            Q->push(vector<unsigned int> {top[0] - 1,top[1] + 1});
                            map_matrix[top[0] - 1][top[1] + 1] = 1;
                        }else if(equal(gradient[top[0]][top[1] - 1], UnknownEdge) && equal(map_matrix[top[0]][top[1] - 1], 0)){
                            S->push(vector<unsigned int> {top[0],top[1] - 1});
                            Q->push(vector<unsigned int> {top[0],top[1] - 1});
                            map_matrix[top[0]][top[1] - 1] = 1;
                        }else if(equal(gradient[top[0]][top[1] + 1], UnknownEdge) && equal(map_matrix[top[0]][top[1] + 1], 0)){
                            S->push(vector<unsigned int> {top[0],top[1] + 1});
                            Q->push(vector<unsigned int> {top[0],top[1] + 1});
                            map_matrix[top[0]][top[1] + 1] = 1;
                        }else if(equal(gradient[top[0] + 1][top[1] - 1], UnknownEdge) && equal(map_matrix[top[0] + 1][top[1] - 1], 0)){
                            S->push(vector<unsigned int> {top[0] + 1,top[1] - 1});
                            Q->push(vector<unsigned int> {top[0] + 1,top[1] - 1});
                            map_matrix[top[0] + 1][top[1] - 1] = 1;
                        }else if(equal(gradient[top[0] + 1][top[1]], UnknownEdge) && equal(map_matrix[top[0] + 1][top[1]], 0)){
                            S->push(vector<unsigned int> {top[0] + 1,top[1]});
                            Q->push(vector<unsigned int> {top[0] + 1,top[1]});
                            map_matrix[top[0] + 1][top[1]] = 1;
                        }else if(equal(gradient[top[0] + 1][top[1] + 1], UnknownEdge) && equal(map_matrix[top[0] + 1][top[1] + 1], 0)){
                            S->push(vector<unsigned int> {top[0] + 1,top[1] + 1});
                            Q->push(vector<unsigned int> {top[0] + 1,top[1] + 1});
                            map_matrix[top[0] + 1][top[1] + 1] = 1;
                        }else{
                            S->pop();
                        }
                        if (!connected){
                            if (equal(gradient[top[0] - 1][top[1] - 1], Edge)){
                                connected = true;
                            }else if (equal(gradient[top[0] - 1][top[1]], Edge)){
                                connected = true;
                            }else if (equal(gradient[top[0] - 1][top[1] + 1], Edge)){
                                connected = true;
                            }else if (equal(gradient[top[0]][top[1] - 1], Edge)){
                                connected = true;
                            }else if (equal(gradient[top[0]][top[1] + 1], Edge)){
                                connected = true;
                            }else if (equal(gradient[top[0] + 1][top[1] - 1], Edge)){
                                connected = true;
                            }else if (equal(gradient[top[0] + 1][top[1]], Edge)){
                                connected = true;
                            }else if (equal(gradient[top[0] + 1][top[1] + 1], Edge)){
                                connected = true;
                            }
                        }
                    }
                    }
                }
                while (!Q->empty()){
                    if (connected){
                        gradient[Q->front()[0]][Q->front()[1]] = Edge;
                    }else{
                        gradient[Q->front()[0]][Q->front()[1]] = NonEdge;
                    }
                    Q->pop();
                }
                connected = false;
            }
        }

    delete S;
    delete Q;

    for (unsigned int i=0;i<row;i++){
        gradient[i][0] = NonEdge;
        gradient[i][col-1] = NonEdge;
    }

    for (unsigned int j=0;j<col;j++){
        gradient[0][j] = NonEdge;
        gradient[row-1][j] = NonEdge;
    }
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            new_red[i][j]=gradient[i][j];
            new_gre[i][j]=gradient[i][j];
            new_blu[i][j]=gradient[i][j];
        }
    }

    Gauss_Matrix.freeMatrix();
    grey.freeMatrix();
    sobel_matrix_x_axis.freeMatrix();
    sobel_matrix_y_axis.freeMatrix();
    x_gradient.freeMatrix();
    y_gradient.freeMatrix();
    A.freeMatrix();
    B.freeMatrix();
    gradient.freeMatrix();
    gradient_direction.freeMatrix();
    map_matrix.freeMatrix();
}

void FT_magnitude(){
    // first it comes to free the matrix memory
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    new_image=assign(image_cache.top());
    unsigned int row_num=new_image[0].getrownum();
    unsigned int col_num=new_image[0].getcolnum();
    float **red,**gre,**blu,**new_red,**new_gre,**new_blu;
    red=image_cache.top()[0].getaddress();
    gre=image_cache.top()[1].getaddress();
    blu=image_cache.top()[2].getaddress();
    new_red=new_image[0].getaddress();
    new_gre=new_image[1].getaddress();
    new_blu=new_image[2].getaddress();

    // now to get the grey image

    for (unsigned int i=0;i<row_num;i++){
        for (unsigned int j=0;j<col_num;j++){
            float grey=red[i][j]*float(0.299)+gre[i][j]*float(0.587)+blu[i][j]*float(0.114);
            int black=int(grey/32)*32;
            new_red[i][j]=black;
            new_gre[i][j]=black;
            new_blu[i][j]=black;
        }
    }

    // now use image new_image this grey image to do operation
    int row = 0, col = 0, numrows = 0, numcols = 0, max_val = 0;

    // using complex signal to process signal
    Complex *signal;
    Complex **all_image;
    //stringstream ss;
    //string inputLine = "";
    double max = 0;

    Matrix test_blue = new_image[2] ;

    numcols = test_blue.getcolnum() ;
    numrows = test_blue.getrownum() ;
    max_val = test_blue.maximum() ;
    // cout<<"jjj"<<endl;

    //initialze arrays
    //signal = new Complex[numcols];        // a complex array pointor
    all_image = new Complex*[numrows];   // this set as new output image

    for (int i = 0; i < numrows; i++)
        all_image[i] = new Complex[numcols];     // all image is the all the three rgb matrix

    signal = test_blue.transform_to_long_vector() ;

    // apply FFT on every row

    for (row = 0; row < numrows; row++)
    {
        for (col = 0; col < numcols; col++)
        {

            signal[col] = test_blue[row][col] ;

        }

        Complex_Array x(signal, numcols);  // fft on each row
        fft(x);

        for (int i = 0; i<numcols; i++)
        {
            all_image[row][i] = x[i];
        }

        // apply on every row of the matrix
    }


    for (col = 0; col<numcols; col++)
    {
        Complex column[numrows];
        for (int i = 0; i<numrows; i++)
        {
            column[i] = all_image[i][col];
        }
        Complex_Array x(column, numrows);
        fft(x);

        for (int i = 0; i<numrows; i++)
        {
            all_image[i][col] = x[i];
            if (abs(x[i])>max)
                max = abs(x[i]);
        }
    }

    //cout << "Finished FFT on the whole image in " << endl;

    // now the FFT information results are all in the all_image

    //calculate a scaling factor for the spectrum frequency output values
    float scaling_factor = 255 / log(1 + max);

    //cout << "Status: Writing the frequency spectrum image to the hard disk." << endl;

    // allocate the memeory for freuqency
    Complex ** output_freq = new Complex*[numrows] ;

    for (int i = 0; i < numrows; i++)
        output_freq[i] = new Complex[numcols];     // all image is the all the three rgb matrix

    for (int k = 0 ; k < 3 ; k++){
    //output fourth quadrant as the first quadrant and third quadrant as second
    for (int i = numrows / 2; i<numrows; i++)
    {
        for (int j = numcols / 2; j<numcols; j++){
            // output_freq << int(scaling_factor*log(1 + abs(all_image[i][j]))) << endl;
            output_freq[i][j] = int(scaling_factor*log(1 + abs(all_image[i][j]))) ;}
        for (int j = 0; j<numcols / 2; j++){
            // output_freq << int(scaling_factor*log(1 + abs(all_image[i][j]))) << endl;
            output_freq[i][j] = int(scaling_factor*log(1 + abs(all_image[i][j]))) ;}
    }

    //output second quadrant as the third quadrant and first quadrant as forth
    for (int i = 0; i<numrows / 2; i++)
    {
        for (int j = numcols / 2; j<numcols; j++){
           //  output_freq << int(scaling_factor*log(1 + abs(all_image[i][j]))) << endl;
            output_freq[i][j] = int(scaling_factor*log(1 + abs(all_image[i][j]))) ;}
        for (int j = 0; j<numcols / 2; j++){
            // output_freq << int(scaling_factor*log(1 + abs(all_image[i][j]))) << endl;
            output_freq[i][j] = int(scaling_factor*log(1 + abs(all_image[i][j]))) ;}
    }
    }


    //cout << "Status: Applying IFFT to reconstruct the image." << endl;

    //apply the IFFT to reconstruct the image

    for (col = 0; col<numcols; col++)
    {
        Complex column[numrows];
        for (int i = 0; i<numrows; i++)
        {
            column[i] = all_image[i][col];
        }
        Complex_Array x(column, numrows);
        ifft(x);

        for (int i = 0; i<numrows; i++)
        {
            all_image[i][col] = x[i];
        }
    }

    for (row = 0; row < numrows; row++)
    {
        Complex single_row[numcols];
        for (int i = 0; i < numcols; i++)
        {
            single_row[i] = all_image[row][i];
        }

        Complex_Array x(single_row, numcols);
        ifft(x);

        for (int i = 0; i<numcols; i++)
        {
            all_image[row][i] = x[i];
        }
    }

    // -----------------------------------------------------------
    //cout << "Finished IFFT on the whole image in " <<  endl;

    //cout << "Status: Writing the reconstructed image to the hard disk." << endl;

    // in all_image this variable

   // ofstream output_recon(argv[3]);
   // output_recon << "P2" << endl;
   // output_recon << "# Reconstructed Image" << endl;
   // output_recon << numcols << " " << numrows << endl;
   // output_recon << 255 << endl;
   // Matrix *output_image = new Matrix[3] ;

    //outut the real values only since they correspond to the actual pixel values
    for (int k = 0 ; k < 3; k++){
    for (int i = 0; i<numrows; i++){
        for (int j = 0; j<numcols; j++){
           // output_recon << (int)real(all_image[i][j]) << endl;}
            new_image[k][i][j] = (int)abs(all_image[i][j]) ;
           // new_image[k][i][j] = (int)real(output_freq[i][j]) ;
           }
   //  output_recon.close();
  };};
    for (int i = 0; i < numrows; i++)
        delete [] all_image[i];
    delete[] signal;
    delete []all_image;
    for (int i = 0; i < numrows; i++)
        delete[] output_freq[i] ;
    delete [] output_freq;

   //  new_image = output_image ;
};

void FT_imaginary(){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    new_image=assign(image_cache.top());
    unsigned int row_num=new_image[0].getrownum();
    unsigned int col_num=new_image[0].getcolnum();
    float **red,**gre,**blu,**new_red,**new_gre,**new_blu;
    red=image_cache.top()[0].getaddress();
    gre=image_cache.top()[1].getaddress();
    blu=image_cache.top()[2].getaddress();
    new_red=new_image[0].getaddress();
    new_gre=new_image[1].getaddress();
    new_blu=new_image[2].getaddress();

    // now to get the grey image

    for (unsigned int i=0;i<row_num;i++){
        for (unsigned int j=0;j<col_num;j++){
            float grey=red[i][j]*float(0.299)+gre[i][j]*float(0.587)+blu[i][j]*float(0.114);
            int black=int(grey/32)*32;
            new_red[i][j]=black;
            new_gre[i][j]=black;
            new_blu[i][j]=black;
        }
    }
    // now use image new_image this grey image to do operation

    Matrix * test = new_image ;
    int row = 0, col = 0, numrows = 0, numcols = 0, max_val = 0;

    // using complex signal to process signal
    Complex *signal;
    Complex **all_image;
    //stringstream ss;
    //string inputLine = "";
    double max = 0;

    Matrix test_blue = test[2] ;
    //Matrix alpha = test[3] ;

    numcols = test_blue.getcolnum() ;
    numrows = test_blue.getrownum() ;
    max_val = test_blue.maximum() ;
    // cout<<"jjj"<<endl;
    //initialze arrays
    //signal = new Complex[numcols];        // a complex array pointor
    all_image = new Complex*[numrows];   // this set as new output image


    for (int i = 0; i < numrows; i++)
        all_image[i] = new Complex[numcols];     // all image is the all the three rgb matrix

    //cout << "Status: Applying FFT to the image." << endl;

    signal = test_blue.transform_to_long_vector() ;

    // apply FFT on every row

    for (row = 0; row < numrows; row++)
    {
        for (col = 0; col < numcols; col++)
        {

            signal[col] = test_blue[row][col] ;

        }

        Complex_Array x(signal, numcols);  // fft on each row
        fft(x);

        for (int i = 0; i<numcols; i++)
        {
            all_image[row][i] = x[i];
        }

        // apply on every row of the matrix
    }


    for (col = 0; col<numcols; col++)
    {
        Complex column[numrows];
        for (int i = 0; i<numrows; i++)
        {
            column[i] = all_image[i][col];
        }
        Complex_Array x(column, numrows);
        fft(x);

        for (int i = 0; i<numrows; i++)
        {
            all_image[i][col] = x[i];
            if (abs(x[i])>max)
                max = abs(x[i]);
        }
    }

    //cout << "Finished FFT on the whole image in " << endl;

    // now the FFT information results are all in the all_image


    //calculate a scaling factor for the spectrum frequency output values
    float scaling_factor = 255 / log(1 + max);
    //cout << "Status: Writing the frequency spectrum image to the hard disk." << endl;



    // allocate the memeory for freuqency
    Complex ** output_freq = new Complex*[numrows] ;

    for (int i = 0; i < numrows; i++)
        output_freq[i] = new Complex[numcols];     // all image is the all the three rgb matrix

    for (int k = 0 ; k < 3 ; k++){
    //output fourth quadrant as the first quadrant and third quadrant as second
    for (int i = numrows / 2; i<numrows; i++)
    {
        for (int j = numcols / 2; j<numcols; j++){
            // output_freq << int(scaling_factor*log(1 + abs(all_image[i][j]))) << endl;
            output_freq[i][j] = int(scaling_factor*log(1 + abs(all_image[i][j]))) ;}
        for (int j = 0; j<numcols / 2; j++){
            // output_freq << int(scaling_factor*log(1 + abs(all_image[i][j]))) << endl;
            output_freq[i][j] = int(scaling_factor*log(1 + abs(all_image[i][j]))) ;}
    }

    //output second quadrant as the third quadrant and first quadrant as forth
    for (int i = 0; i<numrows / 2; i++)
    {
        for (int j = numcols / 2; j<numcols; j++){
           //  output_freq << int(scaling_factor*log(1 + abs(all_image[i][j]))) << endl;
            output_freq[i][j] = int(scaling_factor*log(1 + abs(all_image[i][j]))) ;}
        for (int j = 0; j<numcols / 2; j++){
            // output_freq << int(scaling_factor*log(1 + abs(all_image[i][j]))) << endl;
            output_freq[i][j] = int(scaling_factor*log(1 + abs(all_image[i][j]))) ;}
    }

    }


    //cout << "Status: Applying IFFT to reconstruct the image." << endl;

    //apply the IFFT to reconstruct the image

    for (col = 0; col<numcols; col++)
    {
        Complex column[numrows];
        for (int i = 0; i<numrows; i++)
        {
            column[i] = all_image[i][col];
        }
        Complex_Array x(column, numrows);
        ifft(x);

        for (int i = 0; i<numrows; i++)
        {
            all_image[i][col] = x[i];
        }
    }

    for (row = 0; row < numrows; row++)
    {
        Complex single_row[numcols];
        for (int i = 0; i < numcols; i++)
        {
            single_row[i] = all_image[row][i];
        }

        Complex_Array x(single_row, numcols);
        ifft(x);

        for (int i = 0; i<numcols; i++)
        {
            all_image[row][i] = x[i];
        }
    }


    // -----------------------------------------------------------
    //cout << "Finished IFFT on the whole image in " <<  endl;

    //cout << "Status: Writing the reconstructed image to the hard disk." << endl;

    // in all_image this variable


   // ofstream output_recon(argv[3]);
   // output_recon << "P2" << endl;
   // output_recon << "# Reconstructed Image" << endl;
   // output_recon << numcols << " " << numrows << endl;
   // output_recon << 255 << endl;



   // Matrix *output_image = new Matrix[3] ;

    //outut the real values only since they correspond to the actual pixel values
    for (int k = 0 ; k < 3; k++){
    for (int i = 0; i<numrows; i++){
        for (int j = 0; j<numcols; j++){
           // output_recon << (int)real(all_image[i][j]) << endl;}
            new_image[k][i][j] = (int)imag(all_image[i][j]) ;
           // new_image[k][i][j] = (int)real(output_freq[i][j]) ;
           }
   //  output_recon.close();
  };};
    for (int i = 0; i < numrows; i++)
        delete [] all_image[i];
    delete[] signal;
    delete []all_image;
    for (int i = 0; i < numrows; i++)
        delete[] output_freq[i] ;
    delete [] output_freq;
} ;


void FT_real_part(){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    new_image=assign(image_cache.top());
    unsigned int row_num=new_image[0].getrownum();
    unsigned int col_num=new_image[0].getcolnum();
    float **red,**gre,**blu,**new_red,**new_gre,**new_blu;
    red=image_cache.top()[0].getaddress();
    gre=image_cache.top()[1].getaddress();
    blu=image_cache.top()[2].getaddress();
    new_red=new_image[0].getaddress();
    new_gre=new_image[1].getaddress();
    new_blu=new_image[2].getaddress();

    // now to get the grey image

    for (unsigned int i=0;i<row_num;i++){
        for (unsigned int j=0;j<col_num;j++){
            float grey=red[i][j]*float(0.299)+gre[i][j]*float(0.587)+blu[i][j]*float(0.114);
            int black=int(grey/32)*32;
            new_red[i][j]=black;
            new_gre[i][j]=black;
            new_blu[i][j]=black;
        }
    }

    // now use image new_image this grey image to do operation

    Matrix * test = new_image ;
    int row = 0, col = 0, numrows = 0, numcols = 0, max_val = 0;

    // using complex signal to process signal
    Complex *signal;
    Complex **all_image;
    //stringstream ss;
    //string inputLine = "";
    double max = 0;
    Matrix test_blue = test[2] ;
    //Matrix alpha = test[3] ;

    numcols = test_blue.getcolnum() ;
    numrows = test_blue.getrownum() ;
    max_val = test_blue.maximum() ;
    // cout<<"jjj"<<endl;

    //initialze arrays
    //signal = new Complex[numcols];        // a complex array pointor
    all_image = new Complex*[numrows];   // this set as new output image
    for (int i = 0; i < numrows; i++)
        all_image[i] = new Complex[numcols];     // all image is the all the three rgb matrix

    //cout << "Status: Applying FFT to the image." << endl;

    signal = test_blue.transform_to_long_vector() ;

    // apply FFT on every row

    for (row = 0; row < numrows; row++)
    {
        for (col = 0; col < numcols; col++)
        {

            signal[col] = test_blue[row][col] ;

        }

        Complex_Array x(signal, numcols);  // fft on each row
        fft(x);

        for (int i = 0; i<numcols; i++)
        {
            all_image[row][i] = x[i];
        }

        // apply on every row of the matrix
    }


    for (col = 0; col<numcols; col++)
    {
        Complex column[numrows];
        for (int i = 0; i<numrows; i++)
        {
            column[i] = all_image[i][col];
        }
        Complex_Array x(column, numrows);
        fft(x);

        for (int i = 0; i<numrows; i++)
        {
            all_image[i][col] = x[i];
            if (abs(x[i])>max)
                max = abs(x[i]);
        }
    }

    //cout << "Finished FFT on the whole image in " << endl;

    // now the FFT information results are all in the all_image


    //calculate a scaling factor for the spectrum frequency output values
    float scaling_factor = 255 / log(1 + max);
    //cout << "Status: Writing the frequency spectrum image to the hard disk." << endl;
    // allocate the memeory for freuqency
    Complex ** output_freq = new Complex*[numrows] ;

    for (int i = 0; i < numrows; i++)
        output_freq[i] = new Complex[numcols];     // all image is the all the three rgb matrix

    for (int k = 0 ; k < 3 ; k++){
    //output fourth quadrant as the first quadrant and third quadrant as second
    for (int i = numrows / 2; i<numrows; i++)
    {
        for (int j = numcols / 2; j<numcols; j++){
            // output_freq << int(scaling_factor*log(1 + abs(all_image[i][j]))) << endl;
            output_freq[i][j] = int(scaling_factor*log(1 + abs(all_image[i][j]))) ;}
        for (int j = 0; j<numcols / 2; j++){
            // output_freq << int(scaling_factor*log(1 + abs(all_image[i][j]))) << endl;
            output_freq[i][j] = int(scaling_factor*log(1 + abs(all_image[i][j]))) ;}
    }

    //output second quadrant as the third quadrant and first quadrant as forth
    for (int i = 0; i<numrows / 2; i++)
    {
        for (int j = numcols / 2; j<numcols; j++){
           //  output_freq << int(scaling_factor*log(1 + abs(all_image[i][j]))) << endl;
            output_freq[i][j] = int(scaling_factor*log(1 + abs(all_image[i][j]))) ;}
        for (int j = 0; j<numcols / 2; j++){
            // output_freq << int(scaling_factor*log(1 + abs(all_image[i][j]))) << endl;
            output_freq[i][j] = int(scaling_factor*log(1 + abs(all_image[i][j]))) ;}
    }

    }


    //cout << "Status: Applying IFFT to reconstruct the image." << endl;

    //apply the IFFT to reconstruct the image

    for (col = 0; col<numcols; col++)
    {
        Complex column[numrows];
        for (int i = 0; i<numrows; i++)
        {
            column[i] = all_image[i][col];
        }
        Complex_Array x(column, numrows);
        ifft(x);

        for (int i = 0; i<numrows; i++)
        {
            all_image[i][col] = x[i];
        }
    }

    for (row = 0; row < numrows; row++)
    {
        Complex single_row[numcols];
        for (int i = 0; i < numcols; i++)
        {
            single_row[i] = all_image[row][i];
        }

        Complex_Array x(single_row, numcols);
        ifft(x);

        for (int i = 0; i<numcols; i++)
        {
            all_image[row][i] = x[i];
        }
    }


    // -----------------------------------------------------------
    //cout << "Finished IFFT on the whole image in " <<  endl;

    //cout << "Status: Writing the reconstructed image to the hard disk." << endl;

    // in all_image this variable


   // ofstream output_recon(argv[3]);
   // output_recon << "P2" << endl;
   // output_recon << "# Reconstructed Image" << endl;
   // output_recon << numcols << " " << numrows << endl;
   // output_recon << 255 << endl;



   // Matrix *output_image = new Matrix[3] ;

    //outut the real values only since they correspond to the actual pixel values
    for (int k = 0 ; k < 3; k++){
    for (int i = 0; i<numrows; i++){
        for (int j = 0; j<numcols; j++){
           // output_recon << (int)real(all_image[i][j]) << endl;}
            new_image[k][i][j] = (int)real(all_image[i][j]) ;
           // new_image[k][i][j] = (int)real(output_freq[i][j]) ;
           }
   //  output_recon.close();
  };};
    for (int i = 0; i < numrows; i++)
        delete [] all_image[i];
    delete[] signal;
    delete []all_image;
    for (int i = 0; i < numrows; i++)
        delete[] output_freq[i] ;
    delete [] output_freq;
};

void FT_phase(){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    new_image=assign(image_cache.top());
    unsigned int row_num=new_image[0].getrownum();
    unsigned int col_num=new_image[0].getcolnum();
    float **red,**gre,**blu,**new_red,**new_gre,**new_blu;
    red=image_cache.top()[0].getaddress();
    gre=image_cache.top()[1].getaddress();
    blu=image_cache.top()[2].getaddress();
    new_red=new_image[0].getaddress();
    new_gre=new_image[1].getaddress();
    new_blu=new_image[2].getaddress();

    // now to get the grey image

    for (unsigned int i=0;i<row_num;i++){
        for (unsigned int j=0;j<col_num;j++){
            float grey=red[i][j]*float(0.299)+gre[i][j]*float(0.587)+blu[i][j]*float(0.114);
            int black=int(grey/32)*32;
            new_red[i][j]=black;
            new_gre[i][j]=black;
            new_blu[i][j]=black;
        }
    }

    // now use image new_image this grey image to do operation

    Matrix * test = new_image ;
    int row = 0, col = 0, numrows = 0, numcols = 0, max_val = 0;

    // using complex signal to process signal
    Complex *signal;
    Complex **all_image;
    //stringstream ss;
    //string inputLine = "";
    double max = 0;
    Matrix test_blue = test[2] ;
    //Matrix alpha = test[3] ;

    numcols = test_blue.getcolnum() ;
    numrows = test_blue.getrownum() ;
    max_val = test_blue.maximum() ;
    // cout<<"jjj"<<endl;

    //initialze arrays
    //signal = new Complex[numcols];        // a complex array pointor
    all_image = new Complex*[numrows];   // this set as new output image

    for (int i = 0; i < numrows; i++)
        all_image[i] = new Complex[numcols];     // all image is the all the three rgb matrix

    //cout << "Status: Applying FFT to the image." << endl;

    signal = test_blue.transform_to_long_vector() ;

    // apply FFT on every row

    for (row = 0; row < numrows; row++)
    {
        for (col = 0; col < numcols; col++)
        {

            signal[col] = test_blue[row][col] ;

        }

        Complex_Array x(signal, numcols);  // fft on each row
        fft(x);

        for (int i = 0; i<numcols; i++)
        {
            all_image[row][i] = x[i];
        }

        // apply on every row of the matrix
    }


    for (col = 0; col<numcols; col++)
    {
        Complex column[numrows];
        for (int i = 0; i<numrows; i++)
        {
            column[i] = all_image[i][col];
        }
        Complex_Array x(column, numrows);
        fft(x);

        for (int i = 0; i<numrows; i++)
        {
            all_image[i][col] = x[i];
            if (abs(x[i])>max)
                max = abs(x[i]);
        }
    }

    //cout << "Finished FFT on the whole image in " << endl;

    // now the FFT information results are all in the all_image


    //calculate a scaling factor for the spectrum frequency output values
    float scaling_factor = 255 / log(1 + max);
    //cout << "Status: Writing the frequency spectrum image to the hard disk." << endl;
    // allocate the memeory for freuqency
    Complex ** output_freq = new Complex*[numrows] ;

    for (int i = 0; i < numrows; i++)
        output_freq[i] = new Complex[numcols];     // all image is the all the three rgb matrix

    for (int k = 0 ; k < 3 ; k++){
    //output fourth quadrant as the first quadrant and third quadrant as second
    for (int i = numrows / 2; i<numrows; i++)
    {
        for (int j = numcols / 2; j<numcols; j++){
            // output_freq << int(scaling_factor*log(1 + abs(all_image[i][j]))) << endl;
            output_freq[i][j] = int(scaling_factor*log(1 + abs(all_image[i][j]))) ;}
        for (int j = 0; j<numcols / 2; j++){
            // output_freq << int(scaling_factor*log(1 + abs(all_image[i][j]))) << endl;
            output_freq[i][j] = int(scaling_factor*log(1 + abs(all_image[i][j]))) ;}
    }

    //output second quadrant as the third quadrant and first quadrant as forth
    for (int i = 0; i<numrows / 2; i++)
    {
        for (int j = numcols / 2; j<numcols; j++){
           //  output_freq << int(scaling_factor*log(1 + abs(all_image[i][j]))) << endl;
            output_freq[i][j] = int(scaling_factor*log(1 + abs(all_image[i][j]))) ;}
        for (int j = 0; j<numcols / 2; j++){
            // output_freq << int(scaling_factor*log(1 + abs(all_image[i][j]))) << endl;
            output_freq[i][j] = int(scaling_factor*log(1 + abs(all_image[i][j]))) ;}
    }

    }

    //cout << "Status: Applying IFFT to reconstruct the image." << endl;

    //apply the IFFT to reconstruct the image

    for (col = 0; col<numcols; col++)
    {
        Complex column[numrows];
        for (int i = 0; i<numrows; i++)
        {
            column[i] = all_image[i][col];
        }
        Complex_Array x(column, numrows);
        ifft(x);

        for (int i = 0; i<numrows; i++)
        {
            all_image[i][col] = x[i];
        }
    }

    for (row = 0; row < numrows; row++)
    {
        Complex single_row[numcols];
        for (int i = 0; i < numcols; i++)
        {
            single_row[i] = all_image[row][i];
        }

        Complex_Array x(single_row, numcols);
        ifft(x);

        for (int i = 0; i<numcols; i++)
        {
            all_image[row][i] = x[i];
        }
    }


    // -----------------------------------------------------------
    //cout << "Finished IFFT on the whole image in " <<  endl;

    //cout << "Status: Writing the reconstructed image to the hard disk." << endl;

    // in all_image this variable


   // ofstream output_recon(argv[3]);
   // output_recon << "P2" << endl;
   // output_recon << "# Reconstructed Image" << endl;
   // output_recon << numcols << " " << numrows << endl;
   // output_recon << 255 << endl;



   // Matrix *output_image = new Matrix[3] ;

    //outut the real values only since they correspond to the actual pixel values
    for (int k = 0 ; k < 3; k++){
    for (int i = 0; i<numrows; i++){
        for (int j = 0; j<numcols; j++){
           // output_recon << (int)real(all_image[i][j]) << endl;}
            new_image[k][i][j] = (int)arg(all_image[i][j]) ;
           // new_image[k][i][j] = (int)real(output_freq[i][j]) ;
           }
   //  output_recon.close();
  };};
    for (int i = 0; i < numrows; i++)
        delete [] all_image[i];
    delete[] signal;
    delete []all_image;
    for (int i = 0; i < numrows; i++)
        delete[] output_freq[i] ;
    delete [] output_freq;
}

bool legal_point(unsigned int old_x, unsigned int old_y, unsigned int new_x,unsigned int new_y,Matrix *process_image){
    return abs(process_image[0][old_y][old_x]-process_image[0][new_y][new_x])<5;
}

void check_neibourhood(stack<unsigned int> *pointx, stack<unsigned int> *pointy,  Matrix *process_image){
   // cout<<pointx->empty()<<endl;
    while (!pointx->empty()){
        unsigned int x=pointx->top();
        unsigned int y=pointy->top();
        pointx->pop();
        pointy->pop();
        process_image[1][y][x]=1;
        if (x>0 && equal(process_image[1][y][x-1],0) && legal_point(x,y,x-1,y,process_image)){
            pointx->push(x-1);
            pointy->push(y);
        }
        if (y>0 && equal(process_image[1][y-1][x],0) && legal_point(x,y,x,y-1,process_image)){
            pointx->push(x);
            pointy->push(y-1);
        }
        if (x<process_image[0].getcolnum()-1 && equal(process_image[1][y][x+1],0) && legal_point(x,y,x+1,y,process_image)){
            pointx->push(x+1);
            pointy->push(y);
        }
        if (y<process_image[0].getrownum()-1 && equal(process_image[1][y+1][x],0) && legal_point(x,y,x,y+1,process_image)){
            pointx->push(x);
            pointy->push(y+1);
        }
    }

}

void intelligentimagesegmentation(Matrix *show_image, Matrix *process_image,int x,int y){
    unsigned int row=image_cache.top()[0].getrownum();
    unsigned int col=image_cache.top()[0].getcolnum();
   // QPoint start = QPoint(350,200);
    if (x<0){
        x=0;
    }else if(x>col-1){
        x=col-1;
    }
    if (y<0){
        y=0;
    }else if (y>row-1){
        y=row-1;
    }
    stack<unsigned int> *pointx=new stack<unsigned int>;
    stack<unsigned int> *pointy=new stack<unsigned int>;
    pointx->push((unsigned int)x);
    pointy->push((unsigned int)y);
    check_neibourhood(pointx,pointy,process_image);
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            if (equal(process_image[1][i][j],1)){
                if (equal(show_image[3][i][j],20)){
                    show_image[3][i][j]=255;
                }
            }
        }
    }
    new_image=assign(show_image);
    show_image[0].freeMatrix();
    show_image[1].freeMatrix();
    show_image[2].freeMatrix();
    show_image[3].freeMatrix();
    process_image[0].freeMatrix();
    delete [] show_image;
    delete [] process_image;
}

Matrix *segmentation_processing_show(){
    Matrix *show_image=new Matrix[4];
    unsigned int row=image_cache.top()[0].getrownum();
    unsigned int col=image_cache.top()[0].getcolnum();
    show_image=assign(image_cache.top());
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            if (show_image[3][i][j]>20){
                show_image[3][i][j]=20;
            }
        }
    }
    return show_image;
}

Matrix *segmentation_processing_process(){
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    unsigned int row=image_cache.top()[0].getrownum();
    unsigned int col=image_cache.top()[0].getcolnum();
    Matrix *process_image=new Matrix[2];
    process_image[0]=Matrix(row,col);
    process_image[1]=Matrix(row,col);
    float **red,**gre,**blu;
    red=image_cache.top()[0].getaddress();
    gre=image_cache.top()[1].getaddress();
    blu=image_cache.top()[2].getaddress();
    for (unsigned int i=0;i<row;i++){
        for (unsigned int j=0;j<col;j++){
            if (equal(image_cache.top()[3][i][j],0)){
                process_image[0][i][j]=300;
            }else{
                process_image[0][i][j]=red[i][j]*float(0.299)+gre[i][j]*float(0.587)+blu[i][j]*float(0.114);
            }
        }
    }
    return process_image;
}
