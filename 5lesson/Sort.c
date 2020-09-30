#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef int(*MyFunc)(int, int);
int comp(int x, int y) {
	if (x > y)
		return 1;
	else 
		return 0;
}

void Sort(int *m, size_t size, MyFunc func) {
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			int res = func(m[i], m[j]);
			if (res) {
				int tmp = m[j];
				m[j] = m[i];
				m[i] = tmp;
			}
			else {
			
			}
		}
	}
}


int main() {
	int N;
	scanf ("%d", &N);
	int m[N];
	
	for (int i = 0; i < N; i++) {
		scanf("%d", m + i);
	}
	
	Sort(m,N, comp);
	
	for (int i = 0; i < N; i++) {
		printf("%d ",m[i]);
	}
	
	
	return 0;
}
