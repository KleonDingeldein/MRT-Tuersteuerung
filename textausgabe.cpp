/*
 * Textausgabe.cpp
 *
 *  Created on: 20.06.2023
 *      Author: mrt
 */

#include "Textausgabe.h"


void schreibe(string x) {
	string filename("tmp.txt");
	fstream file_out;

	file_out.open(filename, std::ios_base::app);
	file_out << x << endl;
}

void schreibe(int x) {
	string filename("tmp.txt");
	fstream file_out;

	file_out.open(filename, std::ios_base::app);
	file_out << x << endl;
}

void schreibe(float x) {
	string filename("tmp.txt");
	fstream file_out;

	file_out.open(filename, std::ios_base::app);
	file_out << x << endl;
}

void schreibe(size_t x) {
	string filename("tmp.txt");
	fstream file_out;

	file_out.open(filename, std::ios_base::app);
	file_out << x << endl;
}


