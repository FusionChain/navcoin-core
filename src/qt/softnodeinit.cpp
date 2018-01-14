#include "softnodeinit.h"
#include "ui_softnodeinit.h"
#include "net.h"
#include "util.h"
#include "skinize.h"

#include <string>
#include <iostream>

#include <QStringList>
#include <QUrl>

SoftNodeInit::SoftNodeInit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SoftNodeInit)
{
    ui->setupUi(this);
}

SoftNodeInit::~SoftNodeInit()
{
    delete ui;
}

void SoftNodeInit::ShowSoftnodeIntro(bool exitAfter)
{
    SoftNodeInit softnodeinit;
    softnodeinit.setWindowIcon(QIcon(":icons/softcoin"));
    softnodeinit.setStyleSheet(Skinize());

    if(!softnodeinit.exec())
    {
        if(exitAfter)
            exit(0);
        else
            return;
    }

    QString ServersToAdd = softnodeinit.GetServers();
    QStringList ss = ServersToAdd.split('\n');

    for (int i = 0; i < ss.size(); ++i){
        QString Server = ss.at(i);
        QString strippedServer = Server.remove(' ');
        if(strippedServer != "")
        {
            WriteConfigFile("addanonserver",strippedServer.toStdString());
        }
    }
}

QString SoftNodeInit::GetServers()
{
    return ui->plainTextEdit->toPlainText();
}
