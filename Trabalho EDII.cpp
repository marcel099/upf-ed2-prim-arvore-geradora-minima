#include <iostream>
#include <fstream>          //usar toupper
#include <stdlib.h>         //aceitar exit
#include <clocale>          //aceitar acentua��o
#include <algorithm>        //usar fill
#include <cctype>           //usar toupper
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
    string rot_ver[q];              //vetor com o r�tulo dos vertices
    string rot_ar[q][q];            //matriz com o r�tulo das arestas
    int peso[q][q];                 //matriz com o peso das arestas

    fill(peso[0], peso[q]+q, 0);    //preenche matriz peso com valor 0 em todos

    for (int i=0; i<q; i++)         //leitura do r�tulo dos v�rtices
        arq>>rot_ver[i];

    arq >> q1;                      //leitura da quantia de arestas


//mostra de valores apenas para DEBUG
    cout<<"V�rtices:\n";
    for(int i=0;i<q;i++){
        cout<<rot_ver[i]<<endl;
    }
    cout<<"Pesos:\n";
    for(int i=0;i<q;i++){
        for(int j=0;j<q;j++){
            cout<<peso[i][j]<<"\t|\t";
        }
        cout<<endl;
    }
    cout<<"Arestas:\n";
    for(int i=0;i<q;i++){
        for(int j=0;j<q;j++){
            cout<<rot_ar[i][j]<<"\t|\t";
        }
        cout<<endl;
}
    pause();
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
