#include "produto.h"

Produto::Produto(int ID, double Preco, QString Nome, QString Descricao)
{
    this->id = ID;
    this->preco = Preco;
    this->nome = Nome;
    this->descricao = Descricao;
}
