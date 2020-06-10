#include "elf64.h"
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>



int findSizeOfFile(const char * file_name){		//returns filesize in bytes
	
	std::ifstream readFileStream(file_name, std::ios::out | std::ios::binary);
	
	if (!readFileStream){
		std::cout << "ERROR: Cannot open file " << file_name << "\n"; //error handling
	}
	
	readFileStream.ignore( std::numeric_limits<std::streamsize>::max() );
	std::streamsize length = readFileStream.gcount();
	readFileStream.clear();   						//not needed?
	readFileStream.seekg( 0, std::ios_base::beg ); 	//not needed?
	
	if (!readFileStream.good()){
		std::cout << "ERROR: Error reading size of file " << file_name << "\n";
	}
	
	readFileStream.close();
	
	return (int) length;
}




void printHeader(Elf64_Ehdr printHeader){ //debug tool
	std::cout << "Magic: ";
    for (int i = 0; i < 16; i++){
		std::cout << std::setfill('0') << std::setw(2) << std::right << std::hex << (int) printHeader.e_ident[i] << std::dec << ' ';
	}
    std::cout << "\n";
	std::cout << "File type: " << printHeader.e_type << "\n";
	std::cout << "Machine: " << printHeader.e_machine << "\n";
	std::cout << "Version: " << printHeader.e_version << "\n";
	std::cout << "Entry point address: " << printHeader.e_entry << "\n";
	std::cout << "Program header table offset: " << printHeader.e_phoff << "\n";
	std::cout << "Section header table offset: " << printHeader.e_shoff << "\n";
	std::cout << "Flags: " << printHeader.e_flags << "\n";
	std::cout << "Header size: " << printHeader.e_ehsize << "\n";
	std::cout << "Program header size: " << printHeader.e_phentsize << "\n";
	std::cout << "Number of program headers: " << printHeader.e_phnum << "\n";
	std::cout << "Size of section headers: " << printHeader.e_shentsize << "\n";
	std::cout << "Number of section headers: " << printHeader.e_shnum << "\n";
	std::cout << "String table offset: " << printHeader.e_shstrndx << "\n";
}


bool createELF (const char * text_name, const char * data_name, const char * file_name, const void** structPointerArray){
	
	std::ofstream fileStream(file_name, std::ios::out | std::ios::binary); //open write file, should probably live in its own function (how tf do you pass a stream?)
	if (!fileStream){
		std::cout << "ERROR: Cannot open file " << file_name << "\n"; //error handling
	}
	
	
	//dump header into file
	fileStream.write((const char *) structPointerArray[0], 64);
	
	
	//dump program header files
	for(int i = 1; i < 4; i++){
		fileStream.write((const char *) structPointerArray[i], 56); //size-8 (program header size) should probably be an argument or these should just both be hardcoded
		//for (int j = 0; j < 8; j++){
			//fileStream << '\0';
		//}
	}
	
	
	//pad until 0x1000 for .text
	//TODO this should pad until where the program header says
	int currentSize = fileStream.tellp();
	int neededPadding = (int)((0x1000 - currentSize));
	
	for (int j = 0; j < neededPadding; j++){
			fileStream << '\0';
		}
	
	
	//dump .text @ 0x1000
	std::ifstream readFileStream(text_name, std::ios::out | std::ios::binary);
	char value;
	while (readFileStream.get(value)){
		fileStream << value;
	}
	readFileStream.close();
	
	
	//pad until 0x2000
	//TODO this should pad until where the program header says
	currentSize = fileStream.tellp();
	neededPadding = (int)((0x2000 - currentSize));
	
	for (int j = 0; j < neededPadding; j++){
			fileStream << '\0';
		}
	
	
	//dump .data @ 0x2000
	std::ifstream readFileStream2(data_name, std::ios::out | std::ios::binary);
	while (readFileStream2.get(value)){
		fileStream << value;
	}
	readFileStream2.close();
	
	
	//pad out eof to fit nicely
	currentSize = fileStream.tellp();
	neededPadding = (16 - (currentSize % 16));
	
	for (int j = 0; j < neededPadding; j++){
			fileStream << '\0';
		}
	
	//close and handle errors
	fileStream.close();
	if (!fileStream.good()){
		std::cout << "ERROR: Writing to " << file_name << "\n"; //error handling
	}
	return;
}


//from https://stackoverflow.com/questions/7775991/how-to-get-hexdump-of-a-structure-data
void hexDump (const char * desc, const void * addr, const int len) {
    int i;
    unsigned char buff[17];
    const unsigned char * pc = (const unsigned char *)addr;

    // Output description if given.

    if (desc != NULL)
        printf ("%s:\n", desc);

    // Length checks.

    if (len == 0) {
        printf("  ZERO LENGTH\n");
        return;
    }
    else if (len < 0) {
        printf("  NEGATIVE LENGTH: %d\n", len);
        return;
    }

    // Process every byte in the data.

    for (i = 0; i < len; i++) {
        // Multiple of 16 means new line (with line offset).

        if ((i % 16) == 0) {
            // Don't print ASCII buffer for the "zeroth" line.

            if (i != 0)
                printf ("  %s\n", buff);

            // Output the offset.

            printf ("  %04x ", i);
        }

        // Now the hex code for the specific character.
        printf (" %02x", pc[i]);

        // And buffer a printable ASCII character for later.

        if ((pc[i] < 0x20) || (pc[i] > 0x7e)) // isprint() may be better.
            buff[i % 16] = '.';
        else
            buff[i % 16] = pc[i];
        buff[(i % 16) + 1] = '\0';
    }

    // Pad out last line if not exactly 16 characters.

    while ((i % 16) != 0) {
        printf ("   ");
        i++;
    }

    // And print the final ASCII buffer.

    printf ("  %s\n", buff);
}
