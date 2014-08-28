#include <QtGui>

#include "AddrDlg.h"

AddrDlg::AddrDlg(QWidget *parent)
: QDialog(parent)
{
   QLabel * hostLabel = new QLabel(tr("&Server name:"));
   QLabel * portLabel = new QLabel(tr("S&erver port:"));

   hostLineEdit = new QLineEdit("127.0.0.1");
   portLineEdit = new QLineEdit("9999");
   portLineEdit->setValidator(new QIntValidator(1, 65535, this));

   hostLabel->setBuddy(hostLineEdit);
   portLabel->setBuddy(portLineEdit);

   QPushButton * connectButton = new QPushButton(tr("Connect"));
   connectButton->setDefault(true);

   QPushButton * quitButton = new QPushButton(tr("Quit"));

   QDialogButtonBox * buttonBox = new QDialogButtonBox;
   buttonBox->addButton(connectButton, QDialogButtonBox::AcceptRole);
   buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

   connect(connectButton, SIGNAL(clicked()), this, SLOT(accept()));
   connect(quitButton, SIGNAL(clicked()), this, SLOT(reject()));
   
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(hostLabel, 0, 0);
    mainLayout->addWidget(hostLineEdit, 0, 1);
    mainLayout->addWidget(portLabel, 1, 0);
    mainLayout->addWidget(portLineEdit, 1, 1);
    mainLayout->addWidget(buttonBox, 3, 0, 1, 2);
    setLayout(mainLayout);

    setWindowTitle(tr("Lamp Server Address"));
    portLineEdit->setFocus();
}

QString AddrDlg::address() const
{
   return hostLineEdit->text();
}

int AddrDlg::port() const
{
   return portLineEdit->text().toInt();
}

