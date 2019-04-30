#pragma once
#include <string>
using namespace std;
class Bus
{
private:
	int number;
	string type;
	string destination;
	string startTime;
	string endTime;
public:
	Bus()
	{

	}
	Bus(int number, string type, string destination, string startTime, string endTime)
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

	void setType(string type)
	{
		this->type = type;
	}

	void setDestination(string destination)
	{
		this->destination = destination;
	}

	void setStartTime(string startTime)
	{
		this->startTime = startTime;
	}

	void setEndTime(string endTime)
	{
		this->endTime = endTime;
	}

	int getNumber()
	{
		return number;
	}

	string getType()
	{
		return type;
	}

	string getDestination()
	{
		return destination;
	}

	string getStartTime()
	{
		return startTime;
	}

	string getEndTime()
	{
		return endTime;
	}
};
