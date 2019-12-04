#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <QDialog>

namespace Ui {
class SecDialog;
}

class SecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SecDialog(QWidget *parent = nullptr);
    ~SecDialog();

private slots:
    void on_pushButton1_clicked();

    void on_textEdit_copyAvailable(bool b);

    void on_pushButton_7_clicked();

    void on_b1_clicked();

private:
    Ui::SecDialog *ui;
};

#endif // SECDIALOG_H
