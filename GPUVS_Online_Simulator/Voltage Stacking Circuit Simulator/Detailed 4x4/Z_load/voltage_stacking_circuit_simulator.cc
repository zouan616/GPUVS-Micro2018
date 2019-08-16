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
#include "GreedinReverse.h"
#include "GreedinReverseWithUncertainty.h"
#include "GetSMPower.h"
#include <fstream>


using namespace std;

typedef void *  funptr_t;
funptr_t dlsym (void *, const char *);

#define true 1
#define false 0
//#define RTLD_LAZY	1	/* lazy function call binding */
//#define RTLD_NOW	2	/* immediate function call binding */
//#define RTLD_GLOBAL	4	/* symbols in this dlopen'ed obj are visible to other dlopen'ed objs */


funptr_t ngSpice_Init_handle = NULL;
funptr_t ngSpice_Command_handle = NULL;
funptr_t ngSpice_Circ_handle = NULL;
funptr_t ngSpice_CurPlot_handle = NULL;
funptr_t ngSpice_AllVecs_handle = NULL;
funptr_t ngSpice_GVI_handle = NULL;


/* callback functions used by ngspice */
int ng_getchar(char* outputreturn, int ident, void* userdata);

int ng_getstat(char* outputreturn, int ident, void* userdata);

int ng_thread_runs(bool noruns, int ident, void* userdata);

bool no_bg = true;
bool not_yet = true;
bool will_unload = false;
int cieq(const char *p, const char *s);
int vecgetnumber = 0;
double v2dat;
static bool has_break = false;

int i;
char ** circarray;
char **vecarray;

ControlledExit ng_exit;
SendData ng_data;
SendInitData ng_initdata;


void * ngdllhandle = NULL;

string powertrace;
string estimate_powertrace;
string temp;
string Current_Load[18];
double Estimate_Current_Load[18];


