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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/sam/backbone/AreaConnection.o \
	${OBJECTDIR}/src/sam/backbone/BoneConnection.o \
	${OBJECTDIR}/src/sam/backbone/ControlConnection.o \
	${OBJECTDIR}/src/sam/backbone/SensorConnection.o \
	${OBJECTDIR}/src/sam/backbone/config/Config.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libbackbone.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libbackbone.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libbackbone.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/sam/backbone/AreaConnection.o: src/sam/backbone/AreaConnection.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/backbone
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/backbone/AreaConnection.o src/sam/backbone/AreaConnection.cpp

${OBJECTDIR}/src/sam/backbone/BoneConnection.o: src/sam/backbone/BoneConnection.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/backbone
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/backbone/BoneConnection.o src/sam/backbone/BoneConnection.cpp

${OBJECTDIR}/src/sam/backbone/ControlConnection.o: src/sam/backbone/ControlConnection.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/backbone
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/backbone/ControlConnection.o src/sam/backbone/ControlConnection.cpp

${OBJECTDIR}/src/sam/backbone/SensorConnection.o: src/sam/backbone/SensorConnection.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/backbone
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/backbone/SensorConnection.o src/sam/backbone/SensorConnection.cpp

${OBJECTDIR}/src/sam/backbone/config/Config.o: src/sam/backbone/config/Config.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/backbone/config
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/backbone/config/Config.o src/sam/backbone/config/Config.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libbackbone.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
