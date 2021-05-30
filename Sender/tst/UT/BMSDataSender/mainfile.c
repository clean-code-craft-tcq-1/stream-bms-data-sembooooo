
#include "testcases.c"
int main()
{
Environment_Initialization(); 
TC_EvaluateIfProperMethodsArelinkedToTransmitter(); 
Environment_Initialization(); 
TC_EvaluateBufferDetailsAttachedForaParameterbyFetch(); 
Environment_Initialization(); 
TC_EvaluateIfEnumToStringConversionIsHappeningProperly(); 
Environment_Initialization(); 
TC_EvaluatePrintTestDoubleIsWithPrintf(); 
Environment_Initialization(); 
TC_EvaluateIfBatteryparameterToStrIsPrintedFirstOnConsole(); 
Environment_Initialization(); 
TC_EvaluateIfSizeIsPrintedSecondOnConsole(); 
Environment_Initialization(); 
TC_EvaluateIfDataSamplesGetsPrintedThridOnConsole();
return 0;
}
