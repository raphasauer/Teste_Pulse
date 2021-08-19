#ifndef CLIENTE_H
#define CLIENTE_H
#include <QString>
#include <pagamento.h>
#include <endereco.h>
#include <produto.h>
#include <QList>

class Cliente
{
public:
    /**
     * @brief Cliente contrutor de cliente
     * @param Nome
     * @param Sobrenome
     */
    Cliente(QString Nome, QString Sobrenome);

    /**
     * @brief carregaCliente consulta o banco de dados e, se o cliente
     * está registrado, carrega ele
     * @param nome nome do cliente
     * @param sobrenome sobrenome do cliente
     */
    void carregaCliente(QString nome, QString sobrenome);

protected:
    int id; //ID do cliente
    QString nome; //Nome do cliente
    QString sobrenome; //Sobrenome do cliente

};

#endif // CLIENTE_H
