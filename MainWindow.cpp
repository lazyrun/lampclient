#include <QtGui>
#include <QtNetwork>

#include "MainWindow.h"
#include "LampWidget.h"
#include "LampCommand.h"
#include "AddrDlg.h"

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), tcpSocket(0), port(0)
{
   lampWidget = new LampWidget(this);
   QWidget * main = new QWidget(this);
   QVBoxLayout * vb = new QVBoxLayout;
   vb->addWidget(lampWidget, 1);
   main->setLayout(vb);

   tcpSocket = new QTcpSocket(this);

   connect(tcpSocket, SIGNAL(connected()), this, SLOT(connectedToHost()));
   connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readCommand()));
   connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));

   setWindowTitle(tr("Lamp Client"));
   setCentralWidget(main);
   setMinimumSize(480, 320);
   QStatusBar * bar = new QStatusBar(this);
   setStatusBar(bar);
   QTimer::singleShot(0, this, SLOT(addrRequest()));
}

void MainWindow::closeEvent(QCloseEvent *)
{
   if (tcpSocket)
   {
      tcpSocket->disconnectFromHost();
   }
}

void MainWindow::addrRequest()
{
   AddrDlg addrDlg;
   if (addrDlg.exec() == QDialog::Accepted)
   {
      addr = addrDlg.address();
      port = addrDlg.port();
      connectToHost();
   }
   else
   {
      QTimer::singleShot(0, this, SLOT(close()));
   }
}

void MainWindow::connectToHost()
{
   tcpSocket->abort();
   tcpSocket->connectToHost(addr, port);
}

void MainWindow::connectedToHost()
{
   statusBar()->showMessage(QString("CONNECTED %1:%2").arg(addr).arg(port));
}

void MainWindow::readCommand()
{
   QByteArray barr = tcpSocket->readAll();
   
   LampCommand cmd(barr.data(), barr.length());
   if (cmd.type() == LampCommand::ON)
   {
      lampWidget->switchOn();
   }
   else if (cmd.type() == LampCommand::OFF)
   {
      lampWidget->switchOff();
   }
   else if (cmd.type() == LampCommand::COLOR)
   {
      int len = cmd.length();
   
      const unsigned char * rgb = (const unsigned char *)cmd.value();
      if (len == 3)
      {
         lampWidget->setColor(qRgb(rgb[0], rgb[1], rgb[2]));
      }
   }
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{
   statusBar()->showMessage("NOT CONNECTED");
   switch (socketError) 
   {
      case QAbstractSocket::RemoteHostClosedError:
         break;
      case QAbstractSocket::HostNotFoundError:
         QMessageBox::information(this, tr("Lamp Client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
         break;
      case QAbstractSocket::ConnectionRefusedError:
         QMessageBox::information(this, tr("Lamp Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
         break;
      default:
         QMessageBox::information(this, tr("Lamp Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(tcpSocket->errorString()));
    }
}
