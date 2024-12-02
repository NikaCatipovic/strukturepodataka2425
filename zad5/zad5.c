#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _P {
    int broj;
    struct _P* next;
} P;

void insert_e(P** head, int b);
void evaluate_operation(P** head, char op);
void free_list(P** head);
int izracunaj(P** head);

int main() {
    P* head = NULL;
    int result = izracunaj(&head);
    printf("Rezultat: %d\n", result);
    return 0;
}

void insert_e(P** head, int b) {
    P* newperson = malloc(sizeof(P));
    if (!newperson) {
        fprintf(stderr, "Greška: nedovoljno memorije.\n");
        exit(EXIT_FAILURE);
    }
    newperson->broj = b;
    newperson->next = *head;
    *head = newperson;
}

void evaluate_operation(P** head, char op) {
    P* curr = *head;
    P* prev = NULL;

    while (curr->next != NULL) {
        prev = curr;
        curr = curr->next;
    }

    if (prev == NULL || curr == NULL) {
        fprintf(stderr, "Greška: nedovoljno operanada za operaciju '%c'.\n", op);
        exit(EXIT_FAILURE);
    }

    int b = curr->broj;
    prev->next = NULL;
    free(curr);
    curr = prev;

    int a = curr->broj;
    switch (op) {
    case '+': curr->broj = a + b; break;
    case '-': curr->broj = a - b; break;
    case '*': curr->broj = a * b; break;
    case '/':
        if (b == 0) {
            fprintf(stderr, "Greška: dijeljenje s nulom.\n");
            exit(EXIT_FAILURE);
        }
        curr->broj = a / b;
        break;
    default:
        fprintf(stderr, "Nepoznata operacija '%c'.\n", op);
        exit(EXIT_FAILURE);
    }
}

void free_list(P** head) {
    P* temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

int izracunaj(P** head) {
    FILE* f = fopen("postfix.txt", "r");
    if (!f) {
        fprintf(stderr, "Greška: ne mogu otvoriti datoteku 'postfix.txt'.\n");
        exit(EXIT_FAILURE);
    }

    char c;
    while (fscanf(f, " %c", &c) != EOF) {
        if (c >= '0' && c <= '9') {
            insert_e(head, c - '0');
        }
        else if (strchr("+-*/", c)) {
            evaluate_operation(head, c);
        }
        else {
            fprintf(stderr, "Greška: nepoznati znak '%c'.\n", c);
            fclose(f);
            exit(EXIT_FAILURE);
        }
    }
    fclose(f);

    if (*head == NULL || (*head)->next != NULL) {
        fprintf(stderr, "Greška: neispravan izraz.\n");
        exit(EXIT_FAILURE);
    }

    int result = (*head)->broj;
    free_list(head);
    return result;
}