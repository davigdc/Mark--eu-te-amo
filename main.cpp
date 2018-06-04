#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

using namespace std;


// -------------------------------------------------------------------------------- ESTRUTURAS PARA GERENCIAR A LISTA DE PASSAGEIROS
struct Passageiro{
    int64_t cpf;
    char nome[30];
    char endereco[30];
    int64_t telefone;
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
        fprintf(arq, "%lld\t%s\t%s\t%lld\n", dado.cpf, dado.nome, dado.endereco, dado.telefone);
    }
}

Passageiro Cadastro_passageiro(FILE *arq, Lista_passageiro *lista){
Passageiro aux;

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

bool pesquisaPassageiro( Lista_passageiro * l,int cpf){
    Celula_passageiro * aux;

    aux = l->inicio->prox;

    while(aux != NULL){
        if(aux->dado.cpf == cpf){
            printf("\nNUMERO DO CPF: %i", aux->dado.cpf);
            printf("\nNOME COMPLETO: %s", aux->dado.nome);
            printf("\nENDEREÇO: %s", aux->dado.endereco);
            printf("\nTELEFONE: %i", aux->dado.telefone);
            cout<<endl;
            return true;
        } else {
            aux = aux->prox;
        }
    }
    cout << "CPF não cadastrado no sistema";
    return false;
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

// -------------------------------------------------------------------------------- ESTRUTURAS PARA GERENCIAR A LISTA DE BAGAGENS
struct Bagagem{
    int64_t cpf;
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
        fprintf(arq, "%lld\t%i\n", dado.cpf,dado.peso);
    }
}

Bagagem Cadastro_bagagem(FILE *arq, Lista_bagagem *lista){
Bagagem aux;
        cout<<"\nCPF do portador da bagagem: ";
        cin>>aux.cpf;

        cout<<"Peso da bagagem: ";
        cin>>aux.peso;

        Inserir_lista_bagagem(lista, aux);
        Gravar_arquivos_bagagem(arq, aux);
        cout<<endl;
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

// -------------------------------------------------------------------------------- ESTRUTURAS PARA GERENCIAR A LISTA DE AVIOES

struct Aviao{
    char destino_id[20];
    int id;
    bool poltrona[10];
    //int destino_id;
};

struct Celula_aviao{
    Aviao dado;
    Celula_aviao * prox;
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

bool Vazia_lista_aviao(Lista_aviao * lista){
    for(int i = 0; i < 10; i++){
        lista->inicio->dado.poltrona[i] = false;
    }
    return lista->tam == 0;
}

void Inserir_lista_aviao(Lista_aviao * lista, Aviao dado){
    Celula_aviao *aux = (Celula_aviao*) malloc(sizeof(Celula_aviao));

    aux->dado = dado;
    aux->prox = NULL;

    lista->fim->prox = aux;
    lista->fim = aux;
    lista->tam++;
}

void Gravar_arquivos_aviao (FILE *arq, Aviao dado){
arq= fopen("dados_aviao.txt", "a+");
    if (arq == NULL) {
        cout<<"\n\tErro na Leitura/Gravacao do arquivo!";
    }else{
        fprintf(arq, "%s\t%i\t%i %i %i %i %i %i %i %i %i %i\n",
                dado.destino_id, dado.id, dado.poltrona[0], dado.poltrona[1], dado.poltrona[2], dado.poltrona[3], dado.poltrona[4],
                dado.poltrona[5], dado.poltrona[6], dado.poltrona[7], dado.poltrona[8], dado.poltrona[9]);
    }
}

void OpenFile_aviao(Lista_aviao *lista){
Celula_aviao *aux = (Celula_aviao*) malloc (sizeof(Celula_aviao));
    if(aux == NULL){
        cout<<"\n\tNao ha memoria disponivel!";
    } else {
        FILE *arq=fopen("dados_aviao.txt", "r");
        if(arq){
            cout<<"\tLendo arquivo de Avioes...\n";
            while(!feof(arq)){
                if(!feof(arq)){
                    fscanf(arq, "%[^\t]\t%i\t%i %i %i %i %i %i %i %i %i %i\n",
                           &aux->dado.destino_id, &aux->dado.id, &aux->dado.poltrona[0], &aux->dado.poltrona[1], &aux->dado.poltrona[2], &aux->dado.poltrona[3], &aux->dado.poltrona[4],
                           &aux->dado.poltrona[5], &aux->dado.poltrona[6], &aux->dado.poltrona[7], &aux->dado.poltrona[8], &aux->dado.poltrona[9]);

                    Inserir_lista_aviao(lista, aux->dado);
/*
                    printf("%s\t%i\t %i %i %i %i %i %i %i %i %i\n",
                            aux->dado.destino_id, aux->dado.id, aux->dado.poltrona[0], aux->dado.poltrona[1], aux->dado.poltrona[2], aux->dado.poltrona[3], aux->dado.poltrona[4],
                            aux->dado.poltrona[5], aux->dado.poltrona[6], aux->dado.poltrona[7], aux->dado.poltrona[8], aux->dado.poltrona[9]);
*/
                }
            }
        }
    }
free(aux);
}

void Imprimir_lista_aviao(Lista_aviao *lista){
    printf("\n\tTamanho da Lista: %i\n", lista->tam);
    for(Celula_aviao *temp = lista->inicio->prox; temp!=NULL; temp=temp->prox){
        printf("Saida, destino: %s\n", temp->dado.destino_id);
        printf("ID: %i \n", temp->dado.id);
        for(int i = 0; i < 10; i++){
            printf("Poltrona %i: %s \n", i, temp->dado.poltrona[i] ? "Ocupado":"Livre");
        }

    }
}

bool pesquisa_aviao(Lista_aviao *lista, int voo_id){

    for(Celula_aviao *temp = lista->inicio->prox; temp!=NULL; temp=temp->prox){
        if(temp->dado.id == voo_id){
            printf("Saida, destino: %s\n", temp->dado.destino_id);
            printf("ID: %i \n", temp->dado.id);
            for(int i = 0; i < 10; i++){
                printf("Poltrona %i: %s \n", i, temp->dado.poltrona[i] ? "Ocupado":"Livre");
            }
        }
    }
}

// --------------------------------------------------------------------------------

// -------------------------------------------------------------------------------- ESTRUTURAS PARA GERENCIAR A LISTA DE PASSAGENS

struct passagens{
    int passagem_id;
    int voo_id;
    int passageiro_id;
    int poltrona_id;
};

struct Celula_passagem{
    passagens dado;
    Celula_passagem * prox;
};

struct Lista_passagem{
    Celula_passagem * inicio, * fim;
    int tam;
};

void Inicializar_passagem(Lista_passagem * lista){
    lista->inicio = (Celula_passagem*) malloc(sizeof(Celula_passagem));
    lista->inicio->prox = NULL;
    lista->fim = lista->inicio;
    lista->tam = 0;

}

void Gravar_arquivos_passagem (FILE *arq, passagens dado){
arq= fopen("dados_passagem.txt", "a+");
    if (arq == NULL) {
        cout<<"\n\tErro na Leitura/Gravacao do arquivo!";
    }else{
        fprintf(arq, "%i\t%i\t%i\t%i\n", dado.passageiro_id, dado.passagem_id, dado.poltrona_id, dado.voo_id);
    }
}

void OpenFile_passagem(Lista_passagem *lista){
Celula_passagem *aux = (Celula_passagem*) malloc (sizeof(Celula_passagem));

    if(aux == NULL){
        cout<<"\n\tNao ha memoria disponivel!";
    } else {
        FILE *arq=fopen("dados_passagem.txt", "r");
        if(arq){
            cout<<"\tLendo arquivo de passagens...\n";
            while(!feof(arq)){
                if(!feof(arq)){
                    fscanf(arq, "%i\t%i\t%i\t%i\n",
                           &aux->dado.passageiro_id, &aux->dado.passagem_id, &aux->dado.poltrona_id, &aux->dado.voo_id);

                    //Inserir_lista_passagem(lista, aux->dado);
/*
                    printf("%i\t%i\t%i\t%i\n",
                           aux->dado.passageiro_id, aux->dado.passagem_id, aux->dado.poltrona_id, aux->dado.voo_id);
*/
                }
            }
        }
    }
}

// --------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- ESTRUTURAS LISTA DE ESPERA

struct Lista_espera{
    Celula_passageiro *inicio, *fim;
    int tam;
};

void Inicializar_espera(Lista_espera *lista){
    lista->inicio = (Celula_passageiro*) malloc(sizeof(Celula_passageiro));
    lista->inicio->prox = NULL;
    lista->inicio->anterior = NULL;
    lista->fim = lista->inicio;
    lista->tam = 0;
}

bool Vazia_espera(Lista_espera *lista){
    return lista->inicio == lista->fim;
}

void Inserir_lista_espera(Lista_espera *lista, Passageiro dado){

    Celula_passageiro *temp = (Celula_passageiro*) malloc(sizeof(Celula_passageiro));

    temp->dado = dado;
    temp->prox = NULL;
    temp->anterior = lista->fim;

    lista->fim->prox = temp;
    lista->fim = temp;

    lista->tam++;
}

void Gravar_arquivos_espera (FILE *arq, Passageiro dado){
arq= fopen("dados_lista_espera.txt", "a+");
    if (arq == NULL) {
        cout<<"\n\tErro na Leitura/Gravacao do arquivo!";
    }else{
        fprintf(arq, "%lld\t%s\t%s\t%lld\n", dado.cpf, dado.nome, dado.endereco, dado.telefone);
    }
}

void OpenFile_espera(Lista_espera *lista){
Celula_passageiro *aux = (Celula_passageiro*) malloc (sizeof(Celula_passageiro));
    if(aux == NULL){
        cout<<"\n\tNao ha memoria disponivel!";
    } else {
        FILE *arq=fopen("dados_lista_espera.txt", "r");
        if(arq){
            cout<<"\tLendo arquivo de passageiros...\n";
            while(!feof(arq)){
                if(!feof(arq)){
                    fscanf(arq, "%i\t%[^\t]\t%[^\t]\t%i\n", &aux->dado.cpf, &aux->dado.nome, &aux->dado.endereco, &aux->dado.telefone);
                    //printf("%i\t%s\t%s\t%i\n", aux->dado.cpf, aux->dado.nome, aux->dado.endereco, aux->dado.telefone);
                    Inserir_lista_espera(lista, aux->dado);
                }
            }
        }
    }
free(aux);
}

Passageiro Remover_lista_espera(Lista_espera *lista, int pos){

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

Passageiro Pesquisa_lista_espera(Lista_espera * l,int cpf){
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

void Imprimir_lista_espera(Lista_espera *lista){
    printf("\n\tTamanho da lista de espera: %i\n", lista->tam);
    for(Celula_passageiro *temp = lista->inicio->prox; temp!=NULL; temp=temp->prox){
        printf("CPF: %i ", temp->dado.cpf);
        printf("\nNOME: %s ", temp->dado.nome);
        printf("\nENDERECO: %s ", temp->dado.endereco);
        printf("\nTELEFONE: %i \n\n", temp->dado.telefone);
    }
}

int Tamanho_lista_espera(Lista_espera *lista){
    return lista->tam;
}

void Finalizar_lista_espera(Lista_espera *lista){
    while(!Vazia_espera(lista))
        Remover_lista_espera(lista,1);
        free(lista->inicio);
}

// -------------------------------------------------------------------------------- FUNCOES DE CADASTRO OU PESQUISA

void Cadastro_passageiro_com_bagagem(FILE *arq, Lista_passageiro *lista, FILE *arq2, Lista_bagagem *lista2){
Passageiro aux;
int bag=0;
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

    cout<<"\nDeseja despachar bagagem? [1] Sim [2] Nao";
            do{
                cin>>bag;
                if(((bag < 1) || (bag > 2)))
                    cout<<"Opcao invalida, digite novamente...";
            }while((bag < 1) || (bag > 2));

    if(bag==1){
        Bagagem aux2;
        cout<<"\nCPF do portador da bagagem: "<<aux.cpf;
        aux2.cpf=aux.cpf;

        cout<<"\nPeso da bagagem (Kg): ";
        cin>>aux2.peso;

        Inserir_lista_bagagem(lista2, aux2);
        Gravar_arquivos_bagagem(arq2, aux2);
        cout<<endl;
    }
}
/*
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
*/

// --------------------------------------------------------------------------------

int main(){
setlocale(LC_ALL,"portuguese");

Lista_passageiro *tripulantes=(Lista_passageiro*) malloc (sizeof(Lista_passageiro));
Inicializar_passageiro(tripulantes);
FILE *arq_passageiro;
OpenFile_passageiros(tripulantes);

Lista_bagagem *bagagem=(Lista_bagagem*) malloc (sizeof(Lista_bagagem));
Inicializar_bagagem(bagagem);
FILE *arq_bagagem;
OpenFile_bagagens(bagagem);

Lista_aviao * l_avioes = (Lista_aviao *) malloc(sizeof(Lista_aviao));
Inicializar_aviao(l_avioes);
FILE *arq_aviao;
OpenFile_aviao(l_avioes);


Lista_passagem * l_passagem = (Lista_passagem *) malloc(sizeof(Lista_passagem));
Inicializar_passagem(l_passagem);
FILE *arq_passagem;
//OpenFile_passagem(l_passagem);

Lista_espera *espera =(Lista_espera*) malloc (sizeof(Lista_espera));
Inicializar_espera(espera);
FILE *arq_espera;
OpenFile_espera(espera);

if(Vazia_lista_aviao(l_avioes)){
    Aviao avioes[3];

    sprintf(avioes[0].destino_id,"BH -> SAO PAULO");
    sprintf(avioes[1].destino_id,"BH -> RIO");
    sprintf(avioes[2].destino_id,"BH -> SALVADOR");

    avioes[0].id = 0;
    avioes[1].id = 1;
    avioes[2].id = 2;

    for(int i = 0; i < 10; i++){
        avioes[0].poltrona[i] = 0;
    }
    for(int i = 0; i < 10; i++){
        avioes[1].poltrona[i] = 0;
    }
    for(int i = 0; i < 10; i++){
        avioes[2].poltrona[i] = 0;
    }

    for(int i=0; i<3; i++){
        Inserir_lista_aviao(l_avioes, avioes[i]);
        Gravar_arquivos_aviao(arq_aviao, avioes[i]);
    }
}

    //--------  MENU
int menu, adc_p=0, cpf=0, voo_id=0;

do{
printf("\t----> Opcoes disponiveis: <----\n[1]-> Cadastrar passageiro;\n[2]-> Pesquisa todos passageiros de um voo;\n[3]-> Pesquisa passageiro em um voo;\n[4]-> Listas de espera;\n[5]-> Remover passageiro;\n[6]-> Bagagens (Despache, embarque e entrega);\n[7]-> Sair; \nEntrada: ");
cin>>menu;
if(menu==7){
    break;
}
if(menu < 1 || menu > 6){
    cout<<"\t\tOpcao invalida, digite novamente...\n";
}

    switch(menu){

    case 1:

        do{
        cout<<"\n\tCadastro passageiro:";
            Cadastro_passageiro_com_bagagem(arq_passageiro, tripulantes, arq_bagagem, bagagem);
            //Linkar passagem
            //Limkar Voo
            cout<<"\nCadastrar mais um passageiro: [1] Sim; [2] Nao. ";
            do{
                cin>>adc_p;
                if(((adc_p < 1) || (adc_p > 2))){
                    cout<<"Opçao invalida, digite novamente...";
                }
            }while((adc_p < 1) || (adc_p > 2));
        }while(adc_p!=2);

    break;

    case 2:
        cout<<"\nop 2\n [2]-> Pesquisa todos passageiros de um voo\n";
        cout<<"Numero do voo: ";
        cin >> voo_id;
        if(pesquisa_aviao(l_avioes, voo_id)){
            for(Celula_passagem * p = l_passagem->inicio->prox; p != NULL; p = p->prox){
                if(p->dado.voo_id == voo_id){
                    pesquisaPassageiro(tripulantes, p->dado.passageiro_id);
                }
            }
        }


    break;

    case 3:
        cout<<"\nop 3\n";
        cout<<"[3]-> Pesquisa passageiro em um voo\n";
        cin >> cpf;
        for(Celula_aviao * av = l_avioes->inicio->prox; av != NULL; av = av->prox){
            if(av->dado.id == voo_id){
                for(Celula_passagem * p = l_passagem->inicio->prox; p != NULL; p = p->prox){
                    if(p->dado.voo_id == av->dado.id){
                        pesquisaPassageiro(tripulantes, p->dado.passageiro_id);
                    }
                }
            }
        }

    break;

    case 4:
        cout<<"\nop 4\n";
        cout <<"[4]-> Listas de espera\n";
        Imprimir_lista_espera(espera);

    break;

    case 5:
        cpf = -1;
        cout<<"\nop 5\n";
        cout<< "[5]-> Remover passageiro\n";
        cout << "Digite o CPF";
        cin >> cpf;
        Remover_passageiro(tripulantes, cpf);

    break;

    case 6:
        voo_id = -1;
        cout<<"\nop 6\n";
        cout<<"[6]-> Bagagens (Despache, embarque e entrega)\n";
        cout<<"Numero do voo";
        cin >> voo_id;
        Imprimir_lista_bagagem(bagagem);

    break;

    }

}while(menu!=7);

    free(bagagem);
    free(tripulantes);
    free(l_avioes);
    free(espera);

return 0;
}
