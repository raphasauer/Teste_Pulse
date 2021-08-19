#include <sel_pagamento.h>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <tipopagamento.h>
#include <QRandomGenerator>
#include <pagamento.h>

selPagamento::selPagamento(QWidget *parent) : QMainWindow(parent)
{
    QScreen *q = QGuiApplication::primaryScreen();
    resize(q->availableSize());

    carregaTipoPagamentos();

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    QScrollArea *scroll = new QScrollArea(centralWidget);
    scroll->setFrameShape(QFrame::NoFrame);
    QWidget *widgetScroll = new QWidget(centralWidget);
    QGridLayout *layoutScroll = new QGridLayout(widgetScroll);

    int k = 0;

    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 3; j++)
        {
            if(k > 5)
                break;
            layoutScroll->addWidget(widgetFormaPagamento(widgetScroll, tipoPagamentos[k].formaPagamento, tipoPagamentos[k].nome, tipoPagamentos[k].parcelas), i, j);
            k++;
        }

    scroll->setWidgetResizable(true);
    scroll->setWidget(widgetScroll);
    layout->addWidget(scroll);
    setCentralWidget(centralWidget);

    this->pag = new Pagamento(this->valorTotal, this->formaPagamento, 0.0);
    pag->confirmarPagamento();
}

QWidget *selPagamento::widgetFormaPagamento(QWidget *parent, int id, QString nome, int parcelas)
{
    QWidget *widget = new QWidget(parent);
    QVBoxLayout *layout = new QVBoxLayout(widget);

    widget->setStyleSheet("QWidget{background-color: rgb(255, 255, 255); border-radius: 20px;} "
    "QPushButton{ background-color: rgb(118, 50, 63); border: none; border-radius: 25px;"
    "color:rgb(215, 206, 199); height: 50px;}"
    "QPushButton:hover{background-color: rgb(124, 59, 71);}"
    "QPushButton:pressed{ background-color: rgb(78, 41, 48);}");

    QLabel *label = new QLabel(nome + ", " + QString::number(parcelas) + " parcela(s)", widget);
    layout->addWidget(label);

    QPushButton *botao = new QPushButton("Selecionar", widget);
    connect(botao, SIGNAL(clicked(bool)), this, SLOT(teste()));
    layout->addWidget(botao);

    return widget;
}


void selPagamento::teste()
{
    qInfo() << QObject::sender();
    qInfo() << "teste";
}

void selPagamento::carregaTipoPagamentos()
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
    QString cmd = "SELECT * FROM tipopagamento";

    if(!query.exec(cmd))
    {
        qInfo() << db.lastError().text();
        qInfo() << query.lastError().text();
    }
    else
    {
        int id;
        QString nome;
        int parcelas;

        while(query.next())
        {

            id = query.value(0).toInt();
            nome = query.value(1).toString();
            parcelas = query.value(2).toInt();
            qInfo() << id << nome << parcelas;
            this->tipoPagamentos.append(TipoPagamento(id, nome, parcelas));
        }
    }

    db.close();
    qInfo() << "Disconnected";
}
