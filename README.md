# Futebol
Você como jogador de futebol deve evitar os obstáculos e adversários para chegar até a área do penalti e realizar aquele gol que ficará marcado na sua carreira.

Trabalho desenvolvido para a cadeira de Fundamentos de Computação Gráfica - 2024/1.

## Como jogar ?
- **W, A, S, D :** movimentação do Jogador
- **V :** alternar entre câmera livre e câmera look-at
- **O :** projeção ortográfica
- **P :** projeção perspectiva
- **Mouse :** controla a direção da câmera
- **Scroll :** zoom-in e zoom-out
- **ESC :** fecha a janela do jogo

## Aplicação dos conceitos de Computação Gráfica
- **Malhas poligonais complexas :** Os objetos presentes na aplicação possuem uma complexidade igual ou maior que o modelo da cow.obj
- **Transformações geométricas controladas pelo usuário :** Jogador consegue chutar a bola e, assim, ela se movimenta para a goleira.
- **Câmera livre e câmera look-at :** Ocorre uma troca entre elas acionando a tecla V.
- **Instâncias de objetos :** Existem diversos objetos e cópias do objeto cone.
- **Quatro tipos de testes de intersecção :** Esfera-Plano, Cilindro-Esfera, Cilindro-Cilindro e Cilindro-Plano
- **Modelos de Iluminação Difusa e Blinn-Phong :** Estão presentes nos dois modelos de interpolação da aplicação, com o objeto Sol utilizando o modelo de iluminação de Blinn-Phong
- **Modelos de Interpolação de Phong e Gouraud :** Todos objetos possuem Interpolação de Phong, exceto o Sol que possui Interpolação de Gouraud;
- **Mapeamento de texturas em todos os objetos :** Todos os objetos possuem textura.
- **Movimentação com curva Bézier cúbica :** Existe um Sol na aplicação que rotaciona pelo campo de futebol.
- **Animações baseadas no tempo ($\Delta t$) :** Movimentação da câmera, movimentação dos adversários e da bola, movimentação da curva de Bézier

# Bibliotecas utilizadas
- OpenGL
- glm
- glad
- glfw
- tiny_obj_loader

Nenhuma biblioteca adicional foi utilizada
