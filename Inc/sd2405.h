#ifndef __SD2405_H
#define __SD2405_H
#include    <stdint.h>

extern Int8U Second_1,Minute_1,Hour_1,Week_1,Day_1,Month_1,Year_1,ReadTimeFlag;
extern void Calendar_Init(void);
extern Int8U turntime(Int8U time);
extern void GpioEventInit(void);
extern void SD2405_Init(void);
extern void gettime(void);
extern void fhzgettime(void);
extern void readtime(void);//获取时间

#endif
