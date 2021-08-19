#include "janelainicial.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <widgetproduto.h>
#include <QWidget>
#include <janelacheckout.h>


janelaInicial::janelaInicial(QWidget *parent) : QMainWindow(parent)
{
    QScreen *q = QGuiApplication::primaryScreen();
    resize(q->availableSize());

    carrinho = 0;

    carregaProdutos();

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->setContentsMargins(75, 75, 75, 75);

    contador = new QLabel(centralWidget);

    QPushButton *proxTela = new QPushButton("Checkout", this);

    connect(proxTela, SIGNAL(clicked(bool)), this, SLOT(proximaTela()));

    layout->addWidget(proxTela);



    layout->addWidget(contador, 0, Qt::AlignRight);

    QScrollArea *scroll = new QScrollArea(centralWidget);
    scroll->setFrameShape(QFrame::NoFrame);
    QWidget *widgetScroll = new QWidget(centralWidget);
    QGridLayout *layoutScroll = new QGridLayout(widgetScroll);

    int k = 0;

    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 3; j++)
        {
            widgetProduto *p = new widgetProduto(this, produtos[k]);
            layoutScroll->addWidget(p, i, j);
            k++;
        }

    scroll->setWidgetResizable(true);
    scroll->setWidget(widgetScroll);
    layout->addWidget(scroll);
    setCentralWidget(centralWidget);
}



void janelaInicial::receiver(Produto *p)
{
    carrinho++;
    QString s;
    contador->setText(s.number(carrinho));
    if(p != nullptr)
    {
        this->checkout.append(*p);
    }
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

void janelaInicial::proximaTela()
{
    janelaCheckout *j = new janelaCheckout(this->checkout, this);
    j->show();
    //this->close();
}
