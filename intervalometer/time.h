#ifndef TIME_H
#define TIME_H

#include "global.h"
#include <TimeLib.h>

extern void setEspTime(DynamicJsonDocument doc);

extern unsigned long millisecond();
extern unsigned long msOffset;

#endif