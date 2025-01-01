#pragma once
#include <string>
#include <iostream>

using namespace std;

class Book
{
public:
	Book(string title, string author);

private:
	string title;
	string author;
};