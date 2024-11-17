//esse comando garante com que este arquivo seja incluido uma unica vez quando estiver acontecido uma compilação
#pragma once
#include "nave.hpp"
#include "laser.hpp"
#include "obstaculo.hpp"
#include "et.hpp"
#include "naveMisteriosa.hpp"

class game{
    public:
        //construtor
        game();
        //destrutor
        ~game();

        //desenhará os objetos do jogo na tela, janela
        void Draw();
        //fará a atulização da posição da nave
        void atualiza();
        //vai adiministrar a entrada do jogador(se ele apertou a botão para ir para esquerda ou para direita)
        void entradaJogador();
        void moveParaDireita();
        void moveParaEsquerda();
        void atiraLaser();

        //caso este atributo esteja com o valor true atribuido, ele
        //esta sendo jogado, se estiver false ele não está sendp jogado
        bool rodar;

        //armazena a qtd de vidas que o jogador possui
         int vidasJogador;

        //atributo que armazena a pontuação do jogador
        int score;

        //pontuação maxima conquistada até o momento
        int pontuacaoMaxima;

    private:
        void deletaLasersInativos();
        nave Nave;
        //este metodo retorna todos os escudos
        std::vector<obstaculo> criaTodosEscudos();
       
        // armazenará todos os escudos
        std::vector<obstaculo> Escudos;

            //metodos que criara estes ets
        std::vector<et> criaEts();
        
        //vector que armazenará os ets
        std::vector<et> Ets;

        //armazenara o lazer dos ets
        std::vector<laser> laserEts;

        //metodo que fará o disparo dos lasers dos ets
        void disparoEts();

        //metodo que fará a movimentação dos ets
        void movimentoEts();

        //metodo que fará a movimentação dos ets para baixo
        void movimentoParaBaixoEts(int distancia);

        //verifica se houve alguma colição dos lasers a partir daquele 
        //metodo que retorna o retangulo
        void checaColisoes();

        //caso a vida do jogador tenha acaba este metodo finaliza o jogo
        void gameOver();

        //este metodo sera utilizado para reiniciar o jogo
        void resetar();

        //este metodo fica responsavel por iniciar o jogo 
        void iniciarJogo();

        //verifica se a pontuação foi a maior a ser conseguida,
        //caso seja será o novo recorde
        void checaRecorde();

        //este metodo faz com que a recorde seja salvo em um arquivo txt
        void salvaRecorde(int recorde);

        //carrega o recorde na tela
        int carregaRecorde();

        //variavel que armazenará o movimento do et
        int direcaoEt;

        //o intervalo de tempo em que acontece os disparos, foi 
        //definida como constante como o tempo de 350 milisegundos
        constexpr static float tempoDeIntervaloDisparoEts = 0.35;

        //este atributo armazena o tempo do ultimo disparo do et
        float tempoUltimoDisparoEts;

        //atributo para conseguir utilizar os metodos da naveMisteriosa
        naveMisteriosa NaveMisteriosa;

        //este atributo armazena o intervalo de tempo de cada nave misteriosa
        float intervaloDeTempoDeAparicaoNaveMisteriosa;

        //este atributo armazena o tempo da ultima aparição
        //de uma nave misteriosa
        float ultimoTempoDeAparicao;

        
};
