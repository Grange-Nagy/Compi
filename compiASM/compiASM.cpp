#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <sstream>
#include "json.hpp"
#include "parseASM.h"

using json = nlohmann::json;



int main(int argc, char **argv)
{
	std::ifstream readJSON ("/home/kali/Documents/Compi/compiASM/x86data.json");
	json x86data;
	readJSON >> x86data;
	readJSON.close();
	
	
	std::string asmLine[4] = {"shrd","rax","r13","0x1a"};
	std::string * asmLineParsed = new std::string[4];
	parseLine(x86data, asmLine, asmLineParsed);
	
	
	
	
	
	//////////////////debug/////////////////////////
	 for (int i = 0; i < 4; i++){
		std::cout << asmLine[i] << " "; 
	} 
	
	std::cout << "\n" << "\n";
	
	 for (int i = 0; i < 4; i++){
		//std::cout << asmLineParsed[i] << " "; 
	} 
	
	//std::cout << "\n" << "\n";
	///////////////////////////////////////////////
	
	
	
	
	std::vector <std::string> instructionVector = searchForInstruction(x86data, asmLineParsed, asmLine);
	std::string opcodeString = instructionVector[3];
	int opcodesCount = (std::count(opcodeString.begin(), opcodeString.end(), ' '))+1;
	std::string opcodeArray[opcodesCount];
	int indexStream = 0;
	std::stringstream opcodeStringStream(opcodeString);
	while (opcodeStringStream.good() && indexStream < opcodesCount){
		opcodeStringStream >> opcodeArray[indexStream];
		indexStream++;
	}
	
	
	for (int printIndex = 0; printIndex < opcodesCount; printIndex++){
		//std::cout << opcodeArray[printIndex];
	}
	//std::cout << "\n";
	
	if (opcodeArray[0] == "REX.W"){
		std::stringstream REXBitConvStream;
		REXBitConvStream << std::hex << std::uppercase << createREXW(x86data, instructionVector, asmLine).to_ulong();
		opcodeArray[0] = REXBitConvStream.str();
	}
	
	
	for (int indexCheckI = 0; indexCheckI < opcodesCount; indexCheckI++){
		for (int indexCheckIeach = 0; indexCheckIeach < opcodesCount; indexCheckIeach++){
			if (opcodeArray[indexCheckIeach] == asmLineParsed[indexCheckI] ){
				opcodeArray[indexCheckIeach] = asmLine[indexCheckI];
			}
	}
	}
	
	
	
	for (int indexCheckRM = 0; indexCheckRM < opcodesCount; indexCheckRM++){
		if (opcodeArray[indexCheckRM] == "/r" || opcodeArray[indexCheckRM] == "/0" ){
			std::stringstream modRMBitConvStream;
			modRMBitConvStream << std::hex << std::uppercase << createModRM(x86data, instructionVector, asmLine).to_ulong();
			opcodeArray[indexCheckRM] = modRMBitConvStream.str();
		}
	}
	
	
	
	
	std::cout << "MACHINE CODE: ";
	for (int printIndex = 0; printIndex < opcodesCount; printIndex++){
		std::cout << opcodeArray[printIndex] << " ";
	}
	std::cout << "\n";
	delete[] asmLineParsed; //this should maybe be built into the search or something
	
	
	
	return 0;
}

