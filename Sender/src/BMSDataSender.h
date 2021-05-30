#pragma once
#include "ParameterBuffer.h"

typedef struct {
    ParameterBuffer_t ParameterBuffer[BatteryParameter_TotalNumber];
    void (*Fetchparameterdata)(ParameterBuffer_t * ParameterBuffer);
    void (*TransmitParameterData)(ParameterBuffer_t * ParameterBuffer);
}BatteryMonitoringSystemTransmitter_t;


