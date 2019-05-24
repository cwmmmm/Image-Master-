#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "basic_dialog.h"
#include"rgb_controller.h"
#include "mymatrix.h"
#include "histogram.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;\

private slots:
    void mousePressEvent(QMouseEvent* event) override;

    void mouseMoveEvent(QMouseEvent* event) override;

    void keyPressEvent(QKeyEvent* event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void enableButton();

    void disableButton();

    void viewImage(Matrix *matrix);

    void viewImage_close();

    void on_actionOpen_triggered();

    void on_actionClose_Image_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionZoom_in_triggered();

    void on_actionZoom_out_triggered();

    void on_actionCut_triggered();

    void on_actionCancel_triggered();

    void on_actionAccept_triggered();

    void on_actionBrightness_triggered();

    void brightness_adjustment_main();

    void brightness_OK();

    void brightness_Cancel();

    void on_actionContrast_triggered();

    void contrast_adjustment_main();

    void contrast_OK();

    void contrast_Cancel();

    void on_actionAlpha_triggered();

    void alpha_adjustment_main();

    void alpha_OK();

    void alpha_Cancel();

    void on_actionBlack_White_triggered();

    void on_actionGrey_Level_triggered();

    void on_actionKeep_Red_triggered();

    void on_actionKeep_Green_triggered();

    void on_actionKeep_Blue_triggered();

    void on_actionReduce_Red_triggered();

    void on_actionReduce_Green_triggered();

    void on_actionReduce_Blue_triggered();

    void on_actionInvert_Color_triggered();

    void on_actionRGB_Controller_triggered();

    void rgb_adjustment_main();

    void rgb_OK();

    void rgb_Cancel();

    void on_actionRotate_Right_90_triggered();

    void on_actionRotate_180_triggered();

    void on_actionRotate_Left_90_triggered();

    void on_actionCustom_Rotation_triggered();

    void custom_rotation_main();

    void custom_rotation_OK();

    void custom_rotation_Cancel();

    void on_actionHorozontal_Mirror_triggered();

    void on_actionVertical_Mirror_triggered();

    void on_actionLow_Sharpen_triggered();

    void on_actionHigh_Sharpen_triggered();

    void on_actionCustom_Sharpen_triggered();

    void custom_sharpen_main();

    void custom_sharpen_Cancel();

    void custom_sharpen_OK();

    void on_actionLow_Reduce_triggered();

    void on_actionHigh_Reduce_triggered();

    void on_actionCustom_Reduce_triggered();

    void custom_reduce_main();

    void custom_reduce_OK();

    void custom_reduce_Cancel();

    void on_actionR_Type_triggered();

    void on_actionG_Type_triggered();

    void on_actionB_Type_triggered();

    void on_actionSynthetical_triggered();

    void on_actionDetection_triggered();

    void detection_main();

    void detection_OK();

    void detection_Cancel();

    void on_actionAnalog_Double_Exposure_triggered();

    void on_actionHorizontal_triggered();

    void on_actionVertical_triggered();

    void on_actionContour_triggered();

    void on_actionBrownness_triggered();

    void on_actionFrost_Glass_triggered();

    void on_actionEmbossment_triggered();

    void on_actionLow_Smooth_triggered();

    void on_actionHigh_Smooth_triggered();

    void on_actionSaturation_triggered();

    void Adjust_Satuation_main();

    void Adjust_Satuation_OK();

    void Adjust_Satuation_Cancel();

    void on_actionScreen_Shot_triggered();

    void onCompleteCapture(QPixmap captureImage);

    void Cut_Screen_triggered();

    void on_actionFourierReal_triggered();

    void on_actionFourierImaginary_triggered();

    void on_actionFourierMagnitude_triggered();

    void on_actionFourierPhase_triggered();

    void on_actionIntelligent_Image_Segmentation_triggered();

    void on_actionScreen_Cut_triggered();

    void on_actionPerspective_Transformation_triggered();

protected:
    bool m_isMousePress;
    bool segTriggered=false;
    bool perTriggered=false;
    vector<Point>  ptr ;
    int idx=0;
    QPoint m_beginPoint, m_endPoint;
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow *ui;
    basic_dialog *brightness_window;
    basic_dialog *contrast_window;
    basic_dialog *satuation_window;
    basic_dialog *alpha_window;
    basic_dialog *custom_sharpen_window;
    basic_dialog *custom_rotation_window;
    basic_dialog *custom_reduce_window;
    basic_dialog *detection_window;
    RGB_Controller *rgb_window;
    Red_Histogram *R_type;
    Green_Histogram *G_type;
    Blue_Histogram *B_type;
    Synthetical_Histogram *Synthetical;
    QWidget *FourierReal;
    QWidget *FourierImaginary;
    QWidget *FourierMagnitude;
    QWidget *FourierPhase;
};

#endif // MAINWINDOW_H
