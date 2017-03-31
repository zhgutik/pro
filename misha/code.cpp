#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <conio.h>

using namespace std;

static const char *INPUT_FILE = "input.txt";
static const char *OUTPUT_FILE = "output.txt";

template <typename T>
class functor
{
public:
	T operator()(T& stuff)
	{
		return stuff = stuff*(-1);
	}
};

template <typename T>
class predicate
{
public:
	bool operator()(const T& arg1)
	{
		return arg1<0;
	}
};

template <typename T>
class printer
{
public:
	void operator()(const T& stuff_to_print)
	{
		cout << stuff_to_print << endl;
	}
};

template <typename T>
class input_reader
{
public:
	//TODO: do this cpp11 way
	vector<T> operator()(const char* input)
	{
		fstream F;
		F.open(input);
		vector<T> source_v;
		int k;
		while (!F.eof())
		{
			F >> k;
			source_v.push_back(k);
		}
		F.close();
		return source_v;
	}
};

template <typename T>
class output_writer
{
public:
	void operator()(const char* filename, const vector<T> vector_to_put_out)
	{
		//TODO: do this cpp11 way
		ofstream output_file(filename, ofstream::trunc);
		for (unsigned int i = 0; i<vector_to_put_out.size(); i++)
		{
			output_file << vector_to_put_out[i] << endl;
		}
	}
};

int main()
{
	vector<int> source_v;
	vector<int> target_v;

	input_reader<int> read;
	source_v = read(INPUT_FILE);

	predicate<int> pred;
	copy_if(source_v.begin(), source_v.end(), back_inserter(target_v), pred);

	functor<int> func;
	for_each(target_v.begin(), target_v.end(), func);

	printer<int> printr;
	for_each(target_v.begin(), target_v.end(), printr);

	output_writer<int> write;
	write(OUTPUT_FILE, target_v);

	_getch();
	return 0;
	
}
