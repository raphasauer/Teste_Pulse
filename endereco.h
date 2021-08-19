#ifndef ENDERECO_H
#define ENDERECO_H
#include <QString>

enum Estado{
    Acre,
    Alagoas,
    Amapa,
    Amazonas,
    Bahia,
    Ceara,
    Distrito_Federal,
    Espirito_Santo,
    Goias,
    Maranhao,
    Mato_Grosso,
    Mato_Grosso_do_Sul,
    Minas_Gerais,
    Para,
    Paraiba,
    Parana,
    Pernambuco,
    Piaui,
    Rio_de_Janeiro,
    Rio_Grande_do_Norte,
    Rio_Grande_do_Sul,
    Rondonia,
    Roraima,
    Santa_Catarina,
    Sao_Paulo,
    Sergipe,
    Tocantins
};


class Endereco
{
public:
    /**
     * @brief Endereco contrutor de endereço
     * @param CEP
     * @param Rua
     * @param Numero
     * @param Complemento
     * @param Cidade
     * @param Estado
     */
    Endereco(QString CEP, QString Rua, int Numero, QString Complemento, QString Cidade, int Estado);

    QString cep; //CEP do endereço
    QString rua; //Nome da rua
    int numero; //Número do endereço
    QString complemento; //Complemento
    QString cidade; //Nome da cidade
    Estado estado; //Estado
protected:

};

#endif // ENDERECO_H
