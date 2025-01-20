#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct City {
    char name[50];
    int population;
    struct City* left;
    struct City* right;
} City;

typedef struct Country {
    char name[50];
    City* cities;
    struct Country* next;
} Country;

City* newCity(char* name, int population);
City* addCity(City* root, char* name, int population);
Country* newCountry(char* name);
Country* addCountry(Country* head, char* name);
void loadCities(Country* country, char* filename);
void loadCountries(Country** head, char* filename);
void printCities(City* root);
void printCountries(Country* head);
void searchCities(City* root, int population);
Country* findCountry(Country* head, char* name);

City* newCity(char* name, int population) {
    City* new = (City*)malloc(sizeof(City));
    strcpy(new->name, name);
    new->population = population;
    new->left = new->right = NULL;
    return new;
}

City* addCity(City* root, char* name, int population) {
    if (root == NULL) return newCity(name, population);
    if (population < root->population || (population == root->population && strcmp(name, root->name) < 0))
        root->left = addCity(root->left, name, population);
    else
        root->right = addCity(root->right, name, population);
    return root;
}

Country* newCountry(char* name) {
    Country* new = (Country*)malloc(sizeof(Country));
    strcpy(new->name, name);
    new->cities = NULL;
    new->next = NULL;
    return new;
}

Country* addCountry(Country* head, char* name) {
    Country* new = newCountry(name);
    if (head == NULL || strcmp(name, head->name) < 0) {
        new->next = head;
        return new;
    }
    Country* current = head;
    while (current->next != NULL && strcmp(name, current->next->name) > 0) {
        current = current->next;
    }
    new->next = current->next;
    current->next = new;
    return head;
}

void loadCities(Country* country, char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }
    char name[50];
    int population;
    while (fscanf(file, "%s %d", name, &population) != EOF) {
        country->cities = addCity(country->cities, name, population);
    }
    fclose(file);
}

void loadCountries(Country** head, char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }
    char country_name[50], city_filename[50];
    while (fscanf(file, "%s %s", country_name, city_filename) != EOF) {
        *head = addCountry(*head, country_name);
        loadCities(*head, city_filename);
    }
    fclose(file);
}

void printCities(City* root) {
    if (root == NULL) return;
    printCities(root->left);
    printf("%s, %d\n", root->name, root->population);
    printCities(root->right);
}

void printCountries(Country* head) {
    while (head != NULL) {
        printf("Country: %s\n", head->name);
        printCities(head->cities);
        head = head->next;
    }
}

void searchCities(City* root, int population) {
    if (root == NULL) return;
    searchCities(root->left, population);
    if (root->population > population) {
        printf("%s, %d\n", root->name, root->population);
    }
    searchCities(root->right, population);
}

Country* findCountry(Country* head, char* name) {
    while (head != NULL) {
        if (strcmp(head->name, name) == 0) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

int main() {
    Country* countries = NULL;
    loadCountries(&countries, "drzave.txt");
    printCountries(countries);

    char country_name[50];
    int population;
    printf("Enter the name of the country: ");
    scanf("%s", country_name);
    printf("Enter the minimum population: ");
    scanf("%d", &population);

    Country* country = findCountry(countries, country_name);
    if (country != NULL) {
        printf("Cities in %s with population greater than %d:\n", country_name, population);
        searchCities(country->cities, population);
    }
    else {
        printf("Country not found.\n");
    }

    return 0;
}



