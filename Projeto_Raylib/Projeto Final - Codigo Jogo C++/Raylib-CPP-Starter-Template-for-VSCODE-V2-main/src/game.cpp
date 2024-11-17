// o arquivo que fará a implementação da classe base game
#include "game.hpp"
#include <iostream>
#include <fstream>

//o construtor esta criando os escudos
game::game(){
 
 iniciarJogo();
 
}

//destrutor
game::~game(){
    et::descarregarImagens();
    //NaveMisteriosa.~naveMisteriosa();
}


//atualiza a posição em que o laser esta, caso tenha saido da tela 
//ele é desativado a movimentação do ets e seus disparos
void game::atualiza(){

    if(rodar){

        // std::cout << "atualizando jogo....... " << std::endl;

        if(GetTime() - ultimoTempoDeAparicao > intervaloDeTempoDeAparicaoNaveMisteriosa){
            //este metodo atualização o estado da nave misteriosa
            //inicializa a nave misteriosa
            NaveMisteriosa.aparece();

            //atribuindo a ultima aparição ao horario atual em que
            //ela aconteceu
            ultimoTempoDeAparicao = GetTime();
            //atribuindo um novo intervalo ao atributo
            intervaloDeTempoDeAparicaoNaveMisteriosa = GetRandomValue(10,20);

        }

        for(auto& laser : Nave.lasers){
            laser.atualiza();
        }
        movimentoEts();
        deletaLasersInativos();
        disparoEts();

        //faz o disparo dos lasers dos ets
        for(auto& laser : laserEts){
            laser.atualiza();
        }
         //teste -> std::cout << "Tamanho do vetor :" << Nave.lasers.size()  << std::endl;

        NaveMisteriosa.atualiza();
        //acada atualização é necessario checar se não houve uma colisão
        checaColisoes();



    }
    else{
        if(IsKeyDown(KEY_ENTER)){
            resetar();
            iniciarJogo();
        }
    }
   
}

//antes de criar este metodo, eu instanciava um objeto do tipo nave no main.cpp diretamente pelo nave.hpp, o que não é o mais seguro já que a classe possui informações importantes, então a classe game.cpp é para a implementação do que a classe nave possui sem possuir o acesso direto
void game::Draw(){
    Nave.draw();

//Este for faz com que os lasers continue sendo atirados 
    for(auto& laser : Nave.lasers){
        laser.Draw();
    }

//este loop desenha cada escudo
     for(auto& Escudo : Escudos){
        Escudo.Draw();
        //std::cout << "entrou" << std::endl;
    }

//este loop desenha cada et
     for(auto& Et : Ets){
        Et.Draw();
    }

//este loop desenha os lasers dos ets
    for(auto& laser : laserEts){
        laser.Draw();
    }
// aparecerá a anave misteriosa na tela
    NaveMisteriosa.Draw();
    
}

//Este método tem o papel de detectar a entrada do jogador e definir 
//o que será feito a partir desta entrada
void game::entradaJogador(){
    
    if(rodar){
        // A funcão abaixo conseguir é utilizada para verificar se uma tecla em especifico está pressionada, neste caso a tecla em especifico é seta para esquerda, se ela estiver pressionada retornará true e entrará no if
        if(IsKeyDown(KEY_LEFT)){
            Nave.moveParaEsquerda();
        }
        //Se a seta direita estiver pressionada ele move a nave para direita
        else if(IsKeyDown(KEY_RIGHT)){
            Nave.moveParaDireita();
        }
        //Se o space estiver pressionado ele atira os lasers
        else if(IsKeyDown(KEY_SPACE)){
            Nave.atiraLaser();
        }
        }
}

