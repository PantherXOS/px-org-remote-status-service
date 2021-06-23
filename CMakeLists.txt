cmake_minimum_required(VERSION 3.10)
project(px-org-remote-status-service)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

find_package(yaml-cpp REQUIRED)

# Generate CapnProto source and header files ==================================
find_package(CapnProto CONFIG REQUIRED)
set(CAPNPC_SRC_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/interface" CACHE STRING "" FORCE)
set(CAPNPC_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/interface" CACHE STRING "" FORCE)
file(MAKE_DIRECTORY "${CAPNPC_OUTPUT_DIR}")
capnp_generate_cpp(CapnpSources CapnpHeaders
        interface/StatEvent.capnp)
include_directories(${CapnProto_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR}/interface)
# =============================================================================

include_directories(src)
include_directories("libs")
include_directories("libs/rapidjson")
include_directories(SQLiteCpp/include)
include_directories(${yaml-cpp_INCLUDE_DIRS})

add_subdirectory(SQLiteCpp)

FILE(GLOB CommonSources
        src/Utils.cpp   src/Utils.h
        src/Logger.cpp  src/Logger.h)

FILE(GLOB RPCSources
        src/RPCServer.cpp       src/RPCServer.h
        src/RPCHandler.cpp      src/RPCHandler.h)

FILE(GLOB StatsSources
        src/Stats.h
        src/SystemStats.h       src/SystemStats.cpp
	src/CpuParams.cpp       src/CpuParams.h
        src/LoadParams.cpp      src/LoadParams.h
        src/MemoryParams.cpp    src/MemoryParams.h
        src/DiskParams.cpp      src/DiskParams.h
        src/GeneralParams.cpp   src/GeneralParams.h
        src/StatsParam.cpp      src/StatsParam.h
        src/DeviceConfig.cpp    src/DeviceConfig.h
        src/DiskStats.cpp       src/DiskStats.h        
        src/StatChecker.cpp     src/StatChecker.h
        src/NetworkParam.cpp    src/NetworkParam.h
        src/InstalledApplication.cpp src/InstalledApplication.h
        src/NetworkAddress.h)

FILE(GLOB ApiSources
        src/DeviceIdentityClient.cpp
        src/IdPClient.cpp)

FILE(GLOB DBSources
        src/StatusDatabase.h        src/StatusDatabase.cpp
        src/EventDatabase.h         src/EventDatabase.cpp)

FILE(GLOB JSON
        src/JsonBuilder.cpp     src/JsonBuilder.h)

FILE(GLOB EventSources
        src/EventHandler.cpp    src/EventHandler.h
        src/EventObject.cpp     src/EventObject.h)

add_executable(px-org-remote-status-service src/main.cpp ${ApiSources} ${RPCSources} ${CommonSources} ${StatsSources} ${CapnpSources} ${CapnpHeaders} ${DBSources} ${JSON} ${EventSources})
set(PROJECT_INCLUDE_DIR "src")
set(RESTCLIENTCPP_INCLUDE_DIR "libs/restclient-cpp/include")
set(HEADER_SEARCH_PATHS ${PROJECT_INCLUDE_DIR} ${RESTCLIENTCPP_INCLUDE_DIR})
set(RESTCLIENT_LIBRARY "librestclient-cpp.a")
set(LIBRARIES_SEARCH_PATHS ${RESTCLIENT_LIBRARY} )
include_directories(${HEADER_SEARCH_PATHS})
target_link_libraries(px-org-remote-status-service CapnProto::capnp-rpc SQLiteCpp sqlite3 dl yaml-cpp restclient-cpp curl pthread)
install(TARGETS px-org-remote-status-service DESTINATION bin)
install(FILES monitrc PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE DESTINATION bin)

#add_executable(Test_Stat test/Test_Stats.cpp ${CommonSources} ${StatsSources} ${DBSources} test/Test_Stats.cpp)
#target_link_libraries(Test_Stat  SQLiteCpp sqlite3 dl)

add_executable(px-org-remote-status-service-event-action src/StatEventAction.cpp ${CapnpSources} ${CapnpHeaders} ${CommonSources})
target_link_libraries(px-org-remote-status-service-event-action CapnProto::capnp-rpc)
install(TARGETS px-org-remote-status-service-event-action DESTINATION bin)

#target_link_libraries(px-org-remote-status-service-event-action CapnProto::capnp-rpc)
#install(TARGETS px-org-remote-status-service-event-action DESTINATION bin)

#add_executable(Test_DB test/Test_Database.cpp  ${CommonSources} ${DBSources} ${JSON})
#target_link_libraries(Test_DB  SQLiteCpp sqlite3 dl yaml-cpp)

#add_executable(Test_RestClient test/Test_RestClient.cpp ${ApiSources})
#target_link_libraries(Test_RestClient ${LIBRARIES_SEARCH_PATHS} pthread curl)
