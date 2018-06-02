#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// -------------------------------------------------------------------------------- ESTRUTURAS PARA GERENCIAR A LISTA DE PASSAGEIROS
struct Passageiro{
    int cpf;
    char nome[30];
    char endereco[30];
    int telefone;
};

struct Celula_passageiro{
    Passageiro dado;
    Celula_passageiro *prox;
};

struct Lista_passageiro{
    Celula_passageiro *inicio, *fim;
    int tam;
};

void Inicializar(Lista_passageiro *lista){
    lista->inicio = (Celula_passageiro*) malloc(sizeof(Celula_passageiro));
    lista->inicio->prox = NULL;
    lista->fim = lista->inicio;
    lista->tam = 0;
}

bool Vazia(Lista_passageiro *lista){
    return lista->inicio == lista->fim;
}

void Inserir(Lista_passageiro *lista, Passageiro dado){

    Celula_passageiro *temp = (Celula_passageiro*) malloc(sizeof(Celula_passageiro));
    temp->dado = dado;
    temp->prox = NULL;

    lista->fim->prox = temp;
    lista->fim = temp;

    lista->tam++;
}

Passageiro Cadastro_passageiro(Lista_passageiro *lista, int n){
Passageiro aux;

    for(int i=0; i<n; i++){

        cout<<"\nNumero do CPF: ";
        cin>>aux.cpf;

        for(Celula_passageiro *temp=lista->inicio; temp!=NULL; temp=temp->prox){
            if(aux.cpf==temp->dado.cpf){
                cout<<"CPF ja cadastrado, insira outro: ";
                cin>>aux.cpf;
                temp=lista->inicio;
            }
        }

        cin.ignore();
        cout<<"\nNome completo: ";
        gets(aux.nome);

        cout<<"\nEndereco: ";
        gets(aux.endereco);

        cout<<"\nTelefone: ";
        cin>>aux.telefone;

        Inserir(lista, aux);
    }
    return aux;
}

Passageiro Remover(Lista_passageiro *lista, int pos){

    // SE A LISTA NÃO POSSUIR A POSICAO INFORMADA RETORNA -1
    if(pos < 1 || pos > lista->tam)
        cout<<"\nPosicao nao encontrada" ;

    // CRIA UM PONTEIRO PARA A CELULA SENTINELA
    Celula_passageiro *CelAnt = lista->inicio;

    // MOVE O PONTEIRO ATÉ A CELULAR ANTERIOR QUE SERA REMOVIDA
    for(int i=0; i<pos-1; i++) CelAnt=CelAnt->prox;

    // CRIA UM PONTEIRO PARA A CELULA QUE SERA REMOVIDO
    Celula_passageiro *temp = CelAnt->prox;

    // ATUALIZA O PONTEIRO DA LISTA
    CelAnt->prox = temp->prox;

    // ARMAZENA O DADO QUE SERA RETORNADO
    Passageiro dado = temp->dado;
    // LIBERA A MEMORIA DA CELULA REMOVIDA
    free(temp);
    // DIMINUI O TAMANHO DA LISTA
    lista->tam--;

    // RETORNA O DADO QUE ESTA NO INICIO DA LISTA
    return dado;
}

// PROCEDIMENTO PARA IMPRIMIR OS DADOS DA LISTA
// DEVE SER ADAPATADO PARA O TIPO DE DADO UTILIZADO!
void Imprimir_lista(Lista_passageiro *lista){
    printf("\n\tTamanho da Lista: %i\n", lista->tam);
    for(Celula_passageiro *temp = lista->inicio->prox; temp!=NULL; temp=temp->prox){
        printf("CPF: %i ", temp->dado.cpf);
        printf("\nNOME: %s ", temp->dado.nome);
        printf("\nENDERECO: %s ", temp->dado.endereco);
        printf("\nTELEFONE: %i \n\n", temp->dado.telefone);
    }
}

// PROCEDIMENTO PARA RETORNAR O TAMANHO DA LISTA
int Tamanho(Lista_passageiro *lista){
    return lista->tam;
}

// PROCEDIMENTO PARA FINALIZAR A LISTA
void Finalizar(Lista_passageiro *lista){
    // ESVAZIA A LISTA
    while(!Vazia(lista))
        Remover(lista,1);

    // LIBERA MEMORIA DO SENTINELA
    free(lista->inicio);
}

// --------------------------------------------------------------------------------

// -------------------------------------------------------------------------------- ESTRUTURAS PARA GERENCIAR A PILHA DE BAGAGENS
struct Dado_bagagem{
    int cpf;
    int peso;
//  passageiro *tripulante;
};

struct Celula_bagagem{
    Dado_bagagem dado;
    Celula_bagagem *prox;
};

struct Pilha_bagagem{
    Celula_bagagem *topo;
    int tam;
};

void Inicializar_bagagem(Pilha_bagagem *pilha){
    pilha->topo = NULL;
    pilha->tam = 0;
}

bool Vazia(Pilha_bagagem *pilha){
    return pilha->topo==NULL;
}

