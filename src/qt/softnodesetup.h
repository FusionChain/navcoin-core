#ifndef SOFTNODESETUP_H
#define SOFTNODESETUP_H

#include "wallet/softnode.h"

#include <QDialog>
#include <QVBoxLayout>

namespace Ui {
class softnodesetup;
}

class softnodesetup : public QDialog
{
    Q_OBJECT

public:
    explicit softnodesetup(QWidget *parent = 0);
    ~softnodesetup();

private:
    Ui::softnodesetup *ui;

public Q_SLOTS:
    void reloadNavtechServers();
    void addNavtechServer();
    void removeNavtechServer();
    void getinfoNavtechServer();
    void showButtons(bool show=true);
    void showNavtechIntro();

};

#endif // SOFTNODESETUP_H
