#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <process.h>
#include <string.h>
#include <conio.c>
#include <time.h>

typedef struct item
{
    int x;
    int y;
}TipoItem;

typedef struct celula
{
    struct celula *prox;
    struct celula *ant;
    TipoItem item;
}Celula;

typedef struct recorde
{
    char *nome;
    float pontos;
    int level;
} Recorde;

typedef struct lista{

    Celula *primeiro;
    Celula *ultimo;
}Lista;

typedef struct 
{
    char **mat;
    Lista posicoes;
    int flag;
    int XAlvo;
    int YAlvo;
    int pontos;
    int ultimove;
    float speed;
    char nome[30];
    int ultimo_x;
    int ultimo_y;
    int corFundo;
    int corSnake;
    int corSemente;
    int corParede;
    int corLetraPlacar;
    int corFundoPlacar;
    int jogoLevel;
    int jogoSementes;
    Recorde recorde;
    int dificuldade;
    Lista blocos;
} Jogo;

void FLVazia (Lista *lista){
    lista->primeiro = (Celula*) malloc(sizeof(Celula));
    lista->ultimo = lista->primeiro;
    lista->ultimo->prox = NULL;
    lista->primeiro->ant = NULL;
}

int Vazia(Lista lista){
    return(lista.primeiro == lista.ultimo);
}

void Insere(Lista *lista, TipoItem x){

    lista->ultimo->prox = (Celula*) malloc (sizeof(Celula));
    lista->ultimo->ant = lista->ultimo;
    lista->ultimo = lista->ultimo->prox;
    lista->ultimo->prox = NULL;
    lista->ultimo->item = x;
 
}

void LimparMatriz (Jogo *jogo){
    
    int i,j;
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 50; j++)
        {
            jogo->mat[i][j] = ' ';
        }   
    }    
}

char** AlocarMatriz(int Linhas,int Colunas){

    int i,j;

    char **m = (char**)malloc(Linhas * sizeof(char*));

    for (i = 0; i < Linhas; i++)
    {
        m[i] = (char*) malloc(Colunas * sizeof(char*));
        for (j = 0; j < Colunas; j++)
        {
            m[i][j] = ' ';
        }
        
    }
    return m;
}

void MarcarJogo(Jogo *jogo){

    int x,y,cont = 0;

    Celula *aux = jogo->posicoes.primeiro;

    while (aux != NULL)
    {
        x = aux->item.x;
        y = aux->item.y;
        
        if (cont==0)
        {
            jogo->mat[x][y] = 178;
            cont++;
        }else{

            jogo->mat[x][y] = 177;
        }
        aux = aux->prox;
    }
    jogo->mat[jogo->XAlvo][jogo->YAlvo]='*';

    aux=jogo->blocos.primeiro->prox;

    while (aux!=NULL)
    {
        jogo->mat[aux->item.x][aux->item.y] = 'p';
        aux = aux->prox;
    }
}

void Baixo(Jogo *jogo){

    if((jogo->posicoes.primeiro->item.x + 1) <20 && jogo->dificuldade > 3){

        Celula *aux = jogo->posicoes.ultimo;
        while (aux->ant != NULL)
        {
            aux->item.x = aux->ant->item.x;
            aux->item.y = aux->ant->item.y;
            aux = aux->ant;
        }
        jogo->mat[jogo->posicoes.primeiro->item.x][jogo->posicoes.primeiro->item.y] = ' ';
        jogo->posicoes.primeiro->item.x++;
        jogo->ultimove = 80;
    }else if(jogo->dificuldade <= 3){

        Celula *aux = jogo->posicoes.ultimo;
        while (aux->ant != NULL)
        {
            aux->item.x = aux->ant->item.x;
            aux->item.y = aux->ant->item.y;
            aux = aux->ant;
        }
        jogo->mat[jogo->posicoes.primeiro->item.x][jogo->posicoes.primeiro->item.y] = ' ';
        if((jogo->posicoes.primeiro->item.x + 1 ) <20){

            jogo->posicoes.primeiro->item.x++;
        }
        else jogo->posicoes.primeiro->item.x = 0;

        jogo->ultimove = 80;
    
    }

    else jogo->flag = -1;
}

