#pragma once
#include <iostream>
#include <string>
using namespace std;

class Student
{
public:
	//����/��������
	Student();
	~Student();

	//get/set����
	string get_name();
	void set_name(string name);
	unsigned get_age();
	void set_age(unsigned age);

	//��ӡ����
	void print();

private:
	string _name;
	unsigned _age;
};