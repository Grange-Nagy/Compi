#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include "json.hpp"


using json = nlohmann::json;

//returns the binary representation of the register
std::bitset<4> getRegisterEncode(json x86data, const std::string registerString){
	//std::cout << "regstring: " << registerString << "\n";
	for (const auto& encodeDataLine : x86data["registerEncode"]){
			for (int j = 1; j < 12; j++){
				if (encodeDataLine[j] == registerString){
					std::bitset<4> returnBitset((std::string)encodeDataLine[0]);
					return returnBitset;
				}
			}
	}
	std::cout << "FATAL ERROR: COULD NOT FIND REGISTER ENCODE\n";
	return NULL;
}





std::string getRegisterClass(json x86data, const std::string registerString){
	
	//support for registers r8-15(b,w,d)
	if ((registerString.front()) > '`'){									//check if the first value of the register string is lowecase
		if (registerString.front() == 'r' && registerString.at(1) < ':'){	//check if it is a r ranged register
			char lastChar = registerString.back();
			if (lastChar < ':'){		//quadword r
				return "r64";
			}else if(lastChar == 'd'){	//doubleword r
				return "r32";
			}else if(lastChar == 'w'){	//word r
				return "r16";
			}else if(lastChar == 'b'){	//byte r
				return "r8";
			}else{
				return "ERROR";
			}
			
		}
		
		//TODO check for the other registers i.e. cr0-15, zmm0-31
		
		
		for (const auto& registerDataLine : x86data["registers"]) {				//walk down the register lines
			for (const auto& registerNameLine : registerDataLine["names"]){		//walk down the names
				if (registerNameLine == registerString){
					return registerDataLine["any"];								//return the class in "any"
				}
			}
		}
		return "ERROR";
	}else{
		return "NOT REGISTER";
	}
}




std::string getImmediateClass(json x86data, const std::string immediateString){
	if (immediateString.front() == '0'){
		int immediateBytes = ((immediateString.length())-2)/2; //get the bytes of the hex
		if (immediateBytes == 8){		//qword 
			return "iq";
		}else if(immediateBytes == 4){	//dword
			return "id";
		}else if(immediateBytes == 2){	//word
			return "iw";
		}else if(immediateBytes == 1){	//byte
			return "ib";
		}else return "MALFORMED IMMEDIATE";
	}else{
		return "NOT AN IMMEDIATE";
	}

}


void parseLine(json x86data, const std::string * asmLine, std::string * asmLineParsed){
	asmLineParsed[0] = asmLine[0];
	asmLineParsed[1] = asmLine[1];
	asmLineParsed[2] = asmLine[2];
	asmLineParsed[3] = asmLine[3];
	
	for (int indexLine = 1; indexLine < 4; indexLine++){
		std::string regCheck = getRegisterClass(x86data, asmLine[indexLine]);
		if (regCheck == "NOT REGISTER"){
			std::string imCheck = getImmediateClass(x86data, asmLine[indexLine]);
			if (imCheck == "MALFORMED IMMEDIATE"){
				//error handling
				std::cout << indexLine << "\n";
				std::cout << imCheck << "\n";
			}else if(imCheck == "NOT AN IMMEDIATE"){
				//deal with other
			}else {
				asmLineParsed[indexLine] = imCheck;
			}
			//not a register do something
		}else if (regCheck == "ERROR"){
			std::cout << "ERROR PARSING OPERAND";
		}else{
			//is a register
			asmLineParsed[indexLine] = regCheck;
		}
	}
	//TODO fix this memory garbage with a vector or something
	//delete[] asmLineParsed;
}


std::vector <std::string> searchForInstruction(json x86data, const std::string * asmLineParsed, const std::string * asmLine){
	
	for (const auto& instructionDataLine : x86data["instructions"]) {
		//std::string noPermString = instructionDataLine[1];
		//if (noPermString.length() > 3){
			//noPermString = noPermString.substr(2, noPermString.length());
			//std::cout << noPermString << "\n";
		//}
		
		if (instructionDataLine[0] == asmLineParsed[0]){
			std::string currentInstructionStringArray[3] = {"","",""};
			int instructionCounter = 0;
			std::string instructionRAW = instructionDataLine[1];
			//std::cout << "instructionRAW: " << instructionRAW << "\n";
			//std::cout << "size " << instructionRAW.capacity() << "\n";
		for (std::string::iterator stringPointer = (instructionRAW.begin()+2); stringPointer != instructionRAW.end(); stringPointer++){
				//std::cout << "stringpointer @ " << stringPointer << " is :" << instructionRAW[stringPointer] << "\n";
				if (*stringPointer == ','){
					instructionCounter++;
					stringPointer++;
				}else{
					currentInstructionStringArray[instructionCounter].push_back(*stringPointer);
				}
			}
			
			
			//std::cout << currentInstructionStringArray[0] << "\n";
			//std::cout << currentInstructionStringArray[1] << "\n";
			//std::cout << currentInstructionStringArray[2] << "\n";
			
			
			if (currentInstructionStringArray[0].find(asmLineParsed[1]) != std::string::npos 
			&&  currentInstructionStringArray[1].find(asmLineParsed[2]) != std::string::npos 
			&&  currentInstructionStringArray[2].find(asmLineParsed[3]) != std::string::npos){
				//std::cout << "FOUND!" << "\n";
				std::vector <std::string> returnLINE;
				for (int i = 0; i < 5; i++){
					returnLINE.push_back(instructionDataLine[i]);
					//std::cout << "instructionLINEdata: " << returnLINE[i] << "\n";
				}
				
				return returnLINE;
			}
		}
	}
	std::vector <std::string> NULLreturn = {""};
	return NULLreturn;
}



