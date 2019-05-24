#include<stdlib.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "mymatrix.h"
#include "loadpng.h"
#include "lodepng.h"
#include "operation.h"
#include "basic_dialog.h"
#include "rgb_controller.h"
#include "histogram.h"
#include "capturescreen.h"
#include <QByteArray>
#include <QFile>
#include <QMessageBox>
#include <QPushButton>
#include<QMouseEvent>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_isMousePress = false;
    ui->paintlable->setEnabled(false);
    ui->paintlable->hide();
    ui->pointlabel->setEnabled(false);
    ui->pointlabel->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent* event){
    ui->label->setMouseTracking(true);
    if(event->button() == Qt::LeftButton){
        m_isMousePress = true;
        m_beginPoint=event->pos()-ui->centralWidget->pos()-ui->scrollArea->pos()-(ui->label->pos()+ui->scrollAreaWidgetContents->pos());
}
    if (segTriggered){
        Matrix *show_image=new Matrix[4];
        Matrix *process_image=new Matrix;
        process_image=segmentation_processing_process();
        show_image=segmentation_processing_show();
        viewImage(show_image);
        int x=m_beginPoint.x();
        int y=m_beginPoint.y();
        intelligentimagesegmentation(show_image,process_image,x,y);
    }
    if (perTriggered){
        // get all the points

        if (m_isMousePress && idx<=3 ){
            Point pt ;
         cout<<"hhh"<<endl;
            unsigned int row=image_cache.top()[0].getrownum();
            unsigned int col=image_cache.top()[0].getcolnum();

           //  pt.x = col* (m_beginPoint.x()/(float((ui->label->geometry().topRight().x()) - (ui->label->geometry().topLeft().x())) ));
           //  pt.y = row *  (m_beginPoint.y()/(float((ui->label->geometry().bottomLeft().y()) - (ui->label->geometry().topLeft().y()))  )) ;


            float ratio_x = (m_beginPoint.x()/(float((ui->label->geometry().topRight().x()) - (ui->label->geometry().topLeft().x())) ) )  ;
            float ratio_y = (m_beginPoint.y()/(float((ui->label->geometry().bottomLeft().y()) - (ui->label->geometry().topLeft().y()))  ))  ;
            float muilt1 = float(col) ;
            float muilt2 = float(row) ;

            idx = idx + 1 ;
            cout<<pt.x<<" and "<<pt.y<<endl;
            cout<<idx<<"FK"<<endl;
            cout<<"col  totoal is : "<<col<<endl;
            cout<<"row totoal is : "<<row<<endl;
            float pt_x  = ratio_x*muilt1  ;
            float pt_y =  ratio_y*muilt2  ;
            pt.x = int(pt_x) ;
            pt.y = int(pt_y) ;
            ptr.push_back(pt);


        };



 if (ptr.size() == 4){

        sortPoints(ptr) ;
        // cout<<"kkkkkk"<<endl;

        Matrix *img = image_cache.top();
        int img_height = img[0].getrownum();
        int img_width = img[0].getcolnum();


        // initilizae the transform, trained it with four input points
         PerspectiveTransform   transform  = quadrilateralToQuadrilateral(
                     float(0),float(0),
                     float(img_width-1),float(0),
                     float(0),float(img_height-1),
                     float(img_width-1),float(img_height-1),
                     float(ptr[0].x),float(ptr[0].y), // top left
                     float(ptr[1].x),float(ptr[1].y), // top right
                     float(ptr[2].x),float(ptr[2].y),// bottom left
                     float(ptr[3].x),float(ptr[3].y)
                     );



         vector<int> ponits ;
                 // = {ptr[0].x,ptr[0].y,ptr[1].x,ptr[1].y, ptr[2].x,ptr[2].y,ptr[3].x,ptr[3].y};
         for(int i=0;i<img_height;i++){
             for(int j=0;j<img_width;j++){
                 ponits.push_back(j);
                 ponits.push_back(i);
             }
         }

         for (int i = 0; i < 10 ; i = i +2){
             cout<<ponits[i]<<" and "<<ponits[i+1]<< endl;
         }
         cout<<"cojmpare "<<endl;



         transform.transformPoints(ponits);

         /*
         for (int i = 0; i < 1000 ; i = i +2){
             cout<<ponits[i]<<" and "<<ponits[i+1]<< endl;
         }*/


         // trained points



            if (new_image!=nullptr){
                (new_image[0]).freeMatrix();
                (new_image[1]).freeMatrix();
                (new_image[2]).freeMatrix();
                (new_image[3]).freeMatrix();
                delete[] new_image;
            }


         new_image = assign(image_cache.top());

         cout<<"gggg"<<endl;
         cout<<ponits.size()<<endl;



      for (int k = 0 ; k <= 2 ; k++){
         for(int i=0;i<img_height;i++){
             //  uchar*  t= img_trans.ptr<uchar>(i);
              for (int j=0;j<img_width;j++){
                  //cout<<"temp os"<<endl;
                  int tmp = i*img_width+j;
                  int x = ponits[tmp*2];
                  int y = ponits[tmp*2+1];
                  if(x<0||x>(img_width-1)||y<0||y>(img_height-1))
                      continue;
                  // uchar* p = img.ptr<uchar>(y);
                  new_image[k][i][j] = image_cache.top()[k][y][x] ;
                  //t[j*3+1] = p[x*3+1];
                  // t[j*3+2] = p[x*3+2];
              }
          }
        }
       idx=0;
        ptr.clear();
         viewImage(new_image) ;
         image_cache.push(assign(new_image));
         enableButton();
         ui->pointlabel->setEnabled(false);
         ui->pointlabel->hide();
         perTriggered=false;
          }
    }
    return QWidget::mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if (m_isMousePress){
        m_endPoint=event->pos()-ui->centralWidget->pos()-ui->scrollArea->pos()-(ui->label->pos()+ui->scrollAreaWidgetContents->pos());
        update();
    }
    return QWidget::mouseMoveEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    m_endPoint=event->pos()-ui->centralWidget->pos()-ui->scrollArea->pos()-(ui->label->pos()+ui->scrollAreaWidgetContents->pos());
    m_isMousePress = false;
    if (segTriggered){
        viewImage(new_image);
        while (undo_cache.size()>0){
            (undo_cache.top()[0]).freeMatrix();
            (undo_cache.top()[1]).freeMatrix();
            (undo_cache.top()[2]).freeMatrix();
            (undo_cache.top()[3]).freeMatrix();
            delete[] undo_cache.top();
            undo_cache.pop();
        }
        image_cache.push(assign(new_image));
        enableButton();
        segTriggered=false;
        this->setCursor((QCursor(Qt::ArrowCursor)));
    }
    return QWidget::mouseReleaseEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent* event){
    switch (event->key()) {
    case (Qt::Key_F1):on_actionZoom_in_triggered();break;
    case (Qt::Key_F2):on_actionZoom_out_triggered();break;
    }
}

