#include <stdio.h>

int count;
 
void hanoi(int n, char from, char middle, char to){
    if (n==1) {
    	count++;
        printf("%d�� ������  %c���� %c�� �̵�\n", n,from,to);
	}
	else{
        hanoi(n-1,from,to,middle);
        printf("%d�� ������  %c���� %c�� �̵�\n", n,from,to);
        count++;
        hanoi(n-1,middle,from,to);
    }
}

int main() {
	int n;
	printf("������ ������ �Է��Ͻÿ�: ");
	scanf("%d",&n);
	hanoi(n,'A','B','C');
	
	printf("�� �̵�Ƚ�� : %d",count);
	return 0;
}
