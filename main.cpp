#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

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
    Celula_passageiro *prox, *anterior;
};

struct Lista_passageiro{
    Celula_passageiro *inicio, *fim;
    int tam;
};

void Inicializar_passageiro(Lista_passageiro *lista){
    lista->inicio = (Celula_passageiro*) malloc(sizeof(Celula_passageiro));
    lista->inicio->prox = NULL;
    lista->inicio->anterior = NULL;
    lista->fim = lista->inicio;
    lista->tam = 0;
}

bool Vazia_passageiro(Lista_passageiro *lista){
    return lista->inicio == lista->fim;
}

void Inserir_lista_passageiro(Lista_passageiro *lista, Passageiro dado){

    Celula_passageiro *temp = (Celula_passageiro*) malloc(sizeof(Celula_passageiro));

    temp->dado = dado;
    temp->prox = NULL;
    temp->anterior = lista->fim;

    lista->fim->prox = temp;
    lista->fim = temp;

    lista->tam++;
}

void Gravar_arquivos_passageiros (FILE *arq, Passageiro dado){
arq= fopen("dados_passageiros.txt", "a+");
    if (arq == NULL) {
        cout<<"\n\tErro na Leitura/Gravacao do arquivo!";
    }else{
        fprintf(arq, "%i\t%s\t%s\t%i\n", dado.cpf, dado.nome, dado.endereco, dado.telefone);
    }
}

Passageiro Cadastro_passageiro(FILE *arq, Lista_passageiro *lista, int n){
Passageiro aux;

    for(int i=0; i<n; i++){

        cout<<"\tPassageiro :"<<i+1;
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

        Inserir_lista_passageiro(lista, aux);
        Gravar_arquivos_passageiros(arq, aux);
        cout<<endl;
    }
    return aux;
}

void OpenFile_passageiros(Lista_passageiro *lista){
Celula_passageiro *aux = (Celula_passageiro*) malloc (sizeof(Celula_passageiro));
    if(aux == NULL){
        cout<<"\n\tNao ha memoria disponivel!";
    } else {
        FILE *arq=fopen("dados_passageiros.txt", "r");
        if(arq){
            cout<<"\tLendo arquivo de passageiros...\n";
            while(!feof(arq)){
                if(!feof(arq)){
                    fscanf(arq, "%i\t%[^\t]\t%[^\t]\t%i\n", &aux->dado.cpf, &aux->dado.nome, &aux->dado.endereco, &aux->dado.telefone);
                    //printf("%i\t%s\t%s\t%i\n", aux->dado.cpf, aux->dado.nome, aux->dado.endereco, aux->dado.telefone);
                    Inserir_lista_passageiro(lista, aux->dado);
                }
            }
        }
    }
free(aux);
}

