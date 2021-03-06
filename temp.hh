// temp.h
// Brandon Finley
// Noodles around with Temps and Labels.
// data representations inspired by ktok07b6 @ github

#pragma once
#include <string>
#include <vector>

class _TempMap;
using Temp_map = _TempMap*;
class Temp_temp {
	public:
		Temp_temp(int num);
		Temp_temp();
        //Temp_temp(/**/);
		~Temp_temp();
        std::string toString()const;
        //std::string toString()const{return specialName;}
	private:
		int num;
        //std::string specialName;
		//static int count;
};

// methods on Temp_temp:
Temp_temp newtemp();
	// call constructor

/*	//////////////	*/

class Temp_label {
	public:
		Temp_label(const std::string &in_name);
		Temp_label(int in_num);
		Temp_label();
		~Temp_label();
		std::string toString() const;
	private:
		std::string name;
		//int num;
};

// methods on Temp_label:
Temp_label newlabel();
Temp_label newnamedlabel(std::string s);
	// call constructor
//Temp_label namedlabel(std::string){};
	// call constructor

class Temp_tempList{
	public:

	private:
		std::vector<Temp_temp*> tempList;
};
