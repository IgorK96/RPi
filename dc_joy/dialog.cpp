#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setup_pins();

    tmr = new QTimer(this);
    connect(tmr, SIGNAL(timeout()), this, SLOT(Analog_Read()));
    tmr ->start(200);
}

Dialog::~Dialog()
{
    delete ui;
}

int Dialog::setup_pins()
{
    wiringPiSetup();
    wiringPiSPISetup(0,10000);
    softPwmCreate(DC1a, 0, 100);
    softPwmCreate(DC1b, 0, 100);
    softPwmCreate(DC2a, 0, 100);
    softPwmCreate(DC2b, 0, 100);
    softPwmCreate(RED, 0, 100);
    softPwmCreate(GREEN, 0, 50);
    softPwmCreate(BLUE, 0, 50);
    softPwmCreate(4, 0, 100);
    softPwmCreate(5, 0, 100);
    softPwmCreate(21, 0, 100);
    softPwmCreate(22, 0, 100);
    QPixmap on("/home/pi/Downloads/on.png");
    QPixmap off("/home/pi/Downloads/off.png");
    QIcon ButtonIconOn(on);
    QIcon BUttonIconOff(off);
    ui->pushButton_6->setIcon(ButtonIconOn);
    ui->pushButton_6->setIconSize(on.rect().size());
    ui->pushButton_7->setIcon(ButtonIconOn);
    ui->pushButton_7->setIconSize(on.rect().size());
    ui->pushButton_8->setIcon(ButtonIconOn);
    ui->pushButton_8->setIconSize(on.rect().size());


    return 0;
}
void Dialog::on_pushButton_clicked() //Breathing
{
    mode = 1;

}

void Dialog::on_pushButton_2_clicked()//Color wheel
{

    mode = 2;

}

void Dialog::on_pushButton_3_clicked()//Motor
{

    mode = 0;

}

void Dialog::on_pushButton_6_clicked()
{
    QPixmap on("/home/pi/Downloads/on.png");
    QPixmap off("/home/pi/Downloads/off.png");
    QIcon ButtonIconOn(on);
    QIcon BUttonIconOff(off);
    if(click6 == 0){
        ui->pushButton_6->setIcon(BUttonIconOff);
        ui->pushButton_6->setIconSize(off.rect().size());
        click6 = 1;
        dc_control_0 = 0;
    }else {
        ui->pushButton_6->setIcon(ButtonIconOn);
        ui->pushButton_6->setIconSize(on.rect().size());
        click6 = 0;
        dc_control_0 = 1;
    }
}

void Dialog::on_pushButton_7_clicked()
{

    QPixmap on("/home/pi/Downloads/on.png");
    QPixmap off("/home/pi/Downloads/off.png");
    QIcon ButtonIconOn(on);
    QIcon BUttonIconOff(off);
    if(click7 == 0){
        ui->pushButton_7->setIcon(BUttonIconOff);
        ui->pushButton_7->setIconSize(off.rect().size());
        click7 = 1;
        dc_control_1 = 0;
    }else {
        ui->pushButton_7->setIcon(ButtonIconOn);
        ui->pushButton_7->setIconSize(on.rect().size());
        click7 = 0;
        dc_control_1 = 1;
    }

}
void Dialog::on_pushButton_8_clicked()
{

    QPixmap on("/home/pi/Downloads/on.png");
    QPixmap off("/home/pi/Downloads/off.png");
    QIcon ButtonIconOn(on);
    QIcon BUttonIconOff(off);
    if(click8 == 0){
        ui->pushButton_8->setIcon(BUttonIconOff);
        ui->pushButton_8->setIconSize(off.rect().size());
        click8 = 1;
        control = 1;
    }else {
        ui->pushButton_8->setIcon(ButtonIconOn);
        ui->pushButton_8->setIconSize(on.rect().size());
        click8 = 0;
        control = 0;
    }
}
void Dialog::on_pushButton_5_clicked()
{
    dc_mode = 1;
    dc_sw = 0;
}

void Dialog::on_pushButton_4_clicked()
{
    dc_mode = 0;
}

int Dialog::myAnalogRead(int spiChannel, int channelConfig, int analogChannel)
{
    if(analogChannel<0 || analogChannel>7)
        return -1;
    unsigned char buffer[3] = {1}; // start bit
    buffer[1] = (channelConfig+analogChannel) << 4;
    wiringPiSPIDataRW(spiChannel, buffer, 3);
    return ( (buffer[1] & 3 ) << 8 ) + buffer[2];
}

int Dialog::adjust_angle(int angle, char led)
{

    if(led == 'R'){
        led_peak_angle = 90;
    }
    if(led == 'B'){
        led_peak_angle = 210;
    }
    if(led == 'G'){
        led_peak_angle = 330;
    }
    return(((angle - led_peak_angle)+360)%360);
}

int Dialog::calculate_next_pwm_duty_cycle(int angle, char led)
{
    angle = adjust_angle(angle, led);
    if((angle > 120) && (angle < 240)){
        return 0;
    }else{
        if(angle <= 120){
            return (100 - (angle * (100 / 120.0)));
        }
        else{
            return 100 - ((360 - angle) * (100 / 120.0));
        }}
}

