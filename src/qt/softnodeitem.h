#ifndef SOFTNODEITEM_H
#define SOFTNODEITEM_H

#include <QWidget>

namespace Ui {
class softnodeitem;
}

class softnodeitem : public QWidget
{
    Q_OBJECT

public:
    explicit softnodeitem(QWidget *parent = 0);
    ~softnodeitem();
    void setHost(QString hostStr);
    void setName(QString nameStr);

private:
    Ui::softnodeitem *ui;
    QString host;
    QString name;
};

#endif // SOFTNODEITEM_H
