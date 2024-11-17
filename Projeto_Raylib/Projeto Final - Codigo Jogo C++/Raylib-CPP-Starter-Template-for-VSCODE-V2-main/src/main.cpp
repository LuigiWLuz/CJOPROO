#include <raylib.h>
#include "game.hpp"
#include <string>


int main() 
{
   //variavel que armazena uma cor
   Color cinza = {29, 29, 27, 255};

   //variavel que armazena o espaçamenento 
   int espacamento = 50;
  
   //variaveis que armazenam a medidas da tela
   int largura = 730;
   int altura = 650;

   // Função para criar uma janela
   InitWindow(largura + espacamento ,altura + 2 * espacamento,"Teste");

   //esta função carrega a fonte para que ela possa ser usada, e o atributo está a armazenando
   Font font = LoadFontEx("./fonte/monogram.ttf",64,0,0);
    
   //Essa variavel armazena a imagem da nave, no qual será usada para representar
   //as vidas restantes do jogador

   Texture2D naveVidas = LoadTexture("./imagensJogo/nave.png");

   //define a velocidade em que o jogo deve rodar, caso não seja definido o computador tentará rodar o jogo o mais rapido possivel 
   SetTargetFPS(60); 

   //objeto que armazena a inicialização do jogo, desenha os objetos
   //do jogo na tela e etc....
   game Game;
   
  

   //um laço para manter o jogo em execução caso não tenha sido apertada o escape ou o fechar da janela não esteja pressionado
   while(WindowShouldClose() == false){

        //Verifica a entrada do jogador para que aconteça determinadas 
        //ações, ir para direita o para esquerda ou direita
        Game.entradaJogador();

        //Atualiza os lasers que estão sendo disparados
        Game.atualiza();
       
        //cria uma tela em branco para que possa desenhar
        //os objetos do jogo 
        BeginDrawing(); 
        
        //sempre que esta funcao for chamada ela limpará o fundo do jogo com a cor que eu informei
        ClearBackground(cinza);

        //este metodo cria uma borda arredondada na tela
        DrawRectangleRoundedLines({15,10,760,760},0.10f,20,2,LIGHTGRAY);

        //adiciona uma linha da tela do jogo, o unico parametro que não
        //era conhecido é o penultimo que se trata da largura da linha
        DrawLineEx({25,700},{760,700},3,LIGHTGRAY);

         if(Game.rodar){
            //este metodo apresenta o texto na tela, é necessario inserir a fonte desejada, o que será escrito, as coodernadas de x e y, tamanho de fonte, espaçamento e cor da fonte
             DrawTextEx(font,"Fase 01",{600,705},34,2,MAGENTA);
         }
         else{
            //este metodo apresenta o texto na tela, é necessario inserir a fonte desejada, o que será escrito, as coodernadas de x e y, tamanho de fonte, espaçamento e cor da fonte
            DrawTextEx(font,"Game Over",{600,705},34,2,MAGENTA);

         }

         //armazena a posição x 
         float x = 50.0;
         //exibe as vidas restantes do jogador
         for(int i = 0; i < Game.vidasJogador; ++i){
            DrawTextureV(naveVidas, {x,710}, RED);
            x+=50;
         }

         //apresenta o score na tela
         DrawTextEx(font,"Score",{50,15},34,2,GOLD);
         std::string scoreConvertido = std::to_string(Game.score);

         //esta variavel esta recebendo o numero de zeros necessarios
         //a serem adicionados a esquerda, a pontuação maxima é de 5 digitos
         int zerosAEsquerda = 5 - scoreConvertido.length();

         //aqui esta sendo atribuido a frente da pontuação a qtd de zeros restantes
         //para que tenha 5 digitos
         scoreConvertido = std::string(zerosAEsquerda,'0') + scoreConvertido;

         DrawTextEx(font, scoreConvertido.c_str(),{50,40},34,2,RAYWHITE);

         //verifica apresenta o novo recorde

          DrawTextEx(font,"High-Score ",{570,15},34,2,GOLD);
         std::string novoScoreConvertido = std::to_string(Game.pontuacaoMaxima);

         //esta variavel esta recebendo o numero de zeros necessarios
         //a serem adicionados a esquerda, a pontuação maxima é de 5 digitos
         int zeroAEsquerda = 5 - novoScoreConvertido.length();

         //aqui esta sendo atribuido a frente da pontuação a qtd de zeros restantes
         //para que tenha 5 digitos
         novoScoreConvertido = std::string(zeroAEsquerda,'0') + novoScoreConvertido;

         //apresenta o maior score até o momento
         DrawTextEx(font, novoScoreConvertido.c_str(),{655,40},34,2,RAYWHITE);


        //Chamando a class Draw() para "desenhar", inserir a nave na tela
        Game.Draw();
        
        //Finaliza este desenho que estava na tela
        EndDrawing();




   }

   // Função para fechar a janela criada
   CloseWindow();


}