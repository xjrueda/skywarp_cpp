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
CC=clang
CCC=clang++
CXX=clang++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=CLang-MacOSX
CND_DLIB_EXT=dylib
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/ClientSession.o \
	${OBJECTDIR}/src/JsonRPCParser.o \
	${OBJECTDIR}/src/JsonSerializer.o \
	${OBJECTDIR}/src/MethodDelegatorManager.o \
	${OBJECTDIR}/src/PublishSubscriptionManager.o \
	${OBJECTDIR}/src/SessionManager.o \
	${OBJECTDIR}/src/SkywarpServer.o \
	${OBJECTDIR}/src/Topic.o \
	${OBJECTDIR}/src/jsoncpp.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-w -O3 -std=c++0x
CXXFLAGS=-w -O3 -std=c++0x

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=/usr/local/lib/libboost_system.dylib

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libskywarp_cpp.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libskywarp_cpp.${CND_DLIB_EXT}: /usr/local/lib/libboost_system.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libskywarp_cpp.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libskywarp_cpp.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -dynamiclib -install_name libskywarp_cpp.${CND_DLIB_EXT} -fPIC

${OBJECTDIR}/src/ClientSession.o: src/ClientSession.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_WEBSOCKETPP_CPP11_STL_ -I/usr/local/include/json -I/usr/local/include/websocketpp -Isrc -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ClientSession.o src/ClientSession.cpp

${OBJECTDIR}/src/JsonRPCParser.o: src/JsonRPCParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_WEBSOCKETPP_CPP11_STL_ -I/usr/local/include/json -I/usr/local/include/websocketpp -Isrc -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/JsonRPCParser.o src/JsonRPCParser.cpp

${OBJECTDIR}/src/JsonSerializer.o: src/JsonSerializer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_WEBSOCKETPP_CPP11_STL_ -I/usr/local/include/json -I/usr/local/include/websocketpp -Isrc -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/JsonSerializer.o src/JsonSerializer.cpp

${OBJECTDIR}/src/MethodDelegatorManager.o: src/MethodDelegatorManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_WEBSOCKETPP_CPP11_STL_ -I/usr/local/include/json -I/usr/local/include/websocketpp -Isrc -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/MethodDelegatorManager.o src/MethodDelegatorManager.cpp

${OBJECTDIR}/src/PublishSubscriptionManager.o: src/PublishSubscriptionManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_WEBSOCKETPP_CPP11_STL_ -I/usr/local/include/json -I/usr/local/include/websocketpp -Isrc -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/PublishSubscriptionManager.o src/PublishSubscriptionManager.cpp

${OBJECTDIR}/src/SessionManager.o: src/SessionManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_WEBSOCKETPP_CPP11_STL_ -I/usr/local/include/json -I/usr/local/include/websocketpp -Isrc -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/SessionManager.o src/SessionManager.cpp

${OBJECTDIR}/src/SkywarpServer.o: src/SkywarpServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_WEBSOCKETPP_CPP11_STL_ -I/usr/local/include/json -I/usr/local/include/websocketpp -Isrc -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/SkywarpServer.o src/SkywarpServer.cpp

${OBJECTDIR}/src/Topic.o: src/Topic.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_WEBSOCKETPP_CPP11_STL_ -I/usr/local/include/json -I/usr/local/include/websocketpp -Isrc -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Topic.o src/Topic.cpp

${OBJECTDIR}/src/jsoncpp.o: src/jsoncpp.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_WEBSOCKETPP_CPP11_STL_ -I/usr/local/include/json -I/usr/local/include/websocketpp -Isrc -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/jsoncpp.o src/jsoncpp.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libskywarp_cpp.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
