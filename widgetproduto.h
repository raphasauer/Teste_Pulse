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
    explicit widgetProduto(QWidget *parent, Produto p);
    void paintEvent(QPaintEvent *event);

private:
    Produto *prod = nullptr;

signals:
    void sender(Produto *p); // trocar inteiro por produto
public slots:
    void send();

};

#endif // WIDGETPRODUTO_H
