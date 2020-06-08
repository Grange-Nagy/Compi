##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=Compi
ConfigurationName      :=Release
WorkspaceConfiguration := $(ConfigurationName)
WorkspacePath          :=/home/kali/Documents/Compi
ProjectPath            :=/home/kali/Documents/Compi/Compi
IntermediateDirectory  :=../build-$(ConfigurationName)/Compi
OutDir                 :=../build-$(ConfigurationName)/Compi
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=kali
Date                   :=06/08/20
CodeLitePath           :=/home/kali/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=../build-$(ConfigurationName)/bin/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -O2 -Wall $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=../build-$(ConfigurationName)/Compi/elf.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): ../build-$(ConfigurationName)/Compi/.d $(Objects) 
	@mkdir -p "../build-$(ConfigurationName)/Compi"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@mkdir -p "../build-$(ConfigurationName)/Compi"
	@mkdir -p ""../build-$(ConfigurationName)/bin""

../build-$(ConfigurationName)/Compi/.d:
	@mkdir -p "../build-$(ConfigurationName)/Compi"

PreBuild:


##
## Objects
##
../build-$(ConfigurationName)/Compi/elf.cpp$(ObjectSuffix): elf.cpp ../build-$(ConfigurationName)/Compi/elf.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/kali/Documents/Compi/Compi/elf.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/elf.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/Compi/elf.cpp$(DependSuffix): elf.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/Compi/elf.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/Compi/elf.cpp$(DependSuffix) -MM elf.cpp

../build-$(ConfigurationName)/Compi/elf.cpp$(PreprocessSuffix): elf.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/Compi/elf.cpp$(PreprocessSuffix) elf.cpp


-include ../build-$(ConfigurationName)/Compi//*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


