#pragma once

#include <filesystem>
#include <vector>
#include <string>
#include <future>
#include <iostream>
#include <thread>

#include "FileMonitor.h"

using std::vector;
using std::string;
using std::filesystem::path;
using std::filesystem::directory_iterator;
using std::future;
using std::cout;
using std::async;
using std::ref;

//vector<string> listDir(path const& dir);
//
//vector<string> listDirs(vector<path> const& paths);

void listDir(string path, FileMonitor& fileSink);

void listDirs(vector<path> paths, FileMonitor& fileSink);