void MainWindow::enableButton(){
    ui->menuBar->setEnabled(true);
    ui->mainToolBar->setEnabled(true);
    ui->actionOpen->setEnabled(true);
    ui->actionClose_Image->setEnabled(image_cache.size()>0);
    ui->actionSave->setEnabled(image_cache.size()>0);
    ui->actionSave_as->setEnabled(image_cache.size()>0);
    ui->actionUndo->setEnabled(image_cache.size()>1);
    ui->actionRedo->setEnabled(undo_cache.size()>0);
    ui->actionZoom_in->setEnabled(image_cache.size()>0);
    ui->actionZoom_out->setEnabled(image_cache.size()>0);
    ui->actionCut->setEnabled(image_cache.size()>0);
    ui->actionBrightness->setEnabled(image_cache.size()>0);
    ui->actionContrast->setEnabled(image_cache.size()>0);
    ui->actionSaturation->setEnabled(image_cache.size()>0);
    ui->actionAlpha->setEnabled(image_cache.size()>0);
    ui->actionBlack_White->setEnabled(image_cache.size()>0);
    ui->actionGrey_Level->setEnabled(image_cache.size()>0);
    ui->actionKeep_Red->setEnabled(image_cache.size()>0);
    ui->actionKeep_Green->setEnabled(image_cache.size()>0);
    ui->actionKeep_Blue->setEnabled(image_cache.size()>0);
    ui->actionReduce_Red->setEnabled(image_cache.size()>0);
    ui->actionReduce_Green->setEnabled(image_cache.size()>0);
    ui->actionReduce_Blue->setEnabled(image_cache.size()>0);
    ui->actionRGB_Controller->setEnabled(image_cache.size()>0);
    ui->actionInvert_Color->setEnabled(image_cache.size()>0);
    ui->actionRotate_Right_90->setEnabled(image_cache.size()>0);
    ui->actionRotate_180->setEnabled(image_cache.size()>0);
    ui->actionRotate_Left_90->setEnabled(image_cache.size()>0);
    ui->actionHorozontal_Mirror->setEnabled(image_cache.size()>0);
    ui->actionVertical_Mirror->setEnabled(image_cache.size()>0);
    ui->actionLow_Sharpen->setEnabled(image_cache.size()>0);
    ui->actionHigh_Sharpen->setEnabled(image_cache.size()>0);
    ui->actionCustom_Sharpen->setEnabled(image_cache.size()>0);
    ui->actionLow_Reduce->setEnabled(image_cache.size()>0);
    ui->actionHigh_Reduce->setEnabled(image_cache.size()>0);
    ui->actionCustom_Reduce->setEnabled(image_cache.size()>0);
    ui->actionCustom_Rotation->setEnabled(image_cache.size()>0);
    ui->actionR_Type->setEnabled(image_cache.size()>0);
    ui->actionG_Type->setEnabled(image_cache.size()>0);
    ui->actionB_Type->setEnabled(image_cache.size()>0);
    ui->actionSynthetical->setEnabled(image_cache.size()>0);
    ui->actionDetection->setEnabled(image_cache.size()>0);
    ui->actionAnalog_Double_Exposure->setEnabled(image_cache.size()>0);
    ui->actionBrownness->setEnabled(image_cache.size()>0);
    ui->actionVertical->setEnabled(image_cache.size()>0);
    ui->actionHorizontal->setEnabled(image_cache.size()>0);
    ui->actionContour->setEnabled(image_cache.size()>0);
    ui->actionFrost_Glass->setEnabled(image_cache.size()>0);
    ui->actionEmbossment->setEnabled(image_cache.size()>0);
    ui->actionLow_Smooth->setEnabled(image_cache.size()>0);
    ui->actionHigh_Smooth->setEnabled(image_cache.size()>0);
    ui->actionFourierReal->setEnabled(image_cache.size()>0);
    ui->actionFourierImaginary->setEnabled(image_cache.size()>0);
    ui->actionFourierMagnitude->setEnabled(image_cache.size()>0);
    ui->actionFourierPhase->setEnabled(image_cache.size()>0);
    ui->actionIntelligent_Image_Segmentation->setEnabled(image_cache.size()>0);
    ui->actionPerspective_Transformation->setEnabled(image_cache.size()>0);
}

void MainWindow::disableButton(){
    ui->menuBar->setEnabled(false);
    ui->mainToolBar->setEnabled(false);
}

void MainWindow::viewImage(Matrix *matrix){

    int row=int(matrix->getrownum());
    int col=int(matrix->getcolnum());
    int x_pos, y_pos;
    if (col*scale_value >= ui->scrollArea->width()) x_pos=0;
    else x_pos=(ui->scrollArea->width()-col*scale_value)/2;
    if (row*scale_value >= ui->scrollArea->height()) y_pos=0;
    else y_pos=(ui->scrollArea->height()-row*scale_value)/2;
    ui->scrollAreaWidgetContents->setMinimumWidth(col*scale_value);
    ui->scrollAreaWidgetContents->setMinimumHeight(row*scale_value);
    ui->label->setGeometry(x_pos,y_pos,col*scale_value,row*scale_value);
    ui->paintlable->setGeometry(x_pos,y_pos,col*scale_value,row*scale_value);
    ui->pointlabel->setGeometry(x_pos,y_pos,col*scale_value,row*scale_value);
    unsigned char *cache;
    cache=png_cache(matrix);
    QImage *image = new QImage(cache,col,row,QImage::Format_RGBA8888);
    QPixmap pix=QPixmap::fromImage(*image);
    pix=pix.scaled(col*scale_value,row*scale_value);
    ui->label->setPixmap(pix);
    delete[] cache;
    delete image;
}

void MainWindow::viewImage_close(){
    viewImage(image_cache.top());
    enableButton();
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   if (image_cache.size()>0) viewImage(image_cache.top());
}