void game::deletaLasersInativos(){
    //esse for utiliza um iterador que pega sempre a proxima posição
    //do vetor até que ele chegue ao fim
    for(auto iterador = Nave.lasers.begin(); iterador != Nave.lasers.end();){

        //se o atributo ativo não for true ele esta inativo, logo
        //entrará na condição e será apagado caso ele esteja ativo ele passa para proxima posição do vetor para continuar a verificação
        if(!iterador->ativo){
            //funcao erase apaga essa posicão do vetor que se encaixou na condição realoca as outras posicoes e retorna um vetor novo
            iterador = Nave.lasers.erase(iterador);
        }
        else{
            ++iterador;
        }
    }

    //Apagando os lasers os ets

     //esse for utiliza um iterador que pega sempre a proxima posição
    //do vetor até que ele chegue ao fim
    for(auto iterador = laserEts.begin(); iterador != laserEts.end();){

        //se o atributo ativo não for true ele esta inativo, logo
        //entrará na condição e será apagado caso ele esteja ativo ele passa para proxima posição do vetor para continuar a verificação
        if(!iterador->ativo){
            //funcao erase apaga essa posicão do vetor que se encaixou na condição realoca as outras posicoes e retorna um vetor novo
            iterador =laserEts.erase(iterador);
        }
        else{
            ++iterador;
        }
    }
}

std::vector<obstaculo> game::criaTodosEscudos()
{
    //para saber a largura do escudo é necessário a qtd de 
    //colunas que a matriz possui multiplicado por tres porque cada 
    //possui é multiplicado por 3 para formar o bloco
    int larguraEscudo = obstaculo::grade[0].size() * 3;

    //para saber distancia exata, os espacos entre os escudos, é necessário 
    // o tamanho da tela - quantidade total de largura dos 4 escudos dividido por 5
    // existir 5 lacunas, espaços na tela
    float espaco = (GetScreenWidth() - (larguraEscudo*4))/5;
    //std::cout << "escudos: " << espaco << std::endl;

    for(int i = 0; i < 4; ++i){
        //essa variavel define exatamente onde cada escudo deve estar posicionado
        float espacoEntreosEscudos = (i + 1) * espaco + i * larguraEscudo;
        Escudos.push_back(obstaculo({espacoEntreosEscudos,float(GetScreenHeight())-100}));
    }

    return Escudos;
}

std::vector<et> game::criaEts()
{
  std::vector<et> ets;
  //os loops são para criação da grade parecido
  //com o que foi feito para a criação dos escudos
  //neste caso será para crição da grade para os ets
  // com estrutura de 5 linhas e 11 colunas
  for(int linha = 0; linha < 5; ++linha){
    for(int coluna = 0; coluna < 11; ++coluna){

        int tipoEt;
        if(linha == 0){
            tipoEt = 3;
        }
        else if( linha == 1 || linha == 2){
            tipoEt = 2;
        }
        else{
            tipoEt = 1;
        }

        //55 é a quantidade de pixels é tamanho que defini para
        //cada bloco de cada et
        //75 e 110 são os espaçamento horizontal e vertical dos ets
        float x = 75 + coluna * 55;
        float y = 110 + linha * 55;
        ets.push_back(et(tipoEt,{x,y}));
    }
  }
  //retorna o vetor de ets
  return ets;
}

void game::disparoEts()
{
    double tempoAtual = GetTime();
   
    //mesma logica que foi ultilzada para os disparos da nave,
    //verifica se o tempo atual - o ultimo disparo é maior que 
    // 0.35 e se o vetor de laser dos ets não está vazio
    if(tempoAtual - tempoUltimoDisparoEts >= tempoDeIntervaloDisparoEts && !Ets.empty()){

         //para conseguir pegar um et de maneira aleatoria
        int etAleatorio = GetRandomValue(0, Ets.size() - 1);
   
        et& Et = Ets[etAleatorio];

        // neste caso {Et.posicaoEt.x + Et.imagemEts[Et.tipo - 1].width/2,Et.posicaoEt.y + Et.imagemEts[Et.tipo - 1].height} este expressão foi para calcular o centro do et para ele dispara o laser e depois
        // a velocidade(direção do laser) no caso é para baixo
        laserEts.push_back(laser({Et.posicaoEt.x + Et.imagemEts[Et.tipo - 1].width/2,Et.posicaoEt.y + Et.imagemEts[Et.tipo - 1].height},6));

        //atualiza o tempo do ultimo disparo
        tempoUltimoDisparoEts = GetTime();
    }
}

