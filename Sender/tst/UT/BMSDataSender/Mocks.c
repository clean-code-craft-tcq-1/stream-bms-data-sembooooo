#include "../../../src/BMSDataSender.h"

char Printf_FormartString[100];
int call_Printf;
float printf_floatpar_data[2];

int print_Mock_FilenotfoundInstance(char *Par_s)
{
    strcpy(Printf_FormartString,Par_s);
}

int print_Mock_ForDataEvaluation(char *Par_s,float temp,float chargerate)
{
    call_Printf++;
    strcpy(Printf_FormartString,Par_s);
    printf_floatpar_data[0] =temp;
    printf_floatpar_data[1] =chargerate;
    RequestToStopDataTransmission();
}
