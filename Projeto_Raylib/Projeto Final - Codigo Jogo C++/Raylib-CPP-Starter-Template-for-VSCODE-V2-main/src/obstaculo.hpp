//esse comando garante com que este arquivo seja incluido uma unica vez quando estiver acontecido uma compilação
#pragma once
#include "escudo.hpp"
#include <vector>


class obstaculo{
    public:
        //construtor
        obstaculo(Vector2 posicao);
        //desenhará os objetos do jogo na tela, janela
        void Draw();
        
        //este vetor armazenará todos os blocos do retangulo
        Vector2 posicao;

        //será utilizado para armazenar os escudos
        std::vector<escudo> Escudos;
        //sera feito uma grade,matriz para formar os escudos
        static std::vector<std::vector<int>> grade;

    private:
       
};
