#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define arraysize 10000
voidmain(void){
	clock_tstart, end; // объявляем переменные для определения времени выполнения
	int i = 0, j = 0, r;
	char* a = (char*)malloc(arraysize * arraysize);
	char* b = (char*)malloc(arraysize * arraysize);
	int* c = (int*)malloc(arraysize * arraysize*sizeof(int));
	int elem_c;
	//char a[arraysize][arraysize], b[arraysize][arraysize], c[arraysize][arraysize], elem_c;
	srand(time(NULL)); // инициализируем параметры генератора случайных чисел
	while (i < arraysize)
	{
		while (j < arraysize)
		{
			*(a + i * arraysize + j) = rand() % 100 + 1; // заполняем массив случайными числами
			j++;
		}
		i++;
	}
	srand(time(NULL)); // инициализируем параметры генератора случайных чисел
	i = 0; j = 0;
	while (i < arraysize)
	{
		while (j < arraysize)
		{
			*(b + i * arraysize + j) = rand() % 100 + 1; // заполняем массив случайными числами
			j++;
		}
		i++;
	}
	start = clock();
	for (i = 0; i < arraysize; i++)
	{
		for (j = 0; j < arraysize; j++)
		{
			elem_c = 0;
			for (r = 0; r < arraysize; r++)
			{
				elem_c = (int) elem_c + *(a + i * arraysize + r) * *(b + i * arraysize + j);
				*(c + i * arraysize + j) = elem_c;
			}
		}
	}
	end = clock();
	double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Time spent:%lf s", time_spent);
	free(a);
	free(b);
	free(c);
}
b)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void shell(int* items, int count)
{

    int i, j, gap, k;
    int x, a[5];

    a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
                items[j + gap] = items[j];
            items[j + gap] = x;
        }
    }
}

void qs(int* items, int left, int right) //вызов функции: qs(items, 0, count-1);
{
    int i, j;
    int x, y;

    i = left; j = right;

    /* выбор компаранда */
    x = items[(left + right) / 2];

    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;

        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
    } while (i <= j);

    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}

int compare(const void* a, const void* b)
{
    int arg1 = *(const int*)a;
	int arg2 = *(const int*)b;
	
	if (arg1<arg2) return -1;
	if (arg1>arg2) return 1;
	return 0;
}

int main() {
    int arraysize[2] = { 100,100000 };
    clock_t start, end;
    for (char k = 0; k < 8; k++) {
        srand(time(NULL));
         int* a = (int*)malloc(arraysize[k % 2] * sizeof(int));
         int* b = (int*)malloc(arraysize[k % 2] * sizeof(int));
         int* c = (int*)malloc(arraysize[k % 2] * sizeof(int));
         for (int i = 0; i < arraysize[k % 2]; i++){
             switch (k / 2) {
             case 0: {
				 if (i == 0) printf("\nRandom, %i elements:\n", arraysize[k % 2]);
                 b[i] = c[i] = a[i] = rand() % 101;
                 break;
             }
             case 1: {
				 if (i == 0) printf("\nSorted, %i elements:\n", arraysize[k % 2]);
                 a[i] = b[i] = c[i] = i;
                 break;
             }
             case 2: {
				 if (i == 0) printf("\nSorted backwords, %i elements:\n", arraysize[k % 2]);
                 a[i] = b[i] = c[i] = arraysize[k % 2] - i;
                 break;
             }
             case 3: {
				 if (i == 0) printf("\nUp and down, %i elements:\n", arraysize[k % 2]);
                 if (i = arraysize[k % 2] / 2) {
                     i = arraysize[k % 2];
                     break;
                 }
                 a[i] = b[i] = c[i] = i;
                 a[arraysize[k % 2] - i - 1] = b[arraysize[k % 2] - i - 1] = c[arraysize[k % 2] - i - 1] = i;
                 break;
             }
             }
         }
		 start = clock();
		 shell(a,arraysize[k%2]);
		 end = clock();
		 printf("Shell: %lf s\n", (double)(end - start) / CLOCKS_PER_SEC);

		 start = clock();
		 qs(b,0,arraysize[k%2]-1);
		 end = clock();
		 printf("qs: %lf s\n", (double)(end - start) / CLOCKS_PER_SEC);

		 start = clock();
		 qsort(c,arraysize[k%2],sizeof(int),compare);
		 end = clock();
		 printf("qsort: %lf s\n", (double)(end - start) / CLOCKS_PER_SEC);

		 free(a);
		 free(b);
		 free(c);
    }

}
