#ifndef LAMPWIDGET_H
#define LAMPWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QTcpSocket;
QT_END_NAMESPACE

class LampWidget : public QWidget
{
   Q_OBJECT
public:
   LampWidget(QWidget *parent = 0);
   void switchOn();
   void switchOff();
   void setColor(QRgb rgb);
private:
   QLabel * lampLabel;
   bool isOn;
   QColor color;
};

#endif
