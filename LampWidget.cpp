#include <QtGui>
#include "LampWidget.h"

LampWidget::LampWidget(QWidget *parent)
: QWidget(parent), isOn(true), color(Qt::yellow)
{
   QVBoxLayout * vb = new QVBoxLayout;
   setLayout(vb);
   lampLabel = new QLabel(this);
   lampLabel->setAlignment(Qt::AlignCenter);
   vb->addWidget(lampLabel, 1);
   lampLabel->setText("ON");
   lampLabel->setStyleSheet(QString("background: %1").arg(color.name()));
}

void LampWidget::switchOn()
{
   lampLabel->setText("ON");
   lampLabel->setStyleSheet(QString("background: %1").arg(color.name()));
}

void LampWidget::switchOff()
{
   lampLabel->setText("OFF");
   lampLabel->setStyleSheet("");
}

void LampWidget::setColor(QRgb rgb)
{
   switchOn();
   this->color = QColor(rgb);
   lampLabel->setStyleSheet(QString("background: %1").arg(color.name()));
}

