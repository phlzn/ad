/* A&D Implementierung - Semesterprojekt
*
* ISBN in Textdatei suchen
* Algorithmen - Linear Search/Binary Search/Bubble Sort
*
* In der Textdatei dürfen keine leeren Zeilen nach der letzten geschriebenen Zeile vorhanden sein, da sonst versucht wird ein Nullpointer zu dereferenzieren!
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#pragma warning(disable:4996)
#define TRUE 1
#define FALSE 0


typedef struct
{
	char author[100];
	char title[100];
	char publisher[100];
	long long isbn;
	int publicationYear;
}Book;

// Function prototypes
void printAllBooks(Book inventory[], int count);
void linearSearch(Book inventory[], long long ISBN, int count);
void binarySearch(Book inventory[], long long ISBN, int count);

int main(int argc, char* argv[])
{
	FILE *file;
	char* item;
	char line[9001];
	int count = 0;
	int reccount = 0;
	int search = 0;
	long long scannedISBN = 0;
	Book* inventory;


	//Textdatei öffnen
	file = fopen("books.txt", "r");
	if (!file)
	{
		printf("Unable to open file!\n");
	}

	//Zeilen in Textdatei zählen um entsprechend Speicher für das "inventory array" allozieren
	while (fgets(line, 9000, file)) count++;
	fclose(file);
	file = fopen("books.txt", "r");
	inventory = malloc(count * sizeof(Book));

	//Kopieren von Text in entsprechende structs im "inventory array"
	while (fgets(line, 9000, file)) {

		item = strtok(line, ",");
		strcpy(inventory[reccount].author, item);

		item = strtok(NULL, ",");
		strcpy(inventory[reccount].title, item);

		item = strtok(NULL, ",");
		strcpy(inventory[reccount].publisher, item);

		item = strtok(NULL, ",");
		inventory[reccount].isbn = atoll(item);

		item = strtok(NULL, ",");
		inventory[reccount].publicationYear = atoi(item);

		reccount++;
	}

	//Einlesen der gesuchten ISBN Nummer, ISBN muss größer als kleinste 13-stellige Zahl, kleiner als kleinste 14-stellige Zahl und alphanumerisch sein
	printf("Gebe eine ISBN Nummer ohne Bindestrich ein (z.B. 978123456791): ");
	while (scanf_s("%lld", &scannedISBN) && scannedISBN > 1000000000000 && scannedISBN < 10000000000000 && !isalnum(scannedISBN))
	{
		printf("ISBN hat falsches Format!\n");
		printf("Gebe eine ISBN Nummer ein: ");
	}


	//Welche Suchmethode?
	printf("Linear Search(0) o. Binary Search(1): ");
	while (scanf_s("%d", &search) && search != 0 && search != 1)
	{
		printf("Falsche Eingabe!\n");
		printf("Linear Search(0) o. Binary Search(1): ");
	}

	if (search == 0)
	{
		linearSearch(inventory, scannedISBN, count);
	}
	else if (search == 1)
	{
		binarySearch(inventory, scannedISBN, count);
	}


	system("PAUSE");
	return 0;
}

//Funktionen

//Druckt alle "Book structs" des "inventory arrays" aus
void printAllBooks(Book inventory[], int count)
{
	for (int i = 0; i < count; ++i)
	{
		printf("Author: %s\n", inventory[i].author);
		printf("Title: %s\n", inventory[i].title);
		printf("Publisher: %s\n", inventory[i].publisher);
		printf("ISBN: %lld\n", inventory[i].isbn);
		printf("Publication year: %d\n", inventory[i].publicationYear);
		printf("---------------------------------------------------------------------------");
		printf("\n");
	}
}

// Lineare Suche hat eine Komplexität von 0(n)
void linearSearch(Book inventory[], long long ISBN, int count)
{
	int numberOfBooks = 0;
	for (int i = 0; i < count; ++i)
	{
		if (inventory[i].isbn == ISBN)
		{
			printf("\n");
			printf("Author: %s\n", inventory[i].author);
			printf("Title: %s\n", inventory[i].title);
			printf("Publisher: %s\n", inventory[i].publisher);
			printf("ISBN: %lld\n", inventory[i].isbn);
			printf("Publication year: %d\n", inventory[i].publicationYear);
			printf("\n");
			numberOfBooks++;
		}

	}
	printf("\nAnzahl der Buecher im Lager: %d\n\n", numberOfBooks);
}

//Binäre Suche hat eine durchschnittliche Komplexität von O(log n) und ist somit schneller als die lineare Suche
void binarySearch(Book inventory[], long long ISBN, int count) {

	int pass, exchanged = TRUE, i;
	Book temp;
	int n = count;
	int min = 0;
	int max = count - 1;
	int mid;

	//Bubble Sort
	for (pass = 1; pass <= n - 1 && exchanged; pass++)
	{
		exchanged = FALSE;
		for (i = 0; i < n - pass; i++)
		{
			if (inventory[i].isbn > inventory[i + 1].isbn)
			{
				temp = inventory[i];
				inventory[i] = inventory[i + 1];
				inventory[i + 1] = temp;
				exchanged = TRUE;
			}
		}
	}

	//Binary Search nach der gesuchten ISBN Nummer
	while (min <= max) {
		mid = min + (max - min) / 2;
		if (inventory[mid].isbn < ISBN){
			min = mid + 1;
		}
		else if (inventory[mid].isbn == ISBN){
			printf("\n");
			printf("Author: %s\n", inventory[mid].author);
			printf("Title: %s\n", inventory[mid].title);
			printf("Publisher: %s\n", inventory[mid].publisher);
			printf("ISBN: %lld\n", inventory[mid].isbn);
			printf("Publication year: %d\n", inventory[mid].publicationYear);
			printf("\n");
			break;
		}
		else
		{
			max = mid - 1;
		}

		mid = (min + max) / 2;
	}
	if (min > max)
	{
		printf("\n");
		printf("ISBN %lld not found!\n", ISBN);
	}
}
