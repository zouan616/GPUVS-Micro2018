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
#include "GetSMPower.h"
#include <fstream>

#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>



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

string temp;
string temp2;

int i;
char ** circarray;
char **vecarray;

ControlledExit ng_exit;
SendData ng_data;
SendInitData ng_initdata;


void * ngdllhandle = NULL;

string powertrace;
string supply_voltage_trace;

string Current_Load[16];
string supply_voltage[16];
float supply_voltage_float[16];

float measure_voltage[16];

int main(){

    int date_update_frequency = 1;
    int feedback_frequency = 10;


    int cycle_length = 100;








    cout << "Input Power Trace File Name:" <<endl;

    powertrace = "backp_original.txt";
    ifstream infile(powertrace.c_str());
    supply_voltage_trace = "original_voltage.txt";
    ifstream infile2(supply_voltage_trace.c_str());

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
    //ret = ((int * (*)(const char*)) ngSpice_Command_handle)("OneLayerGPUPDN.cir");
    //ret = ((int * (*)(const char*)) ngSpice_Command_handle)("4x4GPUVSPDN.cir");
    ret = ((int * (*)(const char*)) ngSpice_Command_handle)("4x4GPUVSPDN_LDO.cir");


    //set simulation pause time, load current update time i (unit 1ps)
    string a,c;
    int stop_point = 6000;
    for(int k = 1; k< stop_point+100; k++)
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
    int round = 0;
    //upload load current and resume


    for(i = 1; i < stop_point + 100; i++)
    {
      /*
      if((i%500)==0)
      {
        getline(infile2,temp2);


        char ssssss[1024];
        int mmmmmm;
        for( mmmmmm=0;mmmmmm<temp2.length();mmmmmm++)
        {
            ssssss[mmmmmm] = temp2[mmmmmm];
        }
        const char *dddddd = " ,*";
        char *pppppp;
        pppppp = strtok(ssssss,dddddd);
        int outputloadnum2 = 0;


        while(outputloadnum2 < 16)  //Single layer
        {
            //printf("%s\n",p);
            //Divide workload to 6 cores
            double aaaaaa = atof(pppppp);

            supply_voltage_float[outputloadnum2] = aaaaaa;

            outputloadnum2 = outputloadnum2 + 1;
            pppppp=strtok(NULL,dddddd);
        }

        string alter_voltage[5];

        // On-Chip VR
        alter_voltage[0] = "alter vdd dc = ";
        alter_voltage[1] = "altermod switch4 vt = ";
        alter_voltage[2] = "altermod switch3 vt = ";
        alter_voltage[3] = "altermod switch2 vt = ";
        alter_voltage[4] = "altermod switch1 vt = ";

        stringstream zzzzzz0;
        string alter_voltage_value[5];
        //zzzzzz0 << supply_voltage_float[0] + supply_voltage_float[4] + supply_voltage_float[8] + supply_voltage_float[12] + 0.2;
        zzzzzz0 << 4.2;
        alter_voltage_value[0] = zzzzzz0.str();
        stringstream zzzzzz1;
        //zzzzzz1 << supply_voltage_float[0] + supply_voltage_float[4] + supply_voltage_float[8] + supply_voltage_float[12] + 1;
        zzzzzz1 << 4.275;
        alter_voltage_value[1] = zzzzzz1.str();
        stringstream zzzzzz2;
        //zzzzzz2 << supply_voltage_float[4] + supply_voltage_float[8] + supply_voltage_float[12] + 0.25;
        zzzzzz2 << 3.25;
        alter_voltage_value[2] = zzzzzz2.str();
        stringstream zzzzzz3;
        //zzzzzz3 << supply_voltage_float[8] + supply_voltage_float[12] + 0.225;
        zzzzzz3 << 2.225;
        alter_voltage_value[3] = zzzzzz3.str();
        stringstream zzzzzz4;
        //zzzzzz4 << supply_voltage_float[12] + 0.2;
        zzzzzz4 << 1.2;
        alter_voltage_value[4] = zzzzzz4.str();
        string cccccc = "V";
        stringstream load2;

        //if((i%75)==0)
        //{
        for (int n = 0; n < 5; n++) //VS
        {
        string bbbbbb = alter_voltage_value[n];
        string aaaaaa = alter_voltage[n];
        aaaaaa+=bbbbbb;
        aaaaaa+=cccccc;
        const char* alter2 = aaaaaa.c_str();
        //cout << "Supply voltage: " << n << ": " << alter2 << endl;
        ret = ((int * (*)(const char*)) ngSpice_Command_handle)(alter2);
        }
        //}



        // Off-Chip VR
        alter_voltage[0] = "alter vdd dc = ";
        alter_voltage[1] = "altermod switch4_off vt = ";
        alter_voltage[2] = "altermod switch3_off vt = ";
        alter_voltage[3] = "altermod switch2_off vt = ";
        alter_voltage[4] = "altermod switch1_off vt = ";

        zzzzzz0.str("");
        zzzzzz1.str("");
        zzzzzz2.str("");
        zzzzzz3.str("");
        zzzzzz4.str("");

        //zzzzzz0 << supply_voltage_float[0] + supply_voltage_float[4] + supply_voltage_float[8] + supply_voltage_float[12] + 0.2;
        zzzzzz0 << 4.2;
        alter_voltage_value[0] = zzzzzz0.str();

        //zzzzzz1 << supply_voltage_float[0] + supply_voltage_float[4] + supply_voltage_float[8] + supply_voltage_float[12] + 0.25;
        zzzzzz1 << 4.275;
        alter_voltage_value[1] = zzzzzz1.str();

        //zzzzzz2 << supply_voltage_float[4] + supply_voltage_float[8] + supply_voltage_float[12] + 0.225;
        zzzzzz2 << 3.25;
        alter_voltage_value[2] = zzzzzz2.str();

        //zzzzzz3 << supply_voltage_float[8] + supply_voltage_float[12] + 0.2;
        zzzzzz3 << 2.225;
        alter_voltage_value[3] = zzzzzz3.str();

        //zzzzzz4 << supply_voltage_float[12] + 0.175;
        zzzzzz0 << 1.2;
        alter_voltage_value[4] = zzzzzz4.str();


        //if((i%333)==0)
        //{
        for (int n = 0; n < 5; n++) //VS
        {
        string bbbbbb = alter_voltage_value[n];
        string aaaaaa = alter_voltage[n];
        aaaaaa+=bbbbbb;
        aaaaaa+=cccccc;
        const char* alter2 = aaaaaa.c_str();
        cout << "Supply voltage: " << n << ": " << alter2 << endl;
        ret = ((int * (*)(const char*)) ngSpice_Command_handle)(alter2);
        }
        //}



      }
      */




    /*
    if((i%feedback_frequency)==0)
    {

    ret = ((int * (*)(const char*)) ngSpice_Command_handle)("set filetype=ascii");
    //ret = ((int * (*)(const char*)) ngSpice_Command_handle)("set option numdgt = 4");
    ret = ((int * (*)(const char*)) ngSpice_Command_handle)("let n = length(time)");

    ret = ((int * (*)(const char*)) ngSpice_Command_handle)("print V(rc1)[n-1] > SM1_Voltage");
    ret = ((int * (*)(const char*)) ngSpice_Command_handle)("print V(rc2)[n-1] > SM2_Voltage");
    ret = ((int * (*)(const char*)) ngSpice_Command_handle)("print V(rc3)[n-1] > SM3_Voltage");
    ret = ((int * (*)(const char*)) ngSpice_Command_handle)("print V(rc4)[n-1] > SM4_Voltage");

    ret = ((int * (*)(const char*)) ngSpice_Command_handle)("print V(rc5)[n-1] > SM5_Voltage");
    ret = ((int * (*)(const char*)) ngSpice_Command_handle)("print V(rc6)[n-1] > SM6_Voltage");
    ret = ((int * (*)(const char*)) ngSpice_Command_handle)("print V(rc7)[n-1] > SM7_Voltage");
    ret = ((int * (*)(const char*)) ngSpice_Command_handle)("print V(rc8)[n-1] > SM8_Voltage");

    ret = ((int * (*)(const char*)) ngSpice_Command_handle)("print V(rc9)[n-1] > SM9_Voltage");
    ret = ((int * (*)(const char*)) ngSpice_Command_handle)("print V(rc10)[n-1] > SM10_Voltage");
    ret = ((int * (*)(const char*)) ngSpice_Command_handle)("print V(rc11)[n-1] > SM11_Voltage");
    ret = ((int * (*)(const char*)) ngSpice_Command_handle)("print V(rc12)[n-1] > SM12_Voltage");

    ret = ((int * (*)(const char*)) ngSpice_Command_handle)("print V(rc13)[n-1] > SM13_Voltage");
    ret = ((int * (*)(const char*)) ngSpice_Command_handle)("print V(rc14)[n-1] > SM14_Voltage");
    ret = ((int * (*)(const char*)) ngSpice_Command_handle)("print V(rc15)[n-1] > SM15_Voltage");
    ret = ((int * (*)(const char*)) ngSpice_Command_handle)("print V(rc16)[n-1] > SM16_Voltage");

    string SM_Voltage[16];
    SM_Voltage[0] = "SM1_Voltage";
    SM_Voltage[1] = "SM2_Voltage";
    SM_Voltage[2] = "SM3_Voltage";
    SM_Voltage[3] = "SM4_Voltage";
    SM_Voltage[4] = "SM5_Voltage";
    SM_Voltage[5] = "SM6_Voltage";
    SM_Voltage[6] = "SM7_Voltage";
    SM_Voltage[7] = "SM8_Voltage";
    SM_Voltage[8] = "SM9_Voltage";
    SM_Voltage[9] = "SM10_Voltage";
    SM_Voltage[10] = "SM11_Voltage";
    SM_Voltage[11] = "SM12_Voltage";
    SM_Voltage[12] = "SM13_Voltage";
    SM_Voltage[13] = "SM14_Voltage";
    SM_Voltage[14] = "SM15_Voltage";
    SM_Voltage[15] = "SM16_Voltage";


    char ss[1024];
    int mm;
    for(int k=0;k<16;k++)
    {
        ifstream ReadSMVoltage(SM_Voltage[k].c_str());
        getline(ReadSMVoltage,temp);
        ReadSMVoltage.close();
        ReadSMVoltage.clear();

        for( mm=0;mm<temp.length();mm++)
        {
            ss[mm] = temp[mm];
        }

        //cout << "ss:" << ss << endl;

        const char *dd = "= ";
        char *pp;
        pp = strtok(ss,dd);
        pp = strtok(NULL,dd);

        measure_voltage[k] = atof(pp);
        if(measure_voltage[k]>6)
        {
        measure_voltage[k] = 0.1 * measure_voltage[k];
        }

        //cout << "SM "<< k << " Voltage: " << measure_voltage[k] << endl;
     }


    }
    */

    //output 100-1
    if(i > stop_point)
    {
      //Stop back thread simulaton
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("stop");

      // VS Set output file format
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("set filetype=ascii");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("set option numdgt = 7");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM1 V(1000002001)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM2 V(1000008001)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM3 V(1000014001)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM4 V(1000020001)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM1_gnd V(1000002002)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM2_gnd V(1000008002)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM3_gnd V(1000014002)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM4_gnd V(1000020002)");

      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM5 V(1000002003)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM6 V(1000008003)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM7 V(1000014003)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM8 V(1000020003)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM5_gnd V(1000002004)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM6_gnd V(1000008004)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM7_gnd V(1000014004)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM8_gnd V(1000020004)");

      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM9 V(1000002005)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM10 V(1000008005)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM11 V(1000014005)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM12 V(1000020005)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM9_gnd V(1000002006)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM10_gnd V(1000008006)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM11_gnd V(1000014006)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM12_gnd V(1000020006)");

      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM13 V(1000002007)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM14 V(1000008007)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM15 V(1000014007)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM16 V(1000020007)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM13_gnd V(1000002008)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM14_gnd V(1000008008)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM15_gnd V(1000014008)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM16_gnd V(1000020008)");

      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM1_Voltage_1 V(1000002001)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM2_Voltage_1 V(1000008001)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM3_Voltage_1 V(1000014001)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM4_Voltage_1 V(1000020001)");

      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM5_Voltage_1 V(1000002003)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM6_Voltage_1 V(1000008003)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM7_Voltage_1 V(1000014003)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM8_Voltage_1 V(1000020003)");

      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM9_Voltage_1 V(1000002005)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM10_Voltage_1 V(1000008005)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM11_Voltage_1 V(1000014005)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM12_Voltage_1 V(1000020005)");

      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM13_Voltage_1 V(1000002007)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM14_Voltage_1 V(1000008007)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM15_Voltage_1 V(1000014007)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM16_Voltage_1 V(1000020007)");

      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM1_Voltage_2 V(rc1)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM2_Voltage_2 V(rc2)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM3_Voltage_2 V(rc3)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM4_Voltage_2 V(rc4)");

      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM5_Voltage_2 V(rc5)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM6_Voltage_2 V(rc6)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM7_Voltage_2 V(rc7)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM8_Voltage_2 V(rc8)");

      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM9_Voltage_2 V(rc9)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM10_Voltage_2 V(rc10)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM11_Voltage_2 V(rc11)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM12_Voltage_2 V(rc12)");

      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM13_Voltage_2 V(rc13)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM14_Voltage_2 V(rc14)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM15_Voltage_2 V(rc15)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata SM16_Voltage_2 V(rc16)");

      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test1_1 V(140011)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test1_1_gnd V(1400111)");

      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test1_2 V(140021)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test1_2_gnd V(1400211)");

      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test1_3 V(140031)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test1_3_gnd V(1400311)");

      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test1_4 V(140041)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test1_4_gnd V(1400411)");


      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test2_1 V(240011)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test2_1_gnd V(2400111)");

      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test2_2 V(240021)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test2_2_gnd V(2400211)");

      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test2_3 V(240031)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test2_3_gnd V(2400311)");

      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test2_4 V(240041)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test2_4_gnd V(2400411)");



      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test3_1 V(340011)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test3_1_gnd V(3400111)");

      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test3_2 V(340021)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test3_2_gnd V(3400211)");

      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test3_3 V(340031)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test3_3_gnd V(3400311)");

      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test3_4 V(340041)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test3_4_gnd V(3400411)");



      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test4_1 V(340011)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test4_1_gnd V(3400111)");

      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test4_2 V(340021)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test4_2_gnd V(3400211)");

      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test4_3 V(340031)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test4_3_gnd V(3400311)");

      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test4_4 V(340041)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test4_4_gnd V(3400411)");



      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test_off_2_1 V(540011)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test_off_2_1_gnd V(5400111)");

      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test_off_2_2 V(540021)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test_off_2_2_gnd V(5400211)");

      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test_off_2_3 V(540031)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test_off_2_3_gnd V(5400311)");

      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test_off_2_4 V(540041)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata R_test_off_2_4_gnd V(5400411)");

      printf("Simulation finish!!!!!!!!!\n");
      exit(0);
    }

    //cout << i << endl;

      for (;;){
        usleep (1000);
        if (no_bg)
        {
        break;
        }
      }








 // Read from the next cycle

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


      while(outputloadnum < 16)  //Single layer
      {
          //printf("%s\n",p);
          //Divide workload to 6 cores
          double a = atof(p);
          //a = a/6 + 0.5*supply_voltage_float[outputloadnum];
          //a = a*supply_voltage_float[outputloadnum]*supply_voltage_float[outputloadnum];
          if((i>2000)&&(4<=outputloadnum)&&(outputloadnum<8))
          {
          //cout << "label i: " << i << endl;
          a = 0.001;
          }

          //a = 1;

          //Power gating
          //if(i>3000)
          //{
          //if((outputloadnum<8)&&((outputloadnum>3)))
          //if(outputloadnum<4)
          //if((outputloadnum<8)&&((outputloadnum>3)))
          //{
          //a = 0.001;
          //}
          //}

          stringstream sss;
          sss << a;

          Current_Load[outputloadnum] = sss.str();

          outputloadnum = outputloadnum + 1;
          p=strtok(NULL,d);
      }

    cout << "The cycle " << "i:" << i << ":";
    for(int l = 0; l < 16; l++)
    {
    cout << Current_Load[l] << ",";
    }
    cout << endl;


    string alter[96];

    //VS
    //SM1
    alter[0] = "alter i1000000001_1000000002 dc = ";
    alter[1] = "alter i1000002001_1000002002 dc = ";
    alter[2] = "alter i1000004001_1000004002 dc = ";
    alter[3] = "alter i1002000001_1002000002 dc = ";
    alter[4] = "alter i1002002001_1002002002 dc = ";
    alter[5] = "alter i1002004001_1002004002 dc = ";

    //SM2
    alter[6] = "alter i1000006001_1000006002 dc = ";
    alter[7] = "alter i1000008001_1000008002 dc = ";
    alter[8] = "alter i1000010001_1000010002 dc = ";
    alter[9] = "alter i1002006001_1002006002 dc = ";
    alter[10] = "alter i1002008001_1002008002 dc = ";
    alter[11] = "alter i1002010001_1002010002 dc = ";

    //SM3
    alter[12] = "alter i1000012001_1000012002 dc = ";
    alter[13] = "alter i1000014001_1000014002 dc = ";
    alter[14] = "alter i1000016001_1000016002 dc = ";
    alter[15] = "alter i1002012001_1002012002 dc = ";
    alter[16] = "alter i1002014001_1002014002 dc = ";
    alter[17] = "alter i1002016001_1002016002 dc = ";

    //SM4
    alter[18] = "alter i1000018001_1000018002 dc = ";
    alter[19] = "alter i1000020001_1000020002 dc = ";
    alter[20] = "alter i1000022001_1000022002 dc = ";
    alter[21] = "alter i1002018001_1002018002 dc = ";
    alter[22] = "alter i1002020001_1002020002 dc = ";
    alter[23] = "alter i1002022001_1002022002 dc = ";

    //SM5
    alter[24] = "alter i1000000003_1000000004 dc = ";
    alter[25] = "alter i1000002003_1000002004 dc = ";
    alter[26] = "alter i1000004003_1000004004 dc = ";
    alter[27] = "alter i1002000003_1002000004 dc = ";
    alter[28] = "alter i1002002003_1002002004 dc = ";
    alter[29] = "alter i1002004003_1002004004 dc = ";

    //SM6
    alter[30] = "alter i1000006003_1000006004 dc = ";
    alter[31] = "alter i1000008003_1000008004 dc = ";
    alter[32] = "alter i1000010003_1000010004 dc = ";
    alter[33] = "alter i1002006003_1002006004 dc = ";
    alter[34] = "alter i1002008003_1002008004 dc = ";
    alter[35] = "alter i1002010003_1002010004 dc = ";

    //SM7
    alter[36] = "alter i1000012003_1000012004 dc = ";
    alter[37] = "alter i1000014003_1000014004 dc = ";
    alter[38] = "alter i1000016003_1000016004 dc = ";
    alter[39] = "alter i1002012003_1002012004 dc = ";
    alter[40] = "alter i1002014003_1002014004 dc = ";
    alter[41] = "alter i1002016003_1002016004 dc = ";

    //SM8
    alter[42] = "alter i1000018003_1000018004 dc = ";
    alter[43] = "alter i1000020003_1000020004 dc = ";
    alter[44] = "alter i1000022003_1000022004 dc = ";
    alter[45] = "alter i1002018003_1002018004 dc = ";
    alter[46] = "alter i1002020003_1002020004 dc = ";
    alter[47] = "alter i1002022003_1002022004 dc = ";

    //SM9
    alter[48] = "alter i1000000005_1000000006 dc = ";
    alter[49] = "alter i1000002005_1000002006 dc = ";
    alter[50] = "alter i1000004005_1000004006 dc = ";
    alter[51] = "alter i1002000005_1002000006 dc = ";
    alter[52] = "alter i1002002005_1002002006 dc = ";
    alter[53] = "alter i1002004005_1002004006 dc = ";

    //SM10
    alter[54] = "alter i1000006005_1000006006 dc = ";
    alter[55] = "alter i1000008005_1000008006 dc = ";
    alter[56] = "alter i1000010005_1000010006 dc = ";
    alter[57] = "alter i1002006005_1002006006 dc = ";
    alter[58] = "alter i1002008005_1002008006 dc = ";
    alter[59] = "alter i1002010005_1002010006 dc = ";

    //SM11
    alter[60] = "alter i1000012005_1000012006 dc = ";
    alter[61] = "alter i1000014005_1000014006 dc = ";
    alter[62] = "alter i1000016005_1000016006 dc = ";
    alter[63] = "alter i1002012005_1002012006 dc = ";
    alter[64] = "alter i1002014005_1002014006 dc = ";
    alter[65] = "alter i1002016005_1002016006 dc = ";

    //SM12
    alter[66] = "alter i1000018005_1000018006 dc = ";
    alter[67] = "alter i1000020005_1000020006 dc = ";
    alter[68] = "alter i1000022005_1000022006 dc = ";
    alter[69] = "alter i1002018005_1002018006 dc = ";
    alter[70] = "alter i1002020005_1002020006 dc = ";
    alter[71] = "alter i1002022005_1002022006 dc = ";

    //SM13
    alter[72] = "alter i1000000007_1000000008 dc = ";
    alter[73] = "alter i1000002007_1000002008 dc = ";
    alter[74] = "alter i1000004007_1000004008 dc = ";
    alter[75] = "alter i1002000007_1002000008 dc = ";
    alter[76] = "alter i1002002007_1002002008 dc = ";
    alter[77] = "alter i1002004007_1002004008 dc = ";

    //SM14
    alter[78] = "alter i1000006007_1000006008 dc = ";
    alter[79] = "alter i1000008007_1000008008 dc = ";
    alter[80] = "alter i1000010007_1000010008 dc = ";
    alter[81] = "alter i1002006007_1002006008 dc = ";
    alter[82] = "alter i1002008007_1002008008 dc = ";
    alter[83] = "alter i1002010007_1002010008 dc = ";

    //SM15
    alter[84] = "alter i1000012007_1000012008 dc = ";
    alter[85] = "alter i1000014007_1000014008 dc = ";
    alter[86] = "alter i1000016007_1000016008 dc = ";
    alter[87] = "alter i1002012007_1002012008 dc = ";
    alter[88] = "alter i1002014007_1002014008 dc = ";
    alter[89] = "alter i1002016007_1002016008 dc = ";

    //SM16
    alter[90] = "alter i1000018007_1000018008 dc = ";
    alter[91] = "alter i1000020007_1000020008 dc = ";
    alter[92] = "alter i1000022007_1000022008 dc = ";
    alter[93] = "alter i1002018007_1002018008 dc = ";
    alter[94] = "alter i1002020007_1002020008 dc = ";
    alter[95] = "alter i1002022007_1002022008 dc = ";



    string cc = "A";

    stringstream load;




    for (int n = 0; n < 96; n++) //VS
    {



    string bb = Current_Load[(int)n/6];
    string aa = alter[n];
    aa+=bb;
    aa+=cc;
    const char* alter = aa.c_str();
    //cout << n << ": " << alter << endl;

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
