#include "FileMonitor.h"
#include <iostream>

void FileMonitor::print(const string& name)
{
	lock_guard<mutex> lck(m_mtx);
	std::cout << name << std::endl;
}

void FileMonitor::push_back(string str)
{
	lock_guard<mutex> lck(m_mtx);
	m_allDirsAndFiles.push_back(std::move(str));
}

void FileMonitor::pop_back()
{
	lock_guard<mutex> lck(m_mtx);
	if (!m_allDirsAndFiles.empty())
		m_allDirsAndFiles.pop_back();
}

void FileMonitor::push_front(string str)
{
	lock_guard<mutex> lck(m_mtx);
	m_allDirsAndFiles.push_front(std::move(str));
}

void FileMonitor::pop_front()
{
	lock_guard<mutex> lck(m_mtx);
	if (!m_allDirsAndFiles.empty())
		m_allDirsAndFiles.pop_front();
}

bool FileMonitor::isEmpty()
{
	lock_guard<mutex> lck(m_mtx);
	return m_allDirsAndFiles.empty();
}

string FileMonitor::back()
{
	lock_guard<mutex> lck(m_mtx);
	string tmp = m_allDirsAndFiles.back();
	m_allDirsAndFiles.pop_back();
	return tmp;
}