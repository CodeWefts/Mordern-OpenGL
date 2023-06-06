#pragma once

#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <cstdarg>
#include <source_location>

#define DEBUG_LOG(...) {Log::PrintFileLine(); Log::Print(__VA_ARGS__);}

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
	static void PrintFileLine(const source_location loc = source_location::current());
};