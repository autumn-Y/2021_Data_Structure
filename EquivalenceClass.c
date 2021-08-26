#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 24
#define FALSE 0
#define TRUE 1

//구조체 선언
typedef struct node *nodePointer;
typedef struct node {
	int data;
	nodePointer link;
};

int main() {
	int out[MAX_SIZE];
	nodePointer seq[MAX_SIZE];
	nodePointer x, y, top;
	int i, j, n;

	printf("Enter the size (<= %d) ", MAX_SIZE);
	scanf("%d", &n);
	for (i = 0; i < n; i++) {

		out[i] = TRUE;
		seq[i] = NULL;
	}

	printf("Enter a pair of numbers (-1 -1 to quit): ");
	scanf("%d%d", &i, &j);
	while (i >= 0)
	{
		//새 노드를 만들어 j를 넣고 i번 노드에 추가
		x=(nodePointer)malloc(sizeof(nodePointer));
		x->data=j;
		x->link=seq[i]->link;
		seq[i]=x;

		//새 노드를 만들어 i를 넣고 j번 노드에 추가
		x=(nodePointer)malloc(sizeof(nodePointer));
		x->data=i;
		x->link=seq[j]->link;
		seq[j]=x;

		printf("Enter a pair of numbers (-1 -1 to quit): ");
		scanf("%d%d", &i, &j);
	}

	for (i = 0; i < n; i++)
		if (out[i]) {
			printf("\nNew class: %5d", i);

			//클래스 i를 탑색
			out[i] = FALSE;
			x = seq[i];
			top = NULL;
			for (;;) {
				while (x) { 

					j = x->data;
					//아직 탐색되지 않았다면 위치를 저장하고 새로운 리스트로 이동
					if (out[j]) {
						printf("%5d", j);
						out[j] = FALSE;

						y=x->link;
						x->link=top;
						top=x;
						x=y;
					}
					//이미 탐색되었다면 통과
					else 
						x=x->link;
				
				//top이 FALSE이면 전부 탐색한 것
				if (!top) 
					break;
				//위치를 저장해뒀던 top으로 이동
				x = seq[top->data];
				top = top->link;
			}
		}
	printf("%\n");
}
