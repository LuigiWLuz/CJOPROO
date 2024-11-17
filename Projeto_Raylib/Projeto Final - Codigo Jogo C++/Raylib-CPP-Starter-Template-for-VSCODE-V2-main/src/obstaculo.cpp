// o arquivo que fará a implementação da classe base obstaculo
#include "obstaculo.hpp"

//grade esta fora do construtor pera que eu possa acessar este atributo da classe game
//e criar todos os estudos
std::vector<std::vector<int>> obstaculo::grade = {
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1}
    };


obstaculo::obstaculo(Vector2 posicao)
{
    this->posicao = posicao;

    //esse é a estrutura do escudo, como foi dito foi criado uma grade para conseguir fazer esta
    //criação essa grade é formada de zeros e uns onde os uns serão as parte que formam o escudo
    //as partes coloridas
   
    //esses laços são para que seja percorrido toda a grade
    //e feito a verificação de cada posição caso seja armazenado o valor 1 ele
    //é pintado da cor definida
    for(unsigned int linha = 0; linha < grade.size();++linha){
        //o grade[0].size() foi utilizado porque preciso somente da primeira linha
        //para saber quantas colunas a matriz possui
        for(unsigned int coluna = 0; coluna < grade[0].size(); ++coluna){
            if(grade[linha][coluna] == 1){
                //essa variaveis determinam a coordenada correta do bloco,
                //esse bloco que forma o escudo, no caso cada bloco possui
                //o tamanho de 3x3 
                float posicao_x = posicao.x + coluna * 3;
                float posicao_y = posicao.y + linha * 3;
                escudo Escudo = escudo({posicao_x,posicao_y});
                //armazena os blocos que formam o escudo
                Escudos.push_back(Escudo);
            }
        }
    }
}

//desenha os escudos na tela
void obstaculo::Draw(){
    for(auto& bloco : Escudos){
        bloco.Draw();
    }
}