void Dialog::on_horizontalSlider_sliderMoved(int position)
{   if(dc_mode == 1){
        if(position > 50 && position < 60){
            x2_slider = 500;
        }
        if(position > 65 && position < 76){
            x2_slider = 625;
        }
        if(position > 76 && position < 90){
            x2_slider = 860;
        }
        if(position > 90){
            x2_slider = 1000;
        }
        if(position < 45 && position > 36){
            x2_slider = 275;
        }
        if(position < 36 && position >20){
            x2_slider = 150;
        }
        if(position < 20){
            x2_slider = 0;
        }

    }
}


void Dialog::on_horizontalSlider_2_sliderMoved(int position)
{
    if(dc_mode == 1){
        if(position > 50 && position < 60){
            y2_slider = 500;
        }
        if(position > 65 && position < 76){
            y2_slider = 625;
        }
        if(position > 76 && position < 90){
            y2_slider = 860;
        }
        if(position > 90){
            y2_slider = 1000;
        }
        if(position < 45 && position > 36){
            y2_slider = 275;
        }
        if(position < 36 && position >20){
            y2_slider = 150;
        }
        if(position < 20){
            y2_slider = 0;
        }

    }
}

int Dialog::dc_motor(int x2_value, int y2_value)
{
    if(x2_value > 495 && x2_value < 515){
        softPwmWrite(22,0);
        softPwmWrite(21,0);
    }
    if(y2_value > 495 && y2_value < 515){
        softPwmWrite(4,0);
        softPwmWrite(5,0);
    }
    if(x2_value > 515 && x2_value < 640){
        softPwmWrite(22,50);
        softPwmWrite(21,00);
    }
    if(x2_value > 640 && x2_value < 865){
        softPwmWrite(22,75);
        softPwmWrite(21,05);
    }
    if(x2_value > 865 ){
        softPwmWrite(22,100);
        softPwmWrite(21,0);
    }
    if(x2_value < 495 && x2_value > 270){
        softPwmWrite(22,0);
        softPwmWrite(21,50);
    }
    if(x2_value < 270 && x2_value > 100){
        softPwmWrite(22,0);
        softPwmWrite(21,75);
    }
    if(x2_value < 100){
        softPwmWrite(22,0);
        softPwmWrite(21,100);
    }
    if(y2_value > 515 && y2_value < 640){
        softPwmWrite(4,50);
        softPwmWrite(5,00);
    }
    if(y2_value > 640 && y2_value < 865){
        softPwmWrite(4,75);
        softPwmWrite(5,05);
    }
    if(y2_value > 865 ){
        softPwmWrite(4,100);
        softPwmWrite(5,0);
    }
    if(y2_value < 495 && y2_value > 270){
        softPwmWrite(4,0);
        softPwmWrite(5,50);
    }
    if(y2_value < 270 && y2_value > 100){
        softPwmWrite(4,0);
        softPwmWrite(5,75);
    }
    if(y2_value < 100){
        softPwmWrite(4,0);
        softPwmWrite(5,100);
    }
    return 1;}
