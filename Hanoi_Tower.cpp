#include <stdio.h>

int count;
 
void hanoi(int n, char from, char middle, char to){
    if (n==1) {
    	count++;
        printf("%d번 원판을  %c에서 %c로 이동\n", n,from,to);
	}
	else{
        hanoi(n-1,from,to,middle);
        printf("%d번 원판을  %c에서 %c로 이동\n", n,from,to);
        count++;
        hanoi(n-1,middle,from,to);
    }
}

int main() {
	int n;
	printf("원판의 개수를 입력하시오: ");
	scanf("%d",&n);
	hanoi(n,'A','B','C');
	
	printf("총 이동횟수 : %d",count);
	return 0;
}
