#include "pagamento.h"
#include <QRandomGenerator>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

Pagamento::Pagamento(float Valor, int TipoPagamento, float Desconto)
{
    this->valor = Valor;
    this->tipoPagamento = TipoPagamento;
    this->desconto = Desconto;
    this->rastreio = 0;
}

void Pagamento::confirmarPagamento()
{
    /*int idCompra = QRandomGenerator::global()->generate();
    int formaPg = this->tipoPagamento;
    double valor = this->valor;
    double desconto = 0.0;*/

    int idCompra = QRandomGenerator::global()->generate();


    if(idCompra < 0)
        idCompra = -1*idCompra;

    this->rastreio = idCompra;

    int formaPg = 1;
    double valor = 99.9;
    double desconto = 0.0;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/sqlite/TestePulse.db");


    if(!db.open())
    {
        qInfo() << "Falha ao conectar com o banco de dados";
        qInfo() << db.lastError();
        return;
    }

    QSqlQuery query;
    QString cmd = "INSERT INTO pagamento(ID, FORMAPAGAMENTO, VALOR, DESCONTO) VALUES("
    + QString::number(idCompra) + "," +  QString::number(formaPg) + "," + QString::number(valor)
            + "," + QString::number(desconto) + ");";

    if(!query.exec(cmd))
    {
        qInfo() << db.lastError().text();
        qInfo() << query.lastError().text();
    }
    else
    {
        qInfo() << "Operation successful";
    }

    db.close();
    qInfo() << "Disconnected";
}

