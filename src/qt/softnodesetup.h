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
    void reloadSoftnodeServers();
    void addSoftnodeServer();
    void removeSoftnodeServer();
    void getinfoSoftnodeServer();
    void showButtons(bool show=true);
    void showSoftnodeIntro();

};

#endif // SOFTNODESETUP_H
