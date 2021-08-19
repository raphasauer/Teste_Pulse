#include "pagamento.h"
#include <QRandomGenerator>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

Pagamento::Pagamento(float Valor, float Desconto)
{
    this->valor = Valor;
    this->desconto = Desconto;
    this->rastreio = 0;
}

void Pagamento::confirmarPagamento()
{
    int idCompra = QRandomGenerator::global()->generate();
    double valor = this->valor;
    double desconto = 0.0;

    if(idCompra < 0)
        idCompra = -1*idCompra;

    this->rastreio = idCompra;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/sqlite/TestePulse.db");


    if(!db.open())
    {
        qInfo() << "Falha ao conectar com o banco de dados";
        qInfo() << db.lastError();
        return;
    }

    QSqlQuery query;
    QString cmd = "INSERT INTO pagamento(ID, VALOR, DESCONTO) VALUES("
    + QString::number(idCompra) + "," + QString::number(valor)
            + "," + QString::number(desconto) + ");";

    if(!query.exec(cmd))
    {
        qInfo() << db.lastError().text();
        qInfo() << query.lastError().text();
    }


    db.close();
}

