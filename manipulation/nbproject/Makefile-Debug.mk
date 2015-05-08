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
	${OBJECTDIR}/src/DynamicMover.o \
	${OBJECTDIR}/src/Joint.o \
	${OBJECTDIR}/src/JointMover.o


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
LDLIBSOPTIONS=-Wl,-rpath,../../../Dropbox/DEV/goon/utils/dist/Debug/GNU-Linux-x86 -L../../../Dropbox/DEV/goon/utils/dist/Debug/GNU-Linux-x86 -lgoon_utils

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmanipulation.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmanipulation.${CND_DLIB_EXT}: ../../../Dropbox/DEV/goon/utils/dist/Debug/GNU-Linux-x86/libgoon_utils.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmanipulation.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmanipulation.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/DynamicMover.o: src/DynamicMover.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/DynamicMover.o src/DynamicMover.cpp

${OBJECTDIR}/src/Joint.o: src/Joint.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Joint.o src/Joint.cpp

${OBJECTDIR}/src/JointMover.o: src/JointMover.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/JointMover.o src/JointMover.cpp

# Subprojects
.build-subprojects:
	cd ../../../Dropbox/DEV/goon/utils && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmanipulation.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../../../Dropbox/DEV/goon/utils && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
