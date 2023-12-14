#ifndef TIME_H
#define TIME_H

#include <TimeLib.h>

#include "global.h"

extern void setEspTime(DynamicJsonDocument doc);

extern unsigned long millisecond();
extern unsigned long msOffset;

#endif