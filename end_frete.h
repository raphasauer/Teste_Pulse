#ifndef endFrete_H
#define endFrete_H

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
#include <endereco.h>
#include <transportadora.h>

class endFrete : public QMainWindow
{
    Q_OBJECT
public:
    explicit endFrete(QWidget *parent = nullptr);
    /**
     * @brief widgetEndereco função que gera o widget com um endereço
     * @param parent widget pai do widget a ser gerado
     * @param rua rua do endereço
     * @param numero número do endereço
     * @param complemento complemento do endereço
     * @param estado estado do endereço
     * @return retorna um widget com os dados acima para ser exibido na tela
     */

    QWidget *widgetEndereco(QWidget *parent, QString rua, int numero, QString complemento, int estado);
    /**
     * @brief widgetTransportadora widgetEndereco função que gera o widget com uma transportadora
     * @param parent widget pai do widget a ser gerado
     * @param nome nome da transportadora
     * @param prazo prazo de entrega em dias úteis
     * @param valor valor do frete
     * @return retorna um widget com os dados acima para ser exibido na tela
     */
    QWidget *widgetTransportadora(QWidget *parent, QString nome, int prazo, double valor);

    QList<Endereco> enderecos; //Lista com os endereços carregados do BD
    QList<Transportadora> transportadoras; //Lista com as transportadoras carregadas do DB

    double valorCarrinho; //Valor do carrinho atual
    double valorFrete = 0.0; //Valor do frete selecionado
    int prazo = 0; //Prazo de entrega

protected:
    /**
     * @brief carregaEnderecos carrega os endereços disponíveis no banco de dados para a UI
     */
    void carregaEnderecos();
    /**
     * @brief carregaTransportadora carrega as transportadoras disponíveis no banco de dados para a UI
     */
    void carregaTransportadora();

signals:
public slots:
    void teste();

};

#endif // endFrete_H
