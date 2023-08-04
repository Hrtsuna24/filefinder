#include <iostream>
#include <thread>
#include <vector>
#include <list>
#include <filesystem>
#include <string>
#include <execution>

using std::filesystem::directory_iterator;
using std::filesystem::is_directory;
using std::cout;
using std::vector;
using std::string;

void get_files(const std::string& current_path, const std::string& target);
int threadsAmount = 8;

int main() {

	string target = "Ex10.uproject";
	string path = "D:\\";

	get_files(path, target);

	return 0;
}


void get_files(const std::string& current_path, const std::string& target)
{
	std::list<string> directory_to_visit;
	directory_to_visit.push_back(current_path);

	while (!directory_to_visit.empty())
	{
		directory_iterator currentDirr;
		try
		{
			currentDirr = directory_iterator(directory_to_visit.back());
		}
		catch (const std::filesystem::filesystem_error& fe)
		{
			//cout << fe.what() << std::endl;
			directory_to_visit.pop_back();
		}
		directory_to_visit.pop_back();
		std::for_each(
			std::filesystem::begin(currentDirr),
			std::filesystem::end(currentDirr),
			[&directory_to_visit, &target](const std::filesystem::directory_entry& file) //
			{
				//find target file
				if (file.path().filename().string().compare(target) == 0)
				{
					cout << file.path().string() << std::endl;
					return;
				}
			if (is_directory(file))
			{
				directory_to_visit.emplace_front(file.path().string());
			}
			});
	}
}
