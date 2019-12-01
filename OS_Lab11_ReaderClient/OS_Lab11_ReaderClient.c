#include <stdio.h>
#include <Windows.h>
#include "book.h"
#include "filemapping.h"

//READER
int main()
{
	

	//TODO: Take mapped file and get data from it
	//Take data from map file somewhere from here
	HANDLE hFileMap = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, FILEMAP_NAME);
	if (hFileMap == NULL) {
		printf(stderr, "Can't open memory mapped file. Error code: %lu\n", GetLastError());
		return 13;
	}
	else {
		printf("[Console] File opened succesfully\n");
	}

	char* pbMapView = (char*)MapViewOfFile(hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (pbMapView == NULL) {
		printf(stderr, "Can't map view of file. Error code: %lu)\n", GetLastError());
		return 13;
	} else {
		printf("[Console] Map view created succesfully\n");
	}
	
	printf("[Console] Test %s\n", pbMapView);
	printf("\n");
	printf("[Reader] You are reader.\n");

	char readName[BOOK_NAME_LEN] = "The King in Yellow";
	char *readText = calloc(500, sizeof(char));
	readText = "Along the shore the cloud waves break,\n"
		"The twin suns sink behind the lake,\n"
		"The shadows lengthen\n"
		"In Carcosa.\n";
	//To here

	Book *book = book_createFromText(readName, readText);
	printf("[Reader] Proceed to read a book \"%s\".\n", book->name);
	printf("[Reader] Now, read the book till it's finished.\n");
	printf("> ");
	for (char* characher = book->text; *characher != '\0'; ++characher)
	{
		putchar(*characher);
		Sleep((strchr(" .,?!\n\t", *characher)) ? 300 : 50);
		if (*characher == '\n')
			printf("> ");
	}
	printf("[Reader] Reading finished.\n");

	book_dispose(book);

	return 0;
}