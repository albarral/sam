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
	${OBJECTDIR}/src/sam/manipulation/ArmManager.o \
	${OBJECTDIR}/src/sam/manipulation/bus/Bus.o \
	${OBJECTDIR}/src/sam/manipulation/bus/Config.o \
	${OBJECTDIR}/src/sam/manipulation/bus/Connections.o \
	${OBJECTDIR}/src/sam/manipulation/bus/ConnectionsJoint.o \
	${OBJECTDIR}/src/sam/manipulation/bus/ParamsJoint.o \
	${OBJECTDIR}/src/sam/manipulation/bus/ParamsJointMover.o \
	${OBJECTDIR}/src/sam/manipulation/data/Arm.o \
	${OBJECTDIR}/src/sam/manipulation/data/Joint.o \
	${OBJECTDIR}/src/sam/manipulation/modules/ArmMover.o \
	${OBJECTDIR}/src/sam/manipulation/modules/Commands.o \
	${OBJECTDIR}/src/sam/manipulation/modules/ComsManip.o \
	${OBJECTDIR}/src/sam/manipulation/modules/JointControl.o \
	${OBJECTDIR}/src/sam/manipulation/modules/JointMover.o \
	${OBJECTDIR}/src/sam/manipulation/utils/Responder.o \
	${OBJECTDIR}/src/sam/manipulation/utils/module2.o


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
LDLIBSOPTIONS=-Wl,-rpath,../utils/dist/Debug/GNU-Linux-x86 -L../utils/dist/Debug/GNU-Linux-x86 -lgoon_utils -llog4cxx

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsam_manip.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsam_manip.${CND_DLIB_EXT}: ../utils/dist/Debug/GNU-Linux-x86/libgoon_utils.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsam_manip.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsam_manip.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/sam/manipulation/ArmManager.o: src/sam/manipulation/ArmManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/manipulation
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/manipulation/ArmManager.o src/sam/manipulation/ArmManager.cpp

${OBJECTDIR}/src/sam/manipulation/bus/Bus.o: src/sam/manipulation/bus/Bus.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/manipulation/bus
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/manipulation/bus/Bus.o src/sam/manipulation/bus/Bus.cpp

${OBJECTDIR}/src/sam/manipulation/bus/Config.o: src/sam/manipulation/bus/Config.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/manipulation/bus
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/manipulation/bus/Config.o src/sam/manipulation/bus/Config.cpp

${OBJECTDIR}/src/sam/manipulation/bus/Connections.o: src/sam/manipulation/bus/Connections.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/manipulation/bus
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/manipulation/bus/Connections.o src/sam/manipulation/bus/Connections.cpp

${OBJECTDIR}/src/sam/manipulation/bus/ConnectionsJoint.o: src/sam/manipulation/bus/ConnectionsJoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/manipulation/bus
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/manipulation/bus/ConnectionsJoint.o src/sam/manipulation/bus/ConnectionsJoint.cpp

${OBJECTDIR}/src/sam/manipulation/bus/ParamsJoint.o: src/sam/manipulation/bus/ParamsJoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/manipulation/bus
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/manipulation/bus/ParamsJoint.o src/sam/manipulation/bus/ParamsJoint.cpp

${OBJECTDIR}/src/sam/manipulation/bus/ParamsJointMover.o: src/sam/manipulation/bus/ParamsJointMover.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/manipulation/bus
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/manipulation/bus/ParamsJointMover.o src/sam/manipulation/bus/ParamsJointMover.cpp

${OBJECTDIR}/src/sam/manipulation/data/Arm.o: src/sam/manipulation/data/Arm.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/manipulation/data
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/manipulation/data/Arm.o src/sam/manipulation/data/Arm.cpp

${OBJECTDIR}/src/sam/manipulation/data/Joint.o: src/sam/manipulation/data/Joint.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/manipulation/data
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/manipulation/data/Joint.o src/sam/manipulation/data/Joint.cpp

${OBJECTDIR}/src/sam/manipulation/modules/ArmMover.o: src/sam/manipulation/modules/ArmMover.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/manipulation/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/manipulation/modules/ArmMover.o src/sam/manipulation/modules/ArmMover.cpp

${OBJECTDIR}/src/sam/manipulation/modules/Commands.o: src/sam/manipulation/modules/Commands.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/manipulation/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/manipulation/modules/Commands.o src/sam/manipulation/modules/Commands.cpp

${OBJECTDIR}/src/sam/manipulation/modules/ComsManip.o: src/sam/manipulation/modules/ComsManip.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/manipulation/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/manipulation/modules/ComsManip.o src/sam/manipulation/modules/ComsManip.cpp

${OBJECTDIR}/src/sam/manipulation/modules/JointControl.o: src/sam/manipulation/modules/JointControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/manipulation/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/manipulation/modules/JointControl.o src/sam/manipulation/modules/JointControl.cpp

${OBJECTDIR}/src/sam/manipulation/modules/JointMover.o: src/sam/manipulation/modules/JointMover.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/manipulation/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/manipulation/modules/JointMover.o src/sam/manipulation/modules/JointMover.cpp

${OBJECTDIR}/src/sam/manipulation/utils/Responder.o: src/sam/manipulation/utils/Responder.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/manipulation/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/manipulation/utils/Responder.o src/sam/manipulation/utils/Responder.cpp

${OBJECTDIR}/src/sam/manipulation/utils/module2.o: src/sam/manipulation/utils/module2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/manipulation/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/manipulation/utils/module2.o src/sam/manipulation/utils/module2.cpp

# Subprojects
.build-subprojects:
	cd ../utils && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsam_manip.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../utils && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
