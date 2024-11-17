//esse comando garante com que este arquivo seja incluido uma unica vez quando estiver acontecido uma compilação
#pragma once
#include <raylib.h>

class naveMisteriosa{
    public:
       //cosntrutor
       naveMisteriosa();
       //destrutor
       ~naveMisteriosa();
       
       void atualiza();

       void Draw();
      
      //por ser uma nave que aparecerá de vez em quando
      //criarei este metodo para aparecer e desaparecer a nave
       void aparece();
      
        //este metodo irá ser utilizado para retornar um retangulo,
       //neste caso para que seja feito detecção de uma colição 
       //utilizarei um metodo que verifica a colição de um retangulo
       //por isso a criação deste metodo        
       Rectangle getRetangulo();

       //variavel responsavel por armazenar se a nave misteriosa esta viva ou não 
       bool vivo;

       

    private:
     
      //armazena a posição da nave x e y
      Vector2 posicao;
      //armazena a imagem que será carregada
      Texture2D imagemNaveMisteriosa;
      int velocidade;
       
};
