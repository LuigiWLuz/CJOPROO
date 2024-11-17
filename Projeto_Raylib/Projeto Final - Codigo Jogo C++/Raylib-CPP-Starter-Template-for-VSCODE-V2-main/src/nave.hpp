//esse comando garante com que este arquivo seja incluido uma unica vez quando estiver acontecido uma compilação
#pragma once
#include <raylib.h>
#include <vector>
#include "laser.hpp"


class nave{
    public:
        //construtor
        nave();
        //destrutor
        ~nave();

        //"Desenha" os objetos do jogo na tela
        void draw();
        void moveParaDireita();
        void moveParaEsquerda();
        void atiraLaser();
        //este metodo irá ser utilizado para retornar um retangulo,
        //neste caso para que seja feito detecção de uma colição 
        //utilizarei um metodo que verifica a colição de um retangulo
        //por isso a criação deste metodo
        Rectangle getRetangulo();

        void resetaNave();
        
        //armazena os lasers atirados pela nave
        std::vector<laser> lasers;

    private:
        //classe que esta dentro do raylib que nos permite representar uma imagem 2D que pode ser usada pra renderizar graficos
        Texture2D imagem;

        //Sera utilizada para armazenar o posicao atual da nave
        Vector2 posicao;

        //Será utilizada para armazenar o tempo em que um laser pode ser disparado, desde de o ultimo disparo
        double tempoDeDisparo;
};
