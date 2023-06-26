/*
 * Textausgabe.h
 *
 *  Created on: 20.06.2023
 *      Author: mrt
 */

#ifndef TEXTAUSGABE_H_
#define TEXTAUSGABE_H_

// void init_dokument();
#include <fstream>
#include <stdlib.h>


using std::ofstream;
using std::endl;
using std::string;
using std::fstream;
using std::string;

void schreibe(string x);
void schreibe(int x);
void schreibe(float x);





#endif /* TEXTAUSGABE_H_ */

/* Textausgabe in tmp.txt über schreibe(int, float oder string)
 * Textausgabe auf Display über:
 * door_if.DebugString("eeeh Hallo000");
 */
