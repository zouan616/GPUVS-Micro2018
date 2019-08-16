#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#include "sharedspice.h"
#include <dlfcn.h> /* to load libraries*/
#include <unistd.h>
#include <ctype.h>
#include <iostream>
#include <sstream>



void GreedinReverseWithUncertainty(int range);
void UncertaintyMergeSort(struct Power Core_Power[], int l, int r);
void UncertaintyMerge(struct Power Core_Power[], int l, int m, int r);

struct Power
{
  double Estimate_Power;
  double Real_Power;
};
