#include "FileMonitor.h"
#include <iostream>

void FileMonitor::print()
{
	lock_guard<mutex> lck(m_mtx);
	for(const string& name: m_allFiles)
	{
		std::cout << name << std::endl;
	}
}

void FileMonitor::push_back(string str)
{
	lock_guard<mutex> lck(m_mtx);
	m_allFiles.push_back(std::move(str));
}