void game::movimentoEts()
{
    //chama o metodo q cuida da movimentação do et
    for(auto& Et : Ets){
        if(Et.posicaoEt.x + Et.imagemEts[Et.tipo - 1].width > GetScreenWidth()){
            direcaoEt = -1;
            movimentoParaBaixoEts(4);
        }
        if((Et.posicaoEt.x-10) < 0){
           direcaoEt = 1;
           movimentoParaBaixoEts(4);
        }

        Et.atualiza(direcaoEt);
    }
}

//este metodo sempre será chamado quando os ets chegarem ao final da tela
void game::movimentoParaBaixoEts(int distancia)
{
    for(auto& Et : Ets){
        Et.posicaoEt.y += distancia;
    }
}

void game::checaColisoes()
{
    //verfica as colisoes dos lasers com os ets
    //este for percorre todos lasers da nave
    for(auto& laser : Nave.lasers){

        //este interador está atribuido ao primeiro et
        //do vetor de ets  
        auto iterador1 = Ets.begin();

        //este while permanece em loop enquando o
        //vetor nã estiver no fim
        while(iterador1 != Ets.end()){
            //este if em conjunto com este metodo 
            //verifica se o et colidiu com o laser
            //caso isso tenha acontecido ele sera removido do vetor de ets
            if(CheckCollisionRecs(iterador1->getRetangulo(),laser.getRetangulo())){

                //aqui é verificado qual et foi atingido para que
                //possa adicionar a pontuação ao score, o et 1 vale 100 pts,
                //o et 2 vale 200 pts e o et 3 vale 300 pts
                if(iterador1->tipo == 1){
                    score += 100;
                }
                else if(iterador1->tipo == 2){
                    score += 200;
                }
                else if(iterador1->tipo == 3){
                    score += 300;
                }

                //sempre q houver uma colisão com um nave é verifica se houve
                //um novo recorde
                checaRecorde();

                //o iterador é atribuido ao vetor de ets após a exclusão do et
                iterador1 = Ets.erase(iterador1);

                //apos isso o laser é atribuido a falso para q fique inativo
                //pq senão ele acertaria outros ets que estão atras deste et que foi atingido, facilitando o jogo
                laser.ativo = false;
            }
            else{
                //caso aquele et não tenha sofrido uma colisão
                //ele passa para o proximo elemento do vetor de ets 
                ++iterador1;
            }
        }

        //este loop possui o mesmo padrão de verificação,
        //mas neste caso está sendo verificado se laser não bateu
        //no escudo
        for(auto& obs : Escudos){

            auto iterador2 = obs.Escudos.begin();

            while(iterador2 != obs.Escudos.end()){
                 if(CheckCollisionRecs(iterador2->getRetangulo(),laser.getRetangulo())){
                     iterador2 = obs.Escudos.erase(iterador2);
                     laser.ativo = false;
                 }
                 else{
                    ++iterador2;
                 }
            }
        }

        //este if serve para fazer a verificação de colisão
        //da nave misteriosa
        if(CheckCollisionRecs(NaveMisteriosa.getRetangulo(),laser.getRetangulo())){
            NaveMisteriosa.vivo = false;
            laser.ativo = false;
            //pontuação ganha caso esta nave tenha sido atingida
            score += 500;

            //sempre q houver uma colisão com um nave é verifica se houve
            //um novo record
            checaRecorde();
        }
    }

    //colisão do laser dos ets no escudo e na nave

    for(auto& laserEt : laserEts){
        if(CheckCollisionRecs(laserEt.getRetangulo(),Nave.getRetangulo())){
            laserEt.ativo = false;
            --vidasJogador;
            if(vidasJogador == 0){
                gameOver();
            }
        }

         //este loop possui o mesmo padrão de verificação,
        //mas neste caso está sendo verificado se laser não bateu
        //no escudo
        for(auto& obs : Escudos){

            auto iterador2 = obs.Escudos.begin();

            while(iterador2 != obs.Escudos.end()){
                 if(CheckCollisionRecs(iterador2->getRetangulo(),laserEt.getRetangulo())){
                     iterador2 = obs.Escudos.erase(iterador2);
                     laserEt.ativo = false;
                 }
                 else{
                    ++iterador2;
                 }
            }
        }
    }

    //colisão dos ets no escudo, mesma estrutura que dos outros

    for(auto& Et : Ets){
        for(auto& es : Escudos){

           auto iterador3 = es.Escudos.begin();
           
           while(iterador3 != es.Escudos.end()){
                if(CheckCollisionRecs(iterador3->getRetangulo(),Et.getRetangulo())){
                    iterador3 = es.Escudos.erase(iterador3); 
                }
                else{
                    ++iterador3;
                }
           }
        }

        //verifica se o et colidiu com a nave
        if(CheckCollisionRecs(Et.getRetangulo(),Nave.getRetangulo())){
            gameOver();
        }
    }
}

