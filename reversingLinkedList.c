#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

typedef struct Node {
	int data;
	struct Node* nextNode;
}Node;

typedef struct linkedList {
	int curCount;
	Node headNode;
}linkedList;

//stack 구조체 선언 (linked list)
typedef struct StackNode {
	int data;
	struct StackNode* next;
} StackNode;

//linked list functions
int addNode(linkedList* plist, int pos, int data) {
	Node *newNode=NULL, *tNode=NULL;
	if(plist==NULL) {
		printf("addNode() error1\n");
		return FALSE;
	}
	
	if(pos<0 || pos>plist->curCount) {
		printf("addNode() error2\n");
		return FALSE;
	}
	
	newNode=(Node*)malloc(sizeof(Node));
	if(!newNode) {
		printf("addNode() error3\n");
		return FALSE;
	}
	
	newNode->data=data;
	newNode->nextNode=NULL;
	
	tNode=&(plist->headNode);
	for(int i=0;i<pos;i++) {
		tNode=tNode->nextNode;
	}
	
	newNode->nextNode=tNode->nextNode;
	tNode->nextNode=newNode;
	plist->curCount++;

	return TRUE;
}

int removeNode(linkedList* plist, int pos) {
	Node* delNode=NULL, *tNode=NULL;
	
	if(plist==NULL) {
		printf("empty list\n");
		return FALSE;
	}
	
	if(pos<0 || pos>plist->curCount) {
		printf("out of boundary\n");
		return FALSE;
	}
	
	tNode=&(plist->headNode);
	for(int i=0;i<pos;i++) {
		tNode=tNode->nextNode;
	}
	
	delNode=tNode->nextNode;
	tNode->nextNode=delNode->nextNode;
	
	free(delNode);
	plist->curCount--;
	
	return TRUE;
}

void showNode(linkedList* plist) {
	int i=0;
	Node* pnode=NULL;
	
	if(plist==NULL) {
		printf("showNode() error\n");
		return;
	}
	
	printf("현재 Node 개수 : %d \n", plist->curCount);
	pnode=plist->headNode.nextNode;
	
	while(pnode!=NULL) {
		printf("[%d]\n",pnode->data);
		pnode=pnode->nextNode;
	}
	printf("------------------------\n");
	
	free(pnode);
	return;
}

int findPos(linkedList* plist, int data) {
	int pos=0;
	Node* pNode=NULL;
	
	if(plist==NULL) {
		printf("findPoss() error\n");
		return FALSE;
	}
	
	pNode=plist->headNode.nextNode;
	while(pNode!=NULL) {
		if(pNode->data==data) {
			return pos;
		}
		pos++;
		pNode=pNode->nextNode;
	}
	
	return FALSE;
}

void makeEmpty(linkedList* plist){
	Node* dNode=NULL, *tNode=NULL;
	if(plist!=NULL) {
		tNode=plist->headNode.nextNode;
		while(tNode!=NULL) {
			dNode=tNode;
			tNode=tNode->nextNode;
			free(dNode);
		}
		plist->headNode.nextNode=NULL;
	}
	plist->curCount=0;
}

//stack 관련 함수
int isEmpty(StackNode* top) {
	if (top == NULL)
		return TRUE;
	else
		return FALSE;
}

void pushLinkedStack(StackNode** top, int data){
	StackNode *pNode=NULL;

	pNode=(StackNode*)malloc(sizeof(StackNode));
	pNode->data=data;
	pNode->next=NULL;

	if((*top)==NULL) {
		(*top)=pNode;
	}
	
	else {
		pNode->next=(*top);
		(*top)=pNode;
	}
}

StackNode* popLinkedStack(StackNode** top) {
	StackNode *pNode=NULL;

	if(isEmpty(*top)) {
		return NULL;
	}

	else {
		pNode=(*top);
		(*top)=pNode->next;
		pNode->next=NULL;
	}

	return pNode;
}

StackNode* topLinkedStack(StackNode* top) {
	StackNode *Pnode=NULL;

	if(top!=NULL) {
		Pnode=top;
	}

	return Pnode;
}

void deleteLinkedStack(StackNode** top) {
	StackNode *pNode=NULL, *pDelNode=NULL;
	pNode=*top;

	while(pNode!=NULL) {
		pDelNode=pNode;
		pNode=pNode->next;
		free(pDelNode);
	}

	*top=NULL;
}

void showLInkedStack(StackNode* top) {
	StackNode* pNode = NULL;
	if (isEmpty(top)) {
		printf("the stack is empty\n");
		return;
	}

	pNode = top;
	printf("==============Show Stack===============\n");
	while (pNode != NULL) {
		printf("[%d]\n", pNode->data);
		pNode = pNode->next;
	}
	printf("=======================================\n");
}

void reverseList(linkedList *plist, StackNode **top) {
    Node *pNode=NULL;
    StackNode *sNode=NULL;
    printf("Reverse Linked List!\n");

    pNode=plist->headNode.nextNode;

    while(pNode!=NULL) {
        pushLinkedStack(top, pNode->data);
        pNode=pNode->nextNode;
    }
	int n=plist->curCount;
    makeEmpty(plist);

    for(int i=0;i<n;i++) {
        sNode=popLinkedStack(top);
		addNode(plist,i,sNode->data);
    }
}

int main() {
	int pos;
	linkedList* linked_list=(linkedList*)malloc(sizeof(linkedList));
	linked_list->curCount=0;
	linked_list->headNode.nextNode=NULL;
	
    StackNode *top=NULL;
    StackNode *pNode;

	addNode(linked_list, 0, 10);
	addNode(linked_list, 5, 100);
	addNode(linked_list, 1, 20);
	addNode(linked_list, 2, 30);
	addNode(linked_list, 1, 50);
    addNode(linked_list, 1, 70);
    addNode(linked_list, 1, 40);
	
	showNode(linked_list); 

    reverseList(linked_list, &top);
	showNode(linked_list);

	makeEmpty(linked_list);
	showNode(linked_list);
	free(linked_list);
	return 0;
}