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
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/nbproject/private/c_standard_headers_indexer.o \
	${OBJECTDIR}/nbproject/private/cpp_standard_headers_indexer.o \
	${OBJECTDIR}/src/Mesh.o \
	${OBJECTDIR}/src/Shaders.o \
	${OBJECTDIR}/src/Texture.o \
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
LDLIBSOPTIONS=-L../../libs/ogl/lib -L../../libs/glm -L../../libs/soil/lib

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sesion3_1.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sesion3_1.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sesion3_1 ${OBJECTFILES} ${LDLIBSOPTIONS} -lSOIL -lopengl32 -lglu32 -lglew32 -lfreeglut

${OBJECTDIR}/nbproject/private/c_standard_headers_indexer.o: nbproject/private/c_standard_headers_indexer.c
	${MKDIR} -p ${OBJECTDIR}/nbproject/private
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/nbproject/private/c_standard_headers_indexer.o nbproject/private/c_standard_headers_indexer.c

${OBJECTDIR}/nbproject/private/cpp_standard_headers_indexer.o: nbproject/private/cpp_standard_headers_indexer.cpp
	${MKDIR} -p ${OBJECTDIR}/nbproject/private
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../libs/ogl/include -I../../libs/glm -I../../libs/soil/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/nbproject/private/cpp_standard_headers_indexer.o nbproject/private/cpp_standard_headers_indexer.cpp

${OBJECTDIR}/src/Mesh.o: src/Mesh.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../libs/ogl/include -I../../libs/glm -I../../libs/soil/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Mesh.o src/Mesh.cpp

${OBJECTDIR}/src/Shaders.o: src/Shaders.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../libs/ogl/include -I../../libs/glm -I../../libs/soil/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Shaders.o src/Shaders.cpp

${OBJECTDIR}/src/Texture.o: src/Texture.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../libs/ogl/include -I../../libs/glm -I../../libs/soil/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Texture.o src/Texture.cpp

${OBJECTDIR}/src/main.o: src/main.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../libs/ogl/include -I../../libs/glm -I../../libs/soil/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
