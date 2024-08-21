# Futebol
Você como jogador de futebol deve evitar os obstáculos e adversários para chegar até a área do penalti e realizar aquele gol que ficará marcado na sua carreira.
#
Trabalho desenvolvido para a cadeira de Fundamentos de Computação Gráfica - 2024/1.
#
![image](https://github.com/user-attachments/assets/50a0d3e1-2556-4fd6-b433-f3bcb8f6a9e9)
Tela inicial do jogo
![image](https://github.com/user-attachments/assets/7c09b77e-e694-4239-8f5f-b87121fce416)
Jogador realizou um gol
![image](https://github.com/user-attachments/assets/fba807ae-3bc4-46d0-a7c3-24524f7c97ab)
Câmera livre

## Como jogar ?
- **W, A, S, D :** movimentação do Jogador
- **V :** alternar entre câmera livre e câmera look-at
- **Z :** reseta a cena
- **H :** esconde o texto
- **O :** projeção ortográfica
- **P :** projeção perspectiva
- **Mouse :** controla a direção da câmera
- **Scroll :** zoom-in e zoom-out
- **ESC :** fecha a janela do jogo

## Aplicação dos conceitos de Computação Gráfica
- **Malhas poligonais complexas :** O objeto player.obj presente na aplicação possui 78308 faces e 234924 vértices sendo mais complexo que o objeto cow.obj.
- **Transformações geométricas controladas pelo usuário :** Jogador consegue chutar a bola e, assim, ela se movimenta para a goleira.
- **Câmera livre e câmera look-at :** Ocorre uma troca entre elas acionando a tecla V.
- **Instâncias de objetos :** Existem diversos objetos e cópias do objeto cone e do objeto adversário.
- **Quatro tipos de testes de intersecção :** Esfera-Plano, Cilindro-Esfera, Cilindro-Cilindro e Cilindro-Plano
- **Modelos de Iluminação Difusa e Blinn-Phong :** Estão presentes nos dois modelos de interpolação da aplicação, com o objeto Sol utilizando o modelo de iluminação de Blinn-Phong
- **Modelos de Interpolação de Phong e Gouraud :** Todos objetos possuem Interpolação de Phong, exceto o Sol que possui Interpolação de Gouraud;
- **Mapeamento de texturas em todos os objetos :** Todos os objetos possuem textura.
- **Movimentação com curva Bézier cúbica :** Existe um Sol na aplicação que rotaciona pelo campo de futebol.
- **Animações baseadas no tempo ($\Delta t$) :** Movimentação da câmera, movimentação dos adversários e da bola, movimentação da curva de Bézier

## Uso de ferramentas externas
Ferramentas externas como ChatGPT ou opções similares foram utilizadas para pesquisa de algumas possiveis bibliotecas que poderiam ser usadas no projeto e também para geração de códigos que se mostraram ineficaz. Pesquisas sobre como algumas funções funcionam como o desenho de objetos e etc acabou ajudando pois a IA detalhou de forma compreensiva.
Utilizamos algumas fontes disponíveis no moodle para realização do teste de colisões

## Contribuições no projeto
- **Lucas Soller da Silva:** Pesquisa dos objetos 3D utilizados no projeto; Carregamento dos objetos e posicionamento; Animações de movimentação; Colisões; Ajuste de câmera
- **:**

## Bibliotecas utilizadas
- OpenGL
- glm
- glad
- glfw
- tiny_obj_loader
- Nenhuma biblioteca adicional foi utilizada

## Compilação e execução do projeto
