#ifndef OPETATION_H
#define OPETATION_H
#include "mymatrix.h"
#include <QString>
#include <stack>
#include <vector>

extern QString fileName;
extern Matrix *image_Matrix;
extern QString savefileName;
extern stack<Matrix*> image_cache;
extern stack<Matrix*> undo_cache;
extern Matrix *new_image;
extern float scale_value;

void Cut(int x, int y, int width, int height);
void brightness_adjustment(int value);
void contrast_adjustment(int value);
void satuationAdjustment(int);
void alpha_adjustment(int value);
void black_white();
void grey_level();
void keepRed();
void keepGreen();
void keepBlue();
void reduceRed();
void reduceGreen();
void reduceBlue();
void invertColor();
void rgb_adjustment(int red_change,int gre_change,int blu_change);
void rotate_Right90();
void rotate_180();
void rotate_Left90();
void custom_rotation(int value);
void mirror_Horizontal();
void mirror_Vertical();
void lowSharpen();
void medSharpen();
void highSharpen();
void sharpeness_adjustment(int value);
void lowReduce();
void highReduce();
void custom_reduce(int value);
std::vector<int> count_red();
std::vector<int> count_green();
std::vector<int> count_blue();
void verticaledge();
void horizontaledge();
void contour();
void brownness();
void frost_glass();
void embossment();
void lowsmooth();
void highsmooth();
void EdgeDetection(float higher_value);
void FT_magnitude() ;
void FT_phase() ;
void FT_real_part() ;
void FT_imaginary() ;
bool legal_point(unsigned int old_x, unsigned int old_y, unsigned int new_x,unsigned int new_y,Matrix *process_image);
void check_neibourhood(stack<unsigned int> *pointx, stack<unsigned int> *pointy,  Matrix *process_image);
void intelligentimagesegmentation(Matrix *show_image, Matrix *process_image,int x,int y);
Matrix *segmentation_processing_show();
Matrix *segmentation_processing_process();

#endif // OPETATION_H
