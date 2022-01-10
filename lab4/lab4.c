#define _CRT_SECURE_NO_WARNINGS
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node
{
	char* data;
	struct Node* next;
} Node;

Node* newNode(char* str) {
	Node* new;
	new = malloc(sizeof(Node));
	new->data = malloc(strlen(str) + 1);
	strcpy(new->data, str);
	new->next = NULL;
	return(new);
}

int main() {
	char str[BUFSIZ];
	Node* head;
	Node* curr;
	Node* i;
	Node* newNode(char*);
	head = malloc(sizeof(Node));
	head->next = NULL;
	curr = head;
	printf("Line:\n");
	while (gets(str) != NULL)
	{
		if (str[0] == '.')
		{
			break;
		}
		curr->next = newNode(str);
		curr = curr->next;
	}
	for (i = head->next; i != NULL; i = i->next) {
		puts(i->data);
		if(i->data != NULL){
			free(i->data);
		}
		free(i);
	}
	free(head);
	return 0;
}
