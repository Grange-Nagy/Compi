##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=compiASM
ConfigurationName      :=Release
WorkspaceConfiguration := $(ConfigurationName)
WorkspacePath          :=/home/kali/Documents/Compi
ProjectPath            :=/home/kali/Documents/Compi/compiASM
IntermediateDirectory  :=../build-$(ConfigurationName)/compiASM
OutDir                 :=../build-$(ConfigurationName)/compiASM
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=kali
Date                   :=06/14/20
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
CXXFLAGS :=  -O2 -Wall -std=gnu++11 $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=../build-$(ConfigurationName)/compiASM/compiASM.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): ../build-$(ConfigurationName)/compiASM/.d $(Objects) 
	@mkdir -p "../build-$(ConfigurationName)/compiASM"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@mkdir -p "../build-$(ConfigurationName)/compiASM"
	@mkdir -p ""../build-$(ConfigurationName)/bin""

../build-$(ConfigurationName)/compiASM/.d:
	@mkdir -p "../build-$(ConfigurationName)/compiASM"

PreBuild:


##
## Objects
##
../build-$(ConfigurationName)/compiASM/compiASM.cpp$(ObjectSuffix): compiASM.cpp ../build-$(ConfigurationName)/compiASM/compiASM.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/kali/Documents/Compi/compiASM/compiASM.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/compiASM.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/compiASM/compiASM.cpp$(DependSuffix): compiASM.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/compiASM/compiASM.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/compiASM/compiASM.cpp$(DependSuffix) -MM compiASM.cpp

../build-$(ConfigurationName)/compiASM/compiASM.cpp$(PreprocessSuffix): compiASM.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/compiASM/compiASM.cpp$(PreprocessSuffix) compiASM.cpp


-include ../build-$(ConfigurationName)/compiASM//*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


