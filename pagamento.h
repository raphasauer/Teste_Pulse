#ifndef PAGAMENTO_H
#define PAGAMENTO_H


class Pagamento
{
public:
    /**
     * @brief Pagamento contrutor de pagamento
     * @param Valor
     * @param Desconto
     */
    Pagamento(float Valor, int TipoPagamento, float Desconto);

    /**
     * @brief confirmarPagamento registra a transação no DB
     */
    void confirmarPagamento();

    int rastreio;

protected:
    int tipoPagamento; //Tipo de pagamento
    float valor; //Valor total do carrinho
    float desconto; //Porcentagem de desconto aplicado ao valor total
};

#endif // PAGAMENTO_H
