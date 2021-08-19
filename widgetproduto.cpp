#include "widgetproduto.h"

widgetProduto::widgetProduto(QWidget *parent, Produto p) : QWidget(parent)
{
    setStyleSheet("QWidget{background-color: rgb(255, 255, 255); border-radius: 20px;}"
"QPushButton{background-color: rgb(118, 50, 63); border: none; border-radius: 25px;"
"color:rgb(215, 206, 199); height: 50px;}"
"QPushButton::hover{background-color: rgb(124, 59, 71);}"
"QPushButton:pressed{background-color: rgb(78, 41, 48);}");

    prod = new Produto(p.id, p.preco, p.nome, p.descricao);

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *label = new QLabel(p.nome, this);
    layout->addWidget(label);

    QLabel *preco = new QLabel("R$ " + QString::number(p.preco), this);
    layout->addWidget(preco);

    QPushButton *botao = new QPushButton("Adicionar ao carrinho", this);
    layout->addWidget(botao);

    connect(botao, SIGNAL(clicked(bool)), this, SLOT(send()));
    connect(this, SIGNAL(sender(Produto*)), parent, SLOT(receiver(Produto*)));

    setMinimumHeight(300);
}

void widgetProduto::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void widgetProduto::send()
{
    emit sender(prod);
}