void Cima (Jogo *jogo){
    if((jogo->posicoes.primeiro->item.x - 1) >=0 && jogo->dificuldade > 3){

        Celula *aux = jogo->posicoes.ultimo;
        while (aux->ant != NULL)
        {
            aux->item.x = aux->ant->item.x;
            aux->item.y = aux->ant->item.y;
            aux = aux->ant;
        }
        jogo->mat[jogo->posicoes.primeiro->item.x][jogo->posicoes.primeiro->item.y] = ' ';
        jogo->posicoes.primeiro->item.x--;
        jogo->ultimove = 72;

    }else if(jogo->dificuldade <= 3){

        Celula *aux = jogo->posicoes.ultimo;
        while (aux->ant != NULL)
        {
            aux->item.x = aux->ant->item.x;
            aux->item.y = aux->ant->item.y;
            aux = aux->ant;
        }
        jogo->mat[jogo->posicoes.primeiro->item.x][jogo->posicoes.primeiro->item.y] = ' ';
        if((jogo->posicoes.primeiro->item.x - 1 ) >= 0){

            jogo->posicoes.primeiro->item.x--;
        }
        else jogo->posicoes.primeiro->item.x = 19;

        jogo->ultimove = 72;
    }

    else jogo->flag = -1;
}

void Esquerda(Jogo *jogo) {

    if((jogo->posicoes.primeiro->item.y - 1) >=0 && jogo->dificuldade > 3){

        Celula *aux = jogo->posicoes.ultimo;
        while (aux->ant != NULL)
        {
            aux->item.x = aux->ant->item.x;
            aux->item.y = aux->ant->item.y;
            aux = aux->ant;
        }
        jogo->mat[jogo->posicoes.primeiro->item.x][jogo->posicoes.primeiro->item.y] = ' ';
        jogo->posicoes.primeiro->item.y--;
        jogo->ultimove = 75;
    }else if(jogo->dificuldade <= 3){

        Celula *aux = jogo->posicoes.ultimo;
        while (aux->ant != NULL)
        {
            aux->item.x = aux->ant->item.x;
            aux->item.y = aux->ant->item.y;
            aux = aux->ant;
        }
        jogo->mat[jogo->posicoes.primeiro->item.x][jogo->posicoes.primeiro->item.y] = ' ';
        if((jogo->posicoes.primeiro->item.y - 1 ) >=0){

            jogo->posicoes.primeiro->item.y--;
        }
        else jogo->posicoes.primeiro->item.y = 49;

        jogo->ultimove = 75;
    
    }

    else jogo->flag = -1;
}

void Direita(Jogo *jogo){

    if((jogo->posicoes.primeiro->item.y + 1) <50 && jogo->dificuldade > 3){

        Celula *aux = jogo->posicoes.ultimo;
        while (aux->ant != NULL)
        {
            aux->item.x = aux->ant->item.x;
            aux->item.y = aux->ant->item.y;
            aux = aux->ant;
        }
        jogo->mat[jogo->posicoes.primeiro->item.x][jogo->posicoes.primeiro->item.y] = ' ';
        jogo->posicoes.primeiro->item.y++;
        jogo->ultimove = 77;
    }else if(jogo->dificuldade <= 3){

        Celula *aux = jogo->posicoes.ultimo;
        while (aux->ant != NULL)
        {
            aux->item.x = aux->ant->item.x;
            aux->item.y = aux->ant->item.y;
            aux = aux->ant;
        }
        jogo->mat[jogo->posicoes.primeiro->item.x][jogo->posicoes.primeiro->item.y] = ' ';
        if((jogo->posicoes.primeiro->item.y + 1 ) <48){

            jogo->posicoes.primeiro->item.y++;
        }
        else jogo->posicoes.primeiro->item.y = 0;

        jogo->ultimove = 77;
    
    }

    else jogo->flag = -1;
}

