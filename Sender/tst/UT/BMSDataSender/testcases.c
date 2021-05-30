/**
 * Note:
 * -----
 * I do not use Catch framework i instead use assert() for my unit test.
 * Reason being i can perform my testing locally but catch.hpp gives errors 
 * when executed locally.
 */

#include "../../../src/BMSDataSender.c"             /** Unit which sends the data */
#include <assert.h>                                 /* My unit test frame work */
#include <string.h>


/**
 * *****************************************************
 * ******* This is not a testcase so skip this *********
 * *****************************************************
 * Environment_Initialization will be used by the python script which i
 * prepared as a hobby to save me from 
 * - writing main
 * - updating it with the newly added testcase
 * - running the .exe after compiling my testcase (equivalent to run in actions)
 * 
 * The python script shall call this function before every testcase.
 * All global variables are intialized to 0 in this function.
 */ 

static void Environment_Initialization(void)
{
    int parameter =0 ;
    BatteryMonitoringSystemTransmitter.Fetchparameterdata = NULL;
    BatteryMonitoringSystemTransmitter.TransmitParameterData = NULL;
    for(parameter =0; parameter < BatteryParameter_TotalNumber; parameter++)
    {
        BatteryMonitoringSystemTransmitter.ParameterBuffer[parameter].pbuf = NULL;
        BatteryMonitoringSystemTransmitter.ParameterBuffer[parameter].size = 0;
    }
}

/**
 * BatteryMonitoringSystemTransmitter has two methods
 * 1. Fetchparameterdata
 * 2. TransmitParameterData
 * 
 * These two methods should be attached with proper functions
 * by the intialization function initializeBMSTransmitter() which gets called in 
 * BatteryMonitoringSystemTransmitter_Main()
 */ 
static void TC_EvaluateIfProperMethodsArelinkedToTransmitter(void)
{
    BatteryMonitoringSystemTransmitter_Main();
    assert(BatteryMonitoringSystemTransmitter.Fetchparameterdata == &FetchDataFromarray);
    assert(BatteryMonitoringSystemTransmitter.TransmitParameterData == &TransmitDataOntoConsole);
}

/**
 * FetchDataFromArray shall accpet only one input that is the address to the parameter buffers
 * A parameterbuffer shall contain two values
 * 1. address to the location where all the data is stored (databuffer)
 * 2. size : Number of data samples present
 * 
 * This testcase evaluates if FetchDataFromarray does the following
 *  1. linking parameter data buffer to appropriate parameter in BatteryMonitoringSystemTransmitter
 *  2. Entering number of the data samples present in size correctly.
 *    note: number of the data samples per parameter chosen is 7
 */ 

static void TC_EvaluateBufferDetailsAttachedForaParameterbyFetch(void)
{
    ParameterBuffer_t  *ParameterBuffer;
    int parameter;
    ParameterBuffer = &BatteryMonitoringSystemTransmitter.ParameterBuffer[0];

    FetchDataFromarray(&BatteryMonitoringSystemTransmitter.ParameterBuffer[0]);
    
    for (parameter = 0;parameter < BatteryParameter_TotalNumber ; parameter++)
    {
        printf("Asserting buffer details for parameter: %d\n", parameter);
        assert(ParameterBuffer[parameter].pbuf == &Paramter_data[parameter][0]); 
        assert(ParameterBuffer[parameter].size == NUMBER_OF_DATA_PER_PARAMETER);  
    }
     
}

/**
 * This shall be used in TransmitDataOntoConsole()
 * Parameter names as strings shall be stored in a lookup table (which basically is an array)
 * Evaluate if the names are stored in the look up table appropriately
 */ 
static void TC_EvaluateIfEnumToStringConversionIsHappeningProperly(void)
{
    assert(strcmp(ParmaeterToStr[0],"Temparature")==0);
    assert(strcmp(ParmaeterToStr[1],"ChargeRate")==0);
}


/**
 * Created a pointer so that i can create a mock for it in later
 * for now the testdouble print shall contain printf address
 */ 
static void TC_EvaluatePrintTestDoubleIsWithPrintf(void)
{
    assert(print == &printf);
}


int call_printf = 0;
char Printf_FormatString[10];
unsigned int Stringaddr;
static void printf_mock_ForInstance1(char *Par_s, unsigned int Par_stringaddr)
{
    call_printf++;
    if(call_printf == 1)
    {   
        Stringaddr = Par_stringaddr;
        strcpy(Printf_FormatString,Par_s);
    }
} 
int size;
static void printf_mock_ForInstance2(char *Par_s, int Par_Size)
{
    call_printf++;
    if(call_printf == 2)
    {   
        size = Par_Size;
        strcpy(Printf_FormatString ,Par_s);
    }
} 

float printf_pardata[NUMBER_OF_DATA_PER_PARAMETER];
static void printf_mock_ForInstance3(char *Par_s, float Par_datasample)
{
    call_printf++;
    if((call_printf >=3 ) && (call_printf <= (3 + NUMBER_OF_DATA_PER_PARAMETER-1)))
    {
        strcpy(Printf_FormatString,Par_s);
        printf_pardata[call_printf-3] = Par_datasample;
    }
    
    
} 

static void TC_EvaluateIfBatteryparameterToStrIsPrintedFirstOnConsole(void)
{
    call_printf = 0;
    print = &printf_mock_ForInstance1;
    BatteryMonitoringSystemTransmitter_Main();
    assert(strcmp("%s\n",Printf_FormatString)==0);
    assert(Stringaddr == ParmaeterToStr[0]);   
}


static void TC_EvaluateIfSizeIsPrintedSecondOnConsole(void)
{
    call_printf = 0;
    print = &printf_mock_ForInstance2;
    BatteryMonitoringSystemTransmitter_Main();  
    assert(strcmp("%d\n",Printf_FormatString)==0);
    assert(size == BatteryMonitoringSystemTransmitter.ParameterBuffer[0].size); 
}

static void TC_EvaluateIfDataSamplesGetsPrintedThridOnConsole(void)
{
    int index = 0;
    call_printf = 0;
    print = &printf_mock_ForInstance3;
    BatteryMonitoringSystemTransmitter_Main(); 
    assert(strcmp("%f\n",Printf_FormatString)==0);
    for(index = 0; index < NUMBER_OF_DATA_PER_PARAMETER ; index++)
    {
        printf("%d\n", index);
        printf("%f\n",printf_pardata[index]);
        printf("%f\n",BatteryMonitoringSystemTransmitter.ParameterBuffer[0].pbuf[index]);        
       assert(printf_pardata[index] == BatteryMonitoringSystemTransmitter.ParameterBuffer[0].pbuf[index]);
    }
}