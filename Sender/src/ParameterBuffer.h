#pragma once

typedef enum{
    BatteryParameter_Temparature,
    BatteryParameter_ChargeRate,
    BatteryParameter_TotalNumber
} BatteryParameter_t;

typedef struct {
    float *pbuf;
    int size;
}ParameterBuffer_t;
