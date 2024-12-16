#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct direktorij;
typedef struct direktorij dir;
typedef struct direktorij* Node;

struct SimStack;
typedef struct SimStack* Stack;

struct direktorij {
    char ime[10];
    Node Next;
    Node Child;
};

struct SimStack {
    Node Element;
    char path[100]; // Cuvanje putanje
    Stack Next;
};

void IspisDir(Node, char*);
Node IzadjiDir(Node, char*, Stack);
Node UdjiDir(Node, char*, char*, Stack);
void StvoriDir(Node, char*, char*);
void Push(Stack, Node, char*);
Node Pop(Stack, char*);
void AzurirajPutanju(char*, const char*);

int main() {
    char instr[50], ime[10], naredba[10], path[100];
    char* i, * j;
    dir root;
    struct SimStack S;

    Node UpDir = &root;
    S.Next = NULL;

    printf("Unesi ime root direktorija: ");
    fgets(root.ime, sizeof(root.ime), stdin);
    root.ime[strcspn(root.ime, "\n")] = 0; 
    root.Child = NULL;
    root.Next = NULL;

    path[0] = 0;
    strcat(path, root.ime);
    strcat(path, ":\\");

    printf("\nUnesi naredbu:");
    printf("\n\tdir");
    printf("\n\tcd..");
    printf("\n\tcd ime_dir");
    printf("\n\tmk ime_dir");
    printf("\n\n\texit - za kraj\n");

    while (1) {
        printf("\n\n\t%s", path);

        if (!fgets(instr, sizeof(instr), stdin)) {
            printf("Greska prilikom citanja unosa!\n");
            continue;
        }

        instr[strcspn(instr, "\n")] = 0; 

        if (strlen(instr) == 0) continue; 

        memset(ime, 0, sizeof(ime));
        memset(naredba, 0, sizeof(naredba));

        i = strchr(instr, ' ');
        if (NULL == i) {
            strcpy(naredba, instr);
        }
        else {
            strncpy(naredba, instr, i - instr);
            naredba[i - instr] = 0;
            strcpy(ime, i + 1);
        }

        if (strcmp(naredba, "exit") == 0) {
            break;
        }
        else if (strcmp(naredba, "dir") == 0) {
            IspisDir(UpDir, path);
        }
        else if (strcmp(naredba, "cd..") == 0) {
            UpDir = IzadjiDir(UpDir, path, &S);
        }
        else if (strcmp(naredba, "cd") == 0) {
            if (ime[0] == 0) {
                printf("Greska u sintaksi naredbe!\nTreba biti: cd ime_dir\n");
            }
            else {
                UpDir = UdjiDir(UpDir, ime, path, &S);
            }
        }
        else if (strcmp(naredba, "mk") == 0) {
            if (ime[0] == 0) {
                printf("Greska u sintaksi naredbe!\nTreba biti: mk ime_dir\n");
            }
            else {
                StvoriDir(UpDir, ime, path);
            }
        }
        else {
            printf("\nPogresan unos!!\n");
        }
    }

    return 0;
}

void IspisDir(Node N, char* path) {
    int i = 0;
    printf("\nDirectory of %s", path);

    N = N->Child;
    while (N != NULL) {
        printf("\n\t\t %s", N->ime);
        N = N->Next;
        i++;
    }

    printf("\n\t\t %d Dir(s)", i);
}

Node IzadjiDir(Node N, char* path, Stack S) {
    Node temp;
    temp = Pop(S, path);

    if (NULL == temp) {
        printf("Nalazimo se u root direktoriju!\nIz njega se ne moze izaci!\n");
        return N;
    }

    return temp;
}

Node UdjiDir(Node N, char* ime, char* path, Stack S) {
    Node temp = N->Child;

    while (temp != NULL && strcmp(temp->ime, ime) != 0)
        temp = temp->Next;

    if (NULL == temp) {
        printf("\n Ne postoji pod-direktorij s tim imenom!!!\n");
    }
    else {
        Push(S, N, path);
        AzurirajPutanju(path, temp->ime);
        return temp;
    }

    return N;
}

void StvoriDir(Node N, char* ime, char* path) {
    Node q = (Node)malloc(sizeof(dir));
    if (NULL == q) {
        printf("\nGreska u alokaciji memorije!!\n");
        return;
    }

    strcpy(q->ime, ime);
    q->Child = NULL;
    q->Next = NULL;

    if (NULL == N->Child) {
        N->Child = q;
    }
    else {
        q->Next = N->Child;
        N->Child = q;
    }
    printf("Kreiran direktorij: %s u %s\n", ime, path);
}

void Push(Stack S, Node T, char* currentPath) {
    Stack q = (Stack)malloc(sizeof(struct SimStack));
    if (NULL == q) {
        printf("\nGreska kod alokacije memorije!!\n");
        return;
    }

    q->Element = T;
    strcpy(q->path, currentPath); // Cuvamo putanju
    q->Next = S->Next;
    S->Next = q;
}

Node Pop(Stack S, char* currentPath) {
    Node q;
    Stack temp;

    if (NULL == S->Next)
        return NULL;

    q = S->Next->Element;
    strcpy(currentPath, S->Next->path); // Vracamo putanju
    temp = S->Next;
    S->Next = temp->Next;

    free(temp);
    return q;
}

void AzurirajPutanju(char* path, const char* ime) {
    strcat(path, ime);
    strcat(path, "\\");
}
