#pragma once

#define DATASAMPLES_FILENAME    "data.txt"


typedef enum{
    BatteryParameter_Temparature,
    BatteryParameter_ChargeRate,
    BatteryParameter_TotalNumber
} BatteryParameter_t;


typedef struct {
    int isTxStopRequested;
}BMSDataTxControl_t;

typedef struct {
    BMSDataTxControl_t TxControl;
    void (*TrasmitData)(BMSDataTxControl_t *TxControl);
}BMSDataTransmitter_t;

/* Designed For testing purposes */
extern void RequestToStopDataTransmission(void);



