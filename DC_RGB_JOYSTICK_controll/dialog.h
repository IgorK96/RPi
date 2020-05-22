#ifndef DIALOG_H
#define DIALOG_H

#include <stdint.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPiSPI.h>
#include <math.h>

#include <QDialog>
#include <QTimer>
#include <QTime>
#include <QWidget>

#define RED 27
#define GREEN 28
#define BLUE 25
#define PI 3.141592654

#define DC1a 4
#define DC1b 5
#define DC2a 21
#define DC2b 22
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void Analog_Read();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_horizontalSlider_2_sliderMoved(int position);

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::Dialog *ui;
    QTimer *tmr;

    int setup_pins();
    int dc_motor(int x2_value, int y2_value);
    int myAnalogRead(int spiChannel,int channelConfig,int analogChannel);
    int adjust_angle(int angle,char led);
    int calculate_next_pwm_duty_cycle(int angle, char led);
    int led_peak_angle;
    int dc_control_0 = 1;
    int dc_control_1 = 1;
    int control = 0;
    int start = 0x01;
    int end = 0x00;
    int chan = 0x00;
    int color = 1;
    int mode = 0;
    int dc_mode = 0;
    int j = 0;
    int j2 = 0;
    int up = 1;
    int x1_value = 0x00;
    int center_x1_pos = 512;
    int center_x2_pos = 512;
    int center_y1_pos = 512;
    int center_y2_pos = 512;
    int cw_x;
    int cw_y;
    int dc_sw = 0;
    int click6 = 0;
    int click7 = 0;
    int click8 = 0;
    int y1_value = 0x00;
    int sw1_value = 0x00;
    int x2_value = 0x00;
    int y2_value = 0x00;
    int x2_slider = 0x00;
    int y2_slider = 0x00;
    int sw2_value = 0x00;
    float dx,dy,rads;

};

#endif // DIALOG_H
