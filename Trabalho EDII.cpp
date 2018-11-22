#include <iostream>
#include <fstream>          //usar toupper
#include <stdlib.h>         //aceitar exit
#include <clocale>          //aceitar acentuação
#include <algorithm>        //usava fill, mas agora usa stable_sort                  //Como parou de aceitar fill dá pra esconder
#include <cctype>           //usar toupper
#include <vector>
using namespace std;
void menu(){
    system("cls");
    cout << "\n----------------MENU----------------\n\n"
         << "\tA - Árvore Geradora Mínima\n"
         << "\tG - Grau\n"
         << "\tF - Vértices Finais\n"
         << "\tI - Incidência\n"
         << "\tC - Circuito\n"
         << "\tS - Sequência de Graus\n"
         << "\tE - Encerrar Programa\n"
         << "\n----------------------------------------\n\n";
}

int buscaVertice(vector<string> v,string s){
    for(int i=0;i<v.size();i++)
        if(v[i]==s)
            return i;
    return -1;
}

struct dados{
    string rot;             //rótulo da aresta
    int peso;               //peso da aresta
};

void agv(){}

void grau(){}

void finais(){}

void incid(){}

void circuito(){}

void SeqGraus(){}

//void pause(){                         //isso é desnecessauro
//    system("pause");
//}

