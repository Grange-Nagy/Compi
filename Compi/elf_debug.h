#include "elf64.h"
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>

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


void writeStructPointerArrayToFileAsBinary (const char * file_name, const void** structPointerArray, int size){
	std::ofstream fileStream(file_name, std::ios::out | std::ios::binary); //should probably live in its own function
	if (!fileStream){
		std::cout << "ERROR: Cannot open file " << file_name << "\n"; //error handling
	}
	
	
	for(int i = 0; i < 4; i++){
		fileStream.write((const char *) structPointerArray[i], size); //dumps binary and closes, might want to remove the close and move the open to it's own function
	}
	std::ifstream readFileStream("test_text.dat", std::ios::out | std::ios::binary);
	char value;
	while (readFileStream.get(value)){
		fileStream << value;
	}
	readFileStream.close();
	std::ifstream readFileStream2("test_data.dat", std::ios::out | std::ios::binary);
	while (readFileStream2.get(value)){
		fileStream << value;
	}
	readFileStream2.close();
	
	
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
