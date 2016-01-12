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
	${OBJECTDIR}/src/main.o


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
LDLIBSOPTIONS=-Wl,-rpath,../../head/dist/Debug/GNU-Linux -L../../head/dist/Debug/GNU-Linux -lsam_head -Wl,-rpath,../../brooks/dist/Debug/GNU-Linux -L../../brooks/dist/Debug/GNU-Linux -lsam_brooks -Wl,-rpath,../../utils3/dist/Debug/GNU-Linux -L../../utils3/dist/Debug/GNU-Linux -lsam_utils3 -lcurl -llog4cxx

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testHead

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testHead: ../../head/dist/Debug/GNU-Linux/libsam_head.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testHead: ../../brooks/dist/Debug/GNU-Linux/libsam_brooks.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testHead: ../../utils3/dist/Debug/GNU-Linux/libsam_utils3.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testHead: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testHead ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../head/src -I../../brooks/src -I../../utils3/src -I/usr/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

# Subprojects
.build-subprojects:
	cd ../../head && ${MAKE}  -f Makefile CONF=Debug
	cd ../../brooks && ${MAKE}  -f Makefile CONF=Debug
	cd ../../utils3 && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testHead

# Subprojects
.clean-subprojects:
	cd ../../head && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../brooks && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../utils3 && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