int main()
{
    setlocale(LC_ALL, "Portuguese");

    ifstream arq;
    arq.open("xispa.txt");
    if (!arq){
        cout << "Não foi possível abrir o arquivo\n";
        exit(1);
    }

    int QtdVert, QtdArest;                                                                  //futuras duas únicas variáveis globais, mas é complicado criar variável global não iniciaizada
    arq >> QtdVert;                       //leitura da quantia de vértices
    vector<string> vet;         //vetor com o rótulo dos vertices                               //DÚVIDA: pq usar vector sendo q dá pra usar um simples vetor?
    dados m[QtdVert][QtdVert];          //matriz com os pesos e rótulos das arestas

    for (int i=0; i<QtdVert; i++){            //preenche matriz peso com valor 0 em todos
        for (int j=0; j<QtdVert; j++)
            m[i][j].peso = 0;
    }

   // fill(m[0][0].peso, m[QtdVert][QtdVert].peso, 0);  //não faço ideia de como aceitava antes, mas a função fill a princípio é só para vetor e parou de funcionar ao usar matriz de struct


    string rotulo;
    for (int i=0; i<QtdVert; i++){         //leitura do rótulo dos vértices
        arq>>rotulo;
        vet.push_back(rotulo);
    }

    arq >> QtdArest;                      //leitura da quantia de arestas
    string rotulo_aresta, rotulo_vertice;
    int vert[2];                             //vert: núemro dos vértices incidentes da aresta na matriz
    for(int i=0; i<QtdArest; i++){
        arq >> rotulo_aresta;          //leitura do rotulo da aresta

        for(int j=0; j<2; j++){            //leitura dos 2 indices a serem armazenados na matriz
            arq >> rotulo_vertice;
            vert[j] = buscaVertice(vet, rotulo_vertice);
        }
        arq >> m[vert[0]][vert[1]].peso;                             //armazenando o peso da aresta na matriz
        m[vert[1]][vert[0]].peso = m[vert[0]][vert[1]].peso;         //leia a linha acima                   //DÚVIDA: oq essa linha realmente faz?

        m[vert[0]][vert[1]].rot = rotulo_aresta;            //mesma coisa que o peso mas o rótulo da aresta
        m[vert[1]][vert[0]].rot = rotulo_aresta;            //leia linha acima
    }

    char op;
    do{
        int num,cont=0, i, j, aux=vet.size();
        vector<int> graus;
        vector<string> vf;      //Vértices Finais
        bool teste=false;
        string s;

        menu();
        cout << "\tSelecione uma opção: ";
        cin >> op;
        op=toupper(op);
        switch(op){
            case 'A':
//                agf();
                break;
            case 'G':
//                grau();
                cout<<"\n\tQual o vértice desejado? ";
                cin>>s;
                num=buscaVertice(vet,s);
                if(num<0)
                    cout<<"\n\tRótulo não existe.\n";
                else{
                    for(int i=0;i<vet.size();i++){
                        if(m[num][i].peso>0)
                            cont++;
                    }
                    cout<<"\n\tGrau de "<<vet[num]<<": "<<cont<<"\n\n";       //pq deixar tudo grudado? prejudica legibilidade
                }
                break;
            case 'F':
//                finais();         //depois chamará apenas chamará a função de graus para evitar reptição de código já que apenas precisa saber quais são os vetores de grau 1
                for (int i=0; i<vet.size(); i++){                 //um for para gravar cada grau do vetor
                    cont = 0;           //zera o contador após ter terminado de descobrir o grau de um vértice
                    for(int j=0; j<vet.size(); j++){             //passando pra comparar em cada vértice se possui aresta incidente em outro vértice
                        if(m[i][j].peso>0)
                            cont++;             //a cada aresta incidente num vértice incrementa o contador
                    }
                    graus.push_back(cont);                      //insere o grau de cada vértice em um vetor
                }

                for (int i=0; i<graus.size(); i++)
                    if (graus[i] == 1) vf.push_back(vet[i]);

                if(!vf.empty()){
                    cout << "\tVértices Finais: ";             //mostra os vértices finais
                    for (int i=0; i<vf.size(); i++)
                        cout << vf[i] << ' ';
                    cout << endl << endl;
                }
                else
                    cout << "\tEste grafo não possui vértices finais\n\n";

                break;
            case 'I':
//                incid();
                cout<<"\n\tDigite o rótulo de uma aresta: ";
                cin>>s;

                for(int i=0; i<vet.size(); i++, aux--){
                    for(int j=0; j<aux; j++){
                        if(s==m[i][j].rot){
                            cout<<"\n\tRótulos incidentes: "<<vet[i]<<' '<<vet[j]<<endl << endl;        //Não sei pq vcs gostam de deixar tudo grudado, mas tbm nao sei pq gosto de diexar separado
                            teste=true;
                            break;
                        }
                    }
                    if(teste==true) break;
                }
                if(teste==false)
                cout<<"\n\tRótulo não existe.\n\n";

                break;
            case 'C':
//                circuito();
                break;
            case 'S':
//                SeqGraus();
                for (int i=0; i<vet.size(); i++){                 //um for para gravar cada grau do vetor
                    cont = 0;           //zera o contador após ter terminado de descobrir o grau de um vértice
                    for(int j=0; j<vet.size(); j++){             //passando pra comparar em cada vértice se possui aresta incidente em outro vértice
                        if(m[i][j].peso>0)
                            cont++;             //a cada aresta incidente num vértice incrementa o contador
                    }
                    graus.push_back(cont);                      //insere o grau de cada vértice em um vetor
                }
                stable_sort(graus.begin(), graus.end());        //ordena este vetor em ordem crescente

                cout << "\n\tSequência de Graus: ";             //mostra o vetor
                for (int i=0; i<graus.size(); i++)
                    cout << graus[i] << ' ';
                cout << endl << endl;

                break;
            case 'E':
                exit(0);
                //break;                            //esse break é desnecessário pois o programa já encerra dentro deste case
            case 'D': //opção escondida de debug
                cout<<"Vértices:\n";
                for(int i=0;i<vet.size();i++){
                    cout<<vet[i]<<' ';
                }
                cout<<"\nPesos:\n\n\t|\t";
                for(int i=0;i<vet.size();i++){
                    cout<<vet[i]<<"\t|\t";
                }
                cout<<"\n\t|---------------|---------------|---------------|---------------|---------------|\n";

                for(int i=0;i<vet.size();i++){
                    cout<<vet[i]<<"\t|\t";
                    for(int j=0;j<QtdVert;j++){
                        cout<<m[i][j].peso<<"\t|\t";
                    }
                    cout<<endl;
                }

                cout<<"\nArestas:\n\n\t|\t";

                    for(int i=0;i<vet.size();i++){
                    cout<<vet[i]<<"\t|\t";
                }
                cout<<"\n\t|---------------|---------------|---------------|---------------|---------------|\n";

                for(int i=0;i<vet.size();i++){
                    cout<<vet[i]<<"\t|\t";
                    for(int j=0;j<QtdVert;j++){
                        cout<<m[i][j].rot<<"\t|\t";
                    }
                    cout<<endl;
                }

                break;
            default:
                cout << "\n\tEscolha uma opção válida: \n\n\t";     //é o último "case", então não precisa de break

        }
        system("pause");
    }while(true);
}

