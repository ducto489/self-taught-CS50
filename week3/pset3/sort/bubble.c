#include <stdio.h>
#include <cs50.h>

int main(void)
{
	int arr[] = {5,3,2,4,1,6,8,9,7};
	int n = 9;
	do
	{
		int nSwap = 0;
		for (int i = 0; i < n - 1; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				int fake = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1 ] = fake;
				nSwap++;
			}
			//n--;
		}
		n--;
		if (nSwap == 0)
		{
		    break;
		}
	} while (true);
	for (int i = 0; i < 9; i++)
	{
		printf("%i, ", arr[i]);
	}
	return 0;
}