/*
	COP3502C-24 Spring 0023 Lab 4
	Copyright 2024 Shaquille_Miller
*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>



typedef struct node
{
    char letter;
    struct node* next;
} node;



// Returns number of nodes in the linkedList.
int length(node* head)
{
    if (head == NULL) {
        return 0;
    }
    int len = 1;
    //Loop through linked list and track how many
    node* curNode = head;
    while (curNode->next != NULL) {
        len++;
        curNode = curNode->next;
    }
    return len;
}


// parses the string in the linkedList
// if the linked list is head -> |a|->|b|->|c|
// then toCString function wil return "abc"
char* toCString(node* head)
{
    if (head == NULL) {
        return "";
    }

    //Get length of linked list
    int len = length(head);
    char* newString = (char*) malloc((len + 1) * sizeof(char)); //1 extra for the null terminator

    node* curNode = head;
    int charIndex = 0;
    while (curNode != NULL) {
        *(newString + charIndex) = curNode->letter;
        curNode = curNode->next;
        charIndex++;
    }
    //Add null termonator
    *(newString + charIndex) = '\0';
    return newString;
}


// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{
    //If node* isnt pointing to a node
    if (*pHead == NULL) {
        //Create node
        node* newNode = (node*)malloc(sizeof(node));
        //Set first char and return
        newNode->letter = c;
        newNode->next = NULL;

        *pHead = newNode;
        return;
    }

    //Traverse to the end of the linked list 
    node* curNode = (*pHead);
    while (curNode->next != NULL) {
        curNode = curNode->next;
    }
    //At last node, add a new node with the char
    node* newNode = (node*)malloc(sizeof(node));
    newNode->letter = c;
    newNode->next = NULL;
    curNode->next = newNode;
}


// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{   
    //Use to store curnode to delete
    node* curNode = *pHead;
    while (curNode != NULL) {
        *pHead = curNode->next; //Move the head to the next as a placeholder 
        free(curNode);
        curNode = *pHead;
    }
    *pHead = NULL;
}

int main(void)
{
    int i, strLen, numInputs;
    node* head = NULL;
    char* str;
    char c;
    FILE* inFile = fopen("input.txt", "r");
    fscanf(inFile, " %d\n", &numInputs);
    while (numInputs-- > 0)
    {
        fscanf(inFile, " %d\n", &strLen);
        for (i = 0; i < strLen; i++)
        {
            fscanf(inFile, " %c", &c);
            insertChar(&head, c);
        }

        str = toCString(head);
        printf("String is : %s\n", str);
        free(str);
        deleteList(&head);
        if (head != NULL)
        {
            printf("deleteList is not correct!");
            break;
        }
    }
    fclose(inFile);
}
