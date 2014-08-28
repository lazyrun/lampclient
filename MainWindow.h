#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

class LampWidget;
class QLabel;
class QLineEdit;
class QTcpSocket;

class MainWindow : public QMainWindow
{
   Q_OBJECT
public:
   MainWindow(QWidget *parent = 0);

private slots:
   void addrRequest();
   void connectToHost();
   void connectedToHost();
   void readCommand();
   void displayError(QAbstractSocket::SocketError socketError);

private:
   void closeEvent(QCloseEvent * event);
   LampWidget * lampWidget;
   QTcpSocket *tcpSocket;
   QString addr;
   int port;
};

#endif