Passageiro Remover_passageiro(Lista_passageiro *lista, int pos){

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

Passageiro pesquisaPassageiro( Lista_passageiro * l,int cpf){
    Celula_passageiro * aux;

    aux = l->inicio->prox;

    while(aux != NULL){
        if(aux->dado.cpf == cpf){
            printf("\nNUMERO DO CPF: %i", aux->dado.cpf);
            printf("\nNOME COMPLETO: %s", aux->dado.nome);
            printf("\nENDEREÇO: %s", aux->dado.endereco);
            printf("\nTELEFONE: %i", aux->dado.telefone);
            cout<<endl;
            return aux->dado;
        } else {
            aux = aux->prox;
        }
    }
}

void Imprimir_lista_passageiros(Lista_passageiro *lista){
    printf("\n\tTamanho da lista de passageiros: %i\n", lista->tam);
    for(Celula_passageiro *temp = lista->inicio->prox; temp!=NULL; temp=temp->prox){
        printf("CPF: %i ", temp->dado.cpf);
        printf("\nNOME: %s ", temp->dado.nome);
        printf("\nENDERECO: %s ", temp->dado.endereco);
        printf("\nTELEFONE: %i \n\n", temp->dado.telefone);
    }
}

int Tamanho_lista_passageiro(Lista_passageiro *lista){
    return lista->tam;
}

void Finalizar(Lista_passageiro *lista){
    while(!Vazia_passageiro(lista))
        Remover_passageiro(lista,1);
        free(lista->inicio);
}

// --------------------------------------------------------------------------------

// -------------------------------------------------------------------------------- ESTRUTURAS PARA GERENCIAR A PILHA DE BAGAGENS
struct Bagagem{
    int cpf;
    int peso;
//  passageiro *tripulante;
};

struct Celula_bagagem{
    Bagagem dado;
    Celula_bagagem *prox;
};

struct Lista_bagagem{
    Celula_bagagem *inicio, *fim;
    int tam;
};

void Inicializar_bagagem(Lista_bagagem *lista){
    lista->inicio = (Celula_bagagem*) malloc(sizeof(Celula_bagagem));
    lista->inicio->prox = NULL;
    lista->fim = lista->inicio;
    lista->tam = 0;
}

bool Vazia_bagagem(Lista_bagagem *lista){
    return lista->inicio==lista->fim;
}

void Inserir_lista_bagagem(Lista_bagagem *lista, Bagagem dado){

    Celula_bagagem *temp = (Celula_bagagem*) malloc(sizeof(Celula_bagagem));
    temp->dado = dado;
    temp->prox = NULL;

    lista->fim->prox = temp;
    lista->fim = temp;

    lista->tam++;
}

void Gravar_arquivos_bagagem (FILE *arq, Bagagem dado){
arq= fopen("dados_bagagens.txt", "a+");
    if (arq == NULL) {
        cout<<"\n\tErro na Leitura/Gravacao do arquivo!";
    }else{
        fprintf(arq, "%i\t%i\n", dado.cpf,dado.peso);
    }
}

Bagagem Cadastro_bagagem(FILE *arq, Lista_bagagem *lista, int n){
Bagagem aux;

    for(int i=0; i<n; i++){
    cout<<"\tCadastro de bagagem: "<<i+1;
        cout<<"\nCPF do portador da bagagem: ";
        cin>>aux.cpf;

        cout<<"Peso da bagagem: ";
        cin>>aux.peso;

        Inserir_lista_bagagem(lista, aux);
        Gravar_arquivos_bagagem(arq, aux);
        cout<<endl;
    }

}

void OpenFile_bagagens(Lista_bagagem *lista){
Celula_bagagem *aux = (Celula_bagagem*) malloc (sizeof(Celula_bagagem));
    if(aux == NULL){
        cout<<"\n\tNao ha memoria disponivel!";
    } else {
        FILE *arq=fopen("dados_bagagens.txt", "r");
        if(arq){
            cout<<"\tLendo arquivo de bagagens...\n";
            while(!feof(arq)){
                if(!feof(arq)){
                    fscanf(arq, "%i\t%i\n", &aux->dado.cpf, &aux->dado.peso);
                    //printf("%i\t%i\n", aux->dado.cpf, aux->dado.peso);
                    Inserir_lista_bagagem(lista, aux->dado);
                }
            }
        }
    }
free(aux);
}

Bagagem Remover_bagagem(Lista_bagagem *lista, int pos){

    // SE A LISTA NÃO POSSUIR A POSICAO INFORMADA RETORNA -1
    if(pos < 1 || pos > lista->tam)
        cout<<"\nPosicao nao encontrada" ;

    // CRIA UM PONTEIRO PARA A CELULA SENTINELA
    Celula_bagagem *CelAnt = lista->inicio;

    // MOVE O PONTEIRO ATÉ A CELULAR ANTERIOR QUE SERA REMOVIDA
    for(int i=0; i<pos-1; i++) CelAnt=CelAnt->prox;

    // CRIA UM PONTEIRO PARA A CELULA QUE SERA REMOVIDO
    Celula_bagagem *temp = CelAnt->prox;

    // ATUALIZA O PONTEIRO DA LISTA
    CelAnt->prox = temp->prox;

    // ARMAZENA O DADO QUE SERA RETORNADO
    Bagagem dado = temp->dado;
    // LIBERA A MEMORIA DA CELULA REMOVIDA
    free(temp);
    // DIMINUI O TAMANHO DA LISTA
    lista->tam--;

    // RETORNA O DADO QUE ESTA NO INICIO DA LISTA
    return dado;
}

void Imprimir_lista_bagagem(Lista_bagagem *lista){
    printf("\n\tTamanho da lista de bagagem: %i\n", lista->tam);
    for(Celula_bagagem *temp = lista->inicio->prox; temp!=NULL; temp=temp->prox){
        cout<<"\nCPF passageiro: "<<temp->dado.cpf;
        cout<<"\nPeso bagagem: "<<temp->dado.peso;
        cout<<endl;
    }
}

int Tamanho_lista_bagagem(Lista_bagagem *lista){
    return lista->tam;
}

void Finalizar_lista_bagagem(Lista_bagagem *lista){
    while(!Vazia_bagagem(lista))
        Remover_bagagem(lista, 1);
        free(lista->inicio);
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
    lista->inicio->aterior = NULL;
    lista->fim->aterior = lista->inicio;
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
    if(temp == NULL){
        return ;
    }
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

struct celula_voo{
    voo dado;
    celula_voo * prox, * anterior;
};

struct Lista_de_voos{
    celula_voo * primeiro, * ultimo;
    int tam;
};

struct passagens{
    int passagem_id;
    int voo_id;
    int passageiro_id;
    int poltrona_id;
};

bool disponibilida_de_destino(int destino_id, Lista_de_voos * voos){
    celula_voo * aux = (celula_voo*)malloc(sizeof(celula_voo));
    aux = voos->primeiro->prox;
    while(aux != NULL){
        if(aux->dado.id == destino_id){
            return true;
        } else{
            aux = aux->prox;
        }
    }
    return false;
}

bool disponibilidade_de_poltrona(int id, Lista_de_voos * voos){

}

void compra_de_passagem(int cpf, int destino_id, Lista_passageiro * l, Lista_de_voos * voos){
    pesquisaPassageiro(l, cpf);
    if(disponibilida_de_destino(destino_id, voos)){
        if(disponibilidade_de_poltrona(destino_id, voos)){

        }
    }
}

int main(){
    setlocale(LC_ALL,"portuguese");
<<<<<<< HEAD
    FILE *arq_passageiro;
=======

>>>>>>> 1673774f3b3793465bfa2067735311ca423bf897
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

<<<<<<< HEAD
    avioes[0].destino_id = 0;
    avioes[1].destino_id = 1;
    avioes[2].destino_id = 2;

    voos[0].aviao_id = 0;
    voos[1].aviao_id = 1;
    voos[2].aviao_id = 2;

    Lista_aviao * av = (Lista_aviao*) malloc (sizeof(Lista_aviao));
    Inicializar_aviao(av);

    Lista_passageiro *tripulantes = (Lista_passageiro*) malloc (sizeof(Lista_passageiro));
    Inicializar(tripulantes);
    OpenFile_passageiros(tripulantes);
    Pilha_bagagem *bagagem=(Pilha_bagagem*) malloc (sizeof(Pilha_bagagem));
    Inicializar_bagagem(bagagem);
=======
    Lista_passageiro *tripulantes=(Lista_passageiro*) malloc (sizeof(Lista_passageiro));
    Inicializar_passageiro(tripulantes);
    FILE *arq_passageiro;
    OpenFile_passageiros(tripulantes);

    Lista_bagagem *bagagem=(Lista_bagagem*) malloc (sizeof(Lista_bagagem));
    Inicializar_bagagem(bagagem);
    FILE *arq_bagagem;
    OpenFile_bagagens(bagagem);


>>>>>>> 1673774f3b3793465bfa2067735311ca423bf897
    Lista_aviao * l_avioes = (Lista_aviao *) malloc(sizeof(Lista_aviao));
    Inicializar_aviao(l_avioes);
    Imprimir_lista_aviao(l_avioes);
    Inserir_aviao(l_avioes, avioes[0]);
    Imprimir_lista_aviao(l_avioes);

<<<<<<< HEAD
    Dado_bagagem a={1234, 64};
    Dado_bagagem b={1236, 87};

    Empilhar(bagagem, a);
    Empilhar(bagagem, b);
    Imprimir(bagagem);

    //Cadastro_passageiro(arq_passageiro, tripulantes, 2);

    Imprimir_lista(tripulantes);
=======

    //Cadastro_bagagem(arq_bagagem, bagagem, 2);
    Imprimir_lista_bagagem(bagagem);

    //Cadastro_passageiro(arq_passageiro, tripulantes, 1);
    Imprimir_lista_passageiros(tripulantes);

>>>>>>> 1673774f3b3793465bfa2067735311ca423bf897
    pesquisaPassageiro(tripulantes, 123);


    free(bagagem);
    free(tripulantes);
    free(l_avioes);
    return 0;
}
