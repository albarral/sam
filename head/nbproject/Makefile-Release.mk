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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/sam/head/HeadManager.o \
	${OBJECTDIR}/src/sam/head/bus/Bus.o \
	${OBJECTDIR}/src/sam/head/bus/COBus.o \
	${OBJECTDIR}/src/sam/head/bus/SOBus.o \
	${OBJECTDIR}/src/sam/head/modules/Head.o \
	${OBJECTDIR}/src/sam/head/modules/HeadController.o \
	${OBJECTDIR}/src/sam/head/modules/HeadFactory.o \
	${OBJECTDIR}/src/sam/head/modules/IPCamHead.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libhead.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libhead.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libhead.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/sam/head/HeadManager.o: src/sam/head/HeadManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/head
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/head/HeadManager.o src/sam/head/HeadManager.cpp

${OBJECTDIR}/src/sam/head/bus/Bus.o: src/sam/head/bus/Bus.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/head/bus
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/head/bus/Bus.o src/sam/head/bus/Bus.cpp

${OBJECTDIR}/src/sam/head/bus/COBus.o: src/sam/head/bus/COBus.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/head/bus
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/head/bus/COBus.o src/sam/head/bus/COBus.cpp

${OBJECTDIR}/src/sam/head/bus/SOBus.o: src/sam/head/bus/SOBus.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/head/bus
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/head/bus/SOBus.o src/sam/head/bus/SOBus.cpp

${OBJECTDIR}/src/sam/head/modules/Head.o: src/sam/head/modules/Head.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/head/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/head/modules/Head.o src/sam/head/modules/Head.cpp

${OBJECTDIR}/src/sam/head/modules/HeadController.o: src/sam/head/modules/HeadController.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/head/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/head/modules/HeadController.o src/sam/head/modules/HeadController.cpp

${OBJECTDIR}/src/sam/head/modules/HeadFactory.o: src/sam/head/modules/HeadFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/head/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/head/modules/HeadFactory.o src/sam/head/modules/HeadFactory.cpp

${OBJECTDIR}/src/sam/head/modules/IPCamHead.o: src/sam/head/modules/IPCamHead.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/head/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/head/modules/IPCamHead.o src/sam/head/modules/IPCamHead.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libhead.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
