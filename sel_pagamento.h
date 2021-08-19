#ifndef selPagamento_H
#define selPagamento_H

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
#include <tipopagamento.h>
#include <pagamento.h>

class selPagamento : public QMainWindow
{
    Q_OBJECT
public:
    explicit selPagamento(QWidget *parent = nullptr);
    QWidget *widgetFormaPagamento(QWidget *parent, int id, QString nome, int parcelas);
    QList<TipoPagamento> tipoPagamentos; //Lista com os tipos de pagamento carregados do BD
    Pagamento *pag = nullptr;
    double valorCarrinho;
    double valorFrete;
    int prazo;
    double valorTotal = 0.0;
    int formaPagamento = 0;


protected:
    /**
     * @brief carregaTipoPagamentos carrega os tipos de pagamento do banco de dados para a UI
     */
    void carregaTipoPagamentos();

    /**
     * @brief confirmarCompra registra a transação no DB e gera um número aleatório como chave
     */
    void confirmarCompra();

signals:
public slots:
    void teste();

};

#endif // selPagamento_H
