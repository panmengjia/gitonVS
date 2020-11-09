#pragma once

#ifndef MAIN_H__
#define MAIN_H__

#include <iostream>
#include <opencv.hpp>
#include <thread>
#include "windows.h"

using namespace cv;
using namespace std;

extern int maintest();
extern void testarray();
extern int opencvdft();
extern int opencvSapmleOfdft(int argc, const char** argv);


#endif // !MAIN_H__

