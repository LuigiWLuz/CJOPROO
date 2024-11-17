// o arquivo que fará a implementação da classe base escudo
#include "escudo.hpp"
#include <raylib.h>

escudo::escudo(Vector2 posicao)
{
    this->posicao = posicao;
}

 //Esta função cria um retangulo, que será utilizado para criar o escudo são passados como paramentros respectivamente, a posição no eixo x, no eixo y, largura, altura e cor
void escudo::Draw(){
    DrawRectangle(posicao.x,posicao.y,3,3,PURPLE);
}

//por o escudo ter sido criado, no caso não foi utilizada uma imagem, 
//é preciso criar um atributo do tipo Rectangle, 
//atribuir as coordenadas de x e y e suas medidas como a grade que foi
//utilizada para suas criação era 3x3 este serão os valores a serem
//passados
Rectangle escudo::getRetangulo()
{
    Rectangle retangulo;
    retangulo.x = posicao.x;
    retangulo.y = posicao.y;
    retangulo.width = 3;
    retangulo.height = 3;

    return retangulo;
}
