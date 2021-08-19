
CREATE TABLE transportadora(
    ID SERIAL PRIMARY KEY,
    NOME VARCHAR(50) NOT NULL,
    PRAZO INT NOT NULL,
    VALOR FLOAT NOT NULL
);

INSERT INTO transportadora (ID,NOME,PRAZO,VALOR)
VALUES (1, 'Correios', 10, 14.90);
VALUES (2, 'Transportadora', 5, 39.90);
VALUES (3, 'DHL', 2, 99.90);

CREATE TABLE tipopagamento(
    FORMAPAGAMENTO SERIAL PRIMARY KEY,
    NOME VARCHAR(50) NOT NULL,
    PARCELAS INT NOT NULL
);

INSERT INTO tipopagamento (FORMAPAGAMENTO,NOME,PARCELAS);
VALUES (1, 'Boleto', 1);
VALUES (2, 'PIX', 1);
VALUES (3, 'Cartao_Debito', 1);
VALUES (4, 'Cartao_Credito', 1);

CREATE TABLE produto(
    ID SERIAL PRIMARY KEY,
    PRECO FLOAT NOT NULL,
    NOME VARCHAR(50) NOT NULL,
    DESCRICAO VARCHAR(200) NOT NULL
);

INSERT INTO produto (ID,PRECO,NOME,DESCRICAO)
VALUES (1, 49.90,'Mouse', 'Mouse ergonômico sem fio da marca Techlogi');
INSERT INTO produto (ID,PRECO,NOME,DESCRICAO)
VALUES (2, 99.90,'Caixa de som', 'Caixa de som bluetooth da marca LJB');
INSERT INTO produto (ID,PRECO,NOME,DESCRICAO)
VALUES (3, 249.90,'Teclado', 'Teclado mecânico com iluminação RGB');
INSERT INTO produto (ID,PRECO,NOME,DESCRICAO)
VALUES (4, 3999.90,'peraPhone', 'peraPhone 12 última geração 128 GB de memória');
INSERT INTO produto (ID,PRECO,NOME,DESCRICAO)
VALUES (5, 7999.90,'peraBook', 'peraBook de 13 polegadas com processador pera1');
INSERT INTO produto (ID,PRECO,NOME,DESCRICAO)
VALUES (6, 5490.90,'Smart TV', 'TV 4K de 40 polegadas da Sungsamg');

CREATE TABLE pagamento(
    ID SERIAL PRIMARY KEY,
    FORMAPAGAMENTO INT NOT NULL,
    VALOR FLOAT NOT NULL,
    DESCONTO FLOAT
);

INSERT INTO pagamento(ID, FORMAPAGAMENTO, VALOR, DESCONTO)
VALUE(1, 2, 3, 4);

CREATE TABLE endereco(
    ID SERIAL PRIMARY KEY,
    CEP VARCHAR(10) NOT NULL,
    RUA VARCHAR(50) NOT NULL,
    NUMERO INT NOT NULL,
    COMPLEMENTO VARCHAR(50),
    CIDADE VARCHAR(50) NOT NULL,
    ESTADO INT NOT NULL
);

INSERT INTO endereco (ID,CEP,RUA,NUMERO, COMPLEMENTO, CIDADE, ESTADO)
VALUES (1, '12345-678','Rua São Paulo', 318, '', 'Cascavel', 8);
INSERT INTO endereco (ID,CEP,RUA,NUMERO, COMPLEMENTO, CIDADE, ESTADO)
VALUES (2, '98745-352','Rua Pitanga', 478, 'Casa 07', 'Toledo', 8);

CREATE TABLE cliente(
    ID SERIAL PRIMARY KEY,
    NOME VARCHAR(20) NOT NULL,
    SOBRENOME VARCHAR(20) NOT NULL
);

INSERT INTO cliente (ID,NOME,SOBRENOME)
VALUES (1, 'Raphael', 'Sauer');