void GerarAlvo(Jogo *jogo){

    srand(/*(unsigned)*/time(NULL) );
    int flag = 0;
    while (flag == 0)
    {
        jogo->XAlvo = rand() %20;
        jogo->YAlvo = rand() %50;
        if(jogo->mat[jogo->XAlvo][jogo->YAlvo] == ' '){
            flag = 1;
        }
        else flag = 0;
    }

    if (jogo->jogoSementes %3 == 0 && jogo->jogoSementes != 0){
        TipoItem A;
        while (flag == 0)
        {
            jogo->blocos.ultimo->item.x = rand() %20;
            jogo->blocos.ultimo->item.y = rand() %50;
            if (jogo->mat[jogo->blocos.ultimo->item.x][jogo->blocos.ultimo->item.y] == ' ' )
            {
                flag = 1;
                A.x = jogo->blocos.ultimo->item.x;
                A.y = jogo->blocos.ultimo->item.y;
                textcolor(15);
                gotoxy(A.y+2,A.x+3);
                printf("%c", 176);
                Insere(&jogo->blocos,A);
            }
            else flag = 0;
            
        }
        
    }
    
}

int ChecarJogo(Jogo *jogo){
    TipoItem A;
    A.x = 0;
    A.y = 0;
    int x, y;

    if(jogo->flag == -1){
        jogo->flag = -1;
        return -1;
    }
    else{
        Celula *aux = jogo->posicoes.primeiro->prox;
        while (aux != NULL)
        {
            if(jogo->posicoes.primeiro->item.x == aux->item.x && jogo->posicoes.primeiro->item.y){
                jogo->flag = -1;
                return -1;
            }
            aux = aux->prox;
        }
        
        Celula *aux2 = jogo->blocos.primeiro->prox;
        while (aux2 != NULL)
        {
            if(jogo->posicoes.primeiro->item.x == aux2 -> item.x && jogo->posicoes.primeiro->item.y == aux2->item.y){
                jogo->flag = -1;
                return -1;
            }
            aux2 = aux2 ->prox;
        }
        if (jogo->posicoes.primeiro->item.x == jogo->XAlvo && jogo->posicoes.primeiro->item.y == jogo->YAlvo){

            //atualizar placar
            x = jogo->posicoes.primeiro->item.y+2;
            y = jogo->posicoes.primeiro->item.x+3;

            gotoxy(1,1);
            textcolor(jogo->corLetraPlacar);
            textbackground(jogo->corFundoPlacar);
            printf("Nome: %s           PONTUACAO: %d pontos         Level: %d      ", jogo->nome, jogo->pontos, jogo->jogoLevel);
            textcolor(15);
            textbackground(jogo->corFundo);

            gotoxy(x,y);
            jogo->jogoSementes++;
            jogo->pontos = (jogo->jogoSementes*10)*jogo->jogoLevel;

            //atualizar velocidade do jogo
            if(jogo->jogoSementes %3 == 0){
                if(jogo->speed>=60) jogo->speed -=10;
                jogo->jogoLevel++;
                printf("\a");
            }
            Insere(&jogo->posicoes,A);
            GerarAlvo(jogo);
        }
        return 1;
    }
}

//criar paredes do jogo
void ImprimirJogo(Jogo jogo){
    int i,j; /*k*/
    int tamLinha = 20;
    int tamColuna = 50;
    clrscr();
    i=0;
    textcolor(jogo.corParede);
    textbackground(jogo.corFundo);
    printf("\n%c", 178); //201
    while (i<50)
    {
        printf("%c",178); //205
        i++;
    }
    printf("%c", 178); //187
    for (i = 0; i < tamLinha; i++) //cria 
    {
        printf("\n%c", 178); //186
        for (j = 0; j < tamColuna; j++)
        {
            printf("%c", jogo.mat[i][j]);
            if(j==tamColuna-1){
                printf("%c", 178); //186
            }
        }
        
    }
    while (i<50)
    {
        if(i==0) printf("%c", 178); //200
        printf("%c", 178);
        i++;
    }
    printf("%c", 178); //185
}

void Free(Jogo *jogo){

    Celula *aux2 = jogo->posicoes.primeiro;
    Celula *aux1;
    while (aux2->prox != NULL)
    {
        aux1 = aux2;
        aux2 = aux2->prox;
        free(aux1);
    }
    
}

