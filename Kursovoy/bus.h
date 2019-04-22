#pragma once
#include <string>
using namespace std;
class Bus
{
private:
	int number;
	std::string type;
	std::string destination;
	std::string startTime;
	std::string endTime;
public:
	Bus()
	{
		number = 0;
	}
	Bus(int number, std::string type, std::string destination, std::string startTime, std::string endTime)
	{
		this->number = number;
		this->type = type;
		this->destination = destination;
		this->startTime = startTime;
		this->endTime = endTime;
	}
	~Bus()
	{

	}

	void setNumber(int number)
	{
		this->number = number;
	}

	void setType(std::string type)
	{
		this->type = type;
	}

	void setDestination(std::string destination)
	{
		this->destination = destination;
	}

	void setStartTime(std::string startTime)
	{
		this->startTime = startTime;
	}

	void setEndTime(std::string endTime)
	{
		this->endTime = endTime;
	}

	int getNumber()
	{
		return number;
	}

	std::string getType()
	{
		return type;
	}

	std::string getDestination()
	{
		return destination;
	}

	std::string getStartTime()
	{
		return startTime;
	}

	std::string getEndTime()
	{
		return endTime;
	}
	};
