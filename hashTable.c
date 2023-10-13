#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define HASH_TABLE_SIZE 10
#define DATA_ARRAY_SIZE 100

typedef struct linkedList {
	int value;
	struct linkedList* next;
} linkedList;

typedef struct hashTable {
	unsigned int index;
	linkedList* head;
}hashTable;

void printHashTable(hashTable** table, int tableSize) {
	printf("=====\t\t=====\n");
	printf("index\t|\tvalues\n");
	printf("-----\t\t-----\n");
	for (int i = 0; i < tableSize; i++)
	{
		printf("%d\t|\t", table[i]->index);
		linkedList* tmp = table[i]->head;
		if (tmp == NULL) {
			printf("<-empty->");
		}
		else {
			printf("%d", tmp->value);

			while (tmp->next != NULL) {
				tmp = tmp->next;
				printf(" -> %d", tmp->value);
			}
		}
		printf("\n");
	}
	printf("=====\t\t=====\n");
}

void insertValueInHashTable(hashTable** table, int value, int tableSize) {
	linkedList* newNode = calloc(1, sizeof(linkedList));
	newNode->value = value;
	newNode->next = NULL;

	int index = value % tableSize;
	if (table[index]->head == NULL) {
		table[index]->head = newNode;
		return;
	}

	linkedList* now = table[index]->head;

	while (now->next != NULL) {
		if (now->value == value) {
			printf("value %d has been insert into the hash table.\n", value);
			return;
		}
		now = now->next;
	}
	if (now->value == value) {
		printf("value %d has been insert into the hash table.\n", value);
		return;
	}
	now->next = newNode;
}

bool findValueInHashTable(hashTable** table, int value, int tableSize) {
	int index = value % tableSize;
	linkedList* now = table[index]->head;
	while (now != NULL) {
		if (now->value == value) {
			return true;
		}
		now = now->next;
	}
	return false;
}

bool deleteValueInHashTable(hashTable** table, int value, int tableSize) {
	bool head_flag = true;
	int index = value % tableSize;

	linkedList* now = table[index]->head;
	linkedList* tmp = now;

	while (now != NULL) {
		if (now->value == value) {
			if (head_flag) {
				tmp = now->next;
				free(now);
				now = tmp;
				table[index]->head = now;
			}
			else {
				tmp->next = now->next;
				free(now);
				now = tmp;
			}
			return true;
		}
		else {
			head_flag = false;
			tmp = now;
			now = now->next;
		}
	}
	return false;
}

int main()
{	
	hashTable* table[HASH_TABLE_SIZE];
	for (int i = 0; i < HASH_TABLE_SIZE; i++) {
		table[i] = calloc(1, sizeof(hashTable));
		table[i]->index = i;
		table[i]->head = NULL;
	}
	printHashTable(&table, HASH_TABLE_SIZE);

	int elements[DATA_ARRAY_SIZE], element_num = DATA_ARRAY_SIZE;
	for (int i = 0; i < DATA_ARRAY_SIZE; i++) {
	 	 elements[i] = rand() % DATA_ARRAY_SIZE + 1;
	}

	//int elements[14] = { 85, 100, 26, 71, 1, 4, 3, 2, 5, 16, 24, 8, 96, 17 }, element_num = 14;

	for (int i = 0; i < element_num; i++) {
		insertValueInHashTable(&table, elements[i], HASH_TABLE_SIZE);
	}

	printHashTable(&table, HASH_TABLE_SIZE);

	int targets[] = { 17,4,24,98,13,25 };
	int target_num = 6;

	for (int i = 0; i < target_num; i++) {
		if (findValueInHashTable(&table, targets[i], HASH_TABLE_SIZE)) {
			printf("value %d found\n", targets[i]);
		}
		else {
			printf("value %d not found\n", targets[i]);
		}
	}

	for (int i = 0; i < target_num; i++) {
		if (deleteValueInHashTable(&table, targets[i], HASH_TABLE_SIZE)) {
			printf("value %d deleted successfully\n", targets[i]);
		}
		else {
			printf("value %d not found\n", targets[i]);
		}
	}

	printHashTable(&table, HASH_TABLE_SIZE);

	return 0;
}
