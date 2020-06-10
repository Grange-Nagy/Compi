#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "json.hpp"


using json = nlohmann::json;


std::string getRegisterClass(json x86data, const std::string registerString){
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

