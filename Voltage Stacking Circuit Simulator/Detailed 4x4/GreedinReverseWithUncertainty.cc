#include "GreedinReverse.h"
#include "GreedinReverseWithUncertainty.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include <time.h>


using namespace std;


void GreedinReverseWithUncertainty(int range)
{
  //set the uncertainty for the power trace
  double uncertainty = 0;

  extern string Current_Load[];
  extern double Estimate_Current_Load[];
  double arr[18];
  double real_output[18];
  double estimate_output[18];
  double real_layer_1 = 0;
  double real_layer_2 = 0;
  double real_layer_3 = 0;
  double estimate_layer_1 = 0;
  double estimate_layer_2 = 0;
  double estimate_layer_3 = 0;

  const char* load;
  const char* estimate_load;

  struct Power Core_Power[18];

  srand((unsigned)time(NULL));

  for(int im = 0; im < 18; im++)
  {
    load = Current_Load[im].c_str();

    Core_Power[im].Real_Power = atof(load);
    Core_Power[im].Estimate_Power = Estimate_Current_Load[im]/range;
  }

  int arr_size = sizeof(Core_Power)/sizeof(Core_Power[0]);


//Output estimate and real power trace
  cout << "Before Schedule:" << endl;
  for(int i = 0; i < 18; i++)
  {
  cout<< "Estimate: " << Core_Power[i].Estimate_Power << "-----" << "Real: " << Core_Power[i].Real_Power << endl;
  }

  cout << "layer1: " << Core_Power[0].Real_Power + Core_Power[1].Real_Power + Core_Power[2].Real_Power + Core_Power[3].Real_Power + Core_Power[4].Real_Power + Core_Power[5].Real_Power << endl;
  cout << "layer2: " << Core_Power[0+6].Real_Power + Core_Power[1+6].Real_Power + Core_Power[2+6].Real_Power + Core_Power[3+6].Real_Power + Core_Power[4+6].Real_Power + Core_Power[5+6].Real_Power << endl;
  cout << "layer3: " << Core_Power[0+12].Real_Power + Core_Power[1+12].Real_Power + Core_Power[2+12].Real_Power + Core_Power[3+12].Real_Power + Core_Power[4+12].Real_Power + Core_Power[5+12].Real_Power << endl;




  UncertaintyMergeSort(Core_Power, 0, arr_size - 1);


  //compare and reverse
  for(int i = 0;i<6;i++)
  {

  if((estimate_layer_1<=estimate_layer_2)&&(estimate_layer_1<=estimate_layer_3))
    {
      real_output[i+0] = Core_Power[17-3*i].Real_Power;
      estimate_output[i+0] = Core_Power[17-3*i].Estimate_Power;
      real_layer_1 = real_layer_1 + real_output[i+0];
      estimate_layer_1 = estimate_layer_1 + estimate_output[i+0];

      if(estimate_layer_2 <= estimate_layer_3)
      {
        real_output[i+6] = Core_Power[16-3*i].Real_Power;
        estimate_output[i+6] = Core_Power[16-3*i].Estimate_Power;
        real_layer_2 = real_layer_2 + real_output[i+6];
        estimate_layer_2 = estimate_layer_2 + estimate_output[i+6];

        real_output[i+12] = Core_Power[15-3*i].Real_Power;
        estimate_output[i+12] = Core_Power[15-3*i].Estimate_Power;
        real_layer_3 = real_layer_3 + real_output[i+12];
        estimate_layer_3 = estimate_layer_3 + estimate_output[i+12];
      }
      else
      {
        real_output[i+6] = Core_Power[15-3*i].Real_Power;
        estimate_output[i+6] = Core_Power[15-3*i].Estimate_Power;
        real_layer_2 = real_layer_2 + real_output[i+6];
        estimate_layer_2 = estimate_layer_2 + estimate_output[i+6];

        real_output[i+12] = Core_Power[16-3*i].Real_Power;
        estimate_output[i+12] = Core_Power[16-3*i].Estimate_Power;
        real_layer_3 = real_layer_3 + real_output[i+12];
        estimate_layer_3 = estimate_layer_3 + estimate_output[i+12];
      }
    }



    else if((estimate_layer_2 <= estimate_layer_1)&&(estimate_layer_2 <= estimate_layer_3))
      {
        real_output[i+6] = Core_Power[17-3*i].Real_Power;
        estimate_output[i+6] = Core_Power[17-3*i].Estimate_Power;
        real_layer_2 = real_layer_2 + real_output[i+6];
        estimate_layer_2 = estimate_layer_2 + estimate_output[i+6];
        if(estimate_layer_1 <= estimate_layer_3)
        {
          real_output[i+0] = Core_Power[16-3*i].Real_Power;
          estimate_output[i+0] = Core_Power[16-3*i].Estimate_Power;
          real_layer_1 = real_layer_1 + real_output[i+0];
          estimate_layer_1 = estimate_layer_1 + estimate_output[i+0];

          real_output[i+12] = Core_Power[15-3*i].Real_Power;
          estimate_output[i+12] = Core_Power[15-3*i].Estimate_Power;
          real_layer_3 = real_layer_3 + real_output[i+12];
          estimate_layer_3 = estimate_layer_3 + estimate_output[i+12];
        }
        else
        {
          real_output[i+0] = Core_Power[15-3*i].Real_Power;
          estimate_output[i+0] = Core_Power[15-3*i].Estimate_Power;
          real_layer_1 = real_layer_1 + real_output[i+0];
          estimate_layer_1 = estimate_layer_1 + estimate_output[i+0];

          real_output[i+12] = Core_Power[16-3*i].Real_Power;
          estimate_output[i+12] = Core_Power[16-3*i].Estimate_Power;
          real_layer_3 = real_layer_3 + real_output[i+12];
          estimate_layer_3 = estimate_layer_3 + estimate_output[i+12];
        }
      }


      else
        {
          real_output[i+12] = Core_Power[17-3*i].Real_Power;
          estimate_output[i+12] = Core_Power[17-3*i].Estimate_Power;
          real_layer_3 = real_layer_3 + real_output[i+12];
          estimate_layer_3 = estimate_layer_3 + estimate_output[i+12];
          if(estimate_layer_1 <= estimate_layer_2)
          {
            real_output[i+0] = Core_Power[16-3*i].Real_Power;
            estimate_output[i+0] = Core_Power[16-3*i].Estimate_Power;
            real_layer_1 = real_layer_1 + real_output[i+0];
            estimate_layer_1 = estimate_layer_1 + estimate_output[i+0];

            real_output[i+6] = Core_Power[15-3*i].Real_Power;
            estimate_output[i+6] = Core_Power[15-3*i].Estimate_Power;
            real_layer_2 = real_layer_2 + real_output[i+6];
            estimate_layer_2 = estimate_layer_2 + estimate_output[i+6];
          }
          else
          {
            real_output[i+0] = Core_Power[15-3*i].Real_Power;
            estimate_output[i+0] = Core_Power[15-3*i].Estimate_Power;
            real_layer_1 = real_layer_1 + real_output[i+0];
            estimate_layer_1 = estimate_layer_1 + estimate_output[i+0];

            real_output[i+6] = Core_Power[16-3*i].Real_Power;
            estimate_output[i+6] = Core_Power[16-3*i].Estimate_Power;
            real_layer_2 = real_layer_2 + real_output[i+6];
            estimate_layer_2 = estimate_layer_2 + estimate_output[i+6];
          }
        }

  } //for end









  for(int i = 0; i < 18; i++)
  {
  stringstream sss;
  sss << real_output[i];
  Current_Load[i] = sss.str();
  }



  cout << "After Schedule:" << endl;
  for(int i = 0; i < 18; i++)
  {
  cout<< "Estimate: " << estimate_output[i] << "-----" << "Real: " << real_output[i] << endl;
  }

  cout << "layer1: " << real_output[0] + real_output[1] + real_output[2] + real_output[3] + real_output[4] + real_output[5] << endl;
  cout << "layer2: " << real_output[6] + real_output[7] + real_output[8] + real_output[9] + real_output[10] + real_output[11] << endl;
  cout << "layer3: " << real_output[12] + real_output[13] + real_output[14] + real_output[15] + real_output[16] + real_output[17] << endl;








}



void UncertaintyMergeSort(struct Power Core_Power[], int l, int r)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for
		// large l and h
		int m = l+(r-l)/2;

		// Sort first and second halves
		UncertaintyMergeSort(Core_Power, l, m);
		UncertaintyMergeSort(Core_Power, m+1, r);

		UncertaintyMerge(Core_Power, l, m, r);
	}
}

void UncertaintyMerge(struct Power Core_Power[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp struct */
	struct Power L[n1], R[n2];

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = Core_Power[l + i];
	for (j = 0; j < n2; j++)
		R[j] = Core_Power[m + 1+ j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = l; // Initial index of merged subarray
	while (i < n1 && j < n2)
	{
		if (L[i].Estimate_Power <= R[j].Estimate_Power)
		{
			Core_Power[k] = L[i];
			i++;
		}
		else
		{
			Core_Power[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	are any */
	while (i < n1)
	{
		Core_Power[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	are any */
	while (j < n2)
	{
		Core_Power[k] = R[j];
		j++;
		k++;
	}
}
