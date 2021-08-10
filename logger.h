#pragma once

#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

namespace color
{
	void set(int color);

	std::ostream &reset(std::ostream &os);
	std::ostream &green(std::ostream &os);
	std::ostream &yellow(std::ostream &os);
	std::ostream &red(std::ostream &os);
}

namespace logger
{
	std::string get_time();
	void set_log_file(std::string name);

	void info(std::string text);
	void warn(std::string text);
	void error(std::string text);

	using color_method_t = decltype(color::reset);
	void log(color_method_t color, std::string tag, std::string text);
}