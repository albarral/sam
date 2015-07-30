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
CND_PLATFORM=GNU-Linux-x86
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
LDLIBSOPTIONS=-Wl,-rpath,../../manipulation/dist/Debug/GNU-Linux-x86 -L../../manipulation/dist/Debug/GNU-Linux-x86 -lsam_manip -Wl,-rpath,../../utils/dist/Debug/GNU-Linux-x86 -L../../utils/dist/Debug/GNU-Linux-x86 -lsam_utils -Wl,-rpath,../../backbone/dist/Debug/GNU-Linux-x86 -L../../backbone/dist/Debug/GNU-Linux-x86 -lsam_backbone -llog4cxx

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testmanip

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testmanip: ../../manipulation/dist/Debug/GNU-Linux-x86/libsam_manip.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testmanip: ../../utils/dist/Debug/GNU-Linux-x86/libsam_utils.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testmanip: ../../backbone/dist/Debug/GNU-Linux-x86/libsam_backbone.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testmanip: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testmanip ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../manipulation/src -I../../utils/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

# Subprojects
.build-subprojects:
	cd ../../manipulation && ${MAKE}  -f Makefile CONF=Debug
	cd ../../utils && ${MAKE}  -f Makefile CONF=Debug
	cd ../../backbone && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testmanip

# Subprojects
.clean-subprojects:
	cd ../../manipulation && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../utils && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../backbone && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
