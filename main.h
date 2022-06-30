#ifndef MAIN_H
#define MAIN_H
#define MBED_PROJECT    "Transmission Example"

#include "lib_Transmission.h"

BusOut              Led(LED1, LED2, LED3);
#if MBED_MAJOR_VERSION > 5
UnbufferedSerial    pc(USBTX, USBRX, 230400);
#else
Serial              pc(USBTX, USBRX, 230400);
#endif
EthernetInterface   eth;

string              transmission_processing(string);
Transmission        transmission(&pc, &eth, &transmission_processing);
#endif