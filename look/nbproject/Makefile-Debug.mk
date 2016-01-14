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
	${OBJECTDIR}/src/sam/look/LookManager.o \
	${OBJECTDIR}/src/sam/look/bus/Bus.o \
	${OBJECTDIR}/src/sam/look/bus/COBus.o \
	${OBJECTDIR}/src/sam/look/bus/SOBus.o \
	${OBJECTDIR}/src/sam/look/modules/tracker/Tracker.o


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
LDLIBSOPTIONS=-Wl,-rpath,../brooks/dist/Debug/GNU-Linux -L../brooks/dist/Debug/GNU-Linux -lsam_brooks -Wl,-rpath,../utils3/dist/Debug/GNU-Linux -L../utils3/dist/Debug/GNU-Linux -lsam_utils3 -Wl,-rpath,../network2/dist/Debug/GNU-Linux -L../network2/dist/Debug/GNU-Linux -lsam_network2

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblook.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblook.${CND_DLIB_EXT}: ../brooks/dist/Debug/GNU-Linux/libsam_brooks.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblook.${CND_DLIB_EXT}: ../utils3/dist/Debug/GNU-Linux/libsam_utils3.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblook.${CND_DLIB_EXT}: ../network2/dist/Debug/GNU-Linux/libsam_network2.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblook.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblook.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/sam/look/LookManager.o: src/sam/look/LookManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/look
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils3/src -I../network2/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/look/LookManager.o src/sam/look/LookManager.cpp

${OBJECTDIR}/src/sam/look/bus/Bus.o: src/sam/look/bus/Bus.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/look/bus
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils3/src -I../network2/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/look/bus/Bus.o src/sam/look/bus/Bus.cpp

${OBJECTDIR}/src/sam/look/bus/COBus.o: src/sam/look/bus/COBus.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/look/bus
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils3/src -I../network2/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/look/bus/COBus.o src/sam/look/bus/COBus.cpp

${OBJECTDIR}/src/sam/look/bus/SOBus.o: src/sam/look/bus/SOBus.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/look/bus
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils3/src -I../network2/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/look/bus/SOBus.o src/sam/look/bus/SOBus.cpp

${OBJECTDIR}/src/sam/look/modules/tracker/Tracker.o: src/sam/look/modules/tracker/Tracker.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/look/modules/tracker
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils3/src -I../network2/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/look/modules/tracker/Tracker.o src/sam/look/modules/tracker/Tracker.cpp

# Subprojects
.build-subprojects:
	cd ../brooks && ${MAKE}  -f Makefile CONF=Debug
	cd ../utils3 && ${MAKE}  -f Makefile CONF=Debug
	cd ../network2 && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblook.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../brooks && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../utils3 && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../network2 && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
