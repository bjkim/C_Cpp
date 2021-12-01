#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>
#include <cstring>
#include <initializer_list>
#include <exception>
#include <memory>

#include "AutoPtr.h"
#include "Resource.h"
#include "Timer.h"

using namespace std;

template <class T>
void MySwap(T &a, T &b) // std::swap
{
	//T tmp = a;
	//a = b;
	//b = tmp;

	T tmp{std::move(a)};
	a = std::move(b);
	b = std::move(tmp);
};

AutoPtr<Resource<int>> generateResource()
{
	AutoPtr<Resource<int>> res(new Resource<int>(10000000));

	return res;
}

int main()
{
	streambuf *orig_buf = cout.rdbuf();
	//cout.rdbuf(NULL); // disconnect cout from buffer

	Timer timer;

	/*{
		AutoPtr<Resource<int>> main_res;
		main_res = generateResource();
	}*/
	/*{
		AutoPtr<Resource<int>> res1(new Resource<int>(10000000));

		cout << res1.m_ptr << endl;
		
		AutoPtr<Resource<int>> res2 = res1;

		cout << res1.m_ptr << endl;
		cout << res2.m_ptr << endl;
	}*/

	/*{
		AutoPtr<Resource<int>> res1(new Resource<int>(3));
		res1->setAll(3);
		
		AutoPtr<Resource<int>> res2(new Resource<int>(5));
		res2->setAll(5);

		res1->print();
		res2->print();

		MySwap(res1, res2);

		res1->print();
		res2->print();
	}*/

	/*{
		vector<string> v;
		string str = "Hello";

		v.push_back(str);

		cout << str << endl;
		cout << v[0] << endl;

		v.push_back(std::move(str));

		cout << str << " " << v[1] << endl;
		cout << v[0] << " " << v[1] << endl;
	
	}*/

	/*{
		std::string x{ "abc" };
		std::string y{ "de" };

		std::cout << "x :" << x << std::endl;
		std::cout << "y :" << y << std::endl;

		MySwap(x, y);

		std::cout << "x :" << x << std::endl;
		std::cout << "y :" << y << std::endl;
	}*/
	//{
	//	auto res1 = std::make_unique < Resource<int>>(5);
	//	res1->setAll(1);
	//	res1->print();

	//	std::cout << std::boolalpha;
	//	std::cout << static_cast<bool>(res1) << std::endl;

	//	//doSomething2(res1.get());
	//	doSomething2(std::move(res1));

	//	std::cout << std::boolalpha;
	//	std::cout << static_cast<bool>(res1) << std::endl;
	//	res1->print();
	//
	//}

	cout.rdbuf(orig_buf);

	cout << endl;
	timer.elapsed();

	return 0;
}
