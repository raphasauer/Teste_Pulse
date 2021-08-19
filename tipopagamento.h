#ifndef TIPOPAGAMENTO_H
#define TIPOPAGAMENTO_H
#include <QString>

enum FormaPagamento{
    Boleto,
    PIX,
    Cartao_debito,
    Cartao_credito,
};

class TipoPagamento
{
public:

    /**
     * @brief TipoPagamento contrutor TipoPagamento
     * @param fp forma de pagamento
     * @param nome
     * @param parcel pareclas
     */
    TipoPagamento(int fp, QString nome, int parcel);
    FormaPagamento formaPagamento; //Forma de pagamento
    QString nome; //Nome da forma de pagamento
    int parcelas; //Quantas parcelas caso pagamento não seja a vista
};

#endif // TIPOPAGAMENTO_H
