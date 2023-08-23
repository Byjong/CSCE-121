#include <iostream>
#include <iomanip>
#include <string>
#include "parallel_tracks.h"
#include <sstream>
#include <fstream>
#include <stdexcept>

using std::string, std::ifstream, std::istringstream;

//-------------------------------------------------------
// Name: get_runner_data
// PreCondition:  the prepped parallel arrays , and a legit filename is pass
// PostCondition: all arrays contain data from the text file given
//---------------------------------------------------------
void get_runner_data( const std::string& file, double timeArray[], std::string countryArray[], 
		unsigned int numberArray[], std::string lastnameArray[])
{
	ifstream fin(file);
	if(!fin.is_open()){
	  throw std::invalid_argument("Cannot open file");
	}
	
	string line = "";
	
	double time = 0.0;
	string country = "";
	unsigned int num = 0;
	string lastname = "";
  
	for(unsigned int i = 0; i < SIZE; i++){
		getline(fin, line);
		istringstream sin(line);
		
		if(line.length() <= 1){
			throw std::domain_error("File missing data");
		}
		
		sin >> time;
		if(time < 0 || sin.fail() == true){
			throw std::domain_error("File contains invalid data (time)");
			
		}
		timeArray[i] = time;
		
		sin >> country;
		if(country.length() != 3){
			throw std::domain_error("File contains invalid data (country)");
		}
		else{
			for(long unsigned int c = 0; c < country.length(); c++){
				if(!isupper(country.at(c)) || !isalpha(country.at(c))){
					throw std::domain_error("File contains invalid data (country)");
				}
			}
		}
		countryArray[i] = country;
		
		sin >> num;
		if(num / 100 >= 1 || sin.fail() == true){
			throw std::domain_error("File contains invalid data (number)");
		}
		numberArray[i] = num;
		
		sin >> lastname;
		if(sin.fail()){
			throw std::domain_error("File contains invalid data (name)");
		}
		lastname = trim(lastname);
		if(lastname.length() < 2){
			throw std::domain_error("File contains invalid data (name)");
		}
		else{
			for(long unsigned int j = 0; j < lastname.length(); j++){
				if(!isalpha(lastname.at(j))){
					throw std::domain_error("File contains invalid data (name)");
				}
			}
		}
		lastnameArray[i] = lastname;
	}
}

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  a double arrays is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_double_array(double ary[])
// making sure all values within the array are set to 0.0;
{
	for(unsigned int idx = 0; idx < SIZE; idx++){
		ary[idx] = 0.0;
	}
}

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  an unsigned int arrays is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_unsigned_int_array(unsigned int ary[])
// making sure all values within the array are set to 0;
{
	for(unsigned int idx = 0; idx < SIZE; idx++){
		ary[idx] = 0;
	}
}

//-------------------------------------------------------
// Name: prep_string_array
// PreCondition:  a string arrays is pass in
// PostCondition: data in the array is "N/A" out to determine if
// a value has changed
//---------------------------------------------------------
void prep_string_array(std::string ary[])
// making sure all values within the array are set to "N/A";
{
	for(unsigned int idx = 0; idx < SIZE; idx++){
		ary[idx] = "N/A";
	}
}

//-------------------------------------------------------
// Name: get_ranking
// PreCondition:  just the time array is passed in, and has valid data
// PostCondition: after a very inefficient nested loop to determine the placements 
// and places the ranks in a new array. That new array is returned
//---------------------------------------------------------
void get_ranking(const double timeArray[], unsigned int rankArray[])
{
	for(unsigned int rank = SIZE; rank > 0; rank--){
		double slowest = 0;
		int place = 0;
		
		for(unsigned int idx = 0; idx < SIZE; idx++){
			if(slowest < timeArray[idx] && rankArray[idx] == 0){
				slowest = timeArray[idx];
				place = idx;
			}
		}
		rankArray[place] = rank;
	}
}

//-------------------------------------------------------
// Name: print_results
// PreCondition:  almost all parallel arrays are passed in and have valid data
// PostCondition: after a very inefficient nested loop to determine the ranks
// it then displays then along with a delta in time from the start
//---------------------------------------------------------
void print_results(const double timeArray[], const std::string countryArray[],
		const std::string lastnameArray[], const unsigned int rankArray[])
{

	std::cout << "Final results!!";
	std::cout << std::setprecision(2) << std::showpoint << std::fixed << std::endl;
	double best_time = 0.0;
		
	// print the results, based on rank, but measure the time difference_type
	for(unsigned int j = 1; j <= SIZE; j++)
	{
		
		// go thru each array, find who places in "i" spot
		for(unsigned int i = 0; i < SIZE; i++)
		{
			if(rankArray[i] == 1) // has to be a better way, but need the starting time
			{
				best_time = timeArray[i];
			}
			
			
			if(rankArray[i] == j) // then display this person's data
			{
				// this needs precision display
				std::cout << "[" << j << "]  " << timeArray[i] << " " << std::setw(15) << std::left << lastnameArray[i] << "\t" << "(" << countryArray[i] << ")  +" << (timeArray[i] - best_time) << std::endl; 
			}
			
		}
	}	
}

std::string trim(std::string ret) {
	// remove whitespace from the beginning
	while (!ret.empty() && isspace(ret.at(0))) {
			ret.erase(0, 1);
		}

	// remove whitespace from the end
	//  Note: last index is (.size() - 1) due to 0 based indexing
	while (!ret.empty() && isspace(ret.at(ret.size()-1))) {
		ret.erase(ret.size()-1, 1);
	}
	
	return ret;
}