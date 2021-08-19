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

    connect(this, SIGNAL(checkoutFinalizado()), parent, SLOT(checkoutFeito()));

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->setContentsMargins(75, 75, 75, 75);

    QScrollArea *scroll = new QScrollArea(centralWidget);
    scroll->setFrameShape(QFrame::NoFrame);
    QWidget *widgetScroll = new QWidget(centralWidget);
    QFormLayout *layoutScroll = new QFormLayout(widgetScroll);

    layoutScroll->setVerticalSpacing(50);

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

    QPushButton *botao = new QPushButton("Finalizar compra", centralWidget);
    botao->setStyleSheet("QPushButton{background-color: rgb(118, 50, 63); border: none; border-radius: 25px;"
"color:rgb(215, 206, 199); height: 50px;}"
"QPushButton::hover{background-color: rgb(124, 59, 71);}"
"QPushButton:pressed{background-color: rgb(78, 41, 48);}");

    connect(botao, SIGNAL(clicked(bool)), this, SLOT(sucesso()));


    scroll->setWidgetResizable(true);
    scroll->setWidget(widgetScroll);
    layout->addWidget(scroll);
    layout->addWidget(botao);
    setCentralWidget(centralWidget);
}

void janelaCheckout::sucesso()
{
    this->pag = new Pagamento(tot + frete, 0.0);
    pag->confirmarPagamento();
    int retornoBox = QMessageBox::information(this, "Sucesso!", "Compra efetuada com sucesso! Seu código de rastreio é: " + QString::number(pag->rastreio));
    if(retornoBox == QMessageBox::Ok)
    {
        emit checkoutFinalizado();
        this->close();
    }
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
        if(i == 0)
            b->setChecked(true);
        layout->addWidget(b);
    }

    return widget;
}


QWidget *janelaCheckout::widgetFrete(QWidget *parent)
{
    QWidget *widget = new QWidget(parent);

    QGridLayout *layout = new QGridLayout(widget);

    QComboBox *box = new QComboBox(widget);
    box->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    frete = transportadoras[0].valor;

    for(int i = 0; i < transportadoras.size(); i++)
    {
        QString transp;
        transp = transportadoras[i].nome + " " + QString::number(transportadoras[i].prazo) + " dias úteis " + "R$ " + QString::number(transportadoras[i].valor);
        box->addItem(transp);
    }

    connect(box, SIGNAL(currentIndexChanged(int)), this, SLOT(freteChanged(int)));


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
        QRadioButton *btn = new QRadioButton(pag, widget);
        btn->setChecked(true);
        layout->addWidget(btn, i, 0);
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

    precoTotal = new QLabel("Total: R$ " + QString::number(tot + frete), widget);
    layout->addWidget(precoTotal, i, 2);

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
            this->enderecos.append(Endereco(cep, rua, numero, complemento, cidade, estado));
        }
    }

    db.close();
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
            this->transportadoras.append(Transportadora(id, nome, prazo, valor));
        }
    }

    db.close();
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
            this->tipoPagamentos.append(TipoPagamento(id, nome, parcelas));
        }
    }

    db.close();
}

void janelaCheckout::freteChanged(int index)
{
    frete = transportadoras[index].valor;
    precoTotal->setText("Total: R$ " + QString::number(tot + frete));
}





