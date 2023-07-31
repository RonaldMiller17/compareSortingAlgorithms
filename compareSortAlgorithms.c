#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;


void mergeSort(int pData[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        // Recursively sort the left and right halves
        mergeSort(pData, l, m);
        mergeSort(pData, m + 1, r);

        int n1 = m - l + 1;
		int n2 = r - m;

		int* L = malloc(n1 * sizeof(int));
		int* R = malloc(n2 * sizeof(int));

		// Copy data to temporary arrays
		for (int i = 0; i < n1; i++)
			L[i] = pData[l + i];

		for (int j = 0; j < n2; j++)
			R[j] = pData[m + 1 + j];

		// Merge the two subarrays
		int i = 0, j = 0, k = l;
		while (i < n1 && j < n2)
		{
			if (L[i] <= R[j])
			{
				pData[k] = L[i];
				i++;
			}
			else
			{
				pData[k] = R[j];
				j++;
			}
			k++;
		}

		// Copy any remaining elements of the left and right subarrays
		while (i < n1)
		{
			pData[k] = L[i];
			i++;
			k++;
		}
		while (j < n2)
		{
			pData[k] = R[j];
			j++;
			k++;
		}

		free(L);
		free(R);
    }
}


void insertionSort(int* pData, int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = pData[i];
        int j = i - 1;

        // Move elements that are greater than the key to one position ahead of their current position
        while (j >= 0 && pData[j] > key)
        {
            pData[j + 1] = pData[j];
            j--;
        }

        pData[j + 1] = key;
    }
}


void bubbleSort(int* pData, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int swapped = 0;

        for (int j = 0; j < n - i - 1; j++)
        {
            if (pData[j] > pData[j + 1])
            {
				int temp = pData[j];
				pData[j] = pData[j + 1];
				pData[j + 1] = temp;
                swapped = 1;
            }
        }

        if (swapped == 0)
            break;
    }
}


void selectionSort(int* pData, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;

        // Find the index of the minimum element in the unsorted part of the array
        for (int j = i + 1; j < n; j++)
        {
            if (pData[j] < pData[min_idx])
                min_idx = j;
        }

        // Swap the minimum element with the first element of the unsorted part
        if (min_idx != i)
        {
			int temp = pData[i];
			pData[i] = pData[min_idx];
			pData[min_idx] = temp;
        }
    }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);

		for (int i = 0; i < dataSz; ++i)
		{
			fscanf(inFile, "%d\n", *ppData + i);
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}


int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0; i<3; ++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = malloc(sizeof(int) * dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.9lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}