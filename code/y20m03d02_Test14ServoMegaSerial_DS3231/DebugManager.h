#ifndef _DEBUG_MANAGER_H__
#define _DEBUG_MANAGER_H__

#import "src/Debug/ArduinoTrace.h"

#define SPLIT_STR_DB()          TRACE()
#define SPLIT_STR_DB_V(x)       DUMP(x)
#endif