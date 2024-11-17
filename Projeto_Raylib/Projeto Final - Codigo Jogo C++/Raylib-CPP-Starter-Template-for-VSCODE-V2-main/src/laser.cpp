#include "laser.hpp"
#include <iostream>

laser::laser(Vector2 posicao, int velocidade)
{
    this->posicao = posicao;
    this->velocidade = velocidade;
    ativo = true;
}



void laser::Draw(){
    //Esta função cria um retangulo, que será utilizado para criar o laser são passados como paramentros respectivamente, a posição no eixo x, no eixo y, largura, altura e cor
    if(ativo){
        DrawRectangle(posicao.x,posicao.y,4,15,RED);
       // atualiza();
    }

}

//atualiza a posição do laser 
//este if serve para que se o laser passar do tamanho da tela, que ele seje inativo para que não continue sendo atulizado e consumindo memória
void laser::atualiza(){
    posicao.y += velocidade;
    if(posicao.y < 0){
        ativo = false;
        std::cout << "Laser inativo" << std::endl;
    }
}


//por o escudo ter sido criado, no caso não foi utilizada uma imagem, 
//é preciso criar um atributo do tipo Rectangle, 
//atribuir as coordenadas de x e y e suas medidas como a grade que foi
//utilizada para suas criação era 3x3 este serão os valores a serem
//passados
Rectangle laser::getRetangulo()
{
    Rectangle retangulo;
    retangulo.x = posicao.x;
    retangulo.y = posicao.y;
    retangulo.width = 4;
    retangulo.height = 15;
   
    return retangulo;
}