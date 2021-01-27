/*
 * MiClase.cc
 *
 *  Created on: 06/05/2019
 *      Author: Matias - Jesus
 */

#include "MiClase.h"
#include "Logs.h"

#ifdef LOGS
 std::ofstream logs; //por si necesito cambiarlo en algun momento
 struct timespec starttime, endtime, ttime;
 double timeinterval;
 struct timespec firsttime; //este exclusivamente para ver tiempo total
#endif


static void IniLogs()
{
	time_t rawtime;
	struct tm * timeinfo;
	time( &rawtime );
	timeinfo = localtime ( &rawtime );
	char logFileName[200];
	umask(0);
	mkdir("./Log", S_IRWXU | S_IRWXG | S_IRWXO);
	sprintf( logFileName,"./Log/log%04d%02d%02d%02d%02d.log",
			timeinfo->tm_year +1900, timeinfo->tm_mon +1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min );
	logs.open(logFileName);
	clock_gettime(CLOCK_REALTIME, &starttime);
	firsttime = starttime;
}
//

MiClase::MiClase()
{
	IniLogs();
	LOGS( "inicie" );
}

MiClase::~MiClase(){
	logs.close();
}
