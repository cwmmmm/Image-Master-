/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[104];
    char stringdata0[2519];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 15), // "mousePressEvent"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 12), // "QMouseEvent*"
QT_MOC_LITERAL(4, 41, 5), // "event"
QT_MOC_LITERAL(5, 47, 14), // "mouseMoveEvent"
QT_MOC_LITERAL(6, 62, 13), // "keyPressEvent"
QT_MOC_LITERAL(7, 76, 10), // "QKeyEvent*"
QT_MOC_LITERAL(8, 87, 17), // "mouseReleaseEvent"
QT_MOC_LITERAL(9, 105, 12), // "enableButton"
QT_MOC_LITERAL(10, 118, 13), // "disableButton"
QT_MOC_LITERAL(11, 132, 9), // "viewImage"
QT_MOC_LITERAL(12, 142, 7), // "Matrix*"
QT_MOC_LITERAL(13, 150, 6), // "matrix"
QT_MOC_LITERAL(14, 157, 15), // "viewImage_close"
QT_MOC_LITERAL(15, 173, 23), // "on_actionOpen_triggered"
QT_MOC_LITERAL(16, 197, 30), // "on_actionClose_Image_triggered"
QT_MOC_LITERAL(17, 228, 23), // "on_actionSave_triggered"
QT_MOC_LITERAL(18, 252, 26), // "on_actionSave_as_triggered"
QT_MOC_LITERAL(19, 279, 23), // "on_actionUndo_triggered"
QT_MOC_LITERAL(20, 303, 23), // "on_actionRedo_triggered"
QT_MOC_LITERAL(21, 327, 26), // "on_actionZoom_in_triggered"
QT_MOC_LITERAL(22, 354, 27), // "on_actionZoom_out_triggered"
QT_MOC_LITERAL(23, 382, 22), // "on_actionCut_triggered"
QT_MOC_LITERAL(24, 405, 25), // "on_actionCancel_triggered"
QT_MOC_LITERAL(25, 431, 25), // "on_actionAccept_triggered"
QT_MOC_LITERAL(26, 457, 29), // "on_actionBrightness_triggered"
QT_MOC_LITERAL(27, 487, 26), // "brightness_adjustment_main"
QT_MOC_LITERAL(28, 514, 13), // "brightness_OK"
QT_MOC_LITERAL(29, 528, 17), // "brightness_Cancel"
QT_MOC_LITERAL(30, 546, 27), // "on_actionContrast_triggered"
QT_MOC_LITERAL(31, 574, 24), // "contrast_adjustment_main"
QT_MOC_LITERAL(32, 599, 11), // "contrast_OK"
QT_MOC_LITERAL(33, 611, 15), // "contrast_Cancel"
QT_MOC_LITERAL(34, 627, 24), // "on_actionAlpha_triggered"
QT_MOC_LITERAL(35, 652, 21), // "alpha_adjustment_main"
QT_MOC_LITERAL(36, 674, 8), // "alpha_OK"
QT_MOC_LITERAL(37, 683, 12), // "alpha_Cancel"
QT_MOC_LITERAL(38, 696, 30), // "on_actionBlack_White_triggered"
QT_MOC_LITERAL(39, 727, 29), // "on_actionGrey_Level_triggered"
QT_MOC_LITERAL(40, 757, 27), // "on_actionKeep_Red_triggered"
QT_MOC_LITERAL(41, 785, 29), // "on_actionKeep_Green_triggered"
QT_MOC_LITERAL(42, 815, 28), // "on_actionKeep_Blue_triggered"
QT_MOC_LITERAL(43, 844, 29), // "on_actionReduce_Red_triggered"
QT_MOC_LITERAL(44, 874, 31), // "on_actionReduce_Green_triggered"
QT_MOC_LITERAL(45, 906, 30), // "on_actionReduce_Blue_triggered"
QT_MOC_LITERAL(46, 937, 31), // "on_actionInvert_Color_triggered"
QT_MOC_LITERAL(47, 969, 33), // "on_actionRGB_Controller_trigg..."
QT_MOC_LITERAL(48, 1003, 19), // "rgb_adjustment_main"
QT_MOC_LITERAL(49, 1023, 6), // "rgb_OK"
QT_MOC_LITERAL(50, 1030, 10), // "rgb_Cancel"
QT_MOC_LITERAL(51, 1041, 34), // "on_actionRotate_Right_90_trig..."
QT_MOC_LITERAL(52, 1076, 29), // "on_actionRotate_180_triggered"
QT_MOC_LITERAL(53, 1106, 33), // "on_actionRotate_Left_90_trigg..."
QT_MOC_LITERAL(54, 1140, 34), // "on_actionCustom_Rotation_trig..."
QT_MOC_LITERAL(55, 1175, 20), // "custom_rotation_main"
QT_MOC_LITERAL(56, 1196, 18), // "custom_rotation_OK"
QT_MOC_LITERAL(57, 1215, 22), // "custom_rotation_Cancel"
QT_MOC_LITERAL(58, 1238, 36), // "on_actionHorozontal_Mirror_tr..."
QT_MOC_LITERAL(59, 1275, 34), // "on_actionVertical_Mirror_trig..."
QT_MOC_LITERAL(60, 1310, 30), // "on_actionLow_Sharpen_triggered"
QT_MOC_LITERAL(61, 1341, 31), // "on_actionHigh_Sharpen_triggered"
QT_MOC_LITERAL(62, 1373, 33), // "on_actionCustom_Sharpen_trigg..."
QT_MOC_LITERAL(63, 1407, 19), // "custom_sharpen_main"
QT_MOC_LITERAL(64, 1427, 21), // "custom_sharpen_Cancel"
QT_MOC_LITERAL(65, 1449, 17), // "custom_sharpen_OK"
QT_MOC_LITERAL(66, 1467, 29), // "on_actionLow_Reduce_triggered"
QT_MOC_LITERAL(67, 1497, 30), // "on_actionHigh_Reduce_triggered"
QT_MOC_LITERAL(68, 1528, 32), // "on_actionCustom_Reduce_triggered"
QT_MOC_LITERAL(69, 1561, 18), // "custom_reduce_main"
QT_MOC_LITERAL(70, 1580, 16), // "custom_reduce_OK"
QT_MOC_LITERAL(71, 1597, 20), // "custom_reduce_Cancel"
QT_MOC_LITERAL(72, 1618, 25), // "on_actionR_Type_triggered"
QT_MOC_LITERAL(73, 1644, 25), // "on_actionG_Type_triggered"
QT_MOC_LITERAL(74, 1670, 25), // "on_actionB_Type_triggered"
QT_MOC_LITERAL(75, 1696, 30), // "on_actionSynthetical_triggered"
QT_MOC_LITERAL(76, 1727, 28), // "on_actionDetection_triggered"
QT_MOC_LITERAL(77, 1756, 14), // "detection_main"
QT_MOC_LITERAL(78, 1771, 12), // "detection_OK"
QT_MOC_LITERAL(79, 1784, 16), // "detection_Cancel"
QT_MOC_LITERAL(80, 1801, 41), // "on_actionAnalog_Double_Exposu..."
QT_MOC_LITERAL(81, 1843, 29), // "on_actionHorizontal_triggered"
QT_MOC_LITERAL(82, 1873, 27), // "on_actionVertical_triggered"
QT_MOC_LITERAL(83, 1901, 26), // "on_actionContour_triggered"
QT_MOC_LITERAL(84, 1928, 28), // "on_actionBrownness_triggered"
QT_MOC_LITERAL(85, 1957, 30), // "on_actionFrost_Glass_triggered"
QT_MOC_LITERAL(86, 1988, 29), // "on_actionEmbossment_triggered"
QT_MOC_LITERAL(87, 2018, 29), // "on_actionLow_Smooth_triggered"
QT_MOC_LITERAL(88, 2048, 30), // "on_actionHigh_Smooth_triggered"
QT_MOC_LITERAL(89, 2079, 29), // "on_actionSaturation_triggered"
QT_MOC_LITERAL(90, 2109, 21), // "Adjust_Satuation_main"
QT_MOC_LITERAL(91, 2131, 19), // "Adjust_Satuation_OK"
QT_MOC_LITERAL(92, 2151, 23), // "Adjust_Satuation_Cancel"
QT_MOC_LITERAL(93, 2175, 30), // "on_actionScreen_Shot_triggered"
QT_MOC_LITERAL(94, 2206, 17), // "onCompleteCapture"
QT_MOC_LITERAL(95, 2224, 12), // "captureImage"
QT_MOC_LITERAL(96, 2237, 20), // "Cut_Screen_triggered"
QT_MOC_LITERAL(97, 2258, 30), // "on_actionFourierReal_triggered"
QT_MOC_LITERAL(98, 2289, 35), // "on_actionFourierImaginary_tri..."
QT_MOC_LITERAL(99, 2325, 35), // "on_actionFourierMagnitude_tri..."
QT_MOC_LITERAL(100, 2361, 31), // "on_actionFourierPhase_triggered"
QT_MOC_LITERAL(101, 2393, 49), // "on_actionIntelligent_Image_Se..."
QT_MOC_LITERAL(102, 2443, 29), // "on_actionScreen_Cut_triggered"
QT_MOC_LITERAL(103, 2473, 45) // "on_actionPerspective_Transfor..."

    },
    "MainWindow\0mousePressEvent\0\0QMouseEvent*\0"
    "event\0mouseMoveEvent\0keyPressEvent\0"
    "QKeyEvent*\0mouseReleaseEvent\0enableButton\0"
    "disableButton\0viewImage\0Matrix*\0matrix\0"
    "viewImage_close\0on_actionOpen_triggered\0"
    "on_actionClose_Image_triggered\0"
    "on_actionSave_triggered\0"
    "on_actionSave_as_triggered\0"
    "on_actionUndo_triggered\0on_actionRedo_triggered\0"
    "on_actionZoom_in_triggered\0"
    "on_actionZoom_out_triggered\0"
    "on_actionCut_triggered\0on_actionCancel_triggered\0"
    "on_actionAccept_triggered\0"
    "on_actionBrightness_triggered\0"
    "brightness_adjustment_main\0brightness_OK\0"
    "brightness_Cancel\0on_actionContrast_triggered\0"
    "contrast_adjustment_main\0contrast_OK\0"
    "contrast_Cancel\0on_actionAlpha_triggered\0"
    "alpha_adjustment_main\0alpha_OK\0"
    "alpha_Cancel\0on_actionBlack_White_triggered\0"
    "on_actionGrey_Level_triggered\0"
    "on_actionKeep_Red_triggered\0"
    "on_actionKeep_Green_triggered\0"
    "on_actionKeep_Blue_triggered\0"
    "on_actionReduce_Red_triggered\0"
    "on_actionReduce_Green_triggered\0"
    "on_actionReduce_Blue_triggered\0"
    "on_actionInvert_Color_triggered\0"
    "on_actionRGB_Controller_triggered\0"
    "rgb_adjustment_main\0rgb_OK\0rgb_Cancel\0"
    "on_actionRotate_Right_90_triggered\0"
    "on_actionRotate_180_triggered\0"
    "on_actionRotate_Left_90_triggered\0"
    "on_actionCustom_Rotation_triggered\0"
    "custom_rotation_main\0custom_rotation_OK\0"
    "custom_rotation_Cancel\0"
    "on_actionHorozontal_Mirror_triggered\0"
    "on_actionVertical_Mirror_triggered\0"
    "on_actionLow_Sharpen_triggered\0"
    "on_actionHigh_Sharpen_triggered\0"
    "on_actionCustom_Sharpen_triggered\0"
    "custom_sharpen_main\0custom_sharpen_Cancel\0"
    "custom_sharpen_OK\0on_actionLow_Reduce_triggered\0"
    "on_actionHigh_Reduce_triggered\0"
    "on_actionCustom_Reduce_triggered\0"
    "custom_reduce_main\0custom_reduce_OK\0"
    "custom_reduce_Cancel\0on_actionR_Type_triggered\0"
    "on_actionG_Type_triggered\0"
    "on_actionB_Type_triggered\0"
    "on_actionSynthetical_triggered\0"
    "on_actionDetection_triggered\0"
    "detection_main\0detection_OK\0"
    "detection_Cancel\0"
    "on_actionAnalog_Double_Exposure_triggered\0"
    "on_actionHorizontal_triggered\0"
    "on_actionVertical_triggered\0"
    "on_actionContour_triggered\0"
    "on_actionBrownness_triggered\0"
    "on_actionFrost_Glass_triggered\0"
    "on_actionEmbossment_triggered\0"
    "on_actionLow_Smooth_triggered\0"
    "on_actionHigh_Smooth_triggered\0"
    "on_actionSaturation_triggered\0"
    "Adjust_Satuation_main\0Adjust_Satuation_OK\0"
    "Adjust_Satuation_Cancel\0"
    "on_actionScreen_Shot_triggered\0"
    "onCompleteCapture\0captureImage\0"
    "Cut_Screen_triggered\0"
    "on_actionFourierReal_triggered\0"
    "on_actionFourierImaginary_triggered\0"
    "on_actionFourierMagnitude_triggered\0"
    "on_actionFourierPhase_triggered\0"
    "on_actionIntelligent_Image_Segmentation_triggered\0"
    "on_actionScreen_Cut_triggered\0"
    "on_actionPerspective_Transformation_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      96,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  494,    2, 0x08 /* Private */,
       5,    1,  497,    2, 0x08 /* Private */,
       6,    1,  500,    2, 0x08 /* Private */,
       8,    1,  503,    2, 0x08 /* Private */,
       9,    0,  506,    2, 0x08 /* Private */,
      10,    0,  507,    2, 0x08 /* Private */,
      11,    1,  508,    2, 0x08 /* Private */,
      14,    0,  511,    2, 0x08 /* Private */,
      15,    0,  512,    2, 0x08 /* Private */,
      16,    0,  513,    2, 0x08 /* Private */,
      17,    0,  514,    2, 0x08 /* Private */,
      18,    0,  515,    2, 0x08 /* Private */,
      19,    0,  516,    2, 0x08 /* Private */,
      20,    0,  517,    2, 0x08 /* Private */,
      21,    0,  518,    2, 0x08 /* Private */,
      22,    0,  519,    2, 0x08 /* Private */,
      23,    0,  520,    2, 0x08 /* Private */,
      24,    0,  521,    2, 0x08 /* Private */,
      25,    0,  522,    2, 0x08 /* Private */,
      26,    0,  523,    2, 0x08 /* Private */,
      27,    0,  524,    2, 0x08 /* Private */,
      28,    0,  525,    2, 0x08 /* Private */,
      29,    0,  526,    2, 0x08 /* Private */,
      30,    0,  527,    2, 0x08 /* Private */,
      31,    0,  528,    2, 0x08 /* Private */,
      32,    0,  529,    2, 0x08 /* Private */,
      33,    0,  530,    2, 0x08 /* Private */,
      34,    0,  531,    2, 0x08 /* Private */,
      35,    0,  532,    2, 0x08 /* Private */,
      36,    0,  533,    2, 0x08 /* Private */,
      37,    0,  534,    2, 0x08 /* Private */,
      38,    0,  535,    2, 0x08 /* Private */,
      39,    0,  536,    2, 0x08 /* Private */,
      40,    0,  537,    2, 0x08 /* Private */,
      41,    0,  538,    2, 0x08 /* Private */,
      42,    0,  539,    2, 0x08 /* Private */,
      43,    0,  540,    2, 0x08 /* Private */,
      44,    0,  541,    2, 0x08 /* Private */,
      45,    0,  542,    2, 0x08 /* Private */,
      46,    0,  543,    2, 0x08 /* Private */,
      47,    0,  544,    2, 0x08 /* Private */,
      48,    0,  545,    2, 0x08 /* Private */,
      49,    0,  546,    2, 0x08 /* Private */,
      50,    0,  547,    2, 0x08 /* Private */,
      51,    0,  548,    2, 0x08 /* Private */,
      52,    0,  549,    2, 0x08 /* Private */,
      53,    0,  550,    2, 0x08 /* Private */,
      54,    0,  551,    2, 0x08 /* Private */,
      55,    0,  552,    2, 0x08 /* Private */,
      56,    0,  553,    2, 0x08 /* Private */,
      57,    0,  554,    2, 0x08 /* Private */,
      58,    0,  555,    2, 0x08 /* Private */,
      59,    0,  556,    2, 0x08 /* Private */,
      60,    0,  557,    2, 0x08 /* Private */,
      61,    0,  558,    2, 0x08 /* Private */,
      62,    0,  559,    2, 0x08 /* Private */,
      63,    0,  560,    2, 0x08 /* Private */,
      64,    0,  561,    2, 0x08 /* Private */,
      65,    0,  562,    2, 0x08 /* Private */,
      66,    0,  563,    2, 0x08 /* Private */,
      67,    0,  564,    2, 0x08 /* Private */,
      68,    0,  565,    2, 0x08 /* Private */,
      69,    0,  566,    2, 0x08 /* Private */,
      70,    0,  567,    2, 0x08 /* Private */,
      71,    0,  568,    2, 0x08 /* Private */,
      72,    0,  569,    2, 0x08 /* Private */,
      73,    0,  570,    2, 0x08 /* Private */,
      74,    0,  571,    2, 0x08 /* Private */,
      75,    0,  572,    2, 0x08 /* Private */,
      76,    0,  573,    2, 0x08 /* Private */,
      77,    0,  574,    2, 0x08 /* Private */,
      78,    0,  575,    2, 0x08 /* Private */,
      79,    0,  576,    2, 0x08 /* Private */,
      80,    0,  577,    2, 0x08 /* Private */,
      81,    0,  578,    2, 0x08 /* Private */,
      82,    0,  579,    2, 0x08 /* Private */,
      83,    0,  580,    2, 0x08 /* Private */,
      84,    0,  581,    2, 0x08 /* Private */,
      85,    0,  582,    2, 0x08 /* Private */,
      86,    0,  583,    2, 0x08 /* Private */,
      87,    0,  584,    2, 0x08 /* Private */,
      88,    0,  585,    2, 0x08 /* Private */,
      89,    0,  586,    2, 0x08 /* Private */,
      90,    0,  587,    2, 0x08 /* Private */,
      91,    0,  588,    2, 0x08 /* Private */,
      92,    0,  589,    2, 0x08 /* Private */,
      93,    0,  590,    2, 0x08 /* Private */,
      94,    1,  591,    2, 0x08 /* Private */,
      96,    0,  594,    2, 0x08 /* Private */,
      97,    0,  595,    2, 0x08 /* Private */,
      98,    0,  596,    2, 0x08 /* Private */,
      99,    0,  597,    2, 0x08 /* Private */,
     100,    0,  598,    2, 0x08 /* Private */,
     101,    0,  599,    2, 0x08 /* Private */,
     102,    0,  600,    2, 0x08 /* Private */,
     103,    0,  601,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 7,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPixmap,   95,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 1: _t->mouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 2: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 3: _t->mouseReleaseEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 4: _t->enableButton(); break;
        case 5: _t->disableButton(); break;
        case 6: _t->viewImage((*reinterpret_cast< Matrix*(*)>(_a[1]))); break;
        case 7: _t->viewImage_close(); break;
        case 8: _t->on_actionOpen_triggered(); break;
        case 9: _t->on_actionClose_Image_triggered(); break;
        case 10: _t->on_actionSave_triggered(); break;
        case 11: _t->on_actionSave_as_triggered(); break;
        case 12: _t->on_actionUndo_triggered(); break;
        case 13: _t->on_actionRedo_triggered(); break;
        case 14: _t->on_actionZoom_in_triggered(); break;
        case 15: _t->on_actionZoom_out_triggered(); break;
        case 16: _t->on_actionCut_triggered(); break;
        case 17: _t->on_actionCancel_triggered(); break;
        case 18: _t->on_actionAccept_triggered(); break;
        case 19: _t->on_actionBrightness_triggered(); break;
        case 20: _t->brightness_adjustment_main(); break;
        case 21: _t->brightness_OK(); break;
        case 22: _t->brightness_Cancel(); break;
        case 23: _t->on_actionContrast_triggered(); break;
        case 24: _t->contrast_adjustment_main(); break;
        case 25: _t->contrast_OK(); break;
        case 26: _t->contrast_Cancel(); break;
        case 27: _t->on_actionAlpha_triggered(); break;
        case 28: _t->alpha_adjustment_main(); break;
        case 29: _t->alpha_OK(); break;
        case 30: _t->alpha_Cancel(); break;
        case 31: _t->on_actionBlack_White_triggered(); break;
        case 32: _t->on_actionGrey_Level_triggered(); break;
        case 33: _t->on_actionKeep_Red_triggered(); break;
        case 34: _t->on_actionKeep_Green_triggered(); break;
        case 35: _t->on_actionKeep_Blue_triggered(); break;
        case 36: _t->on_actionReduce_Red_triggered(); break;
        case 37: _t->on_actionReduce_Green_triggered(); break;
        case 38: _t->on_actionReduce_Blue_triggered(); break;
        case 39: _t->on_actionInvert_Color_triggered(); break;
        case 40: _t->on_actionRGB_Controller_triggered(); break;
        case 41: _t->rgb_adjustment_main(); break;
        case 42: _t->rgb_OK(); break;
        case 43: _t->rgb_Cancel(); break;
        case 44: _t->on_actionRotate_Right_90_triggered(); break;
        case 45: _t->on_actionRotate_180_triggered(); break;
        case 46: _t->on_actionRotate_Left_90_triggered(); break;
        case 47: _t->on_actionCustom_Rotation_triggered(); break;
        case 48: _t->custom_rotation_main(); break;
        case 49: _t->custom_rotation_OK(); break;
        case 50: _t->custom_rotation_Cancel(); break;
        case 51: _t->on_actionHorozontal_Mirror_triggered(); break;
        case 52: _t->on_actionVertical_Mirror_triggered(); break;
        case 53: _t->on_actionLow_Sharpen_triggered(); break;
        case 54: _t->on_actionHigh_Sharpen_triggered(); break;
        case 55: _t->on_actionCustom_Sharpen_triggered(); break;
        case 56: _t->custom_sharpen_main(); break;
        case 57: _t->custom_sharpen_Cancel(); break;
        case 58: _t->custom_sharpen_OK(); break;
        case 59: _t->on_actionLow_Reduce_triggered(); break;
        case 60: _t->on_actionHigh_Reduce_triggered(); break;
        case 61: _t->on_actionCustom_Reduce_triggered(); break;
        case 62: _t->custom_reduce_main(); break;
        case 63: _t->custom_reduce_OK(); break;
        case 64: _t->custom_reduce_Cancel(); break;
        case 65: _t->on_actionR_Type_triggered(); break;
        case 66: _t->on_actionG_Type_triggered(); break;
        case 67: _t->on_actionB_Type_triggered(); break;
        case 68: _t->on_actionSynthetical_triggered(); break;
        case 69: _t->on_actionDetection_triggered(); break;
        case 70: _t->detection_main(); break;
        case 71: _t->detection_OK(); break;
        case 72: _t->detection_Cancel(); break;
        case 73: _t->on_actionAnalog_Double_Exposure_triggered(); break;
        case 74: _t->on_actionHorizontal_triggered(); break;
        case 75: _t->on_actionVertical_triggered(); break;
        case 76: _t->on_actionContour_triggered(); break;
        case 77: _t->on_actionBrownness_triggered(); break;
        case 78: _t->on_actionFrost_Glass_triggered(); break;
        case 79: _t->on_actionEmbossment_triggered(); break;
        case 80: _t->on_actionLow_Smooth_triggered(); break;
        case 81: _t->on_actionHigh_Smooth_triggered(); break;
        case 82: _t->on_actionSaturation_triggered(); break;
        case 83: _t->Adjust_Satuation_main(); break;
        case 84: _t->Adjust_Satuation_OK(); break;
        case 85: _t->Adjust_Satuation_Cancel(); break;
        case 86: _t->on_actionScreen_Shot_triggered(); break;
        case 87: _t->onCompleteCapture((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        case 88: _t->Cut_Screen_triggered(); break;
        case 89: _t->on_actionFourierReal_triggered(); break;
        case 90: _t->on_actionFourierImaginary_triggered(); break;
        case 91: _t->on_actionFourierMagnitude_triggered(); break;
        case 92: _t->on_actionFourierPhase_triggered(); break;
        case 93: _t->on_actionIntelligent_Image_Segmentation_triggered(); break;
        case 94: _t->on_actionScreen_Cut_triggered(); break;
        case 95: _t->on_actionPerspective_Transformation_triggered(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 96)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 96;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 96)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 96;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
