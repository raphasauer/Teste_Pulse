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
#include <QList>
#include <produto.h>

class janelaInicial : public QMainWindow
{
    Q_OBJECT
public:
    explicit janelaInicial(QWidget *parent = nullptr);
    /**
     * @brief widgetProduto gera um widget para um produto
     * @param parent widget pai do widget gerado
     * @param nome nome do produto
     * @param valor valor do produto
     * @param desc descrição do produto
     * @param id id do produto
     * @return
     */
    QWidget *widgetProduto(QWidget *parent, QString nome, double valor, QString desc, int id);

    QList<Produto> produtos; //Lista com os produtos carregados do BD
    double valorCarrinho = 0.0; //Valor dos items do carrinho atual

protected:
    /**
     * @brief carregaProdutos carrega os produtos disponíveis no banco de dados para a UI
     */
    void carregaProdutos();

signals:
public slots:
    void teste();

};

#endif // JANELAINICIAL_H
