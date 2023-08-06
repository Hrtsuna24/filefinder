#pragma once
#include <list>
#include <string>
#include <mutex>

using std::list;
using std::string;
using std::mutex;
using std::lock_guard;

class FileMonitor
{
	list<string> m_allDirsAndFiles;
	mutex m_mtx;
public:
	void print(const string& name);
	void push_back(string str);
	void pop_back();
	void push_front(string str);
	void pop_front();
	bool isEmpty();
	string back();
};

