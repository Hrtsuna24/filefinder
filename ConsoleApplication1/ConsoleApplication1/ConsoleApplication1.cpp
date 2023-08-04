#include <thread>
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <future>

namespace HTS
{
	using std::thread;
	using std::vector;
	using std::cout;
	using std::promise;
	using std::string;
	using std::future;
}

void fun(std::promise<std::string>&& pr)
{
	std::cout << "Worker throwing \n";
	//pr.set_value("Message from thread");
	try
	{
		throw std::exception("exception");
	}
	catch (...)
	{
		pr.set_exception(std::current_exception());
	}
}

std::string fun(bool flag)
{
	if (flag)
	{
		return "Message";
	}
	else
	{
		throw std::exception("aaaaaa");
		return "Message";
	}
}

void main()
{
	using namespace HTS;

	/*promise<string> pr;
	future<string> fut = pr.get_future();
	thread th(fun, std::move(pr));

	cout << "Main recived: \n";
	try
	{
		cout << fut.get();
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
	th.join();*/


	/// <summary>
	/// ////////////////////////////////
	/// </summary>
	future<string> fut = std::async(fun, true);
	cout << "Main recived: \n";
	try
	{
		cout << fut.get();
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
}