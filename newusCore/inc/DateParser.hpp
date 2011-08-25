
#ifndef DATEPARSER_HPP
#define DATEPARSER_HPP

#include <boost/date_time/posix_time/posix_time.hpp>
#include "AParser.hpp"
#include "Singleton.hpp"

class DateParser : public AParser {
public:
	DateParser(const std::string& text);

	bool operator()(boost::posix_time::ptime& value);

private:
	struct MonthConvertion : Singleton<MonthConvertion> {
	public:
		MonthConvertion() : conversionValue() {
			conversionValue["Jan"] = 1;
			conversionValue["Feb"] = 2;
			conversionValue["Mar"] = 3;
			conversionValue["Apr"] = 4;
			conversionValue["May"] = 5;
			conversionValue["Jun"] = 6;
			conversionValue["Jul"] = 7;
			conversionValue["Aug"] = 8;
			conversionValue["Sep"] = 9;
			conversionValue["Oct"] = 10;
			conversionValue["Nov"] = 11;
			conversionValue["Dec"] = 12;
		}

		std::map<std::string, unsigned int> conversionValue;
	};	
};

#endif  /* DATEPARSER_HPP */