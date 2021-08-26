#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEVEL 3
#define MIN_DATA -9999

//SkipNode 구조체 선언
typedef struct SkipNode {
	int data;
	int level;
	struct SkipNode* next[MAX_LEVEL];
}SkipNode;

//SkipNode 관련 함수
void insertSkipNode(SkipNode** pHeadNode, int data);
void showSkipNode(SkipNode* pHeadNode);
void searchSkipNode(SkipNode* pHeadNode, int data);

int main() {
	//랜덤함수 시드 초기화
	srand(time(NULL));

	//Skip List 생성
	SkipNode* SkipList = (SkipNode*)malloc(sizeof(SkipNode));
	SkipList->level = MAX_LEVEL;
	SkipList->data = MIN_DATA;
	for (int i = 0; i < SkipList->level; i++)
		SkipList->next[i] = NULL;

	insertSkipNode(&SkipList, 3);
	insertSkipNode(&SkipList, 9);
	showSkipNode(SkipList);
	
	insertSkipNode(&SkipList, 1);
	insertSkipNode(&SkipList, 4);
	showSkipNode(SkipList);

	searchSkipNode(SkipList, 4);

	insertSkipNode(&SkipList, 5);
	insertSkipNode(&SkipList, 7);
	showSkipNode(SkipList);

	insertSkipNode(&SkipList, 6);
	insertSkipNode(&SkipList, 8);
	showSkipNode(SkipList);

	insertSkipNode(&SkipList, 2);
	insertSkipNode(&SkipList, 10);
	showSkipNode(SkipList);

	searchSkipNode(SkipList, 7);

}
void insertSkipNode(SkipNode** pHeadNode, int data) 
{
	int level = 1, i, pos = MAX_LEVEL;
	SkipNode* pTmpNode[MAX_LEVEL];
	SkipNode* pNewNode;
	
	//MAX_LEVEL에서 내려가면서 찾을 temp 노드 변수 초기화
	for(i=0;i<MAX_LEVEL;i++)
		pTmpNode[i] = *pHeadNode;

	for (i = MAX_LEVEL - 1; i >= 0; i--)
	{//현재 Level에서 집어 넣을 직전 노드로 이동
		
		while(pTmpNode[i]->next!=NULL) {
			if((pTmpNode[i]->next[i])->data > data) {
				break;
			}
			pTmpNode[i]=pTmpNode[i]->next[i];
		}
	}

	//추가할 노드의 최대 레벨을 계산(coin flip)
	while (rand() % 2)
	{
		level++;
		if (level >= MAX_LEVEL)
			break;
	}
	//추가할 노드 동적 할당 및 초기화
	pNewNode = (SkipNode*)malloc(sizeof(SkipNode));
	pNewNode->level = level;
	pNewNode->data = data;
	for (i = 0; i < MAX_LEVEL; i++)
		pNewNode->next[i] = NULL;

	//추가할 노드의 Level만큼 앞 뒤 연결된 노드들을 연결
	for (i = pNewNode->level - 1; i >= 0; i--)
	{
		pNewNode->next[i]=pTmpNode[i]->next[i];
		pTmpNode[i]->next[i]=pNewNode;
	}


	printf("Insert [%d] with level [%d]\n", data,level);
}
void showSkipNode(SkipNode* pHeadNode)
{
	SkipNode* pTmpNode = NULL;
	int i,j;

	//Level 별로 끝에 도달할 때까지 데이터 출력
	printf("---------------------------------\n");
	for (i = MAX_LEVEL; i >0;i--)
	{
		pTmpNode = pHeadNode->next[i];
		printf("Level %d:\t", i);
		while (pTmpNode != NULL)
		{
			if (pTmpNode->level >= i)
				printf("%d-----", pTmpNode->data);
			else
				printf("------");
			pTmpNode = pTmpNode->next[i--];
		}
		printf("NULL\n");                             
	}
	printf("---------------------------------\n");
}

void searchSkipNode(SkipNode* pHeadNode, int data)
{
	int pos = MAX_LEVEL-1;
	SkipNode* pTmpNode = pHeadNode->next[pos];

	//현재 Level에 속한 노드가 없거나 data가 찾고자 하는 data보다 큰 경우 Level 감소
	while (pTmpNode==NULL || pTmpNode->data > data)
		pTmpNode = pHeadNode->next[--pos];

	printf("Search [%d] : ", data);
	while (pTmpNode->data != data)
	{
		//탐색을 하다가 Node가 끝나거나 찾고자 하는 data가 없을 경우 Level 감소
		if (pTmpNode->next[pos] == NULL || pTmpNode->next[pos]->data > data)
			pos -= 1;
		else
		{
			printf("%d, ", pTmpNode->data);
			pTmpNode = pTmpNode->next[pos];
			if (pTmpNode->data == data)
			{
				printf("%d\n", pTmpNode->data);
				return;
			}
		}
	}
	printf(",,, there is no %d\n", data);
	printf("---------------------------------\n");
}
