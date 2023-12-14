#ifndef SERVER_H
#define SERVER_H

#include "global.h"
#include "resources.h"
#include "time.h"
#include "camera.h"
#include "intervalometer.h"

extern void initServer();

extern void loopProcessRequest();

#endif