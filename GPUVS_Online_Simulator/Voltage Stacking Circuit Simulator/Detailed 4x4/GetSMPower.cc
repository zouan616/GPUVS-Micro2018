#include "GetSMPower.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include <time.h>


using namespace std;

// reorder
void GetSMPower0()
{
extern string Current_Load[];
Current_Load[0] = Current_Load[0];
Current_Load[1] = "0";
Current_Load[2] = "0";
Current_Load[3] = "0";
Current_Load[4] = "0";
Current_Load[5] = "0";

Current_Load[6] = "0";
Current_Load[7] = "0";
Current_Load[8] = "0";
Current_Load[9] = "0";
Current_Load[10] = "0";
Current_Load[11] = "0";

Current_Load[12] = "0";
Current_Load[13] = "0";
Current_Load[14] = "0";
Current_Load[15] = "0";
Current_Load[16] = "0";
Current_Load[17] = "0";
}


void GetSMPower()
{
extern string Current_Load[];

Current_Load[16] = Current_Load[14];
Current_Load[15] = Current_Load[13];
Current_Load[14] = Current_Load[12];
Current_Load[13] = Current_Load[11];
Current_Load[12] = Current_Load[10];

Current_Load[10] = Current_Load[9];
Current_Load[9] = Current_Load[8];
Current_Load[8] = Current_Load[7];
Current_Load[7] = Current_Load[6];
Current_Load[6] = Current_Load[5];


Current_Load[5] = "0";
Current_Load[11] = "0";
Current_Load[17] = "0";

}
