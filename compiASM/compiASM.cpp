#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;



int main(int argc, char **argv)
{
	std::ifstream readJSON ("/home/kali/Documents/Compi/compiASM/x86data.json");
	json x86data;
	readJSON >> x86data;
	readJSON.close();
	
	//https://stackoverflow.com/questions/33028955/how-to-search-for-the-value-of-an-object-in-a-json-file
	for (const auto& obj : x86data["instructions"]) {
		if (obj[0] == "mov") {
			std::cout << obj << std::endl;
		}
	}
	
	
	
	return 0;
}
