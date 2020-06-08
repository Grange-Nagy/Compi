#include "elf64.h"
#include <stdio.h>
#include <limits>
#include <iostream>
#include <iomanip>
#include <fstream>

Elf64_Ehdr createHeader(Elf64_Half fileType,
						Elf64_Addr entryAddress, 
						Elf64_Off programHeaderTableOffset, 
						Elf64_Off sectionHeaderTableOffset, 
						Elf64_Half numberOfProgramHeaders, 
						Elf64_Half numberOfSectionHeaders, 
						Elf64_Half sectionHeaderStringTableIndex)
						{
	Elf64_Ehdr header;
	
	header.e_ident[EI_MAG0] = ELFMAG0; //magic
	header.e_ident[EI_MAG1] = ELFMAG1;
	header.e_ident[EI_MAG2] = ELFMAG2;
	header.e_ident[EI_MAG3] = ELFMAG3;
	header.e_ident[EI_CLASS] = ELFCLASS64; //64-bit
	header.e_ident[EI_DATA] = ELFDATA2LSB; //2's complement, little endian
	header.e_ident[EI_VERSION] = EV_CURRENT; //current
	header.e_ident[EI_ABIVERSION] = ELFOSABI_NONE;
	for(int padIndex = EI_PAD; padIndex < EI_NIDENT; padIndex++){
		header.e_ident[padIndex] = 0;
		//std::cout << "padded @: " << padIndex << "\n";
	}
	header.e_type = fileType;
	header.e_machine = EM_AMD64;
	header.e_version = EV_CURRENT;
	header.e_entry = entryAddress;
	header.e_phoff = programHeaderTableOffset; //could be hardcoded as 64
	header.e_shoff = sectionHeaderTableOffset;
	header.e_flags = 0x00000000; //couldn't find a null x86 ISA machine flag definition?
	header.e_ehsize = 0x00000040; //decimal 64 bytes
	header.e_phentsize = 0x00000038; //decimal 56 bytes
	header.e_phnum = numberOfProgramHeaders;
	header.e_shentsize = 0x00000040; //decimal 64 bytes
	header.e_shnum = numberOfSectionHeaders; //should be 0 if there is no section header
	header.e_shstrndx = sectionHeaderStringTableIndex; //should be SHN_UNDEF if there is no string table
	
	
	return header;
}


Elf64_Shdr createSectionHeader(	Elf64_Word sectionName, //all of these are needed inputs and cannot be hardcoded
								Elf64_Word sectionType,
								Elf64_Xword sectionFlags,
								Elf64_Addr sectionAddress,
								Elf64_Off sectionOffset,
								Elf64_Xword sectionSize,
								Elf64_Word sectionLinkIndex,
								Elf64_Word sectionInfo,
								Elf64_Xword sectionAlign,
								Elf64_Xword sectionEntrySize){
Elf64_Shdr sectionHeader;

sectionHeader.sh_name = sectionName; 			//section name
sectionHeader.sh_type = sectionType;			/* Section type. */
sectionHeader.sh_flags = sectionFlags;			/* Section flags. */
sectionHeader.sh_addr = sectionAddress;			/* Address in memory image. */
sectionHeader.sh_offset = sectionOffset;		/* Offset in file. */
sectionHeader.sh_size = sectionSize;			/* Size in bytes. */
sectionHeader.sh_link = sectionLinkIndex;		/* Index of a related section. */
sectionHeader.sh_info = sectionInfo;			/* Depends on section type. */
sectionHeader.sh_addralign = sectionAlign;		/* Alignment in bytes. */
sectionHeader.sh_entsize = sectionEntrySize;	/* Size of each entry in section. */

return sectionHeader;
}



Elf64_Phdr createProgramHeader(	Elf64_Word	entryType,
								Elf64_Word	permissionFlag,
								Elf64_Off	fileOffset,
								Elf64_Addr	virtualAddress,
								Elf64_Addr	physicalAddress,
								Elf64_Xword	fileSize,
								Elf64_Xword	memorySize,
								Elf64_Xword	alignment){
	Elf64_Phdr programHeader;
	
	programHeader.p_type = entryType;			/* Entry type. */
	programHeader.p_flags = permissionFlag;		/* Access permission flags. */
	programHeader.p_offset = fileOffset;		/* File offset of contents. */
	programHeader.p_vaddr = virtualAddress;		/* Virtual address in memory image. */
	programHeader.p_paddr = physicalAddress;	/* Physical address (not used). */
	programHeader.p_filesz = fileSize;			/* Size of contents in file. */
	programHeader.p_memsz = memorySize;			/* Size of contents in memory. */
	programHeader.p_align = alignment;			/* Alignment in memory and file. */
	
	return programHeader;
	
}


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
