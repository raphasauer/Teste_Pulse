#ifndef PRODUTO_H
#define PRODUTO_H
#include <QString>


class Produto
{
public:

    /**
     * @brief Produto construtor de Produto
     * @param id
     * @param preco
     * @param nome
     * @param descricao
     */
    Produto(int id, double preco, QString nome, QString descricao);
    int id; //ID do produto
    double preco; //Preço do produto
    QString nome; //Nome do produto
    QString descricao; //Descrição do produto
};

#endif // PRODUTO_H
