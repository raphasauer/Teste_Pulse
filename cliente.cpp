#include "cliente.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

Cliente::Cliente(QString Nome, QString Sobrenome)
{
    carregaCliente(Nome, Sobrenome);
}

void Cliente::carregaCliente(QString nome, QString sobrenome)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/sqlite/TestePulse.db");


    if(!db.open())
    {
        qInfo() << "Falha ao conectar com o banco de dados";
        qInfo() << db.lastError();
        return;
    }

    QSqlQuery query;

    QString cmd = "SELECT * FROM CLIENTE WHERE NOME='" + nome + "' AND SOBRENOME='" + sobrenome + "';";

    if(!query.exec(cmd))
    {
        qInfo() << db.lastError().text();
        qInfo() << query.lastError().text();
    }
    else
    {


        this->id = query.value(0).toInt();
        this->nome = query.value(1).toString();
        this->sobrenome = query.value(2).toString();
        qInfo() << id << nome << sobrenome;

    }

    db.close();
    qInfo() << "Disconnected";
}
