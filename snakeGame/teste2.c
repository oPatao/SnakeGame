#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// Estrutura para representar cada segmento da cobra
typedef struct SnakeSegment {
    int x, y;
    struct SnakeSegment* next;
    struct SnakeSegment* prev;
} SnakeSegment;

// Estrutura para representar a cobra
typedef struct Snake {
    SnakeSegment* head;
    SnakeSegment* tail;
    int length;
} Snake;

// Função para inicializar a cobra
Snake* initSnake() {
    Snake* snake = (Snake*)malloc(sizeof(Snake));
    snake->head = NULL;
    snake->tail = NULL;
    snake->length = 0;
    return snake;
}

// Função para adicionar um segmento à cobra
void addSegment(Snake* snake, int x, int y) {
    SnakeSegment* segment = (SnakeSegment*)malloc(sizeof(SnakeSegment));
    segment->x = x;
    segment->y = y;
    segment->next = NULL;
    segment->prev = NULL;

    if (snake->length == 0) {
        snake->head = segment;
        snake->tail = segment;
    } else {
        segment->next = snake->head;
        snake->head->prev = segment;
        snake->head = segment;
    }

    snake->length++;
}

// Função para exibir a cobra na tela
void displaySnake(Snake* snake) {
    SnakeSegment* current = snake->head;

    while (current != NULL) {
        printf("(%d, %d) ", current->x, current->y);
        current = current->next;
    }

    printf("\n");
}

// Função principal
int main() {
    // Inicializar a cobra
    Snake* snake = initSnake();

    // Adicionar alguns segmentos iniciais
    addSegment(snake, 2, 0);
    addSegment(snake, 1, 0);
    addSegment(snake, 0, 0);

    // Exibir a cobra
    displaySnake(snake);

    // Aguardar entrada do usuário
    printf("Pressione qualquer tecla para sair...\n");
    getch();

    return 0;
}
