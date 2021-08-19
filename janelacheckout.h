#ifndef JANELACHECKOUT_H
#define JANELACHECKOUT_H

#include <QMainWindow>
#include <QFormLayout>
#include <QRadioButton>
#include <QGuiApplication>
#include <QScreen>
#include <QScrollArea>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>
#include <QList>
#include <endereco.h>
#include <transportadora.h>
#include <tipopagamento.h>
#include <produto.h>

class janelaCheckout : public QMainWindow
{
    Q_OBJECT
    QWidget *widgetEndereco(QWidget *parent);
    QWidget *widgetFrete(QWidget *parent);
    QWidget *widgetPagamento(QWidget *parent);
    QWidget *widgetProdutos(QWidget *parent);
public:
    explicit janelaCheckout( QList<Produto> lista, QWidget *parent = nullptr);

protected:
    /**
     * @brief carregaEndereco
     */
    void carregaEnderecos();
    /**
     * @brief carregaTransportadora
     */
    void carregaTransportadora();

    /**
     * @brief carregaTipoPagamentos
     */
    void carregaTipoPagamentos();

    QList<Endereco> enderecos;
    QList<Transportadora> transportadoras;
    QList<TipoPagamento> tipoPagamentos;
    QList<Produto> listaProdutos;
    double frete;
    int metodoPagamento;
    double tot;

signals:
public slots:
    void sucesso();

};

#endif // JANELACHECKOUT_H
