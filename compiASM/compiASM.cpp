#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "json.hpp"
#include "parseASM.h"

using json = nlohmann::json;



int main(int argc, char **argv)
{
	std::ifstream readJSON ("/home/kali/Documents/Compi/compiASM/x86data.json");
	json x86data;
	readJSON >> x86data;
	readJSON.close();
	
	
	std::string asmLine[4] = {"xor","eax","eax",""};
	std::string * asmLineParsed = new std::string[4];
	parseLine(x86data, asmLine, asmLineParsed);
	
	
	
	
	
	//////////////////debug/////////////////////////
	 for (int i = 0; i < 4; i++){
		std::cout << asmLine[i] << " "; 
	} 
	
	std::cout << "\n" << "\n";
	
	 for (int i = 0; i < 4; i++){
		std::cout << asmLineParsed[i] << " "; 
	} 
	
	std::cout << "\n" << "\n";
	///////////////////////////////////////////////
	
	
	
	
	searchForInstruction(x86data, asmLineParsed, asmLine);
	delete[] asmLineParsed; //this should maybe be built into the search or something
	
	
	
	return 0;
}

