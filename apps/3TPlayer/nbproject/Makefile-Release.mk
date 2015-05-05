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
	${OBJECTDIR}/src/sam/3tplayer/Bus.o \
	${OBJECTDIR}/src/sam/3tplayer/T3Player.o \
	${OBJECTDIR}/src/sam/3tplayer/core/Game.o \
	${OBJECTDIR}/src/sam/3tplayer/core/Players.o \
	${OBJECTDIR}/src/sam/3tplayer/data/Board.o \
	${OBJECTDIR}/src/sam/3tplayer/data/Player.o \
	${OBJECTDIR}/src/sam/3tplayer/modules/Field.o \
	${OBJECTDIR}/src/sam/3tplayer/modules/Play.o \
	${OBJECTDIR}/src/sam/3tplayer/shared/Config.o \
	${OBJECTDIR}/src/sam/3tplayer/shared/Connections.o \
	${OBJECTDIR}/src/sam/3tplayer/shared/Data.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lib3TPlayer.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lib3TPlayer.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lib3TPlayer.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/sam/3tplayer/Bus.o: src/sam/3tplayer/Bus.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/3tplayer
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/3tplayer/Bus.o src/sam/3tplayer/Bus.cpp

${OBJECTDIR}/src/sam/3tplayer/T3Player.o: src/sam/3tplayer/T3Player.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/3tplayer
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/3tplayer/T3Player.o src/sam/3tplayer/T3Player.cpp

${OBJECTDIR}/src/sam/3tplayer/core/Game.o: src/sam/3tplayer/core/Game.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/3tplayer/core
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/3tplayer/core/Game.o src/sam/3tplayer/core/Game.cpp

${OBJECTDIR}/src/sam/3tplayer/core/Players.o: src/sam/3tplayer/core/Players.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/3tplayer/core
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/3tplayer/core/Players.o src/sam/3tplayer/core/Players.cpp

${OBJECTDIR}/src/sam/3tplayer/data/Board.o: src/sam/3tplayer/data/Board.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/3tplayer/data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/3tplayer/data/Board.o src/sam/3tplayer/data/Board.cpp

${OBJECTDIR}/src/sam/3tplayer/data/Player.o: src/sam/3tplayer/data/Player.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/3tplayer/data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/3tplayer/data/Player.o src/sam/3tplayer/data/Player.cpp

${OBJECTDIR}/src/sam/3tplayer/modules/Field.o: src/sam/3tplayer/modules/Field.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/3tplayer/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/3tplayer/modules/Field.o src/sam/3tplayer/modules/Field.cpp

${OBJECTDIR}/src/sam/3tplayer/modules/Play.o: src/sam/3tplayer/modules/Play.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/3tplayer/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/3tplayer/modules/Play.o src/sam/3tplayer/modules/Play.cpp

${OBJECTDIR}/src/sam/3tplayer/shared/Config.o: src/sam/3tplayer/shared/Config.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/3tplayer/shared
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/3tplayer/shared/Config.o src/sam/3tplayer/shared/Config.cpp

${OBJECTDIR}/src/sam/3tplayer/shared/Connections.o: src/sam/3tplayer/shared/Connections.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/3tplayer/shared
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/3tplayer/shared/Connections.o src/sam/3tplayer/shared/Connections.cpp

${OBJECTDIR}/src/sam/3tplayer/shared/Data.o: src/sam/3tplayer/shared/Data.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/3tplayer/shared
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/3tplayer/shared/Data.o src/sam/3tplayer/shared/Data.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lib3TPlayer.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
