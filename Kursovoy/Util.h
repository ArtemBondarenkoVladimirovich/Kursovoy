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
const static string PATH = "E:\\myBuses.txt";
class Util
{
public:
	//call main menu our program 
	static int getMainMenu()
	{
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		setlocale(LC_ALL, "rus");
		char i;
		system("cls");
		cout << "��������� ��� ����� � ������ ���������" << endl;
		cout << "1.�������� �������" << endl;
		cout << "2.������ ��������� � �������� �����������" << endl;
		cout << "3.����� �� ���������" << endl;
		cin >> i;
		switch (i)
		{
		case '1':inputBus(); break;
		case '2':getChooseDirection(); break;
		case '3':exit(0);
		default: break;
		}
		return 0;
	}
private:
	//Input data of bus and write to file
	static void inputBus()
	{
		string number,type, destination, startTime, endTime;
		Bus bus;
		system("cls");
		cout << "������� ����� ��������:" << endl;
		do
		{
			cin >> number;
		} while (!isInt(number));
		bus.setNumber(stoi(number));
		cout << "������� ��� ��������:" << endl;
		cin >> type;
		bus.setType(type);
		cout << "������� ����� ����������:" << endl;
		cin >> destination;
		bus.setDestination(destination);
		cout << "������� ����� �������� � ������� HH:MM" << endl;
		while (!isRightFormatTime(startTime))
		{
			cin >> startTime;
		}
		bus.setStartTime(startTime);
		cout << "������� ����� �������� � ������� HH:MM" << endl;
		while (!isRightFormatTime((endTime)))
		{
			cin >> endTime;
		}
		bus.setEndTime(endTime);
		writeInFile(bus);
		getMainMenu();
	}
	//call menu input destination for search buses in current direction
	static void getChooseDirection()
	{
		string destination;
		system("cls");
		cout << "������� ������ �����������" << endl;
		cin >> destination;
		if (readOfFile(PATH, destination).empty())
		{
			cout << "��������� � ������ ����������� ���" << endl;
		}
		else {
			cout << "����� ��������\t" << "��� ��������\t" << "����� � ����" << endl;
			for (auto& it : readOfFile(PATH, destination))
			{
				cout << "      " << to_string(it.second.getNumber()) + "\t" << it.second.getType() + "\t" << getTimeInPathForPrint(it.first) + "\t" << endl;
			}
		}
		goBackToMainMenu();

	}
	//write in file information about bus 
	static void writeInFile(Bus bus)
	{
		ofstream fout;
		fout.open(PATH, ofstream::app);
		if (!fout.is_open())
		{
			cout << "������ �������� �����!" << endl;
		}
		else
		{
			fout << bus.getNumber() << "\t" << bus.getType() << "\t" << bus.getDestination() << "\t" << bus.getStartTime() << "\t" << bus.getEndTime() << endl;
		}
		fout.close();
	}
	/*read bus out of file and put buses in current direction in multimap where key is time of trip ,
	value is object of type Bus.Method return multimap<double,Bus>*/
	static multimap<int, Bus> readOfFile(string path, string dest)
	{
		multimap<int, Bus> busesMap;
		string line;
		ifstream fin;
		fin.open(path);
		if (!fin.is_open())
		{
			cout << "������ �������� �����!" << endl;
		}
		else
		{
			while (getline(fin, line))
			{
				int number;
				string type, destination, startTime, endTime;
				istringstream iss(line);
				iss >> number >> type >> destination >> startTime >> endTime;
				Bus bus(number, type, destination, startTime, endTime);
				if (bus.getDestination() == dest)
				{
					busesMap.insert(pair<int, Bus>(getTimeInPath(bus.getStartTime(), bus.getEndTime()), bus));
				}
			}
		}
		fin.close();
		return busesMap;
	}
	//return to main menu
	static void goBackToMainMenu()
	{
		char er;
		cout << endl;
		cout << "������� 1 ��� �������� � ������� ����" << endl;
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
	//return correctness of input time
	static bool isRightFormatTime(string time)
	{
		int hours;
		int minutes;
		if (time.size() < 5 || !isInt(time.substr(0,2)) || !isInt(time.substr(3, 2)))
		{
			return false;
		}
		string str_hours = time.substr(0, 2);
		string str_minutes = time.substr(3, 2);
		hours = stoi(str_hours);
		minutes = stoi(str_minutes);
		return !(hours < 0 || hours > 24 || minutes < 0 || minutes > 60);
	}
	//return time in trip
	static int getTimeInPath(string start, string end)
	{
		return  stoi(end.substr(0, 2)) * 60 + stoi(end.substr(3, 2))
			- stoi(start.substr(0, 2)) * 60 - stoi(start.substr(3, 2));
	}
	//return time of trip in format HH ����� mm ����� for output on screen 
	static string getTimeInPathForPrint(int time)
	{
		return to_string((time / 60)) + " �����  " + to_string((time % 60)) + " �����";
	}
	//checking string to integer
	static bool isInt(string number)
	{
		try
		{
			stoi(number);
			return true;
		}
		catch (invalid_argument & e)
		{
			return false;
		}
	}
};
