#include <stdio.h>
#include <assert.h>
#include "BMSDataSender.h"

///> Test double
int (*print)(const char *format, ...) = &printf;

void TransmitDataFromFileToConsole(BMSDataTxControl_t * TxControlPtr)
{
    float ParameterData[BatteryParameter_TotalNumber];
    int param;
    FILE *fptr = fopen(DATASAMPLES_FILENAME,"r");      
    if(fptr == NULL)
    {
        print("Problem with File opening\n");
        return;
    }
    while(TxControlPtr->isTxStopRequested == 0)
    {
            if(fscanf(fptr,"%f %f",&ParameterData[BatteryParameter_Temparature],
                                   &ParameterData[BatteryParameter_ChargeRate] ) == EOF)
            {
                rewind(fptr);
            }
            else
            {
                print("%f %f\n",ParameterData[BatteryParameter_Temparature],ParameterData[BatteryParameter_ChargeRate]);
            }
    }
    fclose(fptr);
}

BMSDataTransmitter_t BMSDataTransmitter ={
                                        {0},
                                        &TransmitDataFromFileToConsole};

void BatteryMonitoringSystemTransmitter_Main(void)
{
   BMSDataTransmitter.TrasmitData(&BMSDataTransmitter.TxControl);
}

void RequestToStopDataTransmission(void)
{   
    BMSDataTransmitter.TxControl.isTxStopRequested = 1;
}

#ifdef MAIN
/**
 * This main function will only get compiled if this MAIN macro is defined during compilatin
 */ 
int main()
{
    BatteryMonitoringSystemTransmitter_Main();
}
#endif
