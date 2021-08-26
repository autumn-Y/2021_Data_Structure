#define TESTCASE_PATH "testCases.txt"
#define BUFFSIZE 1024

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef struct polyTerm_ {
	int exp;
	int coeff;
	struct polyTerm_* next;
} polyTerm;

typedef struct poly_ {
	polyTerm* head;
} poly;

void initPoly(poly* A) {
	A->head = NULL;
}

void clearPoly(poly* A) {
	polyTerm *dNode=NULL, *tNode=NULL;
    if(A!=NULL) {
        tNode=A->head;
        while(tNode!=NULL) {
            dNode=tNode;
            tNode=tNode->next;
            free(dNode);
        }
        A->head=NULL;
    }
}

void printPoly_impl(poly A, char* buffer) {
    int noTermFlag=1;
    polyTerm *tNode=A.head;

    for(int i=0;tNode!=NULL;i++) {
        char buffTemp[BUFFSIZE]="";
        noTermFlag=0;
        if(tNode->coeff<0){
            sprintf(buffTemp, "%dx^%d", tNode->coeff, tNode->exp);
            strcat(buffer, buffTemp);
        }
        else if(tNode->coeff>0) {
            sprintf(buffTemp, "+%dx^%d", tNode->coeff, tNode->exp);
            strcat(buffer, buffTemp);
        }
		tNode=tNode->next;
    }

    if(noTermFlag==1) {
        sprintf(buffer, "0");
    }
}

void printPoly(poly A) {
	char buffer[BUFFSIZE] = "";
	printPoly_impl(A, buffer);
	printf(buffer);
}

void addTerm(poly* A, int exp, int coeff) {
	polyTerm *nNode=NULL, *tNode=NULL;
    tNode=A->head;

    while(tNode!=NULL) {
		if(tNode->next==NULL || (tNode->next->exp) <= exp)
			break;
        
		tNode=tNode->next;
    }

    if(tNode==NULL){
		nNode=(polyTerm*)malloc(sizeof(polyTerm));
		nNode->exp=exp;
		nNode->coeff=coeff;
		nNode->next=NULL;
		A->head=nNode;
	}
	else if(tNode->next==NULL) {
		nNode=(polyTerm*)malloc(sizeof(polyTerm));
		nNode->exp=exp;
		nNode->coeff=coeff;
		nNode->next=tNode->next;
		tNode->next=nNode;
	}
	else {
		if(tNode->next->exp==exp) {
			tNode->next->coeff+=coeff;
		}
		else {
			nNode=(polyTerm*)malloc(sizeof(polyTerm));
			nNode->exp=exp;
			nNode->coeff=coeff;
			nNode->next=tNode->next;
			tNode->next=nNode;
		}
	}
}

poly multiPoly(poly A, poly B) {
	poly C;
    initPoly(&C);

    polyTerm *a=A.head;
    polyTerm *b=B.head;

    int i, j, ex, coe;
    for(i=0;a!=NULL;i++) {
        for(j=0;b!=NULL;j++) {
            ex=(a->exp) + (b->exp);
            coe=(a->coeff) * (b->coeff);
			addTerm(&C,ex,coe);
			b=b->next;
        }
		b=B.head;
        a=a->next;
    }
    return C;
}

void testPoly() { //You don't have to use this func.
	int breakFlag = 0;
	int breakPoint = -1;
	FILE* fp = fopen(TESTCASE_PATH, "r");
	poly A, B;
	initPoly(&A);
	initPoly(&B);

	int T;
	fscanf(fp, "%d\n", &T);

	char lastTrue[BUFFSIZE] = "";
	char lastAnswer[BUFFSIZE] = "";

	while (T--) {
		char inputOp0, inputOp1;
		char inputStr[BUFFSIZE] = "";
		char buffer[BUFFSIZE] = "";
		int caseNum;

		fscanf(fp, "%d %c ", &caseNum, &inputOp0);

		if (inputOp0 == 'a') {
			int exp, coeff;
			fscanf(fp, "%c %d %d\n", &inputOp1, &exp, &coeff);
			if (inputOp1 == 'A') {
				addTerm(&A, exp, coeff);
			}
			else if (inputOp1 == 'B') {
				addTerm(&B, exp, coeff);
			}
		}

		else if (inputOp0 == 'p') {
			fscanf(fp, "%c\n%s\n", &inputOp1, inputStr);
			if (inputOp1 == 'A') {
				printPoly_impl(A, buffer);
			}
			else if (inputOp1 == 'B') {
				printPoly_impl(B, buffer);
			}

			if (strcmp(inputStr, buffer) != 0) {
				breakFlag = 1;
				breakPoint = caseNum;
				strcpy(lastTrue, inputStr);
				strcpy(lastAnswer, buffer);
				break;
			}
		}

		else if (inputOp0 == 'c') {
			fscanf(fp, "%c\n", &inputOp1);
			if (inputOp1 == 'A') {
				clearPoly(&A);
			}
			else if (inputOp1 == 'B') {
				clearPoly(&B);
			}
		}

		else if (inputOp0 == 'm') {
			fscanf(fp, "%s\n", inputStr);
			printPoly_impl(multiPoly(A, B), buffer);
			if (strcmp(inputStr, buffer) != 0) {
				breakFlag = 1;
				breakPoint = caseNum;
				strcpy(lastTrue, inputStr);
				strcpy(lastAnswer, buffer);
				break;
			}
		}
	}

	fclose(fp);

	if (breakFlag) {
		printf("Test failed on case# %d\n", breakPoint);
		printf("True: %s\nAnswer: %s", lastTrue, lastAnswer);
	}
	else {
		printf("TEST DONE.\n");
	}
}

int main() {
	testPoly(); //use this function if you want.

	poly A, B;
	initPoly(&A);
	initPoly(&B);

	addTerm(&A, 1, 1);
	addTerm(&A, 0, 1);
	printf("poly A: ");
	printPoly(A);
	printf("\n");

	addTerm(&B, 1, 1);
	addTerm(&B, 0, -1);
	printf("poly B: ");
	printPoly(B);
	printf("\n");

	printf("A*B: ");
	printPoly(multiPoly(A, B));

	return 0;
}