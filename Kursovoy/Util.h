#pragma once
#include <iostream>
#include "bus.h"
#include <fstream>
#include <map>
#include <cstdlib>
#include <sstream>
using namespace std;
static string path = "E:\\myBuses.txt";
class Util
{	
public:
	static int getMainMenu()
	{
		setlocale(LC_ALL, "rus");
		int er=0;
		cout << "��������� ��� ����� � ������ ���������" << endl;
		cout << "1.�������� �������" << endl;
		cout << "2.������ ��������� � �������� �����������" << endl;
		cout << "3.����� �� ���������" << endl;
		cin >> er;
			switch (er)
			{
				case 1:inputBus();break;
				case 2:getChooseDirection();break;
				case 3:exit(0);
				default: cout << "�������� �����" << endl;
			}
		return 0;
	}
	static void inputBus()
	{
		int number;
		string type, destination, startTime, endTime;
		Bus* bus = new Bus;
		cout << "������� ����� ��������:" << endl;
		cin >> number;
		bus->setNumber(number);
		cout << "������� ��� ��������:" << endl;
		cin >> type;
		bus->setType(type);
		cout << "������� ����� ����������:" << endl;
		cin >> destination;
		bus->setDestination(destination);
		cout << "������� ����� ��������:" << endl;
		cin >> startTime;
		bus->setStartTime(startTime);
		cout << "������� ����� ��������:" << endl;
		cin >> endTime;
		bus->setEndTime(endTime);
		writeInFile(bus);
		getMainMenu();
	}
	static void getChooseDirection()
	{
		string destination;
		cout << "������� ������ �����������" << endl;
		cin >> destination;
		if (readOfFile(path,destination).empty())
		{
			cout << "��������� � ������ ����������� ���" << endl;
		}
		else {
			cout << "����� ��������      " << "��� ��������       " << "����� � ����" << endl;
			for (auto& it : readOfFile(path,destination))
			{
				cout << it.second.getNumber() << "                " << it.second.getType() << "              " << it.first << endl;
			} 
		}
	}
	static void writeInFile(Bus* bus)
	{
		ofstream fout;
		fout.open(path, ofstream::app);
		if (!fout.is_open())
		{
			cout << "������ �������� �����!" << endl;
		}
		else
		{
			fout << bus->getNumber() << "\t" << bus->getType() << "\t" << bus->getDestination() << "\t" << bus->getStartTime() << "\t" << bus->getEndTime() << endl;
		}
		fout.close();
	}
	static multimap<double,Bus> readOfFile(string path,string dest)
	{
		multimap<double, Bus> busesMap;
		string line;
		ifstream fin;
		fin.open(path);
		if (!fin.is_open())
		{
			cout << "������ �������� �����!" << endl;			
		}
		else
		{
			while (getline(fin,line))
			{
				int number;
				string type, destination, startTime, endTime;
				istringstream iss(line);
				iss >> number >> type >> destination >> startTime >> endTime;
				Bus bus(number,type,destination,startTime,endTime);
				if (bus.getDestination() == dest)
				{
					double start, end;
					end = stod(bus.getEndTime());
					start = stod(bus.getStartTime());
					busesMap.insert(pair<double, Bus>(end - start, bus));
				}
			}
		}
		fin.close();
		return busesMap;
	}
};

