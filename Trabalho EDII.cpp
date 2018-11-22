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

struct grafo{
    vector<string> rotulo_vertices;
    int **pesos;
    string **rotulo_arestas;
    int tam;
    vector<int> grau;
};

int buscaVertice(vector<string> v,string s){
    for(int i=0;i<v.size();i++)
        if(v[i]==s)
            return i;
    return -1;
}

grafo leitura(grafo g){
    ifstream arq;
    arq.open("xispa.txt");
    int tamanho,cont;
    string vertice,aresta;

    if (!arq){
        cout << "Não foi possível abrir o arquivo\n";
        exit(1);
    }
    arq>>tamanho;
    g.tam=tamanho;
    for(int i=0;i<g.tam;i++){
        arq>>vertice;
        g.rotulo_vertices.push_back(vertice);
    }
    //criação da matrizes: pesos e rotulo_arestas
    g.pesos = new int*[g.tam];
    g.rotulo_arestas=new string*[g.tam];
    for (int i=0;i<g.tam;i++){
        g.pesos[i] = new int[g.tam];
        g.rotulo_arestas[i]=new string[g.tam];
        for (int j=0;j<g.tam;j++)
            g.pesos[i][j] = 0;
    }
    int m[2];
    arq>>tamanho;
    for(int i=0;i<tamanho;i++){
        arq>>aresta;          //leitura do rotulo da aresta
        for(int j=0;j<2;j++){            //leitura dos 2 indices a serem armazenados na matriz
            arq>>vertice;
            m[j] = buscaVertice(g.rotulo_vertices,vertice);
        }
        arq>>g.pesos[m[0]][m[1]];            //armazenando o peso na matriz
        g.pesos[m[1]][m[0]]=g.pesos[m[0]][m[1]];//leia a linha acima

        g.rotulo_arestas[m[0]][m[1]]=aresta; //mesma coisa que o peso mas o rótulo da aresta
        g.rotulo_arestas[m[1]][m[0]]=aresta; //leia linha acima
    }

    for(int i=0;i<g.tam;i++){
        cont=0;
        for(int j=0;j<g.tam;j++)
            if(g.pesos[i][j]>0)
                cont++;
        g.grau.push_back(cont);
    }

    return g;
}


void agv(){}

void grau(grafo g){
    string s;
    int num;
    cout << "\n\tQual o vértice desejado? ";
    cin >> s;
    num=buscaVertice(g.rotulo_vertices, s);

    num<0 ? cout << "\tEste rótulo não existe.\n\n" : cout << "\tGrau de " << g.rotulo_vertices[num] << ": " << g.grau[num] << "\n\n";
}
//pq deixar tudo grudado? prejudica legibilidade //entre neste link: https://i.kym-cdn.com/entries/icons/original/000/007/508/neildegrasse.jpg

void finais(grafo g){
    vector<string> vf;
    for (int i=0; i<g.tam; i++)
        if (g.grau[i] == 1) vf.push_back(g.rotulo_vertices[i]);
        cout << vf.size() << endl;
        if(!vf.empty()){
            cout << "\tVértices Finais: ";             //mostra os vértices finais
            for (int i=0; i<vf.size(); i++)
                cout << vf[i] << ' ';
            cout << "\n\n";
        }
        else
            cout << "\tEste grafo não possui vértices finais\n\n";
}

void incid(grafo g){
    string s;
    cout<<"\n\tDigite o rótulo de uma aresta: ";
    cin>>s;

    for(int i=0; i<g.tam; i++){
        for(int j=0; j<g.tam; j++)
            if(s==g.rotulo_arestas[i][j]){
                cout<<"\n\tRótulos incidentes: "<<g.rotulo_vertices[i]<<' '<<g.rotulo_vertices[j]<<endl << endl;        //Não sei pq vcs gostam de deixar tudo grudado, mas tbm nao sei pq gosto de diexar separado
                return;
            }
    }
    cout<<"\n\tRótulo não existe.\n\n";
}

void circuito(){}

void SeqGraus(grafo g)
{
    stable_sort(g.grau.begin(), g.grau.end());        //ordena este vetor em ordem crescente

    cout << "\n\tSequência de Graus: ";             //mostra o vetor
    for (int i=0; i<g.grau.size(); i++)
        cout << g.grau[i] << ' ';
    cout << "\n\n";
}

void debug(grafo g){
    cout << "Vértices:\n";                //só passando pra melhorar a legibilidade
    for(int i=0;i<g.tam;i++)
        cout << g.rotulo_vertices[i] << ' ';

    cout << "\nPesos:\n\n\t|\t";
    for(int i=0;i<g.tam;i++)
        cout << g.rotulo_vertices[i] << "\t|\t";

    cout << "\n\t|---------------|---------------|---------------|---------------|---------------|\n";

    for(int i=0;i<g.tam;i++){
        cout << g.rotulo_vertices[i] << "\t|\t";
        for(int j=0;j<g.tam;j++){
            cout << g.pesos[i][j] << "\t|\t";
        }
        cout << endl;
    }

    cout << "\nArestas:\n\n\t|\t";

    for(int i=0;i<g.tam;i++)
        cout << g.rotulo_vertices[i] << "\t|\t";

    cout<<"\n\t|---------------|---------------|---------------|---------------|---------------|\n";

    for(int i=0;i<g.tam;i++){
        cout << g.rotulo_vertices[i] << "\t|\t";
        for(int j=0;j<g.tam;j++){
            cout << g.rotulo_arestas[i][j] << "\t|\t";
        }
        cout << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    grafo g;
    g=leitura(g);

    char op;
    do{
        int num,cont=0, i, j, aux=g.tam;
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
                grau(g);
                break;
            case 'F':
                finais(g);         //depois chamará apenas chamará a função de graus para evitar reptição de código já que apenas precisa saber quais são os vetores de grau 1
                break;
            case 'I':
                incid(g);
                break;
            case 'C':
//                circuito();
                break;
            case 'S':
                SeqGraus(g);
//                for (int i=0; i<g.tam; i++){                 //um for para gravar cada grau do vetor
//                    cont = 0;           //zera o contador após ter terminado de descobrir o grau de um vértice
//                    for(int j=0; j<g.tam; j++){             //passando pra comparar em cada vértice se possui aresta incidente em outro vértice
//                        if(g.pesos[i][j]>0)
//                            cont++;             //a cada aresta incidente num vértice incrementa o contador
//                    }
//                    graus.push_back(cont);                      //insere o grau de cada vértice em um vetor
//                }
                break;
            case 'E':
                exit(0);
            case 'D':       //opção escondida de debug
                debug(g);
                break;
            default:
                cout << "\n\tEscolha uma opção válida: \n\n\t";

        }
        system("pause");
    }while(true);
}

