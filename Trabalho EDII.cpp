#include <iostream>
#include <fstream>
#include <stdlib.h>         //exit
#include <clocale>          //aceitar acentuação
#include <algorithm>        //stable_sort
#include <cctype>           //usar toupper
#include <vector>
#include <stack>      //pilha pode se tornar desncessária
#include <string>           //usar stoi e substr
#include <climits>          //INT_MAX
using namespace std;
void menu(){
    system("cls");
    cout << "Marcelo - 158114 - 158114@upf.br\n"
         << "Mateus - 171424\n"
         << "Weliton - 166404 - 166404@upf.br\n";
    cout << "\n----------------MENU----------------\n\n"
         << "\tA - Árvore Geradora Mínima\n"
         << "\tM - Mostrar Grafo\n"
         << "\tG - Grau\n"
         << "\tF - Vértices Finais\n"
         << "\tI - Incidência\n"
         << "\tC - Circuito\n"
         << "\tS - Sequência de Graus\n"
         << "\tE - Encerrar Programa\n"
         << "\tJ - Adjacencia\n"
         << "\n----------------------------------------\n\n";
}
//minha anotação pra eu não esquecer mais por enquanto: Ctrl + R -> Localizar e Substituir
struct grafo{
    vector<string> rotulo_vertices;
    int **pesos;
    string **rotulo_arestas;
    int TamVert, TamArest;              //precisei saber quantas arestas possui esse grafo lá dentro do circuito
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
    int tamanho, cont;
    string vertice, aresta;

    if (!arq){
        cout << "Não foi possível abrir o arquivo\n";
        exit(1);
    }

    arq >> tamanho;
    g.TamVert = tamanho;
    for(int i=0; i<g.TamVert; i++){
        arq >> vertice;
        g.rotulo_vertices.push_back(vertice);
    }
    //criação da matrizes: pesos e rotulo_arestas
    g.pesos = new int*[g.TamVert];
    g.rotulo_arestas = new string*[g.TamVert];
    for (int i=0; i<g.TamVert; i++){
        g.pesos[i] = new int[g.TamVert];
        g.rotulo_arestas[i] = new string[g.TamVert];
        for (int j=0; j<g.TamVert; j++)
            g.pesos[i][j] = 0;
    }
    int m[2];
    arq >> tamanho;                                                 //dá pra melhorar esse código, usando as variáveis da própria struct grafo
    g.TamArest = tamanho;                                            //precisei fazer apenas isso pra poder continuar fazendo a função de circuito
    for(int i=0; i<tamanho; i++){
        arq >> aresta;          //leitura do rotulo da aresta
        for(int j=0; j<2; j++){            //leitura dos 2 indices a serem armazenados na matriz
            arq >> vertice;
            m[j] = buscaVertice(g.rotulo_vertices, vertice);
        }
        arq >> g.pesos[m[0]][m[1]];            //armazenando o peso na matriz
        g.pesos[m[1]][m[0]] = g.pesos[m[0]][m[1]];//leia a linha acima

        g.rotulo_arestas[m[0]][m[1]] = aresta; //mesma coisa que o peso mas o rótulo da aresta
        g.rotulo_arestas[m[1]][m[0]] = aresta; //leia linha acima
    }

    for(int i=0; i<g.TamVert; i++){
        cont=0;
        for(int j=0; j<g.TamVert; j++)
            if(g.pesos[i][j] > 0)
                cont++;
        g.grau.push_back(cont);
    }

    return g;
}

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
    vector<string> vf;              //vector que guarda o rótulo dos nodos com grau 1
    for (int i=0; i<g.TamVert; i++)
        if (g.grau[i] == 1)                     //se o grau for 1 insere no vector
            vf.push_back(g.rotulo_vertices[i]);

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
    cout << "\n\tDigite o rótulo de uma aresta: ";
    cin >> s;

    for(int i=0; i<g.TamVert; i++){
        for(int j=0; j<g.TamVert; j++)          //como isso tá funcionando sem as chaves?
            if(s == g.rotulo_arestas[i][j]){
                cout << "\n\tRótulos incidentes: " << g.rotulo_vertices[i] << ' ' << g.rotulo_vertices[j] << "\n\n";        //Não sei pq vcs gostam de deixar tudo grudado, mas tbm nao sei pq gosto de diexar separado
                return;
            }
    }
    cout << "\n\tRótulo não existe.\n\n";
}

