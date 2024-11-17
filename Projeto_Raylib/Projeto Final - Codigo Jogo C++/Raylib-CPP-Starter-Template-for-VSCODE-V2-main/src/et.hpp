//esse comando garante com que este arquivo seja incluido uma unica vez quando estiver acontecido uma compilação
#pragma once
#include <raylib.h>

class et{
    public:
       //cosntrutor

       et(int tipo,Vector2 posicaoEt);
       
       //atuaiza posicao atual do et
       void atualiza(int movimentoEt);
       
       //metodo que desenhará a et na tela
       void Draw();
       
       //este metodo retorna o tipo de et, pois terão diferentes tipos
       int getTipo();
       
       //metodo para limpar a memoria, descarregar imagens utilizadas
       static void descarregarImagens();
       
       //este metodo irá ser utilizado para retornar um retangulo,
       //neste caso para que seja feito detecção de uma colição 
       //utilizarei um metodo que verifica a colição de um retangulo
       //por isso a criação deste metodo        
       Rectangle getRetangulo();
      
       //variavel que erá exibir a imagem do et, foi colocado como 
       //static para otimização quando criado os ets, eram criados 55 ets, só que são tres imagens diferentes, é mais eficiente criar um array de tres posições q armazenas esses tres tipos de ets
       static Texture2D imagemEts[3];
       int tipo;
       //armazena a posicaod do et
       Vector2 posicaoEt;
       

    private:
       
};
