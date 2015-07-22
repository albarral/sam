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
	${OBJECTDIR}/src/sam/backbone/BoneBase.o \
	${OBJECTDIR}/src/sam/backbone/BoneReader.o \
	${OBJECTDIR}/src/sam/backbone/BoneWriter.o \
	${OBJECTDIR}/src/sam/backbone/data/BoneArea.o \
	${OBJECTDIR}/src/sam/backbone/data/BoneModul.o \
	${OBJECTDIR}/src/sam/backbone/data/BoneMsg.o \
	${OBJECTDIR}/src/sam/backbone/utils/DatabaseClient.o


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
LDLIBSOPTIONS=-Wl,-rpath,../utils/dist/Debug/GNU-Linux-x86 -L../utils/dist/Debug/GNU-Linux-x86 -lsam_utils -lmysqlcppconn

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsam_backbone.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsam_backbone.${CND_DLIB_EXT}: ../utils/dist/Debug/GNU-Linux-x86/libsam_utils.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsam_backbone.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsam_backbone.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/sam/backbone/BoneBase.o: src/sam/backbone/BoneBase.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/backbone
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/backbone/BoneBase.o src/sam/backbone/BoneBase.cpp

${OBJECTDIR}/src/sam/backbone/BoneReader.o: src/sam/backbone/BoneReader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/backbone
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/backbone/BoneReader.o src/sam/backbone/BoneReader.cpp

${OBJECTDIR}/src/sam/backbone/BoneWriter.o: src/sam/backbone/BoneWriter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/backbone
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/backbone/BoneWriter.o src/sam/backbone/BoneWriter.cpp

${OBJECTDIR}/src/sam/backbone/data/BoneArea.o: src/sam/backbone/data/BoneArea.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/backbone/data
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/backbone/data/BoneArea.o src/sam/backbone/data/BoneArea.cpp

${OBJECTDIR}/src/sam/backbone/data/BoneModul.o: src/sam/backbone/data/BoneModul.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/backbone/data
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/backbone/data/BoneModul.o src/sam/backbone/data/BoneModul.cpp

${OBJECTDIR}/src/sam/backbone/data/BoneMsg.o: src/sam/backbone/data/BoneMsg.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/backbone/data
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/backbone/data/BoneMsg.o src/sam/backbone/data/BoneMsg.cpp

${OBJECTDIR}/src/sam/backbone/utils/DatabaseClient.o: src/sam/backbone/utils/DatabaseClient.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/backbone/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/backbone/utils/DatabaseClient.o src/sam/backbone/utils/DatabaseClient.cpp

# Subprojects
.build-subprojects:
	cd ../utils && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsam_backbone.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../utils && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
