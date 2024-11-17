// o arquivo que fará a implementação da classe base nave
#include "nave.hpp"

nave::nave()
{
    //a variavel imagem esta sendo atribuida a imagem que esta sendo carrega pela funcao 
    imagem = LoadTexture("./imagensJogo/nave.png");

    //definição da posição inicial da nave
    //(retorna a largura da tela -> GetScreenWidth() - retorna a largura da nave -> imagem.width)/2; Isso é feito para centralizar a nave horizontalmente 
    posicao.x = (GetScreenWidth() - imagem.width)/2;

    //(retorna a largura da tela -> GetScreenWidth() 
    // Isso é feito para definar a nave no fim da tela
    posicao.y = GetScreenHeight() - imagem.height;

    //como a nave esta sendo inicializada não houve nenhum disparo, logo o tempo para que aconteça o proximo disparo ainda não foi definido 
    tempoDeDisparo = 0.0;
}

//Sempre que o jogo for fechado é necessario limpar o espaço de memória que foi utilizado, utilziando o destrutor
nave::~nave()
{
    //a memoria utilizada na imagem que foi carregada é limpa, libera 
    // utilizando esta funcao
    UnloadTexture(imagem);
}


void nave::draw(){
    //função que "Desenha" os objetos do jogo na tela
    //os parametros são (a imagem que já carreguei no construtor, a posicao do nave, a cor que eu defino para nave)
    DrawTextureV(imagem,posicao,{255,218,185,255});
}

//quando chamada esta função decrementa 7 pixels da posição que ele 
//estava, o if criado foi para limitar onde a nave consegue chegar,
//para que não saia da tela
void nave::moveParaEsquerda(){
    posicao.x -= 7;
    if((posicao.x-10) < 0)
        posicao.x = 12;
        
}

//quando chamada esta função incrementa 7 pixels da posição que ele 
//estava, o if criado foi para limitar onde a nave consegue chegar,
//para que não saia da tela
void nave::moveParaDireita(){
    posicao.x += 7;
     if(posicao.x > GetScreenWidth() - imagem.width)
        posicao.x = GetScreenWidth() - imagem.width;
}

void nave::atiraLaser(){
    
    //a condição é que se o tempo atual - menos o tempo do ultimo disparo 
    //for maior que 0.35 ele permite que aconteça outro disparo
    //após isso ele adiciona o tempo atual ao tempo de disparo para
    // que possa existir este tempo de espera até o proximo disparo
    if(GetTime() - tempoDeDisparo >= 0.35){

        //para o laser ficar centralizado é necessário (pegar a posição da nave) posicao.x +  (a largura da nave) imagem.width/2 - (pelo laser ter 4 pixels de largura é preciso subtrair pela sua metade) 2
        lasers.push_back(laser({posicao.x + imagem.width/2 - 2,posicao.y},-6));
        tempoDeDisparo = GetTime();

    }
}

Rectangle nave::getRetangulo()
{
    //no return está sendo retornado as coordenadas da nave e 
    //suas dimensões, e os valores de suas dimensões está sofrendo
    //casting para float pq o construtor da classe Rectangle
    //espera receber valores do tipo float
    return {posicao.x,posicao.y, float(imagem.width), float(imagem.height)};
}

//volta a nave para a posição inicial do jogo, e apaga seu vetor de lasers
void nave::resetaNave()
{
    posicao.x = (GetScreenWidth() - imagem.width)/2.0;
    posicao.y = (GetScreenHeight() - imagem.height);
    lasers.clear();
}
