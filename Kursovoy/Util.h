#pragma once
#include <iostream>
#include "bus.h"
#include <fstream>
#include <map>
#include <cstdlib>
#include <sstream>
#include <windows.h>
#include <ctime>

using namespace std;
static string path = "E:\\myBuses.txt";
class Util
{	
public:
	static int getMainMenu()
	{
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		setlocale(LC_ALL, "rus");
		char i;
		system("cls");
		cout << "Программа для ввода и поиска автобусов" << endl;
		cout << "1.Добавить автобус" << endl;
		cout << "2.Список автобусов в заданном направлении" << endl;
		cout << "3.Выход из программы" << endl;
		cin >> i;
			switch (i)
			{
				case '1':inputBus();break;
				case '2':getChooseDirection();break;
				case '3':exit(0);
				default: break;
			}
		return 0;
	}
private:
	static void inputBus()
	{
		int number;
		string type, destination, startTime, endTime;
		Bus* bus = new Bus;
		system("cls");
		cout << "Введите номер автобуса:" << endl;
		cin >> number;
		bus->setNumber(number);
		cout << "Введите тип автобуса:" << endl;
		cin >> type;
		bus->setType(type);
		cout << "Введите пункт назначения:" << endl;
		cin >> destination;
		bus->setDestination(destination);
		cout << "Введите время отправки в формате HH:MM" << endl;		
		while (!isRighhtFormatTime(startTime))
		{
			cin >> startTime;
		}
		bus->setStartTime(startTime);
		cout << "Введите время прибытия в формате HH:MM" << endl;
		while (!isRighhtFormatTime((endTime)))
		{
			cin >> endTime;
		}
		bus->setEndTime(endTime);
		writeInFile(bus);
		getMainMenu();
	}
	static void getChooseDirection()
	{
		string destination;
		system("cls");
		cout << "Введите нужное направление" << endl;
		cin >> destination;
		if (readOfFile(path,destination).empty())
		{
			cout << "Автобусов в данном направлении нет" << endl;
		}
		else {
			cout << "Номер автобуса\t" << "Тип автобуса\t" << "Время в пути" << endl;
			for (auto& it : readOfFile(path,destination))
			{
				cout <<"      "<< to_string(it.second.getNumber()) + "\t"<< it.second.getType() + "\t"<< getTimeInPathForPrint(it.first) + "\t" << endl;
			} 
		}
		goBackToMainMenu();

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
					busesMap.insert(pair<double, Bus>(getTimeInPath(bus.getStartTime(),bus.getEndTime()), bus));
				}
			}
		}
		fin.close();
		return busesMap;
	}
	 static void goBackToMainMenu()
		{
		char er;
		cout << endl;
		cout << "Введите 1 для возврата в главное меню" << endl;	
			cin >> er;			
			if (er == '1')
			{
				system("cls");
				getMainMenu();
			}
			else
			{
				system(("cls"));
				goBackToMainMenu();
			}
		}
	static bool isRighhtFormatTime(string s)
	{
		int hours;
		int minutes;
		if (s.size()<5)
		{
			return false;
		}
		string str_hours = s.substr(0, 2);
		string str_minutes = s.substr(3, 2);
			hours = atoi(str_hours.c_str());
			minutes = atoi(str_minutes.c_str());

		return !(hours < 0 || hours > 24 || minutes < 0 || minutes > 60);
	}

	static double getTimeInPath(string start,string end)
	{
		int hours = atoi(end.substr(0, 2).c_str()) - atoi(start.substr(0, 2).c_str());
		int minutes = abs(atoi(end.substr(3, 2).c_str()) - atoi(start.substr(3, 2).c_str()));
		return stod(to_string(hours) + "," + to_string(minutes));
	}

	static string getTimeInPathForPrint(double time)
	{
		string hours;
		string minutes;
		if (isdigit(to_string(time).at(1)))
		{
			hours = to_string(time).substr(0, 2);
			minutes = to_string(time).substr(3, 2);
		}
		else
		{
			hours = to_string(time).substr(0, 1);
			minutes = to_string(time).substr(2, 2);
		}
		return hours + " часов  " + minutes + " минут";
	}
};

