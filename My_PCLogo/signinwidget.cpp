#include "signinwidget.h"
#include <QBrush>
#include <QPalette>
#include <QtCore>

LoginDialog::LoginDialog()
{

}

LoginDialog::LoginDialog(int width, int height, QWidget *){

    this->width = width;
    this->height = height;
    this->setWindowModality(Qt::ApplicationModal);
    this->setStyleSheet("QDialog{border-image:url(:images/bk.png)}");
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    Region *Re= new Region(width,height,width/25);
    Re->mask(this);
    this->raise();

    QFont font;
    font.setWeight(30);
    font.setPixelSize(30);

    usrlabel = new QLabel(this);
    psdlabel = new QLabel(this);
    usrlabel->setFont(font);
    psdlabel->setFont(font);
    usrlabel->setAttribute(Qt::WA_TranslucentBackground, true);//透明
    usrlabel->setAlignment(Qt::AlignCenter|Qt::AlignCenter);
    psdlabel->setAttribute(Qt::WA_TranslucentBackground,true);
    psdlabel->setAlignment(Qt::AlignCenter|Qt::AlignCenter);
    usrlabel->setGeometry(1*width/15,height/5,width/5,height/10);
    psdlabel->setGeometry(1*width/15,2*height/5,width/5,height/10);
    usrlabel->setText("用户名:");
    psdlabel->setText("密码:");


    usrinput = new QLineEdit(this);
    psdinput = new QLineEdit(this);
    usrinput->setStyleSheet(
                            "QLineEdit{border-image:url(:/images/input.png);background:rgb(0,255,255);padding-left:30px}"
                            );
    usrinput->setGeometry(width/4+50,height*13/60,width/2,height/15);
    usrinput->setAttribute(Qt::WA_MacShowFocusRect, 0);
    usrinput->setFont(font);
    usrinput->setMaxLength(16);

    psdinput->setStyleSheet(
                            "QLineEdit{border-image:url(:/images/input.png);background:rgb(0,255,255);padding-left:30px;}"
                            );
    psdinput->setAttribute(Qt::WA_MacShowFocusRect, 0);
    psdinput->setGeometry(width/4+50,height*25/60,width/2,height/15);
    psdinput->setFont(font);
    psdinput->setMaxLength(16);


}