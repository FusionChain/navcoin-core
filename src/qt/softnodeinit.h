#ifndef SOFTNODEINIT_H
#define SOFTNODEINIT_H

#include <QDialog>

namespace Ui {
class SoftNodeInit;
}

class SoftNodeInit : public QDialog
{
    Q_OBJECT

public:
    explicit SoftNodeInit(QWidget *parent = 0);
    ~SoftNodeInit();
    QString GetServers();
    void ShowSoftnodeIntro(bool exitAfter = true);

private:
    Ui::SoftNodeInit *ui;
};

#endif // SOFTNODEINIT_H
