
#include "logger.h"

void color::set(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

std::ostream &color::reset(std::ostream &os) { set(7); return os; }
std::ostream &color::green(std::ostream &os) { set(2); return os; }
std::ostream &color::yellow(std::ostream &os) { set(6); return os; }
std::ostream &color::red(std::ostream &os) { set(12); return os; }

std::string log_file {"log.txt"};

std::string logger::get_time()
{
	std::time_t tm {std::time(nullptr)};

	char time[64];
	std::strftime(time, sizeof(time),
		"%Y-%m-%d %H-%M-%S", std::localtime(&tm));

	return time;
}

void logger::set_log_file(std::string name) 
{
	std::string date_format {"%date%"};

	size_t date_pos {name.find(date_format)};
	if (date_pos != name.npos)
	{
		std::string time {get_time()};
		name.replace(date_pos, date_format.length(), time.c_str(), time.length());
	}

	log_file = name;
}

void logger::info(std::string text) {
	log(color::green, "info", text);
}

void logger::warn(std::string text) {
	log(color::yellow, "warn", text);
}

void logger::error(std::string text) {
	log(color::red, "error", text);
}

void logger::log(color_method_t color, std::string tag, std::string text)
{
	std::string time {get_time()};

	std::ofstream file(log_file, std::ios::app);
	if (file.is_open())
	{
		file << time
			<< " | " << tag
			<< " | " << text
			<< std::endl;

		file.close();
	}

	std::cout << time
		<< " | " << color << tag
		<< color::reset << " | " << text
		<< std::endl;
}
