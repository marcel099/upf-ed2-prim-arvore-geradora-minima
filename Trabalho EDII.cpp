#include <iostream>
#include <fstream>
#include <stdlib.h>         //aceitar exit
#include <clocale>          //aceitar acentua��o
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

void leitura()
{
    ifstream arq;
    arq.open("xispa.txt");
    if (!arq){
        cout << "N�o foi poss�vel abrir o arquivo\n";
        exit(1);
    }

    int NumVert, NumArest;
    arq >> NumVert;
    for (int i=0; i<NumVert; i++){

    }
    arq >> NumArest;
    for (int i=0; i<NumVert; i++){

    }
    cout << "Leu\n";
    system("pause");
}

void agv(){}

void grau(){}

void finais(){}

void incid(){}

void circuito(){}

void SeqGraus(){}

//void encerrar(){}

int main()
{
    setlocale(LC_ALL, "Portuguese");

    //int m[][];
    char op;
    do{
        menu();
        cout << "\tSelecione uma op��o: ";
        cin >> op;
        switch(op){
            case 'L':
                leitura();
                break;
            case 'A':
                agf();
                break;
            case 'G':
                grau();
                break;
            case 'F':
                finais();
                break;
            case 'I':
                incid();
                break;
            case 'C':
                circuito();
                break;
            case 'S':
                SeqGraus();
                break;
            case 'E':
                return 0;
            default:
                cout << "\n\tEscolha uma op��o v�lida: \n\n\t";
                system("pause");
        }
    }while(true);
    //return 0;
}