void circuito(grafo g)
{
    vector<bool> ArestVisit;                                 //Arestas Visitadas
    bool formou=false;                                       //formou circuito

    int pos;                                                //posição da aresta encontrada
    vector<string> circ;
    for (int k=0; k<g.TamVert; k++){                          //percorre todo o grafo olhando vértice por vértice buscando formar circuito
        stack<int> VertPass;                                    //Posição no vector dos Vértices Passados

        while (!ArestVisit.empty())                    //se já percorreu todo o grafo antes é necessário remarcar todas as arestas como não visitadas
            ArestVisit.clear();
        for (int i=0; i<g.TamArest; i++)
            ArestVisit.push_back(false);                 //colocando um bool false para cada aresta no vector de bools, indicando que ainda não foram visitados

        int VertOrig = k;                                     //Vértice por onde começou o circuito, precisa disso pra saber quando formou um circuito
        if (g.grau[k] >= 2){                                  //já elimina vértices isolados e vértices finais
            VertPass.push(k);                                                           //insere na PILHAo vértice inicial
            circ.push_back(g.rotulo_vertices[k]);                                       //insere no CIRCUITO o vértice inicial

            while (!formou){                                                  //enquanto não tiver formado circuito
                bool existe=false;                              //Supõe que não existe aresta não visitada a partir do vértice atual           //bool passou: pra saber se já passou por todo o grafo a partir de uma determinada posição e mesmo assim não encontrou circuito
                for(int i=0; i<g.TamVert; i++){
                    if (g.rotulo_arestas[k][i] != ""){                                            //se aresta existir poderá realizar as operações referentes a aresta
                        pos = stoi(g.rotulo_arestas[k][i].substr(1, 2), nullptr) - 1;                        //lê a posição da aresta para poder mudar no vector de bool         //no entanto, isso não funcionará se os números das aresas do arquivo xispa não estiverem perfeitamente consecutivos (1,2,3, etc)       //para contornar este possível problema teria que colocar um vector<string> para as arestas
                        if (!ArestVisit[pos]){                                                    //só vai entrar se a aresta ainda não foi visitada
                            ArestVisit[pos] = true;                                                        //agora a aresta já foi visitada
                            existe = true;                                                                 //existe aresta pra ser visitada a partir do vértice

                            circ.push_back(g.rotulo_arestas[k][i]);                                      //insere essa aresta no vector
                            k = i;                                                                       //vai pro próximo vértice
                            circ.push_back(g.rotulo_vertices[k]);                                        //insere o vértice atual no vector
                            VertPass.push(k);                                                            //insere na pilha depois de ter recebido a posição do novo vértice

                            if (k == VertOrig && circ.size() >= 5)                            //verifica se fechou circuito, e também precisa que o tamanho do vector que armazena o circuito seja maior que 5 pra evitar de dizer que encontrou circuito ao voltar pro vértice inicial vindo de um vértice que não oferece boas arestas
                                formou = true;
                            break;                                                            //sai do for para parar de procurar outras arestas incidentes no mesmo vértice
                        }
                    }
                }

                if (!existe){                                                     //Se não há nenhuma aresta incidente no vértice atual a disposição volta para o vértice anterior
                    if (VertPass.size() == 1)                           //Se estiver no primeiro vértice do grafo por onde começou a procurar circuito. Serve para sair do while que procura circuito quando percebe que não há mais arestas a serem visitadas no grafo inteiro
                        break;

                    VertPass.pop();                                              //tira a posição do vértice atual da pilha, pois este vértice não oferece arestas adequadas
                    circ.pop_back();                                                 //retira o vértice atual
                    circ.pop_back();                                                 //retira a aresta anterior
                    k = VertPass.top();                                          //faz o k voltar para o vértice anterior
                }
            }
        }

        if (formou)                                  //após ter formado um circuito sair do laço que busca um circuito a partir de cada nodo
            break;
        else                                         //se não formou deixa o vector do circuito vazio
            circ.clear();
    }
    if (!formou)                                                                 //se testou todas as possibilidades de circuitos e ainda assim não formou um circuito, então mostra mensagem
        cout << "\tNão existe um circuito para este grafo\n\n";
    else{
        cout << "\tCircuito: ";
        for (int i=0; i<circ.size(); i++)
            cout << circ[i] << ' ';
        cout << "\n\n";
    }
}

void SeqGraus(grafo g)
{
    stable_sort(g.grau.begin(), g.grau.end());        //ordena este vetor em ordem crescente

    cout << "\n\tSequência de Graus: ";             //mostra o vetor
    for (int i=0; i<g.grau.size(); i++)
        cout << g.grau[i] << ' ';
    cout << "\n\n";
}