void EscolherDificuldade(Jogo *jogo){
    clrscr();
    gotoxy(16,2);
    textbackground(12);
    printf("                            ");
    gotoxy(16,3);
    printf(" ");
    textcolor(15);
    textbackground(3);
    printf("                         ");
    textbackground(12);
    printf(" ");
    gotoxy(16, 4);
    printf(" ");
    textbackground(3);
    printf("       DIFICULDADE       ");
    textbackground(12);
    printf(" ");
    gotoxy(16, 5);
    printf(" ");
    textbackground(3);
    printf("                              ");
    textbackground(12);
    printf(" ");
    gotoxy(16,6);
    printf("                                ");
    textcolor(7);
    textbackground(0);
    printf("\n\n\n                         ");
    textcolor(10);
    printf("%c", 175);
    textcolor(15);
    printf("  MUITO FACIL\n");
    printf("\n                            FACIL\n");
    printf("\n                            NORMAL\n");
    printf("\n                            DIFICIL\n");
    printf("\n                            EXPERT\n");
    printf("\n\n  As dificuldades ");
    textcolor(10);
    printf("DIFICIL");
    textcolor(15);
    printf(" e ");
    textcolor(10);
    printf("EXPERT");
    printf("nao e possivel atravessar parede.");
    int tecla;
    while(tecla !=13){
        tecla = getch();
        switch (tecla){
            case 72:
            if(jogo->dificuldade > 0 ) jogo->dificuldade--;
            break;
            case 80:
            if(jogo->dificuldade > 0 ) jogo->dificuldade++;
            break;
        }
        if(jogo->dificuldade == 0){
            gotoxy(21,11);
            printf(" ");
            gotoxy(21,13);
            printf(" ");
            gotoxy(21,15);
            printf(" ");
            gotoxy(21,17);
            printf(" ");
            gotoxy(21,9);
            textcolor(10);
            printf("%c", 175);
            textcolor(15);
        }
        else if(jogo->dificuldade == 1){
            
            gotoxy(21,9);
            printf(" ");
            gotoxy(21,13);
            printf(" ");
            gotoxy(21,15);
            printf(" ");
            gotoxy(21,17);
            printf(" ");
            gotoxy(21,11);
            textcolor(10);
            printf("%c", 175);
            textcolor(15);
        }
        else if(jogo->dificuldade == 2){
            gotoxy(21,9);
            printf(" ");
            gotoxy(21,11);
            printf(" ");
            gotoxy(21,15);
            printf(" ");
            gotoxy(21,17);
            printf(" ");
            gotoxy(21,13);
            textcolor(10);
            printf("%c", 175);
            textcolor(15);
        }
        else if(jogo->dificuldade == 3){
            gotoxy(21,9);
            printf(" ");
            gotoxy(21,11);
            textcolor(10);
            printf(" ");
            textcolor(15);
            gotoxy(21,13);
            printf(" ");
            gotoxy(21,17);
            printf(" ");
            gotoxy(21,15);
            textcolor(10);
            printf("%c", 175);
            textcolor(15);
        }
        else if(jogo->dificuldade == 4){

            gotoxy(21,9);
            printf(" ");
            gotoxy(21,11);
            textcolor(10);
            printf(" ");
            textcolor(15);
            gotoxy(21,13);
            printf(" ");
            gotoxy(21,15);
            printf(" ");
            gotoxy(21,17);
            textcolor(10);
            printf("%c", 175);
            textcolor(15);
        }

    }
    jogo->dificuldade += 1;
    switch(jogo->dificuldade){
        case 1:
            jogo->speed = 250;
            break;
        case 2:
            jogo->speed = 200;
            break;
        case 3:
            jogo->speed = 150;
            break;
        case 4:
            jogo->speed = 100;
            break;
        case 5:
            jogo->speed = 50;
            break;
        default:
        printf("\nOpcao invalida! a dificuldade 'NORMAL' foi escolhida automaticamente");
        jogo->speed = 150;
        break;
    }
    jogo->ultimove = 0;
    clrscr();
}