void MainWindow::on_actionOpen_triggered()
{
    fileName = QFileDialog::getOpenFileName(this,"Choose Image","image",("Image File(*.png)")) ;


    if (not fileName.isEmpty()){
        while (image_cache.size()>0){
            if (image_cache.size()==1){
                (image_cache.top()[0]).freeMatrix();
                (image_cache.top()[1]).freeMatrix();
                (image_cache.top()[2]).freeMatrix();
                (image_cache.top()[3]).freeMatrix();
                free(image_cache.top());
            }else {
                (image_cache.top()[0]).freeMatrix();
                (image_cache.top()[1]).freeMatrix();
                (image_cache.top()[2]).freeMatrix();
                (image_cache.top()[3]).freeMatrix();
                delete[] image_cache.top();
            }
            image_cache.pop();
        }
        while (undo_cache.size()>0){
            (undo_cache.top()[0]).freeMatrix();
            (undo_cache.top()[1]).freeMatrix();
            (undo_cache.top()[2]).freeMatrix();
            (undo_cache.top()[3]).freeMatrix();
            delete[] undo_cache.top();
            undo_cache.pop();
        }
        QByteArray ba = fileName.toLatin1();
        const char *filename;
        filename=ba.data();
        image_Matrix=png_read(filename);
        image_cache.push(image_Matrix);
        int col = int(image_Matrix[0].getcolnum());
        int row = int(image_Matrix[0].getrownum());
        int x_pos, y_pos;
        if (col*scale_value >= ui->scrollArea->width()) x_pos=0;
        else x_pos=(ui->scrollArea->width()-col*scale_value)/2;
        if (row*scale_value >= ui->scrollArea->height()) y_pos=0;
        else y_pos=(ui->scrollArea->height()-row*scale_value)/2;
        ui->scrollAreaWidgetContents->setMinimumWidth(col*scale_value);
        ui->scrollAreaWidgetContents->setMinimumHeight(row*scale_value);
        ui->label->setGeometry(x_pos,y_pos,col*scale_value,row*scale_value);
        ui->paintlable->setGeometry(x_pos,y_pos,col*scale_value,row*scale_value);
        ui->pointlabel->setGeometry(x_pos,y_pos,col*scale_value,row*scale_value);
        unsigned char *cache;
        cache=png_cache(image_Matrix);
        QImage *image = new QImage(cache,col,row,QImage::Format_RGBA8888);
        QPixmap pix=QPixmap::fromImage(*image);
        pix=pix.scaled(col*scale_value,row*scale_value);
        ui->label->setPixmap(pix);
        delete[] cache;
        delete image;
        enableButton();
    }
}

void MainWindow::on_actionClose_Image_triggered()
{
    while (image_cache.size()>0){
        if (image_cache.size()==1){
            (image_cache.top()[0]).freeMatrix();
            (image_cache.top()[1]).freeMatrix();
            (image_cache.top()[2]).freeMatrix();
            (image_cache.top()[3]).freeMatrix();
            free(image_cache.top());
        }else {
            (image_cache.top()[0]).freeMatrix();
            (image_cache.top()[1]).freeMatrix();
            (image_cache.top()[2]).freeMatrix();
            (image_cache.top()[3]).freeMatrix();
            delete[] image_cache.top();
        }
        image_cache.pop();
    }
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    ui->label->clear();
    enableButton();
}

void MainWindow::on_actionSave_triggered()
{
    QFile::remove(fileName);
    QByteArray ba = fileName.toLatin1();
    const char *filename;
    filename=ba.data();
    png_output(filename,image_cache.top());
    unsigned int size=image_cache.size();
    image_Matrix=image_cache.top();
    while (image_cache.size()>0){
        if (image_cache.size()==1){
            (image_cache.top()[0]).freeMatrix();
            (image_cache.top()[1]).freeMatrix();
            (image_cache.top()[2]).freeMatrix();
            (image_cache.top()[3]).freeMatrix();
            free(image_cache.top());
        }else if(image_cache.size()!=size){
            (image_cache.top()[0]).freeMatrix();
            (image_cache.top()[1]).freeMatrix();
            (image_cache.top()[2]).freeMatrix();
            (image_cache.top()[3]).freeMatrix();
            delete[] image_cache.top();
        }
        image_cache.pop();
    }
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    image_cache.push(image_Matrix);
    enableButton();
}

void MainWindow::on_actionSave_as_triggered()
{
    savefileName=QFileDialog::getSaveFileName(this,"Save image as",fileName,("Image File(*.png)"));
    if (not savefileName.isEmpty()){
        QByteArray ba = savefileName.toLatin1();
        const char *savefilename;
        savefilename=ba.data();
        png_output(savefilename,image_cache.top());
        unsigned int size=image_cache.size();
        image_Matrix=image_cache.top();
        while (image_cache.size()>0){
            if (image_cache.size()==1){
                (image_cache.top()[0]).freeMatrix();
                (image_cache.top()[1]).freeMatrix();
                (image_cache.top()[2]).freeMatrix();
                (image_cache.top()[3]).freeMatrix();
                free(image_cache.top());
            }else if(image_cache.size()!=size){
                (image_cache.top()[0]).freeMatrix();
                (image_cache.top()[1]).freeMatrix();
                (image_cache.top()[2]).freeMatrix();
                (image_cache.top()[3]).freeMatrix();
                delete[] image_cache.top();
            }
            image_cache.pop();
        }
        while (undo_cache.size()>0){
            (undo_cache.top()[0]).freeMatrix();
            (undo_cache.top()[1]).freeMatrix();
            (undo_cache.top()[2]).freeMatrix();
            (undo_cache.top()[3]).freeMatrix();
            delete[] undo_cache.top();
            undo_cache.pop();
        }
        image_cache.push(image_Matrix);
        enableButton();
    }
}

void MainWindow::on_actionUndo_triggered()
{
    undo_cache.push(image_cache.top());
    image_cache.pop();
    viewImage(image_cache.top());
    enableButton();
}

void MainWindow::on_actionRedo_triggered()
{
    image_cache.push(undo_cache.top());
    undo_cache.pop();
    viewImage(image_cache.top());
    enableButton();
}

void MainWindow::on_actionZoom_in_triggered()
{
    scale_value+=0.1;
    viewImage(image_cache.top());
}

void MainWindow::on_actionZoom_out_triggered()
{
    scale_value-=0.1;
    viewImage(image_cache.top());
}

void MainWindow::on_actionCut_triggered()
{
    disableButton();
    ui->scrollAreaWidgetContents->setMinimumWidth(0);
    ui->scrollAreaWidgetContents->setMinimumHeight(0);
    ui->mainToolBar->setEnabled(true);
    ui->actionScreen_Shot->setEnabled(false);
    ui->actionOpen->setEnabled(false);
    ui->actionClose_Image->setEnabled(false);
    ui->actionSave->setEnabled(false);
    ui->actionSave_as->setEnabled(false);
    ui->actionUndo->setEnabled(false);
    ui->actionRedo->setEnabled(false);
    ui->actionZoom_in->setEnabled(false);
    ui->actionZoom_out->setEnabled(false);
    ui->actionCut->setEnabled(false);
    ui->actionRotate_Right_90->setEnabled(false);
    ui->actionRotate_180->setEnabled(false);
    ui->actionRotate_Left_90->setEnabled(false);
    ui->actionHorozontal_Mirror->setEnabled(false);
    ui->actionVertical_Mirror->setEnabled(false);
    ui->paintlable->setEnabled(true);
    ui->paintlable->show();
    ui->actionAccept->setEnabled(true);
    ui->actionCancel->setEnabled(true);
}

