#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _node* Position;
typedef struct _node {
    int value;
    Position left;
    Position right;
} Node;

Position AllocateMemory(int);
Position InsertElement(Position, int);
int InOrderPrint(Position);
int PreOrderPrint(Position);
int PostOrderPrint(Position);
Position SearchElement(Position, int);
Position DeleteElement(Position, int);
Position FindMin(Position);

int main() {
    Position root = NULL;
    int choice = 0, element;
    Position temp = NULL;

    do {
        printf("\nOdaberi:\n");
        printf("1 - Unos novog elementa u stablo\n");
        printf("2 - Ispis inorder stabla\n");
        printf("3 - Ispis postorder stabla\n");
        printf("4 - Ispis preorder stabla\n");
        printf("5 - Traženje elementa u stablu\n");
        printf("6 - Brisanje elementa iz stabla\n");
        printf("7 - Izlaz\n");
        printf("Vaš odabir: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Unesite element koji želite unijeti u stablo: ");
            scanf("%d", &element);
            root = InsertElement(root, element);
            printf("Element %d je uspješno dodan!\n", element);
            break;
        case 2:
            printf("Inorder ispis stabla:\n");
            InOrderPrint(root);
            break;
        case 3:
            printf("Postorder ispis stabla:\n");
            PostOrderPrint(root);
            break;
        case 4:
            printf("Preorder ispis stabla:\n");
            PreOrderPrint(root);
            break;
        case 5:
            printf("Unesite element koji tražite u stablu: ");
            scanf("%d", &element);
            temp = SearchElement(root, element);
            if (temp)
                printf("Element %d pronaðen na adresi %p.\n", temp->value, (void*)temp);
            else
                printf("Element %d nije pronaðen u stablu.\n", element);
            break;
        case 6:
            printf("Unesite element koji želite obrisati iz stabla: ");
            scanf("%d", &element);
            root = DeleteElement(root, element);
            printf("Element %d je uspješno obrisan (ako je postojao).\n", element);
            break;
        case 7:
            printf("Izlaz iz programa.\n");
            break;
        default:
            printf("Pogrešan unos! Pokušajte ponovo.\n");
        }
    } while (choice != 7);

    return 0;
}

Position AllocateMemory(int value) {
    Position newNode = (Position)malloc(sizeof(Node));
    if (!newNode) {
        printf("Problem s alokacijom memorije!\n");
        return NULL;
    }
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Position InsertElement(Position root, int value) {
    if (!root)
        return AllocateMemory(value);
    if (value < root->value)
        root->left = InsertElement(root->left, value);
    else if (value > root->value)
        root->right = InsertElement(root->right, value);
    return root;
}

int InOrderPrint(Position root) {
    if (root) {
        InOrderPrint(root->left);
        printf("%d ", root->value);
        InOrderPrint(root->right);
    }
    return 0;
}

int PreOrderPrint(Position root) {
    if (root) {
        printf("%d ", root->value);
        PreOrderPrint(root->left);
        PreOrderPrint(root->right);
    }
    return 0;
}

int PostOrderPrint(Position root) {
    if (root) {
        PostOrderPrint(root->left);
        PostOrderPrint(root->right);
        printf("%d ", root->value);
    }
    return 0;
}

Position SearchElement(Position root, int value) {
    if (!root || root->value == value)
        return root;
    if (value < root->value)
        return SearchElement(root->left, value);
    return SearchElement(root->right, value);
}

Position DeleteElement(Position root, int value) {
    if (!root)
        return root;

    if (value < root->value)
        root->left = DeleteElement(root->left, value);
    else if (value > root->value)
        root->right = DeleteElement(root->right, value);
    else {
        if (!root->left) {
            Position temp = root->right;
            free(root);
            return temp;
        }
        else if (!root->right) {
            Position temp = root->left;
            free(root);
            return temp;
        }
        Position temp = FindMin(root->right);
        root->value = temp->value;
        root->right = DeleteElement(root->right, temp->value);
    }
    return root;
}

Position FindMin(Position root) {
    while (root && root->left)
        root = root->left;
    return root;
}
