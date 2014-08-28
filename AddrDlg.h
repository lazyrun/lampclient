#ifndef ADDRDLG_H
#define ADDRDLG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE

class AddrDlg : public QDialog
{
   Q_OBJECT
public:
   AddrDlg(QWidget *parent = 0);
   QString address() const;
   int port() const;
      
private:
   QLineEdit *hostLineEdit;
   QLineEdit *portLineEdit;
};

#endif
