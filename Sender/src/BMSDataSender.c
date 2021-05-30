
#include <stdio.h>
#include <assert.h>
#include "BMSDataSender.h"

#define NUMBER_OF_DATA_PER_PARAMETER    7
const float Paramter_data[BatteryParameter_TotalNumber][7] = {
                                                        {10.0, 12.0, 13.1, 14.2, 15.3, 16.4, 17.5},
                                                        {0.1,0.25,0.34,0.45,0.54,0.63,0.57}
                                                        };

static const char * ParmaeterToStr[BatteryParameter_TotalNumber] = {"Temparature","ChargeRate"};

///> Test double
int (*print)(const char *format, ...) = &printf;


void FetchDataFromarray(ParameterBuffer_t * ParameterBuffer)
{
    assert(ParameterBuffer != NULL);
    unsigned int parameter = 0;
    for (parameter = 0; parameter < BatteryParameter_TotalNumber ; parameter++, ParameterBuffer++)
    {
        ParameterBuffer->pbuf = (float *)&Paramter_data[parameter][0];
        ParameterBuffer->size = NUMBER_OF_DATA_PER_PARAMETER;
    }    
}


void TransmitDataOntoConsole(ParameterBuffer_t * ParameterBuffer)
{
    unsigned int parameter = 0;
    unsigned int index = 0;
    assert(ParameterBuffer != NULL);   
    for (parameter = 0; parameter < BatteryParameter_TotalNumber ; parameter++)
    {
        print("%s\n",ParmaeterToStr[parameter]);
        print("%d\n",ParameterBuffer->size);
        for(index =0; index < ParameterBuffer->size ; index++)
        {
            print("%f\n",ParameterBuffer->pbuf[index]);
        }
        ParameterBuffer++;    
    }    
}



static  BatteryMonitoringSystemTransmitter_t    BatteryMonitoringSystemTransmitter;


void initializeBMSTransmitter(void)
{
    BatteryMonitoringSystemTransmitter.Fetchparameterdata = &FetchDataFromarray;
    BatteryMonitoringSystemTransmitter.TransmitParameterData = &TransmitDataOntoConsole;
}


void BatteryMonitoringSystemTransmitter_Main(void)
{
    initializeBMSTransmitter();
    BatteryMonitoringSystemTransmitter.Fetchparameterdata(&BatteryMonitoringSystemTransmitter.ParameterBuffer[0]);
    BatteryMonitoringSystemTransmitter.TransmitParameterData(&BatteryMonitoringSystemTransmitter.ParameterBuffer[0]);
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