void MainWindow::on_actionAccept_triggered()
{
    if (m_beginPoint.x()>0 && m_beginPoint.x()<ui->label->width() && m_beginPoint.y()>0 && m_beginPoint.y()<ui->label->height()){
        int start_x,start_y,width,height;
        start_x=m_beginPoint.x()<m_endPoint.x()?m_beginPoint.x():m_endPoint.x();
        start_y=m_beginPoint.y()<m_endPoint.y()?m_beginPoint.y():m_endPoint.y();
        width=abs(m_beginPoint.x()-m_endPoint.x());
        height=abs(m_beginPoint.y()-m_endPoint.y());
        if (start_x<0){
            width+=start_x;
            start_x=0;
        }
        if (start_x+width>ui->label->width()) width=ui->label->width()-start_x;
        if (start_y<0){
            height+=start_y;
            start_y=0;
        }
        if (start_y+height>ui->label->height()) height=ui->label->height()-start_y;
        start_x=start_x/scale_value;
        start_y=start_y/scale_value;
        width=width/scale_value;
        height=height/scale_value;
        cout<<start_x<<" "<<start_y<<" "<< width<<" "<<height<<endl;
        Cut(start_x,start_y,width,height);
        Matrix *push_image=new Matrix;
        push_image=assign(new_image);
        image_cache.push(push_image);
        viewImage(new_image);
        while (undo_cache.size()>0){
            (undo_cache.top()[0]).freeMatrix();
            (undo_cache.top()[1]).freeMatrix();
            (undo_cache.top()[2]).freeMatrix();
            (undo_cache.top()[3]).freeMatrix();
            delete[] undo_cache.top();
            undo_cache.pop();
        }
        enableButton();
        ui->paintlable->setEnabled(false);
        ui->paintlable->hide();
        ui->actionAccept->setEnabled(false);
        ui->actionCancel->setEnabled(false);
    }
}

void MainWindow::on_actionCancel_triggered()
{
    ui->paintlable->setEnabled(false);
    ui->paintlable->hide();
    ui->actionAccept->setEnabled(false);
    ui->actionCancel->setEnabled(false);
    viewImage(image_cache.top());
    enableButton();
}

void MainWindow::on_actionBrightness_triggered()
{
    brightness_window=new basic_dialog();
    brightness_window->setWindowTitle("Brightness");
    brightness_window->setWindowIcon(QIcon(":new/prefix1/Icon/brightness.png"));
    brightness_window->label->setText("Brightness");
    brightness_window->spinBox->setMaximum(100);
    brightness_window->spinBox->setMinimum(-100);
    brightness_window->slider->setMaximum(100);
    brightness_window->slider->setMinimum(-100);
    connect(brightness_window->slider,SIGNAL(valueChanged(int)),this,SLOT(brightness_adjustment_main()));
    connect(brightness_window->OK,SIGNAL(clicked()),this,SLOT(brightness_OK()));
    connect(brightness_window->OK,SIGNAL(clicked()),brightness_window,SLOT(close()));
    connect(brightness_window->Cancel,SIGNAL(clicked()),this,SLOT(brightness_Cancel()));
    connect(brightness_window,SIGNAL(destroyed()),this,SLOT(viewImage_close()));
    brightness_window->show();
    disableButton();
}

void MainWindow::brightness_adjustment_main(){
    int value=brightness_window->spinBox->value();
    brightness_adjustment(value);
    viewImage(new_image);
}

