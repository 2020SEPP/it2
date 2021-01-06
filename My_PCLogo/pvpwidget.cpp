#include "pvpwidget.h"
#include "token.h"
#include <QApplication>
#include <QDebug>
#include <QPropertyAnimation>

PvpWidget::PvpWidget(QWidget *parent) : QWidget(parent) {
    height = window.getH();
    width = window.getW();
    this->setFixedSize(width, height);
    this->setWindowTitle("My PC Logo");
    this->setFocus();
    this->setGeometry(width, 0, width, height);
    this->visible = false;
    QFont font;
    font.setFamily("concolas");
    font.setBold(true);
    font.setPixelSize(20);
    this->setFont(font);
    init(-1);
}

void PvpWidget::init(int r) {
    room = r;
    canvas = new Canvas(this, 0, 0, width / 2, (height * 3) / 4);
    canvas->setGeometry(0, 0, width / 2, (height * 3) / 4);
    enermy = new Canvas(this, 0, 0, width / 2, (height * 3) / 4);
    enermy->setGeometry(width / 2, 0, width / 2, (height * 3) / 4);
    setBG("ffffff");
    console = new Console(this);
    console->setGeometry(0, (height * 3) / 4, width, height / 4);
    console->setStyleSheet(QString::fromUtf8("border: 2px solid gray;"));
    console->write("Welcome to room " + QString::number(room) + "!\nPlease type your code.\n>> ");
    console->setStyleSheet("QTextEdit {"
                           "border-image:url(:/images/image/paint2222.png);"
                           "}");
    console->setAttribute(Qt::WA_InputMethodEnabled, false);
    help = new QPushButton(this);
    exit = new QPushButton(this);
    help->setGeometry(width * 13 / 15, 0, height / 15, height / 15);
    exit->setGeometry(width * 14 / 15, 0, height / 15, height / 15);
    help->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
    exit->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
    help->setStyleSheet("QPushButton{"
                        "border-image:url(:/images/image/bangzhu.png)"
                        "}");
    exit->setStyleSheet("QPushButton{"
                        "border-image:url(:/images/image/tuichu.png)"
                        "}");
    connect(console, SIGNAL(drawLine(qreal, bool)), this, SLOT(drawLine(qreal, bool)));
    connect(console, SIGNAL(turnDirection(qreal, bool)), this, SLOT(turnDirection(qreal, bool)));
    connect(console, SIGNAL(setXT(qreal, qreal)), this, SLOT(setXT(qreal, qreal)));
    connect(console, SIGNAL(setPC(uint)), this, SLOT(setPC(uint)));
    connect(console, SIGNAL(setBG(QString)), this, SLOT(setBG(QString)));
    connect(console, SIGNAL(stampoval(qreal, qreal)), this, SLOT(stampoval(qreal, qreal)));
    connect(exit, SIGNAL(clicked()), this, SLOT(exitClicked()));
}

// SLOT
void PvpWidget::drawLine(qreal len, bool flag) {
    canvas->drawLine(len, flag);
    QString command = (flag ? "fd " : "bk ") + QString::number(len);
    QString url = ADDR + "/match"
                  + "/sendCommand?uid=" + QString::number(ID)
                  + "&rid=" + QString::number(room)
                  + "&command=" + command;
}

void PvpWidget::turnDirection(qreal angle, bool flag) {
    canvas->turnDirection(angle, flag);
    QString command = (flag ? "rt " : "lt ") + QString::number(angle);
    QString url = ADDR + "/match"
                  + "/sendCommand?uid=" + QString::number(ID)
                  + "&rid=" + QString::number(room)
                  + "&command=" + command;
}

void PvpWidget::setXT(qreal x, qreal y) {
    canvas->setXT(x, y);
    QString command = "setxy " + QString::number(x) + " " + QString::number(y);
    QString url = ADDR + "/match"
                  + "/sendCommand?uid=" + QString::number(ID)
                  + "&rid=" + QString::number(room)
                  + "&command=" + command;
}

void PvpWidget::setPC(uint color) {
    canvas->setPC(color);
    QString command = "setpc " + QString::number(color);
    QString url = ADDR + "/match"
                  + "/sendCommand?uid=" + QString::number(ID)
                  + "&rid=" + QString::number(room)
                  + "&command=" + command;
}

void PvpWidget::setBG(QString color) {
    QString qss = "border: 2px solid darkgray; background-color: #";
    qss.append(color);
    canvas->setStyleSheet(qss);
    enermy->setStyleSheet(qss);
    QString command = "setbg " + color;
    QString url = ADDR + "/match"
                  + "/sendCommand?uid=" + QString::number(ID)
                  + "&rid=" + QString::number(room)
                  + "&command=" + command;
}

void PvpWidget::stampoval(qreal x, qreal y) {
    canvas->stampoval(x, y);
    QString command = "stampoval " + QString::number(x) + " " + QString::number(y);
    QString url = ADDR + "/match"
                  + "/sendCommand?uid=" + QString::number(ID)
                  + "&rid=" + QString::number(room)
                  + "&command=" + command;
}

void
PvpWidget::InAnnimation() {
    QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(100);
    if(this->visible) {
        animation->setStartValue(QRect(0, 0, width, height));
        animation->setEndValue(QRect(width, 0, width, height));
        animation->start();
    } else {
        animation->setStartValue(QRect(width, 0, width, height));
        animation->setEndValue(QRect(0, 0, width, height));
        animation->start();
    }
    this->visible = !this->visible;
    this->setWindowModality(Qt::ApplicationModal);
}

void
PvpWidget::keyPressEvent(QKeyEvent *ev) {
    if (ev->key() == Qt::Key_Escape)
        emit ClosePvP(3);
}

void
PvpWidget::exitClicked() {
    emit ClosePvP(3);
}
