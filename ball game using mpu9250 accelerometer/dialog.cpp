#include "dialog.h"
#include "ui_dialog.h"
#include "MPU9250.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setup_pins();

    tmr = new QTimer(this);
    connect(tmr, SIGNAL(timeout()), this, SLOT(Ball_Move()));
    tmr ->start(50);
}

Dialog::~Dialog()
{
    delete ui;
}

int Dialog::setup_pins()
{
    wiringPiSetup();
    MPU9250();
    initMPU9250();

    ball_position[0]= 20;
    ball_position[1]= 20;
    //ball_position[2]= 30; //Z-Axis doesnt matter here

    ui->win->hide();
    ball_move= 1;
    return 0;
}


void Dialog::Ball_Move()
{

    ui->ball->setGeometry(ball_position[0], ball_position[1], 20, 20);
    delay(10);

    //wall_0
    if (((ball_position[1])< (ui->wall_0->y()+6)))
    {
        ball_position[1]= prev_ball_pos[1];
    }

    //wall_1
    if (((ball_position[0])< (ui->wall_1->x()+12)))
    {
        ball_position[0]= prev_ball_pos[0];
    }

    //wall_2
    if (((ball_position[0]+20)> (ui->wall_2->x())))
    {
        ball_position[0]= prev_ball_pos[0];
    }

    //wall_3
    if (((ball_position[1]+20)> (ui->wall_3->y())))
    {
        ball_position[1]= prev_ball_pos[1];
    }

    //wall_4
    if (((ball_position[1])< (ui->wall_4->y()+6)) && ((ball_position[1]+20)> (ui->wall_4->y())) && ((ball_position[0])< (ui->wall_4->x()+ ui->wall_4->width())))
    {
        ball_position[1]= prev_ball_pos[1];
    }

    //wall_5
    if (((ball_position[1])< (ui->wall_5->y()+6)) && ((ball_position[1]+20)> (ui->wall_5->y())) && ((ball_position[0])> ui->wall_5->x()-15) && ((ball_position[0])< ui->wall_5->x()+ ui->wall_5->width()))
    {
        ball_position[1]= prev_ball_pos[1];
    }

    //wall_6
    if (((ball_position[0])< (ui->wall_6->x()+6)) && ((ball_position[0]+20)> (ui->wall_6->x())) && ((ball_position[1])> ui->wall_6->y()-15 ) && ((ball_position[1])< ((ui->wall_6->y())+ ui->wall_6->height())))
    {
        ball_position[0]= prev_ball_pos[0];
    }

    //wall_7
    if (((ball_position[0])< (ui->wall_7->x()+6)) && ((ball_position[0]+20)> (ui->wall_7->x()))&& ((ball_position[1])> ui->wall_7->y()-10) && ((ball_position[1])< ((ui->wall_7->y())+ ui->wall_7->height())))
    {
        ball_position[0]= prev_ball_pos[0];
    }


    //wall_8
    if (((ball_position[0])< (ui->wall_8->x()+6)) && ((ball_position[0]+20)> (ui->wall_8->x()))&& ((ball_position[1])> ui->wall_8->y()-15) && ((ball_position[1])< (ui->wall_8->y() + ui->wall_8->height())))
    {
        ball_position[0]= prev_ball_pos[0];
    }


    //wall_9
    if (((ball_position[0])< (ui->wall_9->x()+6)) && ((ball_position[0]+20)> (ui->wall_9->x()))&& ((ball_position[1])> ui->wall_9->y()-10)&& ((ball_position[1])< (ui->wall_9->y()+ ui->wall_9->height())))
    {
        ball_position[0]= prev_ball_pos[0];
    }

    //wall_10
    if (((ball_position[0])< (ui->wall_10->x()+6)) && ((ball_position[0]+20)> (ui->wall_10->x()))&& ((ball_position[1])> ui->wall_10->y()-20) && ((ball_position[1])< (ui->wall_10->y()+ui->wall_10->height())))
    {
        ball_position[0]= prev_ball_pos[0];
    }

    readAccelData(ACCxyz);
    AmpedAcc[0]= ACCxyz[0]/1200;
    AmpedAcc[1]= ACCxyz[1]/1200;
    if(AmpedAcc[0] > 6)
    {

        AmpedAcc[0]= 6;
    }
    if(AmpedAcc[1] > 6)
    {
        AmpedAcc[1]= 6;

    }
    if(AmpedAcc[0] < -6)
    {
        AmpedAcc[0]= -6;

    }
    if(AmpedAcc[1] < -6)
    {
        AmpedAcc[1]= -6;

    }
    if(ball_move == 1){
    prev_ball_pos[0]= ball_position[0];
    prev_ball_pos[1]= ball_position[1];
    ball_position[0]-= AmpedAcc[0];
    ball_position[1]+= AmpedAcc[1];

    }
    if((ball_position[0] > ui->finish->x()) && ((ball_position[0]+20) < (ui->finish->x()+40)) && (ball_position[1] > ui->finish->y()) && ((ball_position[1]+20) < (ui->finish->y()+40)))
    {
        ball_move= 0;
        ui->win->setGeometry(30, 40, 260, 180);
        ui->win->show();
    }

}

void Dialog::on_reset_clicked()
{
    ball_position[0]= 20;
    ball_position[1]= 20;
    ball_move= 1;
    ui->win->hide();
}
