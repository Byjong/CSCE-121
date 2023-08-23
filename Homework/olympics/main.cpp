/******************************************************************************

File: main.cpp
Author: Prof. Lupoli & Andrew Nemec
Date: 2/16/2021
Section: 
E-mail: slupoli@tamu.edu
Description:
This file contains C++  code that will simulate data collected from a track 
event with 9 lanes. The code will sort the order, then display the results

Updates
Author: J. Michael Moore & Paul Taele

Data File Information
name: data.text
content: The text file will contain data in the constant form of:
<Time (double)> <Abbreviated Country (String)> <Uniform number (int)> <Lastname (String)>
32.7 USA 12 Moore
36.5 RUS 35 Polsley
45.8 ENG 73 Teale
52.34 CHN 14 Nemec
76.45 ITY 23 Lupoli     

*******************************************************************************/

#include <iostream>
#include "parallel_tracks.h"

using std::cin; using std::cout; using std::endl;
using std::string; using std::getline; using std::ifstream;
using std::invalid_argument; using std::domain_error;

int main()
{
	double times[SIZE];
	string countries[SIZE];
	unsigned int jerseys[SIZE];
	string lastnames [SIZE];
	unsigned int ranks[SIZE];
	
	prep_double_array(times);
	prep_string_array(countries);
	prep_unsigned_int_array(jerseys);
	prep_string_array(lastnames);
	prep_unsigned_int_array(ranks);

	bool good = false;
	while(!good){
		try{
			string filename = "";
			cout << "Enter file name: ";
			cin >> filename;
			get_runner_data(filename, times, countries, jerseys, lastnames);
			get_ranking(times, ranks);
			print_results(times, countries, lastnames, ranks);
			good = true;
		}
		catch(std::invalid_argument& e){
			cout << "Invalid File: "<< e.what() << endl;
			good = false;
		}
		catch(std::domain_error& e){
			cout << "Invalid File: "<< e.what() << endl;
			good = false;
		}
	}
    return 0;
}