void Empilhar(Pilha_bagagem *pilha, Dado_bagagem dado){

    Celula_bagagem *temp = (Celula_bagagem*) malloc(sizeof(Celula_bagagem));
    temp->dado = dado;
    temp->prox = pilha->topo;

    pilha->topo = temp;

    pilha->tam++;
}

Dado_bagagem Cadastro_bagagem(Pilha_bagagem *pilha, int n){
Dado_bagagem aux;

    for(int i=0; i<n; i++){
        cout<<"CPF do portador da bagagem: ";
        cin>>aux.cpf;
        /*
            for(Celula_bagagem *temp=pilha->topo; temp!=NULL; temp=temp->prox){
                if()

            }
        */
        cout<<"\nPeso da bagagem: ";
        cin>>aux.peso;
        Empilhar(pilha, aux);
    }

}

Dado_bagagem Desempilhar(Pilha_bagagem *pilha){

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

void Imprimir(Pilha_bagagem *pilha){
    printf("\n\tTamanho da Pilha: %i\n", pilha->tam);
    for(Celula_bagagem *temp = pilha->topo; temp!=NULL; temp=temp->prox){
        cout<<"\nCPF passageiro: "<<temp->dado.cpf;
        cout<<"\nPeso bagagem: "<<temp->dado.peso;
        cout<<endl;
    }
}

// PROCEDIMENTO PARA FINALIZAR A PILHA
void Finalizar(Pilha_bagagem *pilha){
    // ESVAZIA A PILHA
    while(!Vazia(pilha))
        Desempilhar(pilha);
}

// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------

struct Aviao{
    int id;
    bool poltrona[10];
    int destino_id;
};

struct Celula_aviao{
    Aviao dado;
    Celula_aviao * aterior, * prox;
};

struct Lista_aviao{
    Celula_aviao * inicio, * fim;
    int tam;
};

void Inicializar_aviao(Lista_aviao * lista){
    lista->inicio = (Celula_aviao*) malloc(sizeof(Celula_aviao));
    lista->inicio->prox = NULL;
    lista->fim = lista->inicio;
    lista->tam = 0;
}

bool Vazia(Lista_aviao * lista){
    for(int i = 0; i < 10; i++){
        lista->inicio->dado.poltrona[i] = false;
    }
    return lista->tam == 0;
}

void Inserir_aviao(Lista_aviao * lista, Aviao dado){
    Celula_aviao *temp = (Celula_aviao*) malloc(sizeof(Celula_aviao));
    temp->dado = dado;
    temp->prox = NULL;
    for(int i = 0; i < 10; i++){
        temp->dado.poltrona[i] = false;
    }
    lista->fim->prox = temp;
    lista->fim = temp;
    lista->tam++;
}

void Imprimir_lista_aviao(Lista_aviao *lista){
    printf("\n\tTamanho da Lista: %i\n", lista->tam);
    for(Celula_aviao *temp = lista->inicio->prox; temp!=NULL; temp=temp->prox){
        printf("ID: %i \n", temp->dado.id);
        for(int i = 0; i < 10; i++){
            printf("Poltrona %i: %s \n", i, temp->dado.poltrona[i] ? "Ocupado":"Livre");
        }
    }
}

struct voo{
    int id;
    int aviao_id;
    string destino;
};

int main(){

    voo voos[3];
    Aviao avioes[3];

    avioes[0].id = 0;
    avioes[1].id = 1;
    avioes[2].id = 2;

    voos[0].destino = "BH -> SÃO PAULO";
    voos[1].destino = "BH -> RIO";
    voos[2].destino = "BH -> SALVADOR";

    voos[0].id = 0;
    voos[1].id = 1;
    voos[2].id = 2;

    Lista_passageiro *tripulantes=(Lista_passageiro*) malloc (sizeof(Lista_passageiro));
    Pilha_bagagem *bagagem=(Pilha_bagagem*) malloc (sizeof(Pilha_bagagem));
    Inicializar_bagagem(bagagem);
    Inicializar(tripulantes);

    Lista_aviao * l_avioes = (Lista_aviao *) malloc(sizeof(Lista_aviao));
    Inicializar_aviao(l_avioes);
    Imprimir_lista_aviao(l_avioes);
    Inserir_aviao(l_avioes, avioes[0]);
    Imprimir_lista_aviao(l_avioes);

/*
    Dado_bagagem a={1234, 64};
    Dado_bagagem b={1236, 87};

    Empilhar(bagagem, a);
    Empilhar(bagagem, b);

    Imprimir(bagagem);
*/

/*
    Passageiro c={136237, "davi goncalves", "rua", 938003};
    Passageiro d={136245, "fernando goncalves", "rua jair", 938233};
    Inserir(tripulantes, c);
    Inserir(tripulantes, d);
    Cadastro_passageiro(tripulantes, 2);

    Imprimir_lista(tripulantes);
*/
    free(bagagem);
    free(tripulantes);

    return 0;
}
