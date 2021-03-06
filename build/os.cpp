// OpenGL linking.

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "os.h"

#ifdef WIN32
#include <windows.h>
#endif

v8::Handle<v8::Value> os_sleep(const v8::Arguments& x) {
	double t = x[0]->NumberValue();
#ifdef WIN32
	Sleep(t * 1e3);
#else
	struct timespec ts;
	double integ;
	double frac = modf(t, &integ);
	ts.tv_sec = integ;
	ts.tv_nsec = frac * 1e9;
	nanosleep(&ts, NULL);
#endif
	return v8::Integer::New(0);
}

v8::Handle<v8::Value> os_exit(const v8::Arguments& x) {
	exit(x[0]->Int32Value());
	return v8::Integer::New(0);
}

void os_init(v8::Handle<v8::Object>& global) {
	//SCOPE(os);
	//SET(global, os, os);
	FUNC(global, sleep, os_sleep);
	FUNC(global, exit, os_exit);
}