//este metodo atribui o atributo a false paralizando o jogo
void game::gameOver()
{
    rodar = false;
}

//este metodo reseta o jogo
void game::resetar()
{
    Nave.resetaNave();
    Ets.clear();
    laserEts.clear();
    Escudos.clear();
}

void game::iniciarJogo(){
    Escudos = criaTodosEscudos();
    Ets = criaEts();

    //direção q os ets começam é para direita 
    direcaoEt = 1;

    //foi iniciado em 0 pq nenhum et disparou ainda
    tempoUltimoDisparoEts = 0.0;

    // a ultima aparação de uma nave
    //misteriosa foi atribuida a 0, pq esta sendo inicializada neste momento
    ultimoTempoDeAparicao = 0.0;

    //este atributo foi atribuido ao GetRandomValue, 
    //para que o intervalo de tempo em a aparição da nave será
    //aleatorio dentro de 10 a 20 ms

    //quando o jogo é inicializado o jogador possui 3 vidas
    vidasJogador = 3;

    //como o jogo foi inicializado o atributo é recebe o valor true
    rodar = true;

    intervaloDeTempoDeAparicaoNaveMisteriosa = GetRandomValue(10,20);

    score = 0;

    pontuacaoMaxima = carregaRecorde();
    
   
}

void game::checaRecorde()
{
    if(score > pontuacaoMaxima){
        pontuacaoMaxima = score;
        salvaRecorde(pontuacaoMaxima);
    }
}

void game::salvaRecorde(int recorde)
{
    //a classe ofstream cria uma instancia de um arquivo
    //de saida no qual nomeei de "recorde.txt"
    //caso o arquivo não exista, ele será criado
    //se já existir ele irá sobreescrever o 
    //documento 
    std::ofstream arquivoComRecorde("recorde.txt");

    //este if verifica se o arquivo esta aberto,
    //caso esteja ele insere o novo recorde
    if(arquivoComRecorde.is_open()){
        arquivoComRecorde << recorde;
        arquivoComRecorde.close();
    }
}

int game::carregaRecorde(){
    int recordeCarregado = 0;

    //a classe ifStream cria uma instancia de um arquivo
    //de entrada, no qual faz a leitura do arquivo escolhido
    // o "recorde.txt" 

    std::ifstream arquivoCarregado("recorde.txt");

     //este if verifica se o arquivo esta aberto,
    //caso esteja ele atribui o recorde a variavel
    if(arquivoCarregado.is_open()){
        arquivoCarregado >> recordeCarregado;
        arquivoCarregado.close();
    }

    return recordeCarregado;

}
