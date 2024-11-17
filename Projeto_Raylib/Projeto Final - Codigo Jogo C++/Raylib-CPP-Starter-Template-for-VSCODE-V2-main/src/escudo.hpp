//esse comando garante com que este arquivo seja incluido uma unica vez quando estiver acontecido uma compilação
#pragma once
#include <raylib.h>


class escudo{
    public:
        //construtor
        escudo(Vector2 posicao);
        //desenhará os objetos do jogo na tela, janela
        void Draw();
        
       //este metodo irá ser utilizado para retornar um retangulo,
       //neste caso para que seja feito detecção de uma colição 
       //utilizarei um metodo que verifica a colição de um retangulo
       //por isso a criação deste metodo        
       Rectangle getRetangulo();

    private:
        Vector2 posicao;
};
