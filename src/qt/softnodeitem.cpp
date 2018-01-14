#include "softnodeitem.h"
#include "ui_softnodeitem.h"

softnodeitem::softnodeitem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::softnodeitem),
    host(""),
    name("")
{
    ui->setupUi(this);
}

void softnodeitem::setHost(QString hostStr)
{
    host = hostStr;
    ui->serverHostLabel->setText(hostStr);
}

void softnodeitem::setName(QString nameStr)
{
    name = nameStr;
    ui->serverNameLabel->setText(nameStr);
}

softnodeitem::~softnodeitem()
{
    delete ui;
}
