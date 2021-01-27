/*
 * Logs.h
 *
 *  Created on: 06/05/2019
 *      Author: Matias - Jesus
 */

#ifndef LOGS_H_
#define LOGS_H_

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

//=============================================================================
// para generar logs mas completos
//=============================================================================
//

extern struct timespec starttime, endtime, ttime;
extern double timeinterval;
extern struct timespec firsttime; //este exclusivamente para ver tiempo total
extern  std::ofstream logs; //por si necesito cambiarlo en algun momento




#define LOGS(...) {\
	clock_gettime(CLOCK_REALTIME, &endtime);\
	ttime.tv_sec = endtime.tv_sec - firsttime.tv_sec;\
	ttime.tv_nsec = endtime.tv_nsec - firsttime.tv_nsec;\
	starttime = endtime;\
	timeinterval = ttime.tv_sec * 1000000000 + ttime.tv_nsec;\
    logs << __FILE__ << ": " << __FUNCTION__ << "(): " << __LINE__ << ": " << __VA_ARGS__ \
	<< ": " <<(double) timeinterval/1000000 << ": ms" << std::endl;\
	logs.flush(); \
    };






#endif /* LOGS_H_ */
