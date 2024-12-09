#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAZIV 50
#define MAX_DATUM 11
#define MAX_LINIJA 100

typedef struct Artikl {
    char naziv[MAX_NAZIV];
    int kolicina;
    float cijena;
    struct Artikl* next;
} Artikl;

typedef struct Racun {
    char datum[MAX_DATUM];
    Artikl* artikli;
    struct Racun* next;
} Racun;

Racun* ucitajRacune();
Racun* dodajRacunSortirano(Racun* head, Racun* novi);
Artikl* dodajArtiklSortirano(Artikl* head, Artikl* novi);
void ispisiRacune(Racun* head);
void brisiRacune(Racun* head);

int main() {
    Racun* head = ucitajRacune();

    printf("Svi racuni sortirani po datumu:\n");
    ispisiRacune(head);

    brisiRacune(head);
    return 0;
}


Racun* ucitajRacune() {
    Racun* head = NULL;

    FILE* filePointer1 = fopen("racun1.txt", "r");
    if (!filePointer1) {
        printf("Greska pri otvaranju datoteke racun1.txt\n");
    }
    else {
        char datum[MAX_DATUM];
        fgets(datum, sizeof(datum), filePointer1);
        datum[strcspn(datum, "\n")] = '\0';

        Racun* noviRacun = (Racun*)malloc(sizeof(Racun));
        strcpy(noviRacun->datum, datum);
        noviRacun->artikli = NULL;
        noviRacun->next = NULL;

        char linija[MAX_LINIJA];
        while (fgets(linija, sizeof(linija), filePointer1)) {
            Artikl* noviArtikl = (Artikl*)malloc(sizeof(Artikl));
            sscanf(linija, "%s %d %f", noviArtikl->naziv, &noviArtikl->kolicina, &noviArtikl->cijena);
            noviArtikl->next = NULL;

            noviRacun->artikli = dodajArtiklSortirano(noviRacun->artikli, noviArtikl);
        }

        fclose(filePointer1);
        head = dodajRacunSortirano(head, noviRacun);
    }

    FILE* filePointer2 = fopen("racun2.txt", "r");
    if (!filePointer2) {
        printf("Greska pri otvaranju datoteke racun2.txt\n");
    }
    else {
        char datum[MAX_DATUM];
        fgets(datum, sizeof(datum), filePointer2);
        datum[strcspn(datum, "\n")] = '\0';

        Racun* noviRacun = (Racun*)malloc(sizeof(Racun));
        strcpy(noviRacun->datum, datum);
        noviRacun->artikli = NULL;
        noviRacun->next = NULL;

        char linija[MAX_LINIJA];
        while (fgets(linija, sizeof(linija), filePointer2)) {
            Artikl* noviArtikl = (Artikl*)malloc(sizeof(Artikl));
            sscanf(linija, "%s %d %f", noviArtikl->naziv, &noviArtikl->kolicina, &noviArtikl->cijena);
            noviArtikl->next = NULL;

            noviRacun->artikli = dodajArtiklSortirano(noviRacun->artikli, noviArtikl);
        }

        fclose(filePointer2);
        head = dodajRacunSortirano(head, noviRacun);
    }

    return head;
}

Racun* dodajRacunSortirano(Racun* head, Racun* novi) {
    if (!head || strcmp(novi->datum, head->datum) < 0) {
        novi->next = head;
        return novi;
    }

    Racun* trenutni = head;
    while (trenutni->next && strcmp(novi->datum, trenutni->next->datum) > 0) {
        trenutni = trenutni->next;
    }

    novi->next = trenutni->next;
    trenutni->next = novi;
    return head;
}

Artikl* dodajArtiklSortirano(Artikl* head, Artikl* novi) {
    if (!head || strcmp(novi->naziv, head->naziv) < 0) {
        novi->next = head;
        return novi;
    }

    Artikl* trenutni = head;
    while (trenutni->next && strcmp(novi->naziv, trenutni->next->naziv) > 0) {
        trenutni = trenutni->next;
    }

    novi->next = trenutni->next;
    trenutni->next = novi;
    return head;
}

void ispisiRacune(Racun* head) {
    while (head) {
        printf("Datum: %s\n", head->datum);
        Artikl* artikl = head->artikli;
        while (artikl) {
            printf("  - %s: %d x %.2f\n", artikl->naziv, artikl->kolicina, artikl->cijena);
            artikl = artikl->next;
        }
        head = head->next;
        printf("\n");
    }
}

void brisiRacune(Racun* head) {
    while (head) {
        Racun* temp = head;
        head = head->next;
        Artikl* artikl = temp->artikli;
        while (artikl) {
            Artikl* tempArtikl = artikl;
            artikl = artikl->next;
            free(tempArtikl);
        }
        free(temp);
    }
}
