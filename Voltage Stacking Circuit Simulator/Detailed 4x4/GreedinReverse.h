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



void GreedinReverse();
void merge(double arr[], int l, int m, int r);
void mergeSort(double arr[], int l, int r);
void printArray(double A[], int size);
