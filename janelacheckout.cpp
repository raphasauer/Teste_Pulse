#include "janelacheckout.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <endereco.h>
#include <transportadora.h>
#include <tipopagamento.h>
#include <QDebug>
#include <pagamento.h>

janelaCheckout::janelaCheckout(QList<Produto> lista, QWidget *parent) : QMainWindow(parent)
{
    this->listaProdutos = lista;
    this->tot = 0.0;
    QScreen *q = QGuiApplication::primaryScreen();
    resize(q->availableSize());

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->setContentsMargins(75, 75, 75, 75);

    QScrollArea *scroll = new QScrollArea(centralWidget);
    scroll->setFrameShape(QFrame::NoFrame);
    QWidget *widgetScroll = new QWidget(centralWidget);
    QFormLayout *layoutScroll = new QFormLayout(widgetScroll);

    // flarts entrega

    carregaEnderecos();
    carregaTransportadora();
    carregaTipoPagamentos();


    layoutScroll->addRow("1. Endereço de entrega", widgetEndereco(widgetScroll));

    // flarts frete

    layoutScroll->addRow("2. Frete", widgetFrete(widgetScroll));

    // flarts pagamento

    layoutScroll->addRow("3. Pagamento", widgetPagamento(widgetScroll));

    layoutScroll->addRow("4. Produtos", widgetProdutos(widgetScroll));

    QPushButton *botao = new QPushButton("FINALIZAR COMPRA", centralWidget);
    connect(botao, SIGNAL(clicked(bool)), this, SLOT(sucesso()));


    scroll->setWidgetResizable(true);
    scroll->setWidget(widgetScroll);
    layout->addWidget(scroll);
    layout->addWidget(botao);
    setCentralWidget(centralWidget);
}

void janelaCheckout::sucesso()
{
    this->pag = new Pagamento(99.9, 2, 0.0);
    pag->confirmarPagamento();
    QMessageBox::information(this, "Sucesso!", "Compra efetuada com sucesso! Seu código de rastreio é: " + QString::number(pag->rastreio));
}

QWidget *janelaCheckout::widgetEndereco(QWidget *parent)
{
    QWidget *widget = new QWidget(parent);
    QVBoxLayout *layout = new QVBoxLayout(widget);

    QString end;

    for(int i = 0; i < 2; i++)
    {
        end = enderecos[i].rua + " " + QString::number(enderecos[i].numero) + " " + enderecos[i].complemento + " " + enderecos[i].cep;
        QRadioButton *b = new QRadioButton(end, widget);
        layout->addWidget(b);
    }

    return widget;
}

QWidget *janelaCheckout::widgetFrete(QWidget *parent)
{
    QWidget *widget = new QWidget(parent);
    QGridLayout *layout = new QGridLayout(widget);

    QString transp;

    for(int i = 0; i < 3; i++)
    {
        transp = transportadoras[i].nome + " " + QString::number(transportadoras[i].prazo) + " dias úteis";
        QRadioButton *btn = new QRadioButton(transp, widget);
        //connect(btn, SIGNAL(clicked()), this, SLOT(freteMudou));
        layout->addWidget(btn, i, 0);
        layout->addWidget(new QLabel("R$ " + QString::number(transportadoras[i].valor), widget), i, 1);
    }

    return widget;
}

QWidget *janelaCheckout::widgetPagamento(QWidget *parent)
{
    QWidget *widget = new QWidget(parent);
    QGridLayout *layout = new QGridLayout(widget);

    QString pag;

    for(int i = 0; i < 4; i++)
    {
        pag = tipoPagamentos[i].nome;
        layout->addWidget(new QRadioButton(pag, widget), i, 0);
        QComboBox *box = new QComboBox(widget);

        if(pag == "Cartao_Credito")
        {
            for(int j = 1; j < 4; j++)
            {
                QString s;
                box->addItem(s.number(j) + "X sem juros");
            }
        }

        else
        {
             box->addItem("À vista");
        }

        layout->addWidget(box, i, 1);
    }

    return widget;

}

QWidget *janelaCheckout::widgetProdutos(QWidget *parent)
{
    QWidget *widget = new QWidget(parent);
    QGridLayout *layout = new QGridLayout(widget);

    int i = 0;

    for(; i < this->listaProdutos.size(); i++)
    {
        layout->addWidget(new QLabel(listaProdutos[i].nome, widget), i, 0);
        layout->addWidget(new QLabel("R$ " + QString::number(listaProdutos[i].preco), widget), i, 1);
        tot += listaProdutos[i].preco;
    }

    layout->addWidget(new QLabel("Total: R$ " + QString::number(tot), widget), i, 2);

    return widget;

}

void janelaCheckout::carregaEnderecos()
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

void janelaCheckout::carregaTransportadora()
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

void janelaCheckout::carregaTipoPagamentos()
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






