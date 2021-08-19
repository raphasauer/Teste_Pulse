#ifndef WIDGETPRODUTO_H
#define WIDGETPRODUTO_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>
#include <QPushButton>
#include <produto.h>

class widgetProduto : public QWidget
{
    Q_OBJECT
public:

    /**
     * @brief widgetProduto carrega um produto em forma de widget
     * @param parent widget pai
     * @param p produto carregado
     */
    explicit widgetProduto(QWidget *parent, Produto p);
    void paintEvent(QPaintEvent *event);

private:
    Produto *prod = nullptr; //Ponteiro para um produto

signals:

    /**
     * @brief sender envia um sinal do produto para colocar no carrinho
     * @param p produto
     */
    void sender(Produto *p);

public slots:

    /**
     * @brief send recebe um sinal para colocar o produto no carrinho
     */
    void send();

};

#endif // WIDGETPRODUTO_H