void NovoJogo(Jogo *jogo){
    
    jogo->mat = AlocarMatriz(20,50); //20 linhas 50 colunas
    FLVazia(&jogo->posicoes);
    jogo->posicoes.primeiro->item.x = 0;
    jogo->posicoes.primeiro->item.y = 0;
    jogo->flag = 0;
    jogo->pontos = 0;
    jogo->ultimove = 0;
    jogo->ultimo_x = 1;
    jogo->ultimo_y = 1;
    jogo->corFundo = 2;
    jogo->corSnake = 10;
    jogo->corSemente = 12;
    jogo->corFundoPlacar = 0;
    jogo->corLetraPlacar = 15;
    jogo->corParede = 8;
    jogo->speed = 1000;
    jogo->jogoLevel = 1;
    jogo->jogoSementes = 0;
    jogo->dificuldade = 0;
    FLVazia(&jogo->blocos);
    GerarAlvo(jogo);
    MarcarJogo(jogo);
}

void AutoMove(Jogo *jogo){
    Sleep(jogo->speed);
    if(jogo->ultimove == 72){
        jogo->ultimo_x = jogo->posicoes.ultimo->item.x;
        jogo->ultimo_y = jogo->posicoes.ultimo->item.y;
        Cima(jogo);
        LimparMatriz(jogo);
        MarcarJogo(jogo);
    }
    else if(jogo->ultimove == 80){
        jogo->ultimo_x = jogo->posicoes.ultimo->item.x;
        jogo->ultimo_y = jogo->posicoes.ultimo->item.y;
        Baixo(jogo);
        LimparMatriz(jogo);
        MarcarJogo(jogo);
    }
    else if(jogo->ultimove == 77){
        jogo->ultimo_x = jogo->posicoes.ultimo->item.x;
        jogo->ultimo_y = jogo->posicoes.ultimo->item.y;
        Direita(jogo);
        LimparMatriz(jogo);
        MarcarJogo(jogo);
    }
    else if(jogo->ultimove == 75){
        jogo->ultimo_x = jogo->posicoes.ultimo->item.x;
        jogo->ultimo_y = jogo->posicoes.ultimo->item.y;
        Esquerda(jogo);
        LimparMatriz(jogo);
        MarcarJogo(jogo);
    }
}

void ThreadImprimir(Jogo *jogo){
    int cont;

    while (jogo->flag != -1)
    {
        ChecarJogo(jogo);
        gotoxy(1,24);
        textcolor(jogo->corLetraPlacar);
        textbackground(jogo->corFundoPlacar);
        printf("Velocidade: %.2f    Loc x y: {%d,%d}\n",jogo->speed, jogo->posicoes.primeiro->item.x, jogo->posicoes.primeiro->item.y);
        textbackground(jogo->corFundo);

        Celula *aux;
        aux = jogo->posicoes.primeiro;

        //limpar o rabo da cobrinha

        gotoxy((jogo->ultimo_y+2), (jogo->ultimo_x+3));
        printf(" ");
        gotoxy(jogo->YAlvo+2, jogo->XAlvo+3);
        textcolor(jogo->corSemente);
        textbackground(jogo->corFundo);
        printf("%c",254);

        aux=jogo->posicoes.primeiro;
        textcolor(jogo->corSnake);
        textbackground(jogo->corFundo);
        cont = 0;
        while (aux != NULL)
        {
            if(cont == 0){
                gotoxy((aux->item.y+2), (aux->item.x+3));
                textcolor(11);
                printf("%c", 178);
                cont++;
            }
            if(cont > 0){

                textcolor(jogo->corSnake);
                gotoxy((aux->item.y+2),(aux->item.x+3));
                printf("%c", 176);
                cont++;
            }
            aux = aux->prox;
        }
        textcolor(jogo->corFundo);
    }
    
}

void ThreadMove (Jogo *jogo){
    int var;

    while (jogo->flag != -1)
    {
        AutoMove(jogo);
    }
}

