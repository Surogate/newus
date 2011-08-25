
#include "DateParser.hpp"
#include "Singleton.hpp"

DateParser::DateParser(const std::string& text) : AParser(text) 
{}

bool DateParser::operator()(boost::posix_time::ptime& value) {
	std::string day;
	unsigned int numDay;
	std::string month;
	unsigned int year;
	unsigned int hour;
	unsigned int min;
	unsigned int sec;

	int timezone;

	bool result = (
		read_some(day, 3) && consume_str(", ")
		&& readInt(numDay) && consume(' ')
		&& read_some(month, 3) && consume (' ') 
		&& readInt(year) && consume(' ')
		&& readInt(hour) && consume(':')
		&& readInt(min) && consume(':')
		&& readInt(sec) && consume(' ')
		&& readInt(timezone)
		);

	if (result) {
		unsigned int monthValue = MonthConvertion::getInstance().conversionValue[month];
		value = boost::posix_time::ptime(boost::gregorian::date(year, monthValue, numDay), boost::posix_time::time_duration(hour, min, sec));
		value += boost::posix_time::hours(timezone);
	}

	return result;
}