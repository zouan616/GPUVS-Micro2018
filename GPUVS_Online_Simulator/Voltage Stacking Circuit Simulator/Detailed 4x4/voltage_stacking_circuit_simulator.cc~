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
#include <my_shared_mem.h>



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

int i;
char ** circarray;
char **vecarray;

ControlledExit ng_exit;
SendData ng_data;
SendInitData ng_initdata;


void * ngdllhandle = NULL;

string powertrace;
string powertrace_leakage;
string Current_Load[16];

float measure_voltage[16];

int main(){


    
    int date_update_frequency = 1;
    int feedback_frequency = 10;


    int cycle_length = 100;

    int fd;
    struct my_shared_memory *ptr;

    fd = shm_open(shared_memory_name, O_RDWR, S_IRWXU);
    if (fd<0) {
    printf("error open shared memory\n");
    return 0;
    }

    ptr = (struct my_shared_memory *)mmap(NULL, sizeof(my_shared_memory1), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if(ptr  == MAP_FAILED) {
    printf("error map\n");
    return 0;
    }






    cout << "Input Power Trace File Name:" <<endl;

    //powertrace = "/home/anzou/NVIDIA_GPU_Computing_SDK/C/bin/linux/release/per_core_power_record.txt";
    powertrace = "/home/anzou/rodinia_2.0/cuda/backprop/per_core_power_record.txt";
    
    ifstream infile(powertrace.c_str());

    // Skip the previous cycles
    for(int k=0; k<10000; k++)
    {
    getline(infile,temp);
    cout << "skip a line" << endl;
    }


    //powertrace = "/home/anzou/NVIDIA_GPU_Computing_SDK/C/bin/linux/release/leakage_power.txt";
    powertrace_leakage = "/home/anzou/rodinia_2.0/cuda/backprop/leakage_power.txt";
    
    ifstream infile_leakage(powertrace_leakage.c_str());

    // Skip the previous cycles
    for(int k=0; k<10000; k++)
    {
    getline(infile_leakage,temp);
    cout << "skip a line" << endl;
    }







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
    ret = ((int * (*)(const char*)) ngSpice_Command_handle)("4x4GPUVSPDN.cir");


    //set simulation pause time, load current update time i (unit 1ps)
    string a,c;
    int stop_point = 5000;
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

    cout << "start simulation" << endl;
    //start simulation
    ret = ((int * (*)(const char*)) ngSpice_Command_handle)("bg_run");

    int i;

    //upload load current and resume


    for(i = 1; i < stop_point+1; i++)
    {

    if((i%date_update_frequency)==0)
    {
        cout <<"------------Circuit simulator cycle:" << i << endl;
        ptr->gpusim_finish = 0;
        ptr->spice_finish = 1;
        while(ptr->gpusim_finish == 0)
        {
        }

    }


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
     
        cout << "ss:" << ss << endl;

        const char *dd = "= ";
        char *pp;
        pp = strtok(ss,dd);
        pp = strtok(NULL,dd);

        measure_voltage[k] = atof(pp);
        if(measure_voltage[k]>6)
        {
        measure_voltage[k] = 0.1 * measure_voltage[k];
        } 
        
        cout << "SM "<< k << " Voltage: " << measure_voltage[k] << endl;
     }
        //Adjust the power mode according to the Voltage


    for(int k=0;k<16;k++)
    {
        

  
        if(k<=11)
        {
          if((measure_voltage[k] - measure_voltage[k+4])<0.85)
          {
          ptr->power_mode[k] = 6*(measure_voltage[k] - measure_voltage[k+4])-4.9;
          }
          else if(((measure_voltage[k] - measure_voltage[k+4])<=0.92)&&((measure_voltage[k] - measure_voltage[k+4])>=0.85))
          {
          ptr->power_mode[k] = 3*(measure_voltage[k] - measure_voltage[k+4])-2.2;
          }
          else
          {
          ptr->power_mode[k] = ptr->power_mode[k] + 0.04;
          }
        }
        else
        {
          if(ptr->power_mode[k] < 0.85)
          {
          ptr->power_mode[k] = 6*measure_voltage[k] - 4.9;
          }
          else if((measure_voltage[k]<=0.92)&&(measure_voltage[k]>=0.85))
          {
          ptr->power_mode[k] = 3*measure_voltage[k] - 2.2;
          }
          else
          {
          ptr->power_mode[k] = ptr->power_mode[k] + 0.04;
          }
        }



        if(i<1000)
        {
        ptr->power_mode[k] = 2;
        }

        cout << "ptr->power_mode[k]: " << ptr->power_mode[k] << endl;

    }


    }

    //output 100-1
    if(i > (stop_point-1))
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

      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata off_1 V(30000011_off)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata off_2 V(3000001_off)");

      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata on_1 V(30000011)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata on_2 V(3000001)");

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


      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata r_test V(30000021)");
      ret = ((int * (*)(const char*)) ngSpice_Command_handle)("wrdata r_test_gnd V(300000211)");


      printf("Simulation finish!!!!!!!!!\n");
      break;
      //exit(0);
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

      cout << "The cycle " << "i:" << i << ":" << temp << endl;
      char s[1024];
      int m;
      for( m=0;m<temp.length();m++)
      {
          s[m] = temp[m];
      }
      const char *d = " ,*";
      char *p;
      p = strtok(s,d);


      getline(infile_leakage,temp);
      cout << "The cycle leakage power" << "i:" << i << ":" << temp << endl;
      char s_leakage[1024];
      int m_leakage;
      for( m_leakage=0;m_leakage<temp.length();m_leakage++)
      {
          s_leakage[m_leakage] = temp[m_leakage];
      }
      const char *d_leakage = " ,*";
      char *p_leakage;
      p_leakage = strtok(s_leakage,d_leakage);








      int outputloadnum = 0;


      while(outputloadnum < 16)  //Single layer
      {
          //printf("%s\n",p);
          //Divide workload to 6 cores
          // power gating
          //double a = atof(p) + atof(p_leakage);
          double a = atof(p);
          a = a/6;

          stringstream sss;
          sss << a;

          Current_Load[outputloadnum] = sss.str();;

          outputloadnum = outputloadnum + 1;
          p=strtok(NULL,d);
      }


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
