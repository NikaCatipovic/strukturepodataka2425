#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_SIZE 100

#define FILE_ERROR_OPEN -1
#define MALLOC_ERROR -2
#define SCANF_ERROR -3

typedef struct polynomial {
    int coef;
    int exp;
    struct polynomial* next;
} Poly;

int addPolyToPoly(Poly*, Poly*);
int printPoly(Poly*);
int freeMemory(Poly*);
int polySum(Poly*, Poly*, Poly*);
int polyProduct(Poly*, Poly*, Poly*);

int main()
{
    Poly poly1Head = { .coef = 0, .exp = 0, .next = NULL };
    Poly poly2Head = { .coef = 0, .exp = 0, .next = NULL };
    Poly sumHead = { .coef = 0, .exp = 0, .next = NULL };
    Poly productHead = { .coef = 0, .exp = 0, .next = NULL };

    char buffer[MAX_LINE] = { 0 };

    FILE* filePointer = fopen("polynomials.txt", "r");
    if (filePointer == NULL) {
        printf("File could not be opened.\n");
        return FILE_ERROR_OPEN;
    }

    // Uèitavanje prvog polinoma iz prvog retka
    if (fgets(buffer, MAX_LINE, filePointer) != NULL) {
        char* ptr = buffer;
        int coef, exp;

        while (sscanf(ptr, " %dx^%d", &coef, &exp) == 2) {
            Poly* poly = (Poly*)malloc(sizeof(Poly));
            if (poly == NULL) return MALLOC_ERROR;

            poly->coef = coef;
            poly->exp = exp;
            poly->next = NULL;

            addPolyToPoly(&poly1Head, poly);

            // Pomakni pokazivaè `ptr` na sljedeæi èlan
            while (*ptr && *ptr != ' ') ptr++;
            while (*ptr == ' ') ptr++;
        }
    }

    // Uèitavanje drugog polinoma iz drugog retka
    if (fgets(buffer, MAX_LINE, filePointer) != NULL) {
        char* ptr = buffer;
        int coef, exp;

        while (sscanf(ptr, " %dx^%d", &coef, &exp) == 2) {
            Poly* poly = (Poly*)malloc(sizeof(Poly));
            if (poly == NULL) return MALLOC_ERROR;

            poly->coef = coef;
            poly->exp = exp;
            poly->next = NULL;

            addPolyToPoly(&poly2Head, poly);

            // Pomakni pokazivaè `ptr` na sljedeæi èlan
            while (*ptr && *ptr != ' ') ptr++;
            while (*ptr == ' ') ptr++;
        }
    }

    fclose(filePointer);

    printf("Polynomial 1: ");
    printPoly(poly1Head.next);
    printf("Polynomial 2: ");
    printPoly(poly2Head.next);

    polySum(&sumHead, poly1Head.next, poly2Head.next);
    printf("Sum: ");
    printPoly(sumHead.next);

    polyProduct(&productHead, poly1Head.next, poly2Head.next);
    printf("Product: ");
    printPoly(productHead.next);

    freeMemory(&poly1Head);
    freeMemory(&poly2Head);
    freeMemory(&sumHead);
    freeMemory(&productHead);

    return 0;
}

int addPolyToPoly(Poly* head, Poly* poly)
{
    Poly* prev = head;
    Poly* temp = NULL;

    if (poly->coef == 0) {
        free(poly);
        return 0;
    }

    while (prev->next != NULL && prev->next->exp > poly->exp)
        prev = prev->next;

    if (prev->next != NULL && poly->exp == prev->next->exp)
    {
        prev->next->coef += poly->coef;
        free(poly);

        if (prev->next->coef == 0)
        {
            temp = prev->next;
            prev->next = prev->next->next;
            free(temp);
        }
    }
    else {
        poly->next = prev->next;
        prev->next = poly;
    }

    return 0;
}

int printPoly(Poly* current)
{
    if (current != NULL) {
        current->coef > 0 ? printf("%d", current->coef) : printf("- %d", -current->coef);

        if (current->exp == 1) printf("x ");
        else if (current->exp != 0) printf("x^%d ", current->exp);

        current = current->next;
    }

    while (current != NULL)
    {
        if (current->coef > 0) printf("+ ");
        current->coef > 0 ? printf("%d", current->coef) : printf("- %d", -current->coef);

        if (current->exp == 1) printf("x ");
        else if (current->exp != 0) printf("x^%d ", current->exp);

        current = current->next;
    }

    printf("\n");

    return 0;
}

int freeMemory(Poly* head)
{
    Poly* temp = NULL;

    while (head->next != NULL)
    {
        temp = head->next;
        head->next = temp->next;
        free(temp);
    }

    return 0;
}

int polySum(Poly* sum, Poly* poly1, Poly* poly2)
{
    Poly* temp = NULL;

    while (poly1 != NULL)
    {
        temp = (Poly*)malloc(sizeof(Poly));
        if (temp == NULL) return MALLOC_ERROR;

        temp->coef = poly1->coef;
        temp->exp = poly1->exp;

        addPolyToPoly(sum, temp);
        poly1 = poly1->next;
    }

    while (poly2 != NULL)
    {
        temp = (Poly*)malloc(sizeof(Poly));
        if (temp == NULL) return MALLOC_ERROR;

        temp->coef = poly2->coef;
        temp->exp = poly2->exp;

        addPolyToPoly(sum, temp);
        poly2 = poly2->next;
    }

    return 0;
}

int polyProduct(Poly* product, Poly* poly1, Poly* poly2)
{
    Poly* temp = NULL;
    Poly* poly2first = poly2;

    while (poly1 != NULL)
    {
        poly2 = poly2first;
        while (poly2 != NULL)
        {
            temp = (Poly*)malloc(sizeof(Poly));
            if (temp == NULL) return MALLOC_ERROR;

            temp->coef = poly1->coef * poly2->coef;
            temp->exp = poly1->exp + poly2->exp;

            addPolyToPoly(product, temp);
            poly2 = poly2->next;
        }
        poly1 = poly1->next;
    }

    return 0;
}