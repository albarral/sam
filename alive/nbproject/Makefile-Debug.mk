#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/sam/alive/ConsoleControl.o \
	${OBJECTDIR}/src/sam/alive/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-Wl,-rpath,../brooks/dist/Debug/GNU-Linux -L../brooks/dist/Debug/GNU-Linux -lsam_brooks -Wl,-rpath,../utils3/dist/Debug/GNU-Linux -L../utils3/dist/Debug/GNU-Linux -lsam_utils3 -Wl,-rpath,../network2/dist/Debug/GNU-Linux -L../network2/dist/Debug/GNU-Linux -lsam_network2 -Wl,-rpath,../head/dist/Debug/GNU-Linux -L../head/dist/Debug/GNU-Linux -lsam_head -llog4cxx -lcurl

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sam_alive

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sam_alive: ../brooks/dist/Debug/GNU-Linux/libsam_brooks.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sam_alive: ../utils3/dist/Debug/GNU-Linux/libsam_utils3.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sam_alive: ../network2/dist/Debug/GNU-Linux/libsam_network2.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sam_alive: ../head/dist/Debug/GNU-Linux/libsam_head.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sam_alive: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sam_alive ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/sam/alive/ConsoleControl.o: src/sam/alive/ConsoleControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/alive
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils3/src -I../network2/src -I../head/src -I/usr/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/alive/ConsoleControl.o src/sam/alive/ConsoleControl.cpp

${OBJECTDIR}/src/sam/alive/main.o: src/sam/alive/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/alive
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils3/src -I../network2/src -I../head/src -I/usr/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/alive/main.o src/sam/alive/main.cpp

# Subprojects
.build-subprojects:
	cd ../brooks && ${MAKE}  -f Makefile CONF=Debug
	cd ../utils3 && ${MAKE}  -f Makefile CONF=Debug
	cd ../network2 && ${MAKE}  -f Makefile CONF=Debug
	cd ../head && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sam_alive

# Subprojects
.clean-subprojects:
	cd ../brooks && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../utils3 && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../network2 && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../head && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
