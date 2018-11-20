#include <iostream>
#include <fstream>          //usar toupper
#include <stdlib.h>         //aceitar exit
#include <clocale>          //aceitar acentua��o
#include <algorithm>        //usar fill
#include <cctype>           //usar toupper
#include <vector>
using namespace std;
void menu(){
    system("cls");
    cout << "\n----------------MENU----------------\n\n"
         << "\tL - Leitura\n"
         << "\tA - �rvore Geradora M�nima\n"
         << "\tG - Grau\n"
         << "\tF - V�rtices Finais\n"
         << "\tI - Incid�ncia\n"
         << "\tC - Circuito\n"
         << "\tS - Sequ�ncia de Graus\n"
         << "\tE - Encerrar Programa\n"
         << "\n----------------------------------------\n\n";
}

void agv(){}

void grau(){}

void finais(){}

void incid(){}

void circuito(){}

void SeqGraus(){}

void encerrar(){}

void pause(){
    system("pause");
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    ifstream arq;
    arq.open("xispa.txt");
    if (!arq){
        cout << "N�o foi poss�vel abrir o arquivo\n";
        exit(1);
    }
    int q,q1;
    arq >> q;                       //leitura da quantia de v�rtices
    vector<string> rot_ver;         //vetor com o r�tulo dos vertices
    string rot_ar[q][q];            //matriz com o r�tulo das arestas
    int peso[q][q];                 //matriz com o peso das arestas

    fill(peso[0], peso[q]+q, 0);    //preenche matriz peso com valor 0 em todos

    string rotulo;
    for (int i=0; i<q; i++){         //leitura do r�tulo dos v�rtices
        arq>>rotulo;
        rot_ver.push_back(rotulo);
    }
    arq >> q1;                      //leitura da quantia de arestas
    string rotulo_aresta,rotulo_vertice;
    int x,m[2];
    for(int i=0;i<q1;i++){
        arq>>rotulo_aresta;          //leitura do rotulo da aresta
    for(int j=0;j<2;j++){            //leitura dos 2 indices a serem armazenados na matriz
        arq>>rotulo_vertice;
        m[j] = distance(rot_ver.begin(), find(rot_ver.begin(), rot_ver.end(), rotulo_vertice));;
    }
    arq>>peso[m[0]][m[1]];            //armazenando o peso na matriz
    peso[m[1]][m[0]]=peso[m[0]][m[1]];//leia a linha acima

    rot_ar[m[0]][m[1]]=rotulo_aresta; //mesma coisa que o peso mas o r�tulo da aresta
    rot_ar[m[1]][m[0]]=rotulo_aresta; //leia linha acima
    }


    cout<<"V�rtices:\n";
    for(int i=0;i<rot_ver.size();i++){
        cout<<rot_ver[i]<<endl;
    }
    cout<<"\nPesos:\n\n\t|\t";
    for(int i=0;i<rot_ver.size();i++){
        cout<<rot_ver[i]<<"\t|\t";
    }
    cout<<"\n\t|---------------|---------------|---------------|---------------|---------------|\n";

    for(int i=0;i<rot_ver.size();i++){
        cout<<rot_ver[i]<<"\t|\t";
        for(int j=0;j<q;j++){
            cout<<peso[i][j]<<"\t|\t";
        }
        cout<<endl;
    }

    cout<<"\nArestas:\n\n\t|\t";

        for(int i=0;i<rot_ver.size();i++){
        cout<<rot_ver[i]<<"\t|\t";
    }
    cout<<"\n\t|---------------|---------------|---------------|---------------|---------------|\n";

    for(int i=0;i<rot_ver.size();i++){
        cout<<rot_ver[i]<<"\t|\t";
        for(int j=0;j<q;j++){
            cout<<rot_ar[i][j]<<"\t|\t";
        }
        cout<<endl;
}
}

//    char op;
//    do{
//        menu();
//        cout << "\tSelecione uma op��o: ";
//        cin >> op;
//        op=toupper(op);
//        switch(op){
//            case 'L':
//                leitura();
//                break;
//            case 'A':
//                agf();
//                break;
//            case 'G':
//                grau();
//                break;
//            case 'F':
//                finais();
//                break;
//            case 'I':
//                incid();
//                break;
//            case 'C':
//                circuito();
//                break;
//            case 'S':
//                SeqGraus();
//                break;
//            case 'E':
//                return 0;
//            default:
//                cout << "\n\tEscolha uma op��o v�lida: \n\n\t";
//                system("pause");
//        }
//    }while(true);
//    return 0;
//}