int main(){

    int cycle_length = 100;



    cout << "Input Power Trace File Name:" <<endl;
    //cin >> powertrace;
    powertrace = "BACKP1.txt";
    ifstream infile(powertrace.c_str());
    estimate_powertrace = "BACKP1.txt";
    ifstream estimate_infile(estimate_powertrace.c_str());


    int *ret;


    //open handle
    const char *loadstring = "libngspice.so";
    char *errmsg = NULL;
    char *curplot;
    ngdllhandle = dlopen(loadstring, RTLD_LAZY);
    errmsg = dlerror();
    if (errmsg)
        printf("%s\n", errmsg);string temp;


    if (ngdllhandle)
       printf("ngspice dynamic link library loaded successfully\n");
    else {
       printf("ngspice dynamic link library not loaded !\n");
       exit(1);
    }

    ngSpice_Init_handle = dlsym(ngdllhandle, "ngSpice_Init");
    errmsg = dlerror();
    if (errmsg)
        cout << errmsg <<endl;
    ngSpice_Command_handle = dlsym(ngdllhandle, "ngSpice_Command");
    errmsg = dlerror();
    if (errmsg)
        cout << errmsg <<endl;
    ngSpice_CurPlot_handle = dlsym(ngdllhandle, "ngSpice_CurPlot");
    errmsg = dlerror();
    if (errmsg)
        cout << errmsg <<endl;
    ngSpice_AllVecs_handle = dlsym(ngdllhandle, "ngSpice_AllVecs");
    errmsg = dlerror();
    if (errmsg)
        cout << errmsg <<endl;
    ngSpice_GVI_handle = dlsym(ngdllhandle, "ngGet_Vec_Info");
    errmsg = dlerror();
    if (errmsg)
        cout << errmsg <<endl;



    ret = ((int * (*)(SendChar*, SendStat*, ControlledExit*, SendData*, SendInitData*, BGThreadRunning*, void*)) ngSpice_Init_handle)(ng_getchar, ng_getstat, ng_exit, NULL, ng_initdata, ng_thread_runs, NULL);

    //read in circuit
    //ret = ((int * (*)(const char*)) ngSpice_Command_handle)("GPUVoltageStackingPDN.cir");
    //ret = ((int * (*)(const char*)) ngSpice_Command_handle)("OnChipPDN.cir");
    ret = ((int * (*)(const char*)) ngSpice_Command_handle)("GPUVoltageStackingPDN.cir");


    //set simulation pause time, load current update time i (unit 1ps)
    string a,c;
    int stop_point = 8000;
    for(int k= 1; k< stop_point; k++)
    {
    a = "stop when time = ";
    c = "p";
    int tep;
    tep = 1500*k;    //curent load update time 1.5ns
    stringstream ss;
    ss << tep;
    string b = ss.str();
    a+=b;
    a+=c;
    const char* stop_command = a.c_str();
    ret = ((int * (*)(const char*)) ngSpice_Command_handle)(stop_command);
    }


    //start simulation
    ret = ((int * (*)(const char*)) ngSpice_Command_handle)("bg_run");

    int i;

    //upload load current and resume
    for(i = 1; i<stop_point; i++)
    {

    //output 100-1
    if(i == stop_point-1)
    {
      //Stop back thread simulaton
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("stop");
      //Set output file format
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("set filetype=ascii");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM1 V(1000000001)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM2 V(1000002001)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM3 V(1000004001)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM4 V(1002000001)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM5 V(1002002001)");


      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM6 V(1000000002)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM7 V(1000002002)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM8 V(1000004002)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM9 V(1002000002)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM10 V(1002002002)");


      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM11 V(1000000003)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM12 V(1000002003)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM13 V(1000004003)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM14 V(1002000003)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM15 V(1002002003)");

      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata global V(100)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata gnd1 V(1000000004)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata gnd2 V(1000002004)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata gnd3 V(1000004004)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata gnd3 V(1002000004)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata gnd4 V(1002002004)");


      printf("Simulation finish!!!!!!!!!\n");
      exit(1);
    }

    //cout << i << endl;

      for (;;){
      usleep (1000);
        if (no_bg)
        {
        break;
        }
      }
// Read in the Estimate Power trace
// i-1 makes sure the estimation before real value
        if((i-1)%cycle_length == 0)
      {

        int cycle = 0;
        for(int in = 0; in < 18; in++)
        {
          Estimate_Current_Load[in] = 0;
        }

        while(cycle < cycle_length)
        {
          string estimate_temp;
          getline(estimate_infile,estimate_temp);
          char estimate_s[1024];
          int estimate_m;
          for( estimate_m=0;estimate_m<estimate_temp.length();estimate_m++)
          {
              estimate_s[estimate_m] = estimate_temp[estimate_m];
          }

          const char *estimate_d = " ,*";
          char *estimate_p;
          estimate_p = strtok(estimate_s,estimate_d);
          int estimate_outputloadnum = 0;

            while(estimate_outputloadnum < 18)
            {
            //printf("%s\n",p);
            //double a = atof(p);

            Estimate_Current_Load[estimate_outputloadnum] = Estimate_Current_Load[estimate_outputloadnum] + atof(estimate_p);
            estimate_outputloadnum = estimate_outputloadnum + 1;
            estimate_p=strtok(NULL,estimate_d);
            }

            cycle = cycle + 1;
         }

      }


// Read in the power trace
      string temp;
      getline(infile,temp);
      char s[1024];
      int m;
      for( m=0;m<temp.length();m++)
      {
          s[m] = temp[m];
      }
      const char *d = " ,*";
      char *p;
      p = strtok(s,d);
      int outputloadnum = 0;

      //while(outputloadnum < 18) //VS
      while(outputloadnum < 18)  //Single layer
      {
          //printf("%s\n",p);
          //double a = atof(p);

          Current_Load[outputloadnum] = p;
          outputloadnum = outputloadnum + 1;
          p=strtok(NULL,d);
      }

    //Optimization the Power load
    //GreedinReverseWithUncertainty(cycle_length);
    GetSMPower();
    //GreedinReverseWithUncertainty(cycle_length);
    //Allocate the Power
    string alter[18];
    // 1st layer
    alter[0] = "alter r1000000001_1000000002 = ";
    alter[1] = "alter r1000002001_1000002002 = ";
    alter[2] = "alter r1000004001_1000004002 = ";
    alter[3] = "alter r1002000001_1002000002 = ";
    alter[4] = "alter r1002002001_1002002002 = ";
    alter[5] = "alter r1002004001_1002004002 = ";

    alter[6] = "alter r1000000002_1000000003 = ";
    alter[7] = "alter r1000002002_1000002003 = ";
    alter[8] = "alter r1000004002_1000004003 = ";
    alter[9] = "alter r1002000002_1002000003 = ";
    alter[10] = "alter r1002002002_1002002003 = ";
    alter[11] = "alter r1002004002_1002004003 = ";

    alter[12] = "alter r1000000003_1000000004 = ";
    alter[13] = "alter r1000002003_1000002004 = ";
    alter[14] = "alter r1000004003_1000004004 = ";
    alter[15] = "alter r1002000003_1002000004 = ";
    alter[16] = "alter r1002002003_1002002004 = ";
    alter[17] = "alter r1002004003_1002004004 = ";

    //string cc = "A";

    stringstream load;



    //for (int n = 0; n < 18; n++) //VS
    for (int n = 0; n < 18; n++) // single layer
    {

    float resistance;
    float current;
    current = atof(Current_Load[n].c_str());
    cout << "--------------------------read in power： " << current << endl;
    //CHECK that den cannot be zero
    if(current < 0.001)
    {
      resistance = 1000;
    }
    else
    {
    resistance = 1/atof(Current_Load[n].c_str());
    }



    ostringstream oss;
    oss << resistance;
    string bb = oss.str();
    cout << "--------------------resistance:" << resistance << endl;


    string aa = alter[n];
    aa+=bb;

    const char* alter = aa.c_str();
    cout << n << ": " << alter << endl;
    ret = ((int * (*)(const char*)) ngSpice_Command_handle)(alter);

    }




    //resume simulation
    ret = ((int * (*)(const char*)) ngSpice_Command_handle)("resume");
    }

return 1;
}






