void mostra(grafo g,int op){
    switch(op){
        case 0:
            cout << "\tVértices: ";                //só passando pra melhorar a legibilidade
            for(int i=0; i<g.TamVert; i++)
                cout << g.rotulo_vertices[i] << ' ';
            cout << "\n\n";
            break;

        case 1:
            cout << "\nPesos\t|\t";
            for(int i=0; i<g.TamVert; i++)
            cout << g.rotulo_vertices[i] << "\t|\t";
            cout << "\n\t|---------------|---------------|---------------|---------------|---------------|\n";

            for(int i=0; i<g.TamVert; i++){
                cout << g.rotulo_vertices[i] << "\t|\t";
                for(int j=0; j<g.TamVert; j++){
                    if(g.pesos[i][j]==0)
                        cout<<"";
                    else
                        cout << g.pesos[i][j];
                    cout<< "\t|\t";
                }
            cout << endl;
            }
            break;

        case 2:
            cout << "\nArestas\t|\t";
            for(int i=0; i<g.TamVert; i++)
                cout << g.rotulo_vertices[i] << "\t|\t";
            cout << "\n\t|---------------|---------------|---------------|---------------|---------------|\n";
            for(int i=0; i<g.TamVert; i++){
                cout << g.rotulo_vertices[i] << "\t|\t";
                for(int j=0; j<g.TamVert; j++){
                    cout << g.rotulo_arestas[i][j] << "\t|\t";
                }
                cout << endl;
            }
            break;
    }
}

void shutdown(){ //facíl de entender, e o prof n precisa saber dessa função
    int cont=0;
    char op;

    for(int i=0; i<=8; i++){  //perunta repetida 7 vezes
        if(cont == 6)
            cout << "\tMas voce e insistente hein!\n\n";

        if(cont == 7){      //Encerra
            cout << "\tOK, ja pode sair...\n";
            exit(0);
        }
        if(cont >= 0){
            cout << "\tTem certeza ";
            for(int i=0; i<cont; i++){  //Mostra a quantidade de vezes do cont
                cout << "mesmo ";
            }
            cout << "de que quer sair?(S/N): ";
            cin >> op;
            cout << "\n";
        }
        while(toupper(op) != 'S' && toupper(op) != 'N')
            cout << "\tOpcao invalida!\n";

        cont++;
        if(toupper(op) == 'N'){     //se 'N' reinicia a função
            cout << "\tErro! Tente novamente!\n\n";
            cont = i = 0;
        }
    }
}

/*int valor_min(vector<int> key, vector<bool> incluso,int tam){
int min = INT_MAX, min_index;
for (int v = 0; v < tam; v++)
    if (incluso[v] == false && key[v] < min)
        min = key[v], min_index = v;
return min_index;
}

// Função para construir AGM para um grafo representado por uma matriz de adjacencia
void agm(grafo g){
    vector<int> v_agm(g.TamVert);// Vetor para armazenar a AGM construida

    vector<int> key(g.TamVert);// Valor chave usado para pegar o peso minimo
    fill(key.begin(),key.end(),INT_MAX);// Inicializa todas as chaves como infinito

    vector<bool> incluso(g.TamVert);// Representar um conjunto de vertices ainda não inclusos na AGM
    fill(incluso.begin(),incluso.end(),false);

    // Sempre inclui o primeiro vertice na AGM
    // chave 0 para que este vertice seja pego como primeiro vertice
    key[0] = 0;     //ão pergute pq não sei praq serve essa e a linha de baixo mas sem isso o programa crasha
    v_agm[0] =0;

    for (int count = 0; count < g.TamVert-1; count++)
    {
        int u = valor_min(key, incluso,g.rotulo_vertices.size());// Escolhe o vertice com chave minima da lista de vertices ainda não inclusos na AGM

        // Adiciona o vertice escolhido ao conjunto da AGM
        incluso[u] = true;

        // Atualiza o valor chave e o indice pai dos vértices adjacentes do vértice escolhido
        // Considerar apenas vértices ainda não inclusos na AGM
        for (int v = 0; v < g.TamVert; v++)

        // graph[u][v] is non zero only for adjacent vertices of m
        // incluso[v] is false for vertices not yet included in MST
        // Update the key only if graph[u][v] is smaller than key[v]
        if (g.pesos[u][v] && incluso[v] == false && g.pesos[u][v] < key[v])
            v_agm[v] = u, key[v] = g.pesos[u][v];
    }

    int cont=0;
    cout<<"Edge \tWeight\n";
    for (int i = 1; i < g.TamVert; i++){
        cout<<g.rotulo_vertices[v_agm[i]]<<" - "<<g.rotulo_vertices[i]<<"\t"<<g.pesos[i][v_agm[i]]<<"\n";
        cont+=g.pesos[i][v_agm[i]];
    }
    cout<<"Total: "<<cont<<"\n";
}*/

