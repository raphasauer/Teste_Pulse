#ifndef TRANSPORTADORA_H
#define TRANSPORTADORA_H
#include <QString>

class Transportadora
{
public:
    Transportadora(int ID, QString Nome, int Prazo, float Valor);
    int id; //ID da transportadora
    QString nome; //Nome da transportadora
    int prazo; //Prazo de entrega
    float valor; //Valor do frete
protected:

};

#endif // TRANSPORTADORA_H
