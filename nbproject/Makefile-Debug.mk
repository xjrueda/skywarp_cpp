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
	${OBJECTDIR}/skywarppp/ClientSession.o \
	${OBJECTDIR}/skywarppp/JsonRPCParser.o \
	${OBJECTDIR}/skywarppp/JsonSerializer.o \
	${OBJECTDIR}/skywarppp/MethodDelegatorManager.o \
	${OBJECTDIR}/skywarppp/PublishSubscriptionManager.o \
	${OBJECTDIR}/skywarppp/SessionManager.o \
	${OBJECTDIR}/skywarppp/SkywarpServer.o \
	${OBJECTDIR}/skywarppp/Topic.o \
	${OBJECTDIR}/skywarppp/jsoncpp.o


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

${OBJECTDIR}/skywarppp/ClientSession.o: skywarppp/ClientSession.cpp 
	${MKDIR} -p ${OBJECTDIR}/skywarppp
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_WEBSOCKETPP_CPP11_STL_ -I/usr/local/include/json -I/usr/local/include/websocketpp -Iskywarppp -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/skywarppp/ClientSession.o skywarppp/ClientSession.cpp

${OBJECTDIR}/skywarppp/JsonRPCParser.o: skywarppp/JsonRPCParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/skywarppp
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_WEBSOCKETPP_CPP11_STL_ -I/usr/local/include/json -I/usr/local/include/websocketpp -Iskywarppp -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/skywarppp/JsonRPCParser.o skywarppp/JsonRPCParser.cpp

${OBJECTDIR}/skywarppp/JsonSerializer.o: skywarppp/JsonSerializer.cpp 
	${MKDIR} -p ${OBJECTDIR}/skywarppp
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_WEBSOCKETPP_CPP11_STL_ -I/usr/local/include/json -I/usr/local/include/websocketpp -Iskywarppp -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/skywarppp/JsonSerializer.o skywarppp/JsonSerializer.cpp

${OBJECTDIR}/skywarppp/MethodDelegatorManager.o: skywarppp/MethodDelegatorManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/skywarppp
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_WEBSOCKETPP_CPP11_STL_ -I/usr/local/include/json -I/usr/local/include/websocketpp -Iskywarppp -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/skywarppp/MethodDelegatorManager.o skywarppp/MethodDelegatorManager.cpp

${OBJECTDIR}/skywarppp/PublishSubscriptionManager.o: skywarppp/PublishSubscriptionManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/skywarppp
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_WEBSOCKETPP_CPP11_STL_ -I/usr/local/include/json -I/usr/local/include/websocketpp -Iskywarppp -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/skywarppp/PublishSubscriptionManager.o skywarppp/PublishSubscriptionManager.cpp

${OBJECTDIR}/skywarppp/SessionManager.o: skywarppp/SessionManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/skywarppp
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_WEBSOCKETPP_CPP11_STL_ -I/usr/local/include/json -I/usr/local/include/websocketpp -Iskywarppp -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/skywarppp/SessionManager.o skywarppp/SessionManager.cpp

${OBJECTDIR}/skywarppp/SkywarpServer.o: skywarppp/SkywarpServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/skywarppp
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_WEBSOCKETPP_CPP11_STL_ -I/usr/local/include/json -I/usr/local/include/websocketpp -Iskywarppp -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/skywarppp/SkywarpServer.o skywarppp/SkywarpServer.cpp

${OBJECTDIR}/skywarppp/Topic.o: skywarppp/Topic.cpp 
	${MKDIR} -p ${OBJECTDIR}/skywarppp
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_WEBSOCKETPP_CPP11_STL_ -I/usr/local/include/json -I/usr/local/include/websocketpp -Iskywarppp -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/skywarppp/Topic.o skywarppp/Topic.cpp

${OBJECTDIR}/skywarppp/jsoncpp.o: skywarppp/jsoncpp.cpp 
	${MKDIR} -p ${OBJECTDIR}/skywarppp
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_WEBSOCKETPP_CPP11_STL_ -I/usr/local/include/json -I/usr/local/include/websocketpp -Iskywarppp -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/skywarppp/jsoncpp.o skywarppp/jsoncpp.cpp

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
