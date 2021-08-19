#include "end_frete.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <endereco.h>
#include <transportadora.h>

endFrete::endFrete(QWidget *parent) : QMainWindow(parent)
{
    QScreen *q = QGuiApplication::primaryScreen();
    resize(q->availableSize());

    carregaEnderecos();
    carregaTransportadora();

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    QScrollArea *scroll = new QScrollArea(centralWidget);
    scroll->setFrameShape(QFrame::NoFrame);
    QWidget *widgetScroll = new QWidget(centralWidget);
    QGridLayout *layoutScroll = new QGridLayout(widgetScroll);

    int k = 0;

    layoutScroll->addWidget(widgetEndereco(widgetScroll, enderecos[0].rua, enderecos[0].numero, enderecos[0].complemento, enderecos[0].estado), 0, 0);

    layoutScroll->addWidget(widgetEndereco(widgetScroll, enderecos[1].rua, enderecos[1].numero, enderecos[1].complemento, enderecos[1].estado), 0, 1);

    layoutScroll->addWidget(widgetTransportadora(widgetScroll, transportadoras[0].nome, transportadoras[0].prazo, transportadoras[0].valor),   1, 0);

    layoutScroll->addWidget(widgetTransportadora(widgetScroll, transportadoras[1].nome, transportadoras[1].prazo, transportadoras[1].valor),   1, 1);

    layoutScroll->addWidget(widgetTransportadora(widgetScroll, transportadoras[2].nome, transportadoras[2].prazo, transportadoras[2].valor),   1, 2);




   /* for(int i = 0; i < 2; i++)
        for(int j = 0; j < 3; j++)
        {
            if(k > 5)
                break;
            layoutScroll->addWidget(widgetEndereco(widgetScroll, produtos[k].nome, produtos[k].preco, produtos[k].descricao, produtos[k].id), i, j);
            k++;
        }*/

    scroll->setWidgetResizable(true);
    scroll->setWidget(widgetScroll);
    layout->addWidget(scroll);
    setCentralWidget(centralWidget);
}

QWidget *endFrete::widgetEndereco(QWidget *parent, QString rua, int numero, QString complemento, int estado)
{
    QWidget *widget = new QWidget(parent);
    QVBoxLayout *layout = new QVBoxLayout(widget);

    widget->setStyleSheet("QWidget{background-color: rgb(255, 255, 255); border-radius: 20px;} "
    "QPushButton{ background-color: rgb(118, 50, 63); border: none; border-radius: 25px;"
    "color:rgb(215, 206, 199); height: 50px;}"
    "QPushButton:hover{background-color: rgb(124, 59, 71);}"
    "QPushButton:pressed{ background-color: rgb(78, 41, 48);}");

    QLabel *label = new QLabel(rua + ", " + QString::number(numero) + " " + complemento, widget);
    layout->addWidget(label);

    QPushButton *botao = new QPushButton("Selecionar", widget);
    connect(botao, SIGNAL(clicked(bool)), this, SLOT(teste()));
    layout->addWidget(botao);

    return widget;
}

QWidget *endFrete::widgetTransportadora(QWidget *parent, QString nome, int prazo, double valor)
{
    QWidget *widget = new QWidget(parent);
    QVBoxLayout *layout = new QVBoxLayout(widget);

    widget->setStyleSheet("QWidget{background-color: rgb(255, 255, 255); border-radius: 20px;} "
    "QPushButton{ background-color: rgb(118, 50, 63); border: none; border-radius: 25px;"
    "color:rgb(215, 206, 199); height: 50px;}"
    "QPushButton:hover{background-color: rgb(124, 59, 71);}"
    "QPushButton:pressed{ background-color: rgb(78, 41, 48);}");

    QLabel *label = new QLabel(nome, widget);
    QLabel *desc = new QLabel(QString::number(valor), widget);
    layout->addWidget(label);
    layout->addWidget(desc);

    QLabel *preco = new QLabel(QString::number(prazo) + " dias úteis", widget);
    layout->addWidget(preco);

    QPushButton *botao = new QPushButton("Selecionar", widget);
    connect(botao, SIGNAL(clicked(bool)), this, SLOT(teste()));
    layout->addWidget(botao);

    return widget;
}

void endFrete::teste()
{
    qInfo() << QObject::sender();
    qInfo() << "teste";
}

void endFrete::carregaEnderecos()
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
    QString cmd = "SELECT * FROM endereco";

    if(!query.exec(cmd))
    {
        qInfo() << db.lastError().text();
        qInfo() << query.lastError().text();
    }
    else
    {
        int id;
        QString cep;
        QString rua;
        int numero;
        QString complemento;
        QString cidade;
        int estado;

        while(query.next())
        {

            id = query.value(0).toInt();
            cep = query.value(1).toString();
            rua = query.value(2).toString();
            numero = query.value(3).toInt();
            complemento = query.value(4).toString();
            cidade = query.value(5).toString();
            estado = query.value(6).toInt();
            qInfo() << id << cep << rua << numero << complemento << cidade << estado;
            this->enderecos.append(Endereco(cep, rua, numero, complemento, cidade, estado));
        }
    }

    db.close();
    qInfo() << "Disconnected";
}

void endFrete::carregaTransportadora()
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
    QString cmd = "SELECT * FROM transportadora";

    if(!query.exec(cmd))
    {
        qInfo() << db.lastError().text();
        qInfo() << query.lastError().text();
    }
    else
    {
        int id;
        QString nome;
        int prazo;
        double valor;

        while(query.next())
        {

            id = query.value(0).toInt();
            nome = query.value(1).toString();
            prazo = query.value(2).toInt();
            valor = query.value(3).toDouble();
            qInfo() << id << nome << prazo << valor;
            this->transportadoras.append(Transportadora(id, nome, prazo, valor));
        }
    }

    db.close();
    qInfo() << "Disconnected";
}
