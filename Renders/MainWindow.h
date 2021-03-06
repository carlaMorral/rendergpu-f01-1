#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <Renders/GLWidget.h>
#include <GeometryBuilders/Builder.h>

#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
class QSlider;
class GLWidget;
QT_END_NAMESPACE

namespace Ui {
   class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool changes; // Variable de control d
protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    Builder  *builder;
    GLWidget  *glWidget;

    int currentLight; //0: point, 1: directional, 2: spotlight
private slots:

    void on_persVerticalAngleSpin_valueChanged(double arg1);

    void on_persNearSpin_valueChanged(double arg1);

    void on_persFarSpin_valueChanged(double arg1);

    void on_lookEyeXSpin_valueChanged(double arg1);

    void on_lookEyeYSpin_valueChanged(double arg1);

    void on_lookEyeZSpin_valueChanged(double arg1);

    void on_lookCenterXSpin_valueChanged(double arg1);

    void on_lookCenterYSpin_valueChanged(double arg1);

    void on_lookCenterZSpin_valueChanged(double arg1);

    void on_lookUpXSpin_valueChanged(double arg1);

    void on_lookUpYSpin_valueChanged(double arg1);

    void on_lookUpZSpin_valueChanged(double arg1);

    void on_scaleSpin_valueChanged(double arg1);

    void on_translateXSpin_valueChanged(double arg1);

    void on_translateYSpin_valueChanged(double arg1);

    void on_translateZSpin_valueChanged(double arg1);

    void on_rotateAngleSpin_valueChanged(double arg1);

    void on_rotateXSpin_valueChanged(double arg1);

    void on_rotateYSpin_valueChanged(double arg1);

    void on_rotateZSpin_valueChanged(double arg1);

    void on_lightPosXSpin_valueChanged(double arg1);

    void on_lightPosYSpin_valueChanged(double arg1);

    void on_lightPosZSpin_valueChanged(double arg1);

    void on_actionAbout_Qt_triggered();

    void on_action_exit_triggered();

    void on_persVerticalAngleSlider_valueChanged(int value);

    void on_persNearSlider_valueChanged(int value);

    void on_persFarSlider_valueChanged(int value);

    void on_lightId1Spin_valueChanged(double arg1);

    void on_lightId2Spin_valueChanged(double arg1);

    void on_lightId3Spin_valueChanged(double arg1);

    void on_lightIa1Spin_valueChanged(double arg1);

    void on_lightIa2Spin_valueChanged(double arg1);

    void on_lightIa3Spin_valueChanged(double arg1);

    void on_lightIs1Spin_valueChanged(double arg1);

    void on_lightIs2Spin_valueChanged(double arg1);

    void on_lightIs3Spin_valueChanged(double arg1);

    void on_textureFileEdit_returnPressed();

    void on_browseTextureBtn_pressed();

    void on_rotateAngleSlider_valueChanged(int value);

    void setObsCamera(shared_ptr<Camera> cam);

    void setFrustumCamera(shared_ptr<Camera> cam);


    void on_lightCoefC_valueChanged(double arg1);
    void on_lightCoefB_valueChanged(double arg1);
    void on_lightCoefA_valueChanged(double arg1);
    void on_pointLightRadioButton_toggled(bool checked);
    void on_dirLightRadioButton_toggled(bool checked);
    void on_spotLightRadioButton_toggled(bool checked);
    void on_lightDirXSpin_valueChanged(double arg1);
    void on_lightDirYSpin_valueChanged(double arg1);
    void on_lightDirZSpin_valueChanged(double arg1);
    void on_dirLightIaXSpin_valueChanged(double arg1);
    void on_dirLightIaYSpin_valueChanged(double arg1);
    void on_dirLightIaZSpin_valueChanged(double arg1);
    void on_dirLightIdXSpin_valueChanged(double arg1);
    void on_dirLightIdYSpin_valueChanged(double arg1);
    void on_dirLightIdZSpin_valueChanged(double arg1);
    void on_dirLightIsXSpin_valueChanged(double arg1);
    void on_dirLightIsYSpin_valueChanged(double arg1);
    void on_dirLightIsZSpin_valueChanged(double arg1);


    void setPointLight();
    void setDirLight();
    void setSpotLight();
    void on_lightSpotXSpin_valueChanged(double arg1);
    void on_lightSpotYSpin_valueChanged(double arg1);
    void on_lightSpotZSpin_valueChanged(double arg1);
    void on_spotLightIaXSpin_valueChanged(double arg1);
    void on_spotLightIaYSpin_valueChanged(double arg1);
    void on_spotLightIaZSpin_valueChanged(double arg1);
    void on_spotLightIdXSpin_valueChanged(double arg1);
    void on_spotLightIdYSpin_valueChanged(double arg1);
    void on_spotLightIdZSpin_valueChanged(double arg1);
    void on_spotLightIsXSpin_valueChanged(double arg1);
    void on_spotLightIsYSpin_valueChanged(double arg1);
    void on_spotLightIsZSpin_valueChanged(double arg1);
    void on_spotLightAngleSlider_valueChanged(int value);
    void on_spotLightSharpnessSlider_valueChanged(int value);
};

#endif // MAINWINDOW_H