void agm(grafo g){
    string s;
    int u, menor, soma = 0;

    vector<string> vem_de(g.TamVert);       //Cria vetor par armazenar os vertices de origem
    fill(vem_de.begin(),vem_de.end(),"---");    //Iniacila o vetor com ---

    vector<bool> incluso(g.TamVert);        //Cria um vetor para testar se ja foi visitado
    fill(incluso.begin(),incluso.end(),false);  //Inicializa com false

    vector<int> cost(g.TamVert);    //Vetor para guardar os pesos mínimos
    fill(cost.begin(),cost.end(),INT_MAX);  //Inicializa com a capacidade máxima de um int

    cout << "\tVertice inicial: ";  //Lê um vértice inicial
    cin >> s;
    u = buscaVertice(g.rotulo_vertices, s); //Busca o índice do vértice inicial
    if(u == -1){
        cout << "\n\tVertice inexistente!\n\n";
        return;
    }

    incluso[u] = true;  //Marca o vértice inicial como já visitado
    cost[u] = 0;    //Adiciona peso 0 ao vértice de inicio
    for(int cont=0; cont<g.TamVert; cont++){
        if(g.grau[u] > 0){  //Testa se o vertice escolhido possui adjacentes
            for(int i=0; i<g.TamVert; i++){
                if(g.pesos[u][i]>0 && g.pesos[u][i]<cost[i] && incluso[i]==false){  //Encotra os adjacentes e adiciona o peso e o rotulo de origem
                    cost[i] = g.pesos[u][i];
                    vem_de[i] = g.rotulo_vertices[u];
                }
            }
            menor = INT_MAX;    //Menor recebe valor máximo
            for(int j=0; j<cost.size(); j++){   //Procura o maior valor dentre os visitados
                if(cost[j]<menor && incluso[j]==false){
                    menor = cost[j];    //Recebe o menor valor
                    u = j;  //U recebe o indice do menor valor
                }
            }
            incluso[u] = true;  //Vertice de menor valor é marcado como visitado e rercomeça o laço
        }
    }
    cout << "\n\tInicio - Vindo_de - Peso\n";     //Mostra a tabela final
    for(int i=0; i<g.TamVert; i++){
        cout << "\t  " << g.rotulo_vertices[i] << "  |   "
             << vem_de[i] << "\t  |  "
             << cost[i] <<"\n";

        soma += cost[i];
    }
    cout << "\n\tTotal: " << soma << "\n";
}

void adjacencia(grafo g){
    string a1, a2;
    int cont = 0, j=0;

    cout << "\tPrimeiro rótulo de aresta: ";
    cin >> a1;
    cout << "\tSegundo rótulo de aresta: ";
    cin >> a2;

    for(int i=0; i<g.TamVert; i++){
        for(int j=0; j<g.TamVert; j++){
            if(g.rotulo_arestas[i][j] == a1 || g.rotulo_arestas[i][j] == a2){
                cont++;
                if(cont == 2){
                    cout << "\n\tSão adjacentes!\n";
                    return;
                }
            }
        }
        cont = 0;
    }
    cout << "\n\tNão sao adjacentes!\n";
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    grafo g;
    g = leitura(g);

    char op;
    do{
        int num,cont=0, i, j, aux=g.TamVert;
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
                agm(g);
                break;
            case 'M':
                cout << "\n\t(0) Vértices\n\t(1) Pesos\n\t(2) Arestas\n";
                while (cout << "\n\tDeseja ver: " && cin >> num && num!=0 && num!=1 && num!=2)
                    cout << "\tInválido\n";
                mostra(g,num);
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
                circuito(g);
                break;
            case 'S':
                SeqGraus(g);
                break;
            case 'J':
                adjacencia(g);
                break;
            case 'E':
                shutdown();
            default:
                cout << "\n\tEscolha uma opção válida: \n\n\t";
        }
        system("pause");
    }while(true);
}

