#pragma once
#include <vector>
#include <string>
#include <mutex>

using std::vector;
using std::string;
using std::mutex;
using std::lock_guard;

class FileMonitor
{
	vector<string> m_allFiles;
	mutex m_mtx;
public:
	void print();
	void push_back(string str);
};

