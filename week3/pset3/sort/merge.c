///THERE ARE BUGS, NEED TO FIX AND RENAME! 



#include <stdio.h>
#include <cs50.h>
#include <math.h>

int mergeSort(int arr[], int start, int end);
int Merge(int arr1, int arr2);
int Merge(int arr1, int n1, int arr2, int n2);

int main(void)
{
	int arr[9] = {5,3,2,4,1,6,8,9,7};
	arr = mergeSort(arr, 0, 8);
	for (int i = 0; i < 9; i++)
	{
		printf("%i, ", arr[i]);
	}
	return 0;
}
int mergeSort(int arr[], int start, int end)
{
	if (end - start == 0)
		return 0;
	else
	{
		int half = round((start + end)/2);

		int arr1[] = mergeSort(arr, start, half);
		int arr2[] = mergeSort(arr, half + 1, end);
		return Merge(arr, arr1, half - start + 1, arr2, end - half);
	}
}

int Merge(int arr, int arr1, int n1, int arr2, int n2)
{ 
	int k = 0;
	for (int i = 0, j = 0; i < n1 || j < n2; i++, j++)
	{
		if (i == n1)
		{
			arr[k] = n2[j];
		}
		else if (j == n2)
		{
			arr[k] = n1[i];
		}
		else if (n1[i] < n2[j])
			arr[k] = n1[i];
		else
			arr[k] = n2[j];
		k++;
	}
	//return arr;
}
