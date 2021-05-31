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
}

/**
 * If file is not found then the sender function shall exit
 */ 

static TC_ProcessShouldExitIfFileNotFound(void)
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
static EvaluateParametersOrderPrintedOnConsole(void)
{
    print = print_Mock_ForDataEvaluation;
    BatteryMonitoringSystemTransmitter_Main();
    assert(call_Printf == 1);
    assert(printf_floatpar_data[BatteryParameter_Temparature] = 1.0);
    assert(printf_floatpar_data[BatteryParameter_ChargeRate] = 2.0);
}
