#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
// -------------------------------------------------------------------------------- ESTRUTURAS PARA GERENCIAR A PILHA DE BAGAGENS
struct Dado_bagagem{
    int cpf;
    int peso;
//    passageiro *tripulante;
};

struct Celula_bagagem{
    Dado_bagagem dado;
    Celula_bagagem *prox;
};

struct Pilha{
    Celula_bagagem *topo;
    int tam;
};

void Inicializar_bagagem(Pilha *pilha){
    pilha->topo = NULL;
    pilha->tam = 0;
}

bool Vazia(Pilha *pilha){
    return pilha->topo==NULL;
}

void Empilhar(Pilha *pilha, Dado_bagagem dado){

bool valido=true;

    for(Celula_bagagem *temp = pilha->topo; temp!=NULL; temp=temp->prox){
        if(temp->dado.cpf==dado.cpf){
            cout<<"\tCPF cadastrado ja possui bagagem cadastrada!";
            valido=false;
        }
    }

    if(valido){

        Celula_bagagem *temp = (Celula_bagagem*) malloc(sizeof(Celula_bagagem));
        temp->dado = dado;
        temp->prox = pilha->topo;

        pilha->topo = temp;

        pilha->tam++;

    }
}

Dado_bagagem Desempilhar(Pilha *pilha){

    if(Vazia(pilha)){
        cout<<"\nPilha vazia!";
    }else{

    Dado_bagagem dado = pilha->topo->dado;
    Celula_bagagem *temp = pilha->topo;
    pilha->topo = pilha->topo->prox;
    free(temp);
    pilha->tam--;

    return dado;}
}

void Imprimir(Pilha *pilha){
    printf("\n\tTamanho da Pilha: %i\n", pilha->tam);
    for(Celula_bagagem *temp = pilha->topo; temp!=NULL; temp=temp->prox){
        cout<<"\nCPF passageiro: "<<temp->dado.cpf;
        cout<<"\nPeso bagagem: "<<temp->dado.peso;
        cout<<endl;
    }
}

// PROCEDIMENTO PARA FINALIZAR A PILHA
void Finalizar(Pilha *pilha){
    // ESVAZIA A PILHA
    while(!Vazia(pilha))
        Desempilhar(pilha);
}

// --------------------------------------------------------------------------------

struct passageiro{
    string nome;
    int cpf;
    string endereco;
    int telefone;
};

struct aviao{
    int id;
    int poltrona;
};

using namespace std;

int main()
{
    Pilha *bagagem=(Pilha*) malloc (sizeof(Pilha));
    Inicializar_bagagem(bagagem);
    Dado_bagagem a={13623, 64};
    Dado_bagagem b={31502, 87};
    Dado_bagagem c={13623, 90};

    Empilhar(bagagem, a);
    Empilhar(bagagem, b);
    Empilhar(bagagem, c);

    Imprimir(bagagem);

    free(bagagem);


    return 0;
}
