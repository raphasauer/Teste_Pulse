#ifndef JANELAINICIAL_H
#define JANELAINICIAL_H

#include <QMainWindow>
#include <QGuiApplication>
#include <QScreen>
#include <QScrollArea>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QPixmap>
#include "widgetproduto.h"
#include <produto.h>
#include <QList>
#include <janelacheckout.h>


class janelaInicial : public QMainWindow
{
    Q_OBJECT
    int carrinho;
    QWidget *widgetCarrinho(QWidget *parent);
    QLabel *contador;
public:
    explicit janelaInicial(QWidget *parent = nullptr);
    /**
     * @brief carregaProdutos carrega produtos do DB
     */
    void carregaProdutos();
    QList<Produto> produtos;
    QList<Produto> checkout;

signals:
public slots:
    void teste(QString s);
    void receiver(Produto *p); // recebe o produto
    void proximaTela();

};

#endif // JANELAINICIAL_H
