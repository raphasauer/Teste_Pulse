#include "janelainicial.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

janelaInicial::janelaInicial(QWidget *parent) : QMainWindow(parent)
{
    QScreen *q = QGuiApplication::primaryScreen();
    resize(q->availableSize());

    carregaProdutos();

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
            layoutScroll->addWidget(widgetProduto(widgetScroll, produtos[k].nome, produtos[k].preco, produtos[k].descricao, produtos[k].id), i, j);
            k++;
        }

    scroll->setWidgetResizable(true);
    scroll->setWidget(widgetScroll);
    layout->addWidget(scroll);
    setCentralWidget(centralWidget);
}

QWidget *janelaInicial::widgetProduto(QWidget *parent, QString s, double valor, QString desccricao, int id)
{
    setAccessibleName(s);
    QWidget *widget = new QWidget(parent);
    QVBoxLayout *layout = new QVBoxLayout(widget);

    widget->setStyleSheet("QWidget{background-color: rgb(255, 255, 255); border-radius: 20px;} "
    "QPushButton{ background-color: rgb(118, 50, 63); border: none; border-radius: 25px;"
    "color:rgb(215, 206, 199); height: 50px;}"
    "QPushButton:hover{background-color: rgb(124, 59, 71);}"
    "QPushButton:pressed{ background-color: rgb(78, 41, 48);}");

    QLabel *label = new QLabel(s, widget);
    QLabel *desc = new QLabel(desccricao, widget);
    layout->addWidget(label);
    layout->addWidget(desc);

    QLabel *preco = new QLabel("R$ " + QString::number(valor), widget);
    layout->addWidget(preco);

    QPushButton *botao = new QPushButton("Adicionar ao carrinho", widget);
    connect(botao, SIGNAL(clicked(bool)), this, SLOT(teste()));
    layout->addWidget(botao);

    return widget;
}

void janelaInicial::teste()
{
    qInfo() << QObject::sender();
    qInfo() << "teste";
}

void janelaInicial::carregaProdutos()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/rapha/Qt/Teste-Pulse/TestePulse.db");


    if(!db.open())
    {
        qInfo() << "Falha ao conectar com o banco de dados";
        qInfo() << db.lastError();
        return;
    }

    QSqlQuery query;
    QString cmd = "SELECT * FROM produto";

    if(!query.exec(cmd))
    {
        qInfo() << db.lastError().text();
        qInfo() << query.lastError().text();
    }
    else
    {
        int id;
        double preco;
        QString nome;
        QString descricao;

        while(query.next())
        {

            id = query.value(0).toInt();
            preco = query.value(1).toDouble();
            nome = query.value(2).toString();
            descricao = query.value(3).toString();
            qInfo() << id << preco << nome << descricao;
            this->produtos.append(Produto(id, preco, nome, descricao));

        }
    }

    db.close();
    qInfo() << "Disconnected";



}
