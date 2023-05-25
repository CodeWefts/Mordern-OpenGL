#pragma once
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <cstdarg>

#define DEBUG_LOG(...) {Log::Print(__VA_ARGS__);}

using namespace std;

class Log
{
	ofstream file;
	static Log log;

public :

	Log();
	~Log();

	static void OpenFile(filesystem::path const& filename);
	static void Print(const char* format, ...);
};