void Dialog::Analog_Read()
{

    x1_value = myAnalogRead(0,8,1);
    y1_value = myAnalogRead(0,8,0);
    sw1_value = myAnalogRead(0,8,2);
    x2_value = myAnalogRead(0,8,4);
    y2_value = myAnalogRead(0,8,3);
    sw2_value = myAnalogRead(0,8,5);
    dx = x1_value - center_x1_pos;
    dy = y1_value - center_y1_pos;
    /*QString color_r = QString::number(calculate_next_pwm_duty_cycle(rads,'R'));
    QString color_g = QString::number(calculate_next_pwm_duty_cycle(rads,'G'));
    QString color_b = QString::number(calculate_next_pwm_duty_cycle(rads,'B'));
    ui->textEdit->clear();
    ui->textEdit_2->clear();
    ui->textEdit_3->clear();
    ui->textEdit->insertPlainText(color_r);
    ui->textEdit_2->insertPlainText(color_g);
    ui->textEdit_3->insertPlainText(color_b);*/


    rads = (atan2(-dy, dx))*180/PI;
    cw_x = (x1_value /4)-10;
    cw_y = y1_value /4.07;
    if(sw2_value < 50){
        if(dc_sw == 0){
            dc_sw = 1;
        }else {
            dc_sw = 0;
        }
    }
    if(dc_control_0 == 1 && dc_control_1 == 0){
        if(dc_mode == 0){
            if(dc_sw == 0){
                dc_motor(x2_value, 500);
            }else if(dc_sw == 1){
                dc_motor(x2_value, 500);
                dc_sw = 2;
            }
        }
        else {
            dc_motor(x2_slider, 500);
        }
    }else if (dc_control_0 == 0 && dc_control_1 == 1) {
        if(dc_mode == 0){
            if(dc_sw == 0){
                dc_motor(500, y2_value);
            }else if(dc_sw == 1){
                dc_motor(500, y2_value);
                dc_sw = 2;
            }
        }
        else {
            dc_motor(500, y2_slider);
        }
    }else if(dc_control_0 == 1 && dc_control_1 == 1){
        if(dc_mode == 0){
            if(dc_sw == 0){
                dc_motor(x2_value, y2_value);
            }else if(dc_sw == 1){
                dc_motor(x2_value, y2_value);
                dc_sw = 2;
            }
        }
        else {
            dc_motor(x2_slider, y2_slider);
        }
    }else {

        dc_motor(500, 500);
    }

    if(control == 0){
        if(sw1_value < 50){
            if(mode !=3){
                mode = 3;
            }else {
                mode = 0;
            }
            softPwmWrite(RED, calculate_next_pwm_duty_cycle(rads,'R'));
            softPwmWrite(GREEN, calculate_next_pwm_duty_cycle(rads,'G'));
            softPwmWrite(BLUE, calculate_next_pwm_duty_cycle(rads,'B'));
            if((abs(dx) < 10) && (abs(dy) < 10)){
                softPwmWrite(RED, 100);
                softPwmWrite(GREEN, 100);
                softPwmWrite(BLUE, 100);
            }

            //else control = 0;
        }
        if(mode == 0){
            ui->label_6->setGeometry(cw_x,cw_y,16,22);

            if((abs(dx) < 10) && (abs(dy) < 10)){
                softPwmWrite(RED, 100);
                softPwmWrite(GREEN, 100);
                softPwmWrite(BLUE, 100);
            }else{

                softPwmWrite(RED, calculate_next_pwm_duty_cycle(rads,'R'));
                softPwmWrite(GREEN, calculate_next_pwm_duty_cycle(rads,'G'));
                softPwmWrite(BLUE, calculate_next_pwm_duty_cycle(rads,'B'));
            }


        }
        if(mode == 1){ //Breathing
            if((j < 100)&&(up > 0)){

                j=j+4;
            }else {
                up = 0;
                j=j-4;
                if(j == 0){
                    color++;
                    up = 1;
                }
            }
            if(color == 1){
                softPwmWrite(RED, j);
                softPwmWrite(GREEN, 0);
                softPwmWrite(BLUE, 0);
            }else if(color == 2) {
                softPwmWrite(RED, 0);
                softPwmWrite(GREEN, j);
                softPwmWrite(BLUE, 0);
            }
            else if(color == 3){
                softPwmWrite(RED, 0);
                softPwmWrite(GREEN, 0);
                softPwmWrite(BLUE, j);
            }
            else color = 1;
        }
        if(mode == 2){

            if((j2 != 0)&&(up != 1)){
                j2 = 0;
                up = 1;
            }else{
                j2++;
                if(j2 <5 ){
                    softPwmWrite(RED, 100);
                    softPwmWrite(GREEN, 0);
                    softPwmWrite(BLUE, 0);
                }
                if ((j2 >5)&&(j2< 10)){
                    softPwmWrite(RED, 100);
                    softPwmWrite(GREEN, 0);
                    softPwmWrite(BLUE, 0);
                }
                if ((j2 >10)&&(j2< 15)){
                    softPwmWrite(RED, 100);
                    softPwmWrite(GREEN, 25);
                    softPwmWrite(BLUE, 0);
                }
                if ((j2 >15)&&(j2< 20)){
                    softPwmWrite(RED, 100);
                    softPwmWrite(GREEN, 50);
                    softPwmWrite(BLUE, 0);
                }
                if ((j2 >20)&&(j2< 25)){
                    softPwmWrite(RED, 50);
                    softPwmWrite(GREEN, 100);
                    softPwmWrite(BLUE, 0);
                }
                if ((j2 >25)&&(j2< 30)){
                    softPwmWrite(RED, 0);
                    softPwmWrite(GREEN, 100);
                    softPwmWrite(BLUE, 0);
                }
                if ((j2 >30)&&(j2< 35)){
                    softPwmWrite(RED, 0);
                    softPwmWrite(GREEN, 100);
                    softPwmWrite(BLUE, 50);
                }
                if ((j2 >35)&&(j2< 40)){
                    softPwmWrite(RED, 0);
                    softPwmWrite(GREEN, 50);
                    softPwmWrite(BLUE, 100);
                }
                if ((j2 >40)&&(j2< 45)){
                    softPwmWrite(RED, 0);
                    softPwmWrite(GREEN, 0);
                    softPwmWrite(BLUE, 100);
                }
                if ((j2 >45)&&(j2< 50)){
                    softPwmWrite(RED, 50);
                    softPwmWrite(GREEN, 0);
                    softPwmWrite(BLUE, 100);
                }
                if ((j2 >50)&&(j2< 55)){
                    softPwmWrite(RED, 50);
                    softPwmWrite(GREEN, 0);
                    softPwmWrite(BLUE, 50);
                }
                if ((j2 >55)&&(j2< 60)){
                    softPwmWrite(RED, 100);
                    softPwmWrite(GREEN, 0);
                    softPwmWrite(BLUE, 50);
                    up = 0;
                }
            }
        }
    }else {
        softPwmWrite(RED, 0);
        softPwmWrite(GREEN, 0);
        softPwmWrite(BLUE, 0);
    }

}











