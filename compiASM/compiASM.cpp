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
	
	
	std::string asmLine[4] = {"cmp","rax","0x0a",""};
	std::string asmLineParsed[4] = {asmLine[0], asmLine[1], asmLine[2], asmLine[3]};
	
	for (int indexLine = 1; indexLine < 4; indexLine++){
		std::string regCheck = getRegisterClass(x86data, asmLine[indexLine]);
		if (regCheck == "NOT REGISTER"){
			//not a register do something
		}else if (regCheck == "ERROR"){
			std::cout << "ERROR PARSING OPERAND";
		}else{
			//is a register
			asmLineParsed[indexLine] = regCheck;
		}
	}
	
	 for (int i = 0; i < 4; i++){
		std::cout << asmLineParsed[i] << "\n"; 
	} 
	
	std::string operandString;
	if (asmLineParsed[1].front() == 'r'){
		operandString.append("X:");
		operandString.append(asmLineParsed[1]);
		operandString.append("/m");
		operandString.append(asmLineParsed[1].begin()+1, asmLineParsed[2].end());
		operandString.append(", ");
	}
	operandString = "R:r64/m64, id";
	std::cout << operandString<< "\n";
	//https://stackoverflow.com/questions/33028955/how-to-search-for-the-value-of-an-object-in-a-json-file
	for (const auto& instructionDataLine : x86data["instructions"]) {
		if (instructionDataLine[0] == asmLineParsed[0] && instructionDataLine[1] == operandString) {
			std::cout << instructionDataLine[2] << "\n" << instructionDataLine[3] << "\n" << instructionDataLine[4];
		}
	}
	
	
	
	return 0;
}

