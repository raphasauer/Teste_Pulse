# Teste Pulse
Teste para vaga de desenvolvedor Pulse. O código foi desenvolvido utilizando C++ e a framework Qt 6.1. O banco de dados foi feito utilizando SQLITE e os scripts de criação das tabelas se encontram em `tabelas.sql`. A documentação do código foi gerada utilizando a ferramenta Doxygen. Os comentários de documentação em código seguem o padrão Javadoc.

## Fluxo do programa
O programa inicia com uma tela que possui produtos carregados a partir de um banco de dados. O usuário pode inserir produtos no carrinho apertando o botão de "Inserir produto". Após terminar de inserir os produtos desejados, o usuário clica em "Checkout" para avançar para a tela de checkout. Nessa tela é possível escolher alguns endereços cadastrados no banco de dados junto com qual transportadora irá entregar os produtos. Por fim, é possível escolher um método de pagamento (também armazenado no banco de dados) para finalizar a compra. Ao finalizar a compra, é gerado um código de rastreio de forma aleatória e a compra é inserida no banco de dados.

## Capturas de tela

![image](https://user-images.githubusercontent.com/24641708/130147770-ec11b76e-df9d-4918-aa02-102241c0525d.png)

![image](https://user-images.githubusercontent.com/24641708/130147810-f6b784e0-b512-40e2-a8ff-13a36b621f6e.png)

![image](https://user-images.githubusercontent.com/24641708/130147880-f401d5a2-1f27-454e-8fd1-a1a25e25b992.png)

![image](https://user-images.githubusercontent.com/24641708/130147915-8a6a38a8-35f1-40de-aa79-ad8cc3424cf8.png)