void MainWindow::brightness_OK(){
    if (brightness_window->spinBox->value()!=0){
        Matrix *push_image=new Matrix;
        push_image=assign(new_image);
        image_cache.push(push_image);
    }
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::brightness_Cancel(){
    if (brightness_window->slider->value()!=0){
        brightness_window->slider->setValue(0);
        viewImage(new_image);
    }
}

void MainWindow::on_actionContrast_triggered()
{
    contrast_window=new basic_dialog();
    contrast_window->setWindowTitle("Contrast");
    contrast_window->setWindowIcon(QIcon(":new/prefix1/Icon/contrast.png"));
    contrast_window->label->setText("Contrast");
    contrast_window->spinBox->setMaximum(100);
    contrast_window->spinBox->setMinimum(-100);
    contrast_window->slider->setMaximum(100);
    contrast_window->slider->setMinimum(-100);
    connect(contrast_window->slider,SIGNAL(valueChanged(int)),this,SLOT(contrast_adjustment_main()));
    connect(contrast_window->OK,SIGNAL(clicked()),this,SLOT(contrast_OK()));
    connect(contrast_window->OK,SIGNAL(clicked()),contrast_window,SLOT(close()));
    connect(contrast_window->Cancel,SIGNAL(clicked()),this,SLOT(contrast_Cancel()));
    connect(contrast_window,SIGNAL(destroyed()),this,SLOT(viewImage_close()));
    contrast_window->show();
    disableButton();
}

void MainWindow::contrast_adjustment_main(){
    int value=contrast_window->spinBox->value();
    contrast_adjustment(value);
    viewImage(new_image);
}

void MainWindow::contrast_OK(){
    if (contrast_window->slider->value()!=0){
        Matrix *push_image=new Matrix;
        push_image=assign(new_image);
        image_cache.push(push_image);
    }
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::contrast_Cancel(){
    if (contrast_window->slider->value()!=0){
        contrast_window->slider->setValue(0);
        viewImage(new_image);
    }
}

void MainWindow::on_actionSaturation_triggered()
{
    satuation_window=new basic_dialog();
    satuation_window->setWindowTitle("Satuation");
    satuation_window->setWindowIcon(QIcon(":new/prefix1/Icon/saturation.png"));
    satuation_window->label->setText("Satuation");
    satuation_window->spinBox->setMaximum(100);
    satuation_window->spinBox->setMinimum(-100);
    satuation_window->slider->setMaximum(100);
    satuation_window->slider->setMinimum(-100);
    connect(satuation_window->slider,SIGNAL(valueChanged(int)),this,SLOT(Adjust_Satuation_main()));
    connect(satuation_window->OK,SIGNAL(clicked()),this,SLOT(Adjust_Satuation_OK()));
    connect(satuation_window->OK,SIGNAL(clicked()),satuation_window,SLOT(close()));
    connect(satuation_window->Cancel,SIGNAL(clicked()),this,SLOT(Adjust_Satuation_Cancel()));
    connect(satuation_window,SIGNAL(destroyed()),this,SLOT(viewImage_close()));
    satuation_window->show();
    disableButton();
}

void MainWindow::Adjust_Satuation_main(){
    int value=satuation_window->spinBox->value();
    satuationAdjustment(value);
    viewImage(new_image);
}

void MainWindow::Adjust_Satuation_OK(){
    if (satuation_window->slider->value()!=0){
        Matrix *push_image=new Matrix;
        push_image=assign(new_image);
        image_cache.push(push_image);
    }
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::Adjust_Satuation_Cancel(){
    if (satuation_window->slider->value()!=0){
        satuation_window->slider->setValue(0);
        viewImage(new_image);
    }
}

void MainWindow::on_actionAlpha_triggered()
{
    alpha_window=new basic_dialog();
    alpha_window->setWindowTitle("Alpha");
    alpha_window->setWindowIcon(QIcon(":new/prefix1/Icon/alpha.png"));
    alpha_window->label->setText("Alpha");
    alpha_window->spinBox->setMaximum(100);
    alpha_window->spinBox->setMinimum(0);
    alpha_window->slider->setMaximum(100);
    alpha_window->slider->setMinimum(0);
    connect(alpha_window->slider,SIGNAL(valueChanged(int)),this,SLOT(alpha_adjustment_main()));
    connect(alpha_window->OK,SIGNAL(clicked()),this,SLOT(alpha_OK()));
    connect(alpha_window->OK,SIGNAL(clicked()),alpha_window,SLOT(close()));
    connect(alpha_window->Cancel,SIGNAL(clicked()),this,SLOT(alpha_Cancel()));
    connect(alpha_window,SIGNAL(destroyed()),this,SLOT(viewImage_close()));
    alpha_window->show();
    disableButton();
}

void MainWindow::alpha_adjustment_main(){
    int value=alpha_window->spinBox->value();
    alpha_adjustment(value);
    viewImage(new_image);
}

void MainWindow::alpha_OK(){
    if (alpha_window->slider->value()!=0){
        Matrix *push_image=new Matrix;
        push_image=assign(new_image);
        image_cache.push(push_image);
    }
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::alpha_Cancel(){
    if (alpha_window->slider->value()!=0){
        alpha_window->slider->setValue(0);
        viewImage(new_image);
    }
}


void MainWindow::on_actionBlack_White_triggered()
{
    black_white();
    Matrix *push_image=new Matrix;
    push_image=assign(new_image);
    image_cache.push(push_image);
    viewImage(new_image);
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::on_actionGrey_Level_triggered()
{
    grey_level();
    Matrix *push_image=new Matrix;
    push_image=assign(new_image);
    image_cache.push(push_image);
    viewImage(new_image);
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::on_actionKeep_Red_triggered()
{
    keepRed();
    Matrix *push_image=new Matrix;
    push_image=assign(new_image);
    image_cache.push(push_image);
    viewImage(new_image);
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::on_actionKeep_Green_triggered()
{
    keepGreen();
    Matrix *push_image=new Matrix;
    push_image=assign(new_image);
    image_cache.push(push_image);
    viewImage(new_image);
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::on_actionKeep_Blue_triggered()
{
    keepBlue();
    Matrix *push_image=new Matrix;
    push_image=assign(new_image);
    image_cache.push(push_image);
    viewImage(new_image);
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::on_actionReduce_Red_triggered()
{
    reduceRed();
    Matrix *push_image=new Matrix;
    push_image=assign(new_image);
    image_cache.push(push_image);
    viewImage(new_image);
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::on_actionReduce_Green_triggered()
{
    reduceGreen();
    Matrix *push_image=new Matrix;
    push_image=assign(new_image);
    image_cache.push(push_image);
    viewImage(new_image);
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::on_actionReduce_Blue_triggered()
{
    reduceBlue();
    Matrix *push_image=new Matrix;
    push_image=assign(new_image);
    image_cache.push(push_image);
    viewImage(new_image);
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::on_actionInvert_Color_triggered()
{
    invertColor();
    Matrix *push_image=new Matrix;
    push_image=assign(new_image);
    image_cache.push(push_image);
    viewImage(new_image);
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::on_actionRGB_Controller_triggered()
{
    rgb_window=new RGB_Controller;
    connect(rgb_window->red_slider,SIGNAL(valueChanged(int)),this,SLOT(rgb_adjustment_main()));
    connect(rgb_window->gre_slider,SIGNAL(valueChanged(int)),this,SLOT(rgb_adjustment_main()));
    connect(rgb_window->blu_slider,SIGNAL(valueChanged(int)),this,SLOT(rgb_adjustment_main()));
    connect(rgb_window->OK,SIGNAL(clicked()),this,SLOT(rgb_OK()));
    connect(rgb_window->OK,SIGNAL(clicked()),rgb_window,SLOT(close()));
    connect(rgb_window->Cancel,SIGNAL(clicked()),this,SLOT(rgb_Cancel()));
    connect(rgb_window,SIGNAL(destroyed()),this,SLOT(viewImage_close()));
    rgb_window->show();
    disableButton();
}

void MainWindow::rgb_adjustment_main(){
    int red_change=rgb_window->red_slider->value();
    int gre_change=rgb_window->gre_slider->value();
    int blu_change=rgb_window->blu_slider->value();
    rgb_adjustment(red_change,gre_change,blu_change);
    viewImage(new_image);
}

void MainWindow::rgb_OK(){
    if ((rgb_window->red_slider->value()!=0)&(rgb_window->gre_slider->value()!=0)&(rgb_window->blu_slider->value()!=0)){
        Matrix *push_image=new Matrix;
        push_image=assign(new_image);
        image_cache.push(push_image);
    }
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::rgb_Cancel(){
    if ((rgb_window->red_slider->value()!=0)||(rgb_window->gre_slider->value()!=0)||(rgb_window->blu_slider->value()!=0)){
        rgb_window->red_slider->setValue(0);
        rgb_window->gre_slider->setValue(0);
        rgb_window->blu_slider->setValue(0);
        viewImage(new_image);
    }
}


void MainWindow::on_actionRotate_Right_90_triggered()
{
    rotate_Right90();
    Matrix *push_image=new Matrix;
    push_image=assign(new_image);
    image_cache.push(push_image);
    viewImage(new_image);
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::on_actionRotate_180_triggered()
{
    rotate_180();
    Matrix *push_image=new Matrix;
    push_image=assign(new_image);
    image_cache.push(push_image);
    viewImage(new_image);
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::on_actionRotate_Left_90_triggered()
{
    rotate_Left90();
    Matrix *push_image=new Matrix;
    push_image=assign(new_image);
    image_cache.push(push_image);
    viewImage(new_image);
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}


void MainWindow::on_actionCustom_Rotation_triggered()
{
    custom_rotation_window=new basic_dialog();
    custom_rotation_window->setWindowTitle("Rotation");
    custom_rotation_window->setWindowIcon(QIcon(":new/prefix1/Icon/CustomRotate.png"));
    custom_rotation_window->label->setText("Rotation");
    custom_rotation_window->spinBox->setMaximum(180);
    custom_rotation_window->spinBox->setMinimum(-180);
    custom_rotation_window->slider->setMaximum(180);
    custom_rotation_window->slider->setMinimum(-180);
    connect(custom_rotation_window->slider,SIGNAL(valueChanged(int)),this,SLOT(custom_rotation_main()));
    connect(custom_rotation_window->OK,SIGNAL(clicked()),this,SLOT(custom_rotation_OK()));
    connect(custom_rotation_window->OK,SIGNAL(clicked()),custom_rotation_window,SLOT(close()));
    connect(custom_rotation_window->Cancel,SIGNAL(clicked()),this,SLOT(custom_rotation_Cancel()));
    connect(custom_rotation_window,SIGNAL(destroyed()),this,SLOT(viewImage_close()));
    custom_rotation_window->show();
    disableButton();
}

void MainWindow::custom_rotation_main(){
    int value=custom_rotation_window->spinBox->value();
    custom_rotation(-value);
    viewImage(new_image);
}

void MainWindow::custom_rotation_OK(){
    if (custom_rotation_window->spinBox->value()!=0){
        Matrix *push_image=new Matrix;
        push_image=assign(new_image);
        image_cache.push(push_image);
    }
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::custom_rotation_Cancel(){
    if (custom_rotation_window->slider->value()!=0){
        custom_rotation_window->slider->setValue(0);
        viewImage(new_image);
    }
}

void MainWindow::on_actionHorozontal_Mirror_triggered()
{
    mirror_Horizontal();
    Matrix *push_image=new Matrix;
    push_image=assign(new_image);
    image_cache.push(push_image);
    viewImage(new_image);
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::on_actionVertical_Mirror_triggered()
{
    mirror_Vertical();
    Matrix *push_image=new Matrix;
    push_image=assign(new_image);
    image_cache.push(push_image);
    viewImage(new_image);
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::on_actionLow_Sharpen_triggered()
{
    lowSharpen();
    Matrix *push_image=new Matrix;
    push_image=assign(new_image);
    image_cache.push(push_image);
    viewImage(new_image);
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}


void MainWindow::on_actionHigh_Sharpen_triggered()
{
    highSharpen();
    Matrix *push_image=new Matrix;
    push_image=assign(new_image);
    image_cache.push(push_image);
    viewImage(new_image);
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::on_actionCustom_Sharpen_triggered()
{
    custom_sharpen_window=new basic_dialog();
    custom_sharpen_window->setWindowTitle("Sharpen");
    custom_sharpen_window->setWindowIcon(QIcon(":new/prefix1/Icon/CustomSharpen.png"));
    custom_sharpen_window->label->setText("Sharpen");
    custom_sharpen_window->spinBox->setMaximum(100);
    custom_sharpen_window->spinBox->setMinimum(0);
    custom_sharpen_window->slider->setMaximum(100);
    custom_sharpen_window->slider->setMinimum(0);
    connect(custom_sharpen_window->slider,SIGNAL(valueChanged(int)),this,SLOT(custom_sharpen_main()));
    connect(custom_sharpen_window->OK,SIGNAL(clicked()),this,SLOT(custom_sharpen_OK()));
    connect(custom_sharpen_window->OK,SIGNAL(clicked()),custom_sharpen_window,SLOT(close()));
    connect(custom_sharpen_window->Cancel,SIGNAL(clicked()),this,SLOT(custom_sharpen_Cancel()));
    connect(custom_sharpen_window,SIGNAL(destroyed()),this,SLOT(viewImage_close()));
    custom_sharpen_window->show();
    disableButton();
}

void MainWindow::custom_sharpen_main(){
    int value=custom_sharpen_window->spinBox->value();
    sharpeness_adjustment(value);
    viewImage(new_image);
}

void MainWindow::custom_sharpen_OK(){
    if (custom_sharpen_window->spinBox->value()!=0){
        Matrix *push_image=new Matrix;
        push_image=assign(new_image);
        image_cache.push(push_image);
    }
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::custom_sharpen_Cancel(){
    if (custom_sharpen_window->slider->value()!=0){
        custom_sharpen_window->slider->setValue(0);
        viewImage(new_image);
    }
}

void MainWindow::on_actionLow_Reduce_triggered()
{
    lowReduce();
    Matrix *push_image=new Matrix;
    push_image=assign(new_image);
    image_cache.push(push_image);
    viewImage(new_image);
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::on_actionHigh_Reduce_triggered()
{
    highReduce();
    Matrix *push_image=new Matrix;
    push_image=assign(new_image);
    image_cache.push(push_image);
    viewImage(new_image);
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::on_actionCustom_Reduce_triggered()
{
    custom_reduce_window=new basic_dialog();
    custom_reduce_window->setWindowTitle("Reduce");
    custom_reduce_window->setWindowIcon(QIcon(":new/prefix1/Icon/CustomReduce.png"));
    custom_reduce_window->label->setText("Reduce");
    custom_reduce_window->spinBox->setMaximum(5);
    custom_reduce_window->spinBox->setMinimum(1);
    custom_reduce_window->slider->setMaximum(5);
    custom_reduce_window->slider->setMinimum(1);
    connect(custom_reduce_window->slider,SIGNAL(valueChanged(int)),this,SLOT(custom_reduce_main()));
    connect(custom_reduce_window->OK,SIGNAL(clicked()),this,SLOT(custom_reduce_OK()));
    connect(custom_reduce_window->OK,SIGNAL(clicked()),custom_reduce_window,SLOT(close()));
    connect(custom_reduce_window->Cancel,SIGNAL(clicked()),this,SLOT(custom_reduce_Cancel()));
    connect(custom_reduce_window,SIGNAL(destroyed()),this,SLOT(viewImage_close()));
    custom_reduce_window->show();
    disableButton();
}

void MainWindow::custom_reduce_main(){
    int value=custom_reduce_window->spinBox->value();
    custom_reduce(value);
    viewImage(new_image);
}

void MainWindow::custom_reduce_OK(){
    if (custom_reduce_window->spinBox->value()!=0){
        Matrix *push_image=new Matrix;
        push_image=assign(new_image);
        image_cache.push(push_image);
    }
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::custom_reduce_Cancel(){
    if (custom_reduce_window->slider->value()!=1){
        custom_reduce_window->slider->setValue(1);
        viewImage(new_image);
    }
}

void MainWindow::on_actionVertical_triggered()
{
    verticaledge();
    Matrix *push_image=new Matrix;
    push_image=assign(new_image);
    image_cache.push(push_image);
    viewImage(new_image);
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::on_actionHorizontal_triggered()
{
    horizontaledge();
    Matrix *push_image=new Matrix;
    push_image=assign(new_image);
    image_cache.push(push_image);
    viewImage(new_image);
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::on_actionContour_triggered()
{
    contour();
    Matrix *push_image=new Matrix;
    push_image=assign(new_image);
    image_cache.push(push_image);
    viewImage(new_image);
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::on_actionBrownness_triggered()
{
    brownness();
    Matrix *push_image=new Matrix;
    push_image=assign(new_image);
    image_cache.push(push_image);
    viewImage(new_image);
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::on_actionFrost_Glass_triggered()
{
    frost_glass();
    Matrix *push_image=new Matrix;
    push_image=assign(new_image);
    image_cache.push(push_image);
    viewImage(new_image);
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}


void MainWindow::on_actionEmbossment_triggered(){
    embossment();
    Matrix *push_image=new Matrix;
    push_image=assign(new_image);
    image_cache.push(push_image);
    viewImage(new_image);
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::on_actionLow_Smooth_triggered(){
    lowsmooth();
    Matrix *push_image=new Matrix;
    push_image=assign(new_image);
    image_cache.push(push_image);
    viewImage(new_image);
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::on_actionHigh_Smooth_triggered(){
    highsmooth();
    Matrix *push_image=new Matrix;
    push_image=assign(new_image);
    image_cache.push(push_image);
    viewImage(new_image);
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::on_actionR_Type_triggered()
{
   R_type=new Red_Histogram();
   R_type->show();

}

void MainWindow::on_actionG_Type_triggered()
{
    G_type=new Green_Histogram();
    G_type->show();
}

void MainWindow::on_actionB_Type_triggered()
{
    B_type=new Blue_Histogram();
    B_type->show();
}

void MainWindow::on_actionSynthetical_triggered()
{
    Synthetical = new Synthetical_Histogram();
    Synthetical->show();
}

void MainWindow::on_actionDetection_triggered()
{
    detection_window = new basic_dialog();
    detection_window->setWindowTitle("Edge Detection");
    detection_window->setWindowIcon(QIcon(":new/prefix1/Icon/Detection.png"));
    detection_window->label->setText("Strength");
    detection_window->slider->setMaximum(255);
    detection_window->slider->setMinimum(0);
    detection_window->spinBox->setMaximum(255);
    detection_window->spinBox->setMinimum(0);
    connect(detection_window->slider,SIGNAL(valueChanged(int)),this,SLOT(detection_main()));
    connect(detection_window->OK,SIGNAL(clicked()),this,SLOT(detection_OK()));
    connect(detection_window->OK,SIGNAL(clicked()),detection_window,SLOT(close()));
    connect(detection_window->Cancel,SIGNAL(clicked()),this,SLOT(detection_Cancel()));
    connect(detection_window,SIGNAL(destroyed()),this,SLOT(viewImage_close()));
    detection_window->show();
    disableButton();
}

void MainWindow::detection_main(){
    int value=detection_window->spinBox->value();
    EdgeDetection(value);
    viewImage(new_image);
}

void MainWindow::detection_OK(){
    if (detection_window->spinBox->value()!=0){
        Matrix *push_image=new Matrix;
        push_image=assign(new_image);
        image_cache.push(push_image);
    }
    while (undo_cache.size()>0){
        (undo_cache.top()[0]).freeMatrix();
        (undo_cache.top()[1]).freeMatrix();
        (undo_cache.top()[2]).freeMatrix();
        (undo_cache.top()[3]).freeMatrix();
        delete[] undo_cache.top();
        undo_cache.pop();
    }
    enableButton();
}

void MainWindow::detection_Cancel(){
    if (detection_window->slider->value()!=0){
        detection_window->slider->setValue(0);
        viewImage(new_image);
    }
}

void MainWindow::on_actionAnalog_Double_Exposure_triggered()
{
    QString fileName2 = QFileDialog::getOpenFileName(this,"Choose an Image","image",("Image File(*.png)")) ;
    if (fileName2!=""){
        QByteArray ba = fileName2.toLatin1();
        const char *filename2;
        filename2=ba.data();
        Matrix *doubleEx_matrix=new Matrix[4];
        doubleEx_matrix=png_read(filename2);
        unsigned int col2 = (doubleEx_matrix[0].getcolnum());
        unsigned int row2 = (doubleEx_matrix[0].getrownum());
        if (new_image!=nullptr){
            (new_image[0]).freeMatrix();
            (new_image[1]).freeMatrix();
            (new_image[2]).freeMatrix();
            (new_image[3]).freeMatrix();
            delete[] new_image;
        }
        unsigned int col=image_cache.top()[0].getcolnum();
        unsigned int row=image_cache.top()[0].getrownum();
        float **red2,**gre2,**blu2,**red,**gre,**blu;
        red=image_cache.top()[0].getaddress();
        gre=image_cache.top()[1].getaddress();
        blu=image_cache.top()[2].getaddress();
        red2=doubleEx_matrix[0].getaddress();
        gre2=doubleEx_matrix[1].getaddress();
        blu2=doubleEx_matrix[2].getaddress();
        unsigned int largeCol,smallCol,largeRow,smallRow;
        if(col>=col2){
            largeCol = col;
            smallCol = col2;
        }
        else {
            largeCol = col2;
            smallCol = col;
        }
        if(row>=row2){
            largeRow = row;
            smallRow = row2;
        }
        else{
            largeRow = row2;
            smallRow = row;
        }
        new_image=new Matrix[4];
        new_image[0]=Matrix(largeRow, largeCol);
        new_image[1]=Matrix(largeRow, largeCol);
        new_image[2]=Matrix(largeRow, largeCol);
        new_image[3]=Matrix(largeRow, largeCol);
        for (unsigned int i=0;i < largeRow;i++){
             for (unsigned int j=0; j < largeCol;j++){
                 if(j<smallCol && i<smallRow){
                     new_image[0][i][j] = (red[i][j]+red2[i][j])/2;
                     new_image[1][i][j] = (gre[i][j]+gre2[i][j])/2;
                     new_image[2][i][j] = (blu[i][j]+blu2[i][j])/2;
                     new_image[3][i][j] = 255;
                 }
                 }
             }
        image_cache.push(assign(new_image));
        viewImage(image_cache.top());
        (doubleEx_matrix[0]).freeMatrix();
        (doubleEx_matrix[1]).freeMatrix();
        (doubleEx_matrix[2]).freeMatrix();
        (doubleEx_matrix[3]).freeMatrix();
        delete [] doubleEx_matrix;
    }
        enableButton();
}



void MainWindow::on_actionScreen_Shot_triggered()
{
    CaptureScreen* captureHelper = new CaptureScreen();
    connect(captureHelper, SIGNAL(signalCompleteCapture(QPixmap)), this, SLOT(onCompleteCapture(QPixmap)));
    captureHelper->show();
}

void MainWindow::onCompleteCapture(QPixmap captureImage)
{
    QFile file("tempFile.png");
    file.open(QIODevice::WriteOnly);
    captureImage.save(&file, "PNG");

    fileName = file.fileName();
    QByteArray ba = fileName.toLatin1();
    const char *filename;
    filename=ba.data();
    if (new_image!=nullptr){
        (new_image[0]).freeMatrix();
        (new_image[1]).freeMatrix();
        (new_image[2]).freeMatrix();
        (new_image[3]).freeMatrix();
        delete[] new_image;
    }
    new_image=png_read(filename);
    image_cache.push(assign(new_image));
    viewImage(image_cache.top());
    enableButton();
    this->showNormal();
}

void MainWindow::Cut_Screen_triggered()
{
    on_actionScreen_Shot_triggered();
}

void MainWindow::on_actionFourierReal_triggered()
{
    FT_real_part();
    FourierReal=new QWidget;
    float scale_tem=1;
    int maxWidth=1000;
    int maxHeight=1000;
    int Width=new_image->getcolnum();
    int Height=new_image->getrownum();
    if (Width>maxWidth){
        scale_tem=float(maxWidth)/Width;
        Width=maxWidth;
        Height=Height*scale_tem;
    }
    if (Height>maxHeight){
        Width=Width*(float(maxHeight)/Height);
        scale_tem=scale_tem*(maxHeight/Height);
        Height=maxHeight;
    }
    FourierReal->setFixedSize(Width,Height);
    FourierReal->setWindowTitle("Fourier Real");
    FourierReal->setWindowIcon(QIcon(":new/prefix1/Icon/Real.png"));
    QLabel *label=new QLabel(FourierReal);
    label->setGeometry(0,0,Width,Height);
    unsigned char *cache;
    cache=png_cache(new_image);
    QImage *image = new QImage(cache,new_image->getcolnum(),new_image->getrownum(),QImage::Format_RGBA8888);
    QPixmap pix=QPixmap::fromImage(*image);
    pix=pix.scaled(new_image->getcolnum()*scale_tem,new_image->getrownum()*scale_tem);
    label->setPixmap(pix);
    delete[] cache;
    delete image;
    FourierReal->show();
    label->show();
    FourierReal->setAttribute(Qt::WA_DeleteOnClose,true);
    FourierReal->setWindowModality(Qt::ApplicationModal);
    label->setAttribute(Qt::WA_DeleteOnClose,true);
}

void MainWindow::on_actionFourierImaginary_triggered()
{
    FT_imaginary();
    FourierImaginary=new QWidget;
    float scale_tem=1;
    int maxWidth=1000;
    int maxHeight=1000;
    int Width=new_image->getcolnum();
    int Height=new_image->getrownum();
    if (Width>maxWidth){
        scale_tem=float(maxWidth)/Width;
        Width=maxWidth;
        Height=Height*scale_tem;
    }
    if (Height>maxHeight){
        Width=Width*(float(maxHeight)/Height);
        scale_tem=scale_tem*(maxHeight/Height);
        Height=maxHeight;
    }
    FourierImaginary->setFixedSize(Width,Height);
    FourierImaginary->setWindowTitle("Fourier Imaginary");
    FourierImaginary->setWindowIcon(QIcon(":new/prefix1/Icon/Imaginary.png"));
    QLabel *label=new QLabel(FourierImaginary);
    label->setGeometry(0,0,Width,Height);
    unsigned char *cache;
    cache=png_cache(new_image);
    QImage *image = new QImage(cache,new_image->getcolnum(),new_image->getrownum(),QImage::Format_RGBA8888);
    QPixmap pix=QPixmap::fromImage(*image);
    pix=pix.scaled(new_image->getcolnum()*scale_tem,new_image->getrownum()*scale_tem);
    label->setPixmap(pix);
    delete[] cache;
    delete image;
    FourierImaginary->show();
    label->show();
    FourierImaginary->setAttribute(Qt::WA_DeleteOnClose,true);
    FourierImaginary->setWindowModality(Qt::ApplicationModal);
    label->setAttribute(Qt::WA_DeleteOnClose,true);
}

void MainWindow::on_actionFourierMagnitude_triggered()
{
    FT_magnitude();
    FourierMagnitude=new QWidget;
    float scale_tem=1;
    int maxWidth=1000;
    int maxHeight=1000;
    int Width=new_image->getcolnum();
    int Height=new_image->getrownum();
    if (Width>maxWidth){
        scale_tem=float(maxWidth)/Width;
        Width=maxWidth;
        Height=Height*scale_tem;
    }
    if (Height>maxHeight){
        Width=Width*(float(maxHeight)/Height);
        scale_tem=scale_tem*(maxHeight/Height);
        Height=maxHeight;
    }
    FourierMagnitude->setFixedSize(Width,Height);
    FourierMagnitude->setWindowTitle("Fourier Magnitude");
    FourierMagnitude->setWindowIcon(QIcon(":new/prefix1/Icon/Magnitude.png"));
    QLabel *label=new QLabel(FourierMagnitude);
    label->setGeometry(0,0,Width,Height);
    unsigned char *cache;
    cache=png_cache(new_image);
    QImage *image = new QImage(cache,new_image->getcolnum(),new_image->getrownum(),QImage::Format_RGBA8888);
    QPixmap pix=QPixmap::fromImage(*image);
    pix=pix.scaled(new_image->getcolnum()*scale_tem,new_image->getrownum()*scale_tem);
    label->setPixmap(pix);
    delete[] cache;
    delete image;
    FourierMagnitude->show();
    label->show();
    FourierMagnitude->setAttribute(Qt::WA_DeleteOnClose,true);
    FourierMagnitude->setWindowModality(Qt::ApplicationModal);
    label->setAttribute(Qt::WA_DeleteOnClose,true);
}

void MainWindow::on_actionFourierPhase_triggered()
{
    FT_phase();
    FourierPhase=new QWidget;
    float scale_tem=1;
    int maxWidth=1000;
    int maxHeight=1000;
    int Width=new_image->getcolnum();
    int Height=new_image->getrownum();
    if (Width>maxWidth){
        scale_tem=float(maxWidth)/Width;
        Width=maxWidth;
        Height=Height*scale_tem;
    }
    if (Height>maxHeight){
        Width=Width*(float(maxHeight)/Height);
        scale_tem=scale_tem*(maxHeight/Height);
        Height=maxHeight;
    }
    FourierPhase->setFixedSize(Width,Height);
    FourierPhase->setWindowTitle("Fourier Phase");
    FourierPhase->setWindowIcon(QIcon(":new/prefix1/Icon/Phase.png"));
    QLabel *label=new QLabel(FourierPhase);
    label->setGeometry(0,0,Width,Height);
    unsigned char *cache;
    cache=png_cache(new_image);
    QImage *image = new QImage(cache,new_image->getcolnum(),new_image->getrownum(),QImage::Format_RGBA8888);
    QPixmap pix=QPixmap::fromImage(*image);
    pix=pix.scaled(new_image->getcolnum()*scale_tem,new_image->getrownum()*scale_tem);
    label->setPixmap(pix);
    delete[] cache;
    delete image;
    FourierPhase->show();
    label->show();
    FourierPhase->setAttribute(Qt::WA_DeleteOnClose,true);
    FourierPhase->setWindowModality(Qt::ApplicationModal);
    label->setAttribute(Qt::WA_DeleteOnClose,true);
}

void MainWindow::on_actionIntelligent_Image_Segmentation_triggered()
{
    segTriggered=true;
    disableButton();
    this->setCursor((QCursor(Qt::CrossCursor)));
}

void MainWindow::on_actionScreen_Cut_triggered()
{
    this->hide();
    on_actionScreen_Shot_triggered();
}

void MainWindow::on_actionPerspective_Transformation_triggered()
{
    disableButton();
    ui->pointlabel->setEnabled(true);
    ui->pointlabel->show();
    perTriggered=true;
}
