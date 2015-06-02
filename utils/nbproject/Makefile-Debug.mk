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
	${OBJECTDIR}/src/goon/utils/Click.o \
	${OBJECTDIR}/src/goon/utils/Console.o \
	${OBJECTDIR}/src/goon/utils/PID.o \
	${OBJECTDIR}/src/goon/utils/brooks/control.o \
	${OBJECTDIR}/src/goon/utils/brooks/inhibition.o \
	${OBJECTDIR}/src/goon/utils/brooks/suppress_control.o \
	${OBJECTDIR}/src/goon/utils/draw.o \
	${OBJECTDIR}/src/goon/utils/module.o


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
LDLIBSOPTIONS=-L/opt/ros/hydro/lib -lopencv_core

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_utils.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_utils.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_utils.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/goon/utils/Click.o: src/goon/utils/Click.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I/opt/ros/hydro/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/utils/Click.o src/goon/utils/Click.cpp

${OBJECTDIR}/src/goon/utils/Console.o: src/goon/utils/Console.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I/opt/ros/hydro/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/utils/Console.o src/goon/utils/Console.cpp

${OBJECTDIR}/src/goon/utils/PID.o: src/goon/utils/PID.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I/opt/ros/hydro/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/utils/PID.o src/goon/utils/PID.cpp

${OBJECTDIR}/src/goon/utils/brooks/control.o: src/goon/utils/brooks/control.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/utils/brooks
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I/opt/ros/hydro/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/utils/brooks/control.o src/goon/utils/brooks/control.cpp

${OBJECTDIR}/src/goon/utils/brooks/inhibition.o: src/goon/utils/brooks/inhibition.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/utils/brooks
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I/opt/ros/hydro/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/utils/brooks/inhibition.o src/goon/utils/brooks/inhibition.cpp

${OBJECTDIR}/src/goon/utils/brooks/suppress_control.o: src/goon/utils/brooks/suppress_control.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/utils/brooks
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I/opt/ros/hydro/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/utils/brooks/suppress_control.o src/goon/utils/brooks/suppress_control.cpp

${OBJECTDIR}/src/goon/utils/draw.o: src/goon/utils/draw.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I/opt/ros/hydro/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/utils/draw.o src/goon/utils/draw.cpp

${OBJECTDIR}/src/goon/utils/module.o: src/goon/utils/module.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I/opt/ros/hydro/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/utils/module.o src/goon/utils/module.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_utils.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