void Mover(Jogo *jogo){
    int var;

    while (jogo->flag != -1)
    {
        fflush(stdin);
        var = getch();
        //limpar matriz jogo
        switch(var){
            case 112:
                jogo->ultimove = 112;
                break;
            case 72:
                if(jogo->ultimove != 80)
                jogo->ultimove = 72;
                break;
            case 80:
                if(jogo->ultimove != 72)
                    jogo->ultimove = 80;
                break;
            case 77:
                if(jogo->ultimove != 75)
                    jogo->ultimove = 77;
                break;
            case 75:
                if(jogo->ultimove != 77)
                    jogo->ultimove = 75;
                break;
            case 43:
                jogo->speed += 10;
                break;
            case 45:
                if(jogo->speed-10 >=10) jogo->speed-=10;
                break;
        }   
    }
    if (jogo->pontos > jogo->recorde.pontos)
    {
        jogo->recorde.pontos = jogo->pontos;
        jogo->recorde.nome = jogo->nome;
        jogo->recorde.level = jogo->jogoLevel;
    }
    getch();
    textcolor(15);
    textbackground(0);
    system("cls");
    gotoxy(25,15);
    printf("\a");
    printf("Voce perdeu! Tente de novo!\n");
    Free(jogo);
    getch();
    system("cls");
}   

void ImprimirSlowMotionChar(char *string){
    int i = 0;
    while(string[i]!= '\0'){
    Sleep(15);
    printf("%c", string[i]);
    i++;
    }
}

