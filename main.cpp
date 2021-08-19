#include <QCoreApplication>
#include <QDebug>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QPluginLoader>
#include <QVariant>
#include <QApplication>
#include "janelainicial.h"
#include <cliente.h>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Cliente *cl = new Cliente("Raphael", "Sauer");
    janelaInicial j;
    j.show();
    return app.exec();
}
