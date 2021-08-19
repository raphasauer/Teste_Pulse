#include "tipopagamento.h"

TipoPagamento::TipoPagamento(int fp, QString Nome, int parcel)
{
    this->formaPagamento = (FormaPagamento) fp;
    this->nome = Nome;
    this->parcelas = parcel;
}
