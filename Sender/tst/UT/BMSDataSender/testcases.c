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
#include "Mocks.h"

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
    BMSDataTransmitter.TxControl.isTxStopRequested =0;
    print = &printf;
    Reset_all_print_mocks();
}

/**
 * If file is not found then the sender function shall exit
 */ 

static void TC_ProcessShouldExitIfFileNotFound(void)
{
    #undef DATASAMPLES_FILENAME
    #define DATASAMPLES_FILENAME "dat.txt"
    print = Printf_FormartString;
    BatteryMonitoringSystemTransmitter_Main();
    assert(strcmp("Problem with File opening\n",Printf_FormartString)==0);
}


/**
 * The parameters are stored in the order following order in the file temparature
 *      temparatre chargerate
 *      temparatre chargerate 
 *      temparatre chargerate
 *          ....
 *          ....
 * 
 * So the parameters should also get printed in the same order on console
 *      temparatre chargerate
 *      temparatre chargerate 
 *      temparatre chargerate
 *          ....
 *          ....
 */ 
static void TC_EvaluateParametersOrderPrintedOnConsole(void)
{
    print = print_Mock_ForDataEvaluation;
    BatteryMonitoringSystemTransmitter_Main();
    assert(call_Printf == 1);
    assert(printf_floatpar_data[BatteryParameter_Temparature] == 1.0);
    assert(printf_floatpar_data[BatteryParameter_ChargeRate] == 2.0);
}

/**
 * While fetching the values from data.txt file , ifEnd of the file is reached then the
 * reading should again start from the top of the file.
 * This allows us to send data continously until user stops
 * 
 * The data.txt file in this unittest is written in the following way
 * 1.0 2.0
 * 3.0 4.0
 * 5.0 6.0
 * 
 * So after 4th read again 1.0 and 2.0 should be passed on to console (printf)
 *
 */ 
static void TC_EvaluateIfFilereadingisIteratedatEOF(void)
{
    int index;
    float datasamples[4][2] ={ {1.0,2.0},
                                {3.0,4.0},
                                {5.0,6.0},
                                {1.0,2.0}};
    print = print_Mocks_ForFileIterationInstance;
    numberofcallsToRequestStop = 4;
    BatteryMonitoringSystemTransmitter_Main();
    assert(call_Printf == 4);
    for (index = 0; index <4 ; index ++)
    {
        assert(printf_floatpar_AlldataSamples[index][0] ==datasamples[index][0]);
        assert(printf_floatpar_AlldataSamples[index][1] ==datasamples[index][1]);
    }
}
/**
 * To Evaluate if the testdouble is assigned properly with printf or not
 */ 
static void TC_EvaluateIfPrintfIsAssigned(void)
{
    assert(print == &printf);
}


int main()
{
Environment_Initialization(); 
TC_ProcessShouldExitIfFileNotFound(); 
Environment_Initialization(); 
TC_EvaluateParametersOrderPrintedOnConsole(); 
Environment_Initialization(); 
TC_EvaluateIfFilereadingisIteratedatEOF(); 
Environment_Initialization(); 
TC_EvaluateIfPrintfIsAssigned();
return 0;
}
