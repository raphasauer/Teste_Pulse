#include "endereco.h"

Endereco::Endereco(QString CEP, QString Rua, int Numero, QString Complemento, QString Cidade, int est)
{
    this->cep = CEP;
    this->rua = Rua;
    this->numero = Numero;
    this->complemento = Complemento;
    this->cidade = Cidade;
    this->estado = (Estado) est;
}
