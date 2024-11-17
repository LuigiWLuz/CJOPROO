#include "et.hpp"

Texture2D et::imagemEts[3];
et::et(int tipo, Vector2 posicaoEt)
{
    this->tipo = tipo;
    this->posicaoEt = posicaoEt;


    //este verifica se o tipo de et(a imagem) ja foi iniciada
    //caso ela já tenha sido incializada ela será atribuida a 1
    //então indica que ja foi inicializada 
    if(imagemEts[tipo-1].id  == 0){
        //este switch atribui a variavel a imagem(tipo de et) que ela será 
        //atribuido
        switch(tipo){
            case 1 : imagemEts[0] = LoadTexture("./imagensJogo/alien_1.png");
                break;
            case 2 : imagemEts[1] = LoadTexture("./imagensJogo/alien_2.png");
                break;
            case 3 : imagemEts[2] = LoadTexture("./imagensJogo/alien_3.png");
                break; 
            default : imagemEts[0] = LoadTexture("./imagensJogo/alien_1.png");
                break;
        }
    }
}

void et::Draw(){
    //função que "Desenha" os objetos do jogo na tela
    //os parametros são (a imagem que já atribui no switch, a posicao do et, a cor que eu defino para o et)
   if(tipo == 2)
   DrawTextureV(imagemEts[tipo-1],posicaoEt,ORANGE);
   else
   DrawTextureV(imagemEts[tipo-1],posicaoEt,WHITE);
}

int et::getTipo(){
    return tipo;
}


//metodo para descarregar as imagens
//por se tratar de array utilizei um loop para fazer isso
void et::descarregarImagens()
{
   for(int i = 0; i < 3; ++i){
     UnloadTexture(imagemEts[i]);
   }
}

Rectangle et::getRetangulo()
{
     //no return está sendo retornado as coordenadas da nave e 
    //suas dimensões, e os valores de suas dimensões está sofrendo
    //casting para float pq o construtor da classe Rectangle
    //espera receber valores do tipo float
    return {posicaoEt.x,posicaoEt.y,float(imagemEts[tipo-1].width),float(imagemEts[tipo-1].height)};
}

//este metodo adiciona movimento para os ets
void et::atualiza(int movimentoEt){
    posicaoEt.x += movimentoEt;
}