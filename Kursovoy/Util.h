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
		cout << "Программа для ввода и поиска автобусов" << endl;
		cout << "1.Добавить автобус" << endl;
		cout << "2.Список автобусов в заданном направлении" << endl;
		cout << "3.Выход из программы" << endl;
		cin >> er;
			switch (er)
			{
				case 1:inputBus();break;
				case 2:getChooseDirection();break;
				case 3:exit(0);
				default: cout << "Неверный выбор" << endl;
			}
		return 0;
	}
	static void inputBus()
	{
		int number;
		string type, destination, startTime, endTime;
		Bus* bus = new Bus;
		cout << "Введите номер автобуса:" << endl;
		cin >> number;
		bus->setNumber(number);
		cout << "Введите тип автобуса:" << endl;
		cin >> type;
		bus->setType(type);
		cout << "Введите пункт назначения:" << endl;
		cin >> destination;
		bus->setDestination(destination);
		cout << "Введите время отправки:" << endl;
		cin >> startTime;
		bus->setStartTime(startTime);
		cout << "Введите время прибытия:" << endl;
		cin >> endTime;
		bus->setEndTime(endTime);
		writeInFile(bus);
		getMainMenu();
	}
	static void getChooseDirection()
	{
		string destination;
		cout << "Введите нужное направление" << endl;
		cin >> destination;
		if (readOfFile(path,destination).empty())
		{
			cout << "Автобусов в данном направлении нет" << endl;
		}
		else {
			cout << "Номер автобуса      " << "Тип автобуса       " << "Время в пути" << endl;
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
			cout << "Ошибка открытия файла!" << endl;
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
			cout << "Ошибка открытия файла!" << endl;			
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

