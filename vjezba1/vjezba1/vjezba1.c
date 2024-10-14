#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX (1024)
#define MAX_BODOVI (100)

int ReadRows(const char* fileName);

typedef struct {
	char ime[50];
	char prezime[50];
	double bodovi;

} Student;

Student* AllocateStudents(int numberOfStudents);

void PrintStudents(int numberOfStudents, Student* students);

double relbod(double bodovi);




int main() {

	int numberOfRows = 0;

	numberOfRows = ReadRows("dat.txt");

	Student* students = NULL;

	if (numberOfRows > 0) {
		students = AllocateStudents(numberOfRows);
		PrintStudents(numberOfStudents, students);
		
		free(students);
	}

	return 0;
}

int ReadRows(const char* fileName)
{
	int numberOfRow = 0;
	FILE* fp = NULL;
	char buffer[MAX] = { '\0' };

	fp = fopen(fileName, "r");
	if (!fp)
	{
		return -1;
	}

	while (!feof(fp))
	{
		fgets(buffer, MAX, fp);
		numberOfRow++;
		
	}
	fclose(fp);

	return numberOfRow;
}

Student* AllocateStudents(int numberOfStudents); {


	int counter = 0;
	FILE* fp = NULL;
	Student* students = NULL;

	students = (Student*)malloc(numberOfStudents * sizeof(Student));
	if (!students) {
		printf("Nije alocirana memorija!\n");
		return NULL;
	
	}
	fp = fopen("dat.txt", "r");
	if (!fp) {
		printf("Datoteka nije otvorena!\n");
		return NULL;
	}
	while (!feof(fp)) {
		fscanf(fp, "%s %s %lf", students[numberOfRows].ime, students[numberOfRows].prezime, &studnets[numberOfRows].bodovi);
		numberOfRows++;
	}
	fclose(fp);

	return students;

}

double relbod(double bodovi)
{
	return ((bodovi / MAX_BODOVI) * 100);

}


int PrintStudents(int numberOfStudents, Student* students)
{
	int numberOfRows = 0;

	for (numberOfRows;  numberOfRows < numberOfStudents; numberOfRows++)
	{
		printf("ime: %s\t prezime: %s\t Apsolutni bodovi: %.2lf\t Relative bodovi: %.2lf%\t\n", students[numberOfRows].ime,
			students[numberOfRows].prezime, students[numberOfRows].bodovi, relbod(students[numberOfRows].bodovi));
	}

	return 0;