int ng_getchar(char* outputreturn, int ident, void* userdata)
{
    printf("%s\n", outputreturn);
    return 0;
}

/* Callback function called from bg thread in ngspice to transfer
   simulation status (type and progress in percent. */
int ng_getstat(char* outputreturn, int ident, void* userdata)
{
    printf("%s\n", outputreturn);
    return 0;
}

/* Callback function called from ngspice upon starting (returns true) or
  leaving (returns false) the bg thread. */
int ng_thread_runs(bool noruns, int ident, void* userdata)
{
    no_bg = noruns;
    if (noruns)
        printf("bg not running\n");
    else
        printf("bg running\n");

    return 0;
}

int ng_exit(int exitstatus, bool immediate, bool quitexit, int ident, void* userdata)
{

    if(quitexit) {
        printf("DNote: Returned from quit with exit status %d\n", exitstatus);
    }
    if(immediate) {
        printf("DNote: Unload ngspice\n");
        ((int * (*)(const char*)) ngSpice_Command_handle)("bg_pstop");

        dlclose(ngdllhandle);
    }

    else {
        printf("DNote: Prepare unloading ngspice\n");
        will_unload = true;
    }

    return exitstatus;

}


/* Callback function called from bg thread in ngspice once per accepted data point */
int ng_data(pvecvaluesall vdata, int numvecs, int ident, void* userdata)
{
    int *ret;

    v2dat = vdata->vecsa[vecgetnumber]->creal;
    if (!has_break && (v2dat > 0.5)) {
    /* using signal SIGTERM by sending to main thread, alterp() then is run from the main thread,
      (not on Windows though!)  */

        has_break = true;
    /* leave bg thread for a while to allow halting it from main */

        usleep (100000);

//        ret = ((int * (*)(char*)) ngSpice_Command_handle)("bg_halt");
    }
    return 0;
}

int ng_initdata(pvecinfoall intdata, int ident, void* userdata)
{
    int i;
    int vn = intdata->veccount;
    for (i = 0; i < vn; i++) {
        printf("Vector: %s\n", intdata->vecs[i]->vecname);
        /* find the location of V(2) */
        if (cieq(intdata->vecs[i]->vecname, "V(2)"))
            vecgetnumber = i;
    }
    return 0;
}

int cieq(const char *p, const char *s)
{
    while (*p) {
        if ((isupper(*p) ? tolower(*p) : *p) !=
            (isupper(*s) ? tolower(*s) : *s))
            return(false);
        p++;
        s++;
    }
    return (*s ? false : true);
}
