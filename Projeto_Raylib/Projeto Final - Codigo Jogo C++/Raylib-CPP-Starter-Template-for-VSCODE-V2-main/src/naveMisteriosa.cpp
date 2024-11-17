// o arquivo que fará a implementação da classe base naveMisteriosa
#include "naveMisteriosa.hpp"
#include <iostream>


//construtor
naveMisteriosa::naveMisteriosa()
{
    imagemNaveMisteriosa = LoadTexture("./imagensJogo/naveMisteriosa.png");
    //a nave é definada como falsa na sua inicialização para conseguir 
    //fazer este controle da aparcer e desaparecer
    vivo = false;
}

//destrutor
naveMisteriosa::~naveMisteriosa()
{
    UnloadTexture(imagemNaveMisteriosa);
}

void naveMisteriosa::aparece()
{
    
    posicao.y = 90;
    //essa variavel define de maneira aleatoria qual será o lado 
    //em que a nave aparecera, no caso essa função que pega um valor 
    //aleatoria foram passados os valores 0 e 1, no qual
    //respectivamente representam o lado esquerdo e o direito
    int lado = GetRandomValue(0,1);

    if(lado == 0){
        //std::cout << "Entrou" << std::endl;
        posicao.x = 0;
        //velocidade não é nada mais a distancia em que a imagem anda a cada atualização
        velocidade = 3;
    }
    else{
      //  std::cout << "Entrou no atualizar else" << std::endl; 
        posicao.x = GetScreenWidth() - imagemNaveMisteriosa.width;
        //velocidade não é nada mais a distancia em que a imagem anda a cada atualização, neste caso é menos -3 pq ele vai da direita para esquerda, então ele decrementa até chegar a 0
        velocidade = -3;
    }

    vivo = true;
}

void naveMisteriosa::atualiza()
{
    if(vivo){
      //  std::cout << "Entrou no atualizar" << std::endl;
        posicao.x += velocidade;
        //neste if verifica se a nave já saiu da tela, caso tenha
        // ele é atribuido a falso, para que ela deixa de continuar se movimentando
        if(posicao.x > GetScreenWidth() - imagemNaveMisteriosa.width || posicao.x < 0){
        //    std::cout << "Entrou na verificação atualizar" << std::endl;
            vivo = false;
        }
    }
}

void naveMisteriosa::Draw(){
   if(vivo){
       // std::cout << "Entrou no desenhar" << std::endl;
        //faz a nave aparecer na tela
        DrawTextureV(imagemNaveMisteriosa,posicao,PINK);
   }
}

Rectangle naveMisteriosa::getRetangulo()
{
    //este if serve para que só aconteça uma colição
    //com a nave misteriosa caso ela esteja visivel
    if(vivo){
        //no return está sendo retornado as coordenadas da nave e 
        //suas dimensões, e os valores de suas dimensões está sofrendo
        //casting para float pq o construtor da classe Rectangle
        //espera receber valores do tipo float
        return {posicao.x,posicao.y,float(imagemNaveMisteriosa.width),float(imagemNaveMisteriosa.height)};
    }
    //caso a nave não esteja visivel ele torna sua posição, mas suas
    //dimensões não 
    else{
        return {posicao.x,posicao.y,0,0};
    }
}