std::bitset<8> createREXW(json x86data, std::vector <std::string> instructionVector, const std::string * asmLine){
	std::bitset<8> rexwBitset("01001000");
	int operandCount = 0;
	for (int i = 1; i < 3; i++){
		if (asmLine[i] != ""){
			operandCount++;
		}
	}
	int indexR = -1;
	for (int j = 0; j < operandCount; j++){
		if (instructionVector[2][j] == 'R'){
			//std::cout << "found R @ " << j << "\n";
			indexR = j;
			break;
		}
	}
	
	
	
	if (indexR == -1){
		//std::cout << "R NOT FOUND IN REXW INSTRUCTION\n";
	}else{
		std::bitset<4> encodeBitset = getRegisterEncode(x86data, asmLine[indexR+1]);
		//std::cout << encodeBitset << "\n";
		rexwBitset[2] = encodeBitset[3];
		//std::cout << rexwBitset << "\n";
	}
	
	
	int indexM = -1;
	for (int k = 0; k < operandCount; k++){
		if (instructionVector[2][k] == 'M'){
			//std::cout << "found M @ " << k << "\n";
			indexM = k;
			break;
		}
	}
	if (indexM == -1){
		//std::cout << "M NOT FOUND IN REXW INSTRUCTION\n";
	}else{
		std::bitset<4> encodeBitset2 = getRegisterEncode(x86data, asmLine[indexM+1]);
		//std::cout << encodeBitset2 << "\n";
		rexwBitset[0] = encodeBitset2[3];
		//std::cout << rexwBitset << "\n";
	}
	
	
	
	//std::cout << "REX.W is: 0x" << std::hex << std::uppercase << rexwBitset.to_ulong();
	//std::cout << operandCount << "\n";
	
	
	return rexwBitset;
}

std::bitset<8> createModRM(json x86data, std::vector <std::string> instructionVector, const std::string * asmLine){
	std::bitset<8> modRMBitset("11000000");
	int operandCount = 0;
	for (int i = 1; i < 3; i++){
		if (asmLine[i] != ""){
			operandCount++;
		}
	}
	int indexM = -1;
	for (int j = 0; j < operandCount; j++){
		if (instructionVector[2][j] == 'M'){
			//std::cout << "found M @ " << j << "\n";
			indexM = j;
			break;
		}
	}
	
	
	
	if (indexM == -1){
		//std::cout << "M NOT FOUND IN modRM INSTRUCTION\n";
	}else{
		std::bitset<4> encodeBitset = getRegisterEncode(x86data, asmLine[indexM+1]);
		//std::cout << encodeBitset << "\n";
		modRMBitset[2] = encodeBitset[2];
		modRMBitset[1] = encodeBitset[1];
		modRMBitset[0] = encodeBitset[0];
		//std::cout << modRMBitset << "\n";
	}
	
	
	int indexR = -1;
	for (int k = 0; k < operandCount; k++){
		if (instructionVector[2][k] == 'R'){
			//std::cout << "found M @ " << k << "\n";
			indexR = k;
			break;
		}
	}
	if (indexR == -1){
		//std::cout << "M NOT FOUND IN modRM INSTRUCTION\n";
	}else{
		std::bitset<4> encodeBitset2 = getRegisterEncode(x86data, asmLine[indexR+1]);
		//std::cout << encodeBitset2 << "\n";
		modRMBitset[5] = encodeBitset2[2];
		modRMBitset[4] = encodeBitset2[1];
		modRMBitset[3] = encodeBitset2[0];
		//std::cout << modRMBitset << "\n";
	}
	
	
	
	//std::cout << "modRM is: 0x" << std::hex << std::uppercase << modRMBitset.to_ulong();
	//std::cout << operandCount << "\n";
	
	
	return modRMBitset;
}


