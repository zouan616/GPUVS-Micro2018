#include "GreedinReverse.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

using namespace std;


void GreedinReverse()
{
  extern string Current_Load[];
  double arr[18];
  double output[18];
  double layer_1 = 0;
  double layer_2 = 0;
  double layer_3 = 0;
  const char* load;
  for(int i = 0; i < 18; i++)
  {
    load = Current_Load[i].c_str();
    arr[i] = atof(load);
  }

  int arr_size = sizeof(arr)/sizeof(arr[0]);

  printf("Given Power Trace is \n");
  printArray(arr, arr_size);

  mergeSort(arr, 0, arr_size - 1);


  layer_1 = 0;
  layer_2 = 0;
  layer_3 = 0;


  //compare and reverse
  for(int i = 0;i<6;i++)
  {

  if((layer_1<=layer_2)&&(layer_1<=layer_3))
    {
      output[i+0] = arr[17-3*i];
      layer_1 = layer_1 + output[i+0];
      if(layer_2 <= layer_3)
      {
        output[i+6] = arr[16-3*i];
        layer_2 = layer_2 + output[i+6];
        output[i+12] = arr[15-3*i];
        layer_3 = layer_3 + output[i+12];
      }
      else
      {
        output[i+6] = arr[15-3*i];
        layer_2 = layer_2 + output[i+6];
        output[i+12] = arr[16-3*i];
        layer_3 = layer_3 + output[i+12];
      }
    }



    else if((layer_2 <= layer_1)&&(layer_2 <= layer_3))
      {
        output[i+6] = arr[17-3*i];
        layer_2 = layer_2 + output[i+6];
        if(layer_1 <= layer_3)
        {
          output[i+0] = arr[16-3*i];
          layer_1 = layer_1 + output[i+0];
          output[i+12] = arr[15-3*i];
          layer_3 = layer_3 + output[i+12];
        }
        else
        {
          output[i+0] = arr[15-3*i];
          layer_1 = layer_1 + output[i+0];
          output[i+12] = arr[16-3*i];
          layer_3 = layer_3 + output[i+12];
        }
      }


      else
        {
          output[i+12] = arr[17-3*i];
          layer_3 = layer_3 + output[i+12];
          if(layer_1 <= layer_2)
          {
            output[i+0] = arr[16-3*i];
            layer_1 = layer_1 + output[i+0];
            output[i+6] = arr[15-3*i];
            layer_2 = layer_2 + output[i+6];
          }
          else
          {
            output[i+0] = arr[15-3*i];
            layer_1 = layer_1 + output[i+0];
            output[i+6] = arr[16-3*i];
            layer_2 = layer_2 + output[i+6];
          }
        }

  }





  for(int i = 0; i < 18; i++)
  {
  stringstream sss;
  sss << output[i];
  Current_Load[i] = sss.str();
  }

  printf("\nSorted Power Trace is \n");
  printArray(output, arr_size);

  cout << "" << endl;
  cout << "Layer1: " << layer_1 << endl;
  cout << "Layer2: " << layer_2 << endl;
  cout << "Layer3: " << layer_3 << endl;
  cout << "" << endl;


}


/* C program for Merge Sort */

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(double arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	double L[n1], R[n2];

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1+ j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = l; // Initial index of merged subarray
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	are any */
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	are any */
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}

/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(double arr[], int l, int r)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for
		// large l and h
		int m = l+(r-l)/2;

		// Sort first and second halves
		mergeSort(arr, l, m);
		mergeSort(arr, m+1, r);

		merge(arr, l, m, r);
	}
}

/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(double A[], int size)
{
	int i;
	for (i=0; i < size; i++)
		printf("%lf ", A[i]);
	printf("\n");
}

/* Driver program to test above functions */
//int main()
//{
//	int arr[] = {12, 11, 13, 5, 6, 7, 1, 4};
//	int arr_size = sizeof(arr)/sizeof(arr[0]);

//	printf("Given array is \n");
//	printArray(arr, arr_size);

//	mergeSort(arr, 0, arr_size - 1);

//	printf("\nSorted array is \n");
//	printArray(arr, arr_size);
//	return 0;
//}
