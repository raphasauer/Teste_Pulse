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
    int carrinho; //Número de itens no carrinho

    /**
     * @brief widgetCarrinho widget onde aparece o carrinho
     * @param parent widget pai
     * @return
     */
    QWidget *widgetCarrinho(QWidget *parent);

    QLabel *contador; //Label de contador utilizada
public:

    /**
     * @brief janelaInicial
     * @param parent
     */
    explicit janelaInicial(QWidget *parent = nullptr);

    /**
     * @brief carregaProdutos carrega produtos do DB
     */
    void carregaProdutos();

    QList<Produto> produtos; //Produtos carregados do DB
    QList<Produto> checkout; //Produtos no carrinho

signals:
public slots:

    /**
     * @brief receiver Recebe um produto para adicionar no carrinho
     * @param p produto
     */
    void receiver(Produto *p);

    /**
     * @brief proximaTela carrega próxima tela
     */
    void proximaTela();


    /**
     * @brief checkoutFeito recebe um sinal de que o checkout foi feito. Limpa o carrinho
     */
    void checkoutFeito();
};

#endif // JANELAINICIAL_H