void ImprimirLogo(){
    system("cls");
    textbackground(12);
    gotoxy(14,2);
    printf("                                             ");
    textcolor(15);
    textbackground(3);
    gotoxy(14,3);
    textbackground(12);
    printf(" ");
    textbackground(3);
    printf("                                            ");
    textbackground(12);
    printf(" ");
    gotoxy(14,4);
    printf(" ");
    textbackground(3);
    printf("     %c%c%c%c%c   %c     %c     %c    %c  %c%c%c%c%c%c%c", 219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    textbackground(12);
    printf(" ");
    gotoxy(14,5);
    printf(" ");
    textbackground(3);
    printf("    %c     %c  %c%c    %c    %c %c    %c   %c   %c",219,219,219,219,219,219,219,219,219,219);
    textbackground(12);
    printf(" ");
    gotoxy(14,6);
    printf(" ");
    textbackground(3);
    printf("    %c        %c %c   %c   %c   %c  %c    %c         ", 219,219,219,219,219,219,219,219);
    textbackground(12);
    printf(" ");
    gotoxy(14,7);
    printf(" ");
    textbackground(3);
    printf("     %c%c%c%c%c   %c  %c  %c  %c     %c  %c%c%c     %c%c%c%c%c     ", 219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    textbackground(12);
    printf(" ");
    gotoxy(14,8);
    printf(" ");
    textbackground(3);
    printf("          %c  %c   %c %c  %c%c%c%c%c%c%c  %c  %c    %c         ", 219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    textbackground(12);
    printf(" ");
    gotoxy(14,9);
    printf(" ");
    textbackground(3);
    printf("    %c     %c %c    %c%c  %c     %c  %c   %c   %c         ",219,219,219,219,219,219,219,219,219,219);
    textbackground(12);
    printf(" ");
    gotoxy(14,10);
    printf(" ");
    textbackground(3);
    printf("     %c%c%c%c%c   %c     %c  %c     %c  %c    %c  %c%c%c%c%c%c%c   ", 219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    textbackground(12);
    printf(" ");
    gotoxy(14,11);
    printf(" ");
    printf("                                                 ");
    textbackground(12);
    printf(" ");
    gotoxy(14,12);
    printf("                                                   ");
    textcolor(15);
    textbackground(0);
}

int main(){
    Jogo jogo;
    jogo.recorde.nome= "Vazio";
    jogo.recorde.pontos = 0;
    jogo.recorde.level = 0;
    int var, i = 0;

    char *cred1 = "desenvolvido por Gabriel Henrique";
    char *cred2 = "Aluno da UCB - ENGENHARIA DE SOFTWARE";
    char *cred3 = "Quarto periodo / 2021 - 2024";
    
    char *var1 = "jogo Snake em C utilizando de listas";
    char *var2 = "Divirta-se!";
    printf("\n\n\n\n\n                            ");
    textcolor(10);
    ImprimirSlowMotionChar(var1);
    printf("\n\n                              ");
    ImprimirSlowMotionChar(var2);
    textcolor(7);
    printf("\n\n");
    getch();
    clrscr();
    while(1>0){
        NovoJogo(&jogo);
        ImprimirLogo();
        var = 0;
        int tecla = 0;
        printf("\n\n\n                                     NOVO JOGO\n");
        printf("\n                                     RECORDE\n");
        printf("\n                                     CREDITOS\n");
        printf("\n                                     SAIR\n");
        gotoxy(34,15);
        textcolor(10);
        printf("%c",175);
        textcolor(15);
        while(tecla != 13){
            tecla = getch();
            switch (tecla)
            {
            case 72:
                if(var > 0) var--;
                break;
            case 80:
                if(var < 3) var++;
            }

            if(var == 0){
                gotoxy(34,19);
                printf(" ");
                gotoxy(34,17);
                printf(" ");
                gotoxy(34,21);
                printf(" ");
                gotoxy(34,15);
                textcolor(10);
                printf("%c", 175);
                textcolor(15);
            } else if(var == 1){
                gotoxy(34,15);
                printf(" ");
                gotoxy(34,19);
                printf(" ");
                gotoxy(34,21);
                printf(" ");
                gotoxy(34,17);
                textcolor(10);
                printf("%c", 175);
                textcolor(15);
            }else if(var == 2){
                gotoxy(34,15);
                printf(" ");
                gotoxy(34,17);
                printf(" ");
                gotoxy(34,21);
                printf(" ");
                gotoxy(34,19);
                textcolor(10);
                printf("%c", 175);
                textcolor(15);
            }else if(var == 3){
                gotoxy(34,15);
                printf(" ");
                gotoxy(34,17);
                printf(" ");
                gotoxy(34,19);
                printf(" ");
                gotoxy(34,21);
                textcolor(10);
                printf("%c", 175);
                textcolor(15);
            }
        }
    }
    clrscr();
    var+=1;
    switch (var)
    {
    case 1:
        ImprimirLogo();
        gotoxy(23,15);
        printf("Digite seu nome: ");
        scanf("%s", &jogo.nome);
        EscolherDificuldade(&jogo);
        _beginthread(ThreadMove, 0,&jogo);
        _beginthread(ThreadImprimir, 0, &jogo);
        gotoxy(1,1);
        textcolor(jogo.corLetraPlacar);
        textbackground(jogo.corFundoPlacar);
        printf("Nome: %s          SCORE: %d pontos      Level: %d      ", jogo.nome, jogo.pontos*10,jogo.jogoLevel);
        Mover(&jogo);
        break;
    
    case 2:
        clrscr();
        gotoxy(16,12);
        textbackground(12);
        printf("                             ");
        gotoxy(16,3);
        printf(" ");
        textcolor(15);
        textbackground(3);
        printf("                            ");
        printf(" ");
        gotoxy(16,4);
        printf(" ");
        textbackground(3);
        printf("          HIGH SCORE        ");
        textbackground(12);
        printf(" ");
        gotoxy(16,5);
        printf(" ");
        textbackground(3);
        printf("                            ");
        textbackground(12);
        printf(" ");
        gotoxy(16,6);
        printf("                             ");
        textcolor(7);
        textbackground(0);
        printf("\n                     ");
        textcolor(15);
        printf("\n\n      Nome: %s          SCORE: %.2f pontos      Level: %d",jogo.recorde.nome, jogo.recorde.pontos, jogo.recorde.level);
        getch();
        break;
    case 3:
        printf("\n\n\n\n\n\n\n          ");
        ImprimirSlowMotionChar(cred1);
        printf("\n\n            ");
        ImprimirSlowMotionChar(cred2);
        printf("\n\n            ");
        ImprimirSlowMotionChar(cred3);
        printf("\n\n            ");
        getch();
        break;
    case 4:
        exit(0);
        break;
    }

}