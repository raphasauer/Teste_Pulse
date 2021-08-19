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
#include <pagamento.h>

class janelaCheckout : public QMainWindow
{
    Q_OBJECT
    /**
     * @brief widgetEndereco widgets para os endereços
     * @param parent widget pai
     * @return
     */
    QWidget *widgetEndereco(QWidget *parent);

    /**
     * @brief widgetFrete widgets para os fretes disponíveis
     * @param parent widget pai
     * @return
     */
    QWidget *widgetFrete(QWidget *parent);

    /**
     * @brief widgetPagamento widgets para os tipos de pagamentos
     * @param parent widget pai
     * @return
     */
    QWidget *widgetPagamento(QWidget *parent);

    /**
     * @brief widgetProdutos widgets para os produtos do carrinho
     * @param parent widget pai
     * @return
     */
    QWidget *widgetProdutos(QWidget *parent);



public:

    /**
     * @brief janelaCheckout janela com informações do checkout
     * @param lista lista de produtos do carrinho
     * @param parent widget pai
     */
    explicit janelaCheckout( QList<Produto> lista, QWidget *parent = nullptr);

protected:
    /**
     * @brief carregaEndereco carrega os endereços presentes no banco de dados
     */
    void carregaEnderecos();

    /**
     * @brief carregaTransportadora carrega as transportadoras armazenadas no banco de dados
     */
    void carregaTransportadora();

    /**
     * @brief carregaTipoPagamentos carregam os tipos de pagamento presentes no banco de dados
     */
    void carregaTipoPagamentos();

    QList<Endereco> enderecos; //Lista com os endereços carregados
    QList<Transportadora> transportadoras; //Lista com as transportadoras carregadas
    QList<TipoPagamento> tipoPagamentos; //Lista com os tipos de pagamento carregados
    QList<Produto> listaProdutos; //Lista com os produtos do carrinho
    QLabel *precoTotal; //Label do preço total

    Pagamento *pag; //Ponteiro para o pagamentp

    double frete; //Frete utilizado

    double tot; //Valor total do carrinho

signals:

    /**
     * @brief checkoutFinalizado enviado quando o checkout é finalizado
     */
    void checkoutFinalizado();
public slots:
    void sucesso();

    /**
     * @brief freteChanged Recebe quando frete foi mudado
     * @param index índice escolhido na combobox
     */
    void freteChanged(int index);


};

#endif // JANELACHECKOUT_H
