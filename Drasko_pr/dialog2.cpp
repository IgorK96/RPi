#include "dialog2.h"
#include "ui_dialog2.h"
#include "dialog.h"

Dialog2::Dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{
    ui->setupUi(this);
}

Dialog2::~Dialog2()
{
    delete ui;
}

void Dialog2::on_pushButton1_clicked()
{
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->insertPlainText("1");
    ui->textEdit->moveCursor(QTextCursor::End);
}


void Dialog2::on_pushButton_7_clicked()
{
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->insertPlainText("2");
    ui->textEdit->moveCursor(QTextCursor::End);
}

void Dialog2::on_pushButton_11_clicked()
{
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->insertPlainText("3");
    ui->textEdit->moveCursor(QTextCursor::End);
}

void Dialog2::on_pushButton_2_clicked()
{
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->insertPlainText("4");
    ui->textEdit->moveCursor(QTextCursor::End);
}

void Dialog2::on_pushButton_6_clicked()
{
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->insertPlainText("5");
    ui->textEdit->moveCursor(QTextCursor::End);
}

void Dialog2::on_pushButton_10_clicked()
{
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->insertPlainText("6");
    ui->textEdit->moveCursor(QTextCursor::End);
}

void Dialog2::on_pushButton_3_clicked()
{
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->insertPlainText("7");
    ui->textEdit->moveCursor(QTextCursor::End);
}

void Dialog2::on_pushButton_8_clicked()
{
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->insertPlainText("8");
    ui->textEdit->moveCursor(QTextCursor::End);
}

void Dialog2::on_pushButton_12_clicked()
{
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->insertPlainText("9");
    ui->textEdit->moveCursor(QTextCursor::End);
}

void Dialog2::on_pushButton_4_clicked()
{
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->insertPlainText("#");
    ui->textEdit->moveCursor(QTextCursor::End);
}

void Dialog2::on_pushButton_5_clicked()
{
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->insertPlainText("0");
    ui->textEdit->moveCursor(QTextCursor::End);
}

void Dialog2::on_pushButton_9_clicked()
{
    newpass
}

void Dialog2::on_textEdit_textChanged()
{
    int maximum = 4;
    if(ui->textEdit->toPlainText().length() > maximum)
    {
        ui->textEdit->textCursor().deletePreviousChar();
    }
}
