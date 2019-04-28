cmake_minimum_required(VERSION 3.12)
project(px-org-remote-status-service)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

include_directories(include)
include_directories("interface")
include_directories("libs")
include_directories("libs/rapidjson")


find_package(CapnProto CONFIG REQUIRED)

find_package(yaml-cpp REQUIRED)

capnp_generate_cpp(CapnpSources CapnpHeaders
        interface/StatEvent.capnp)

include_directories(${CapnProto_INCLUDE_DIRS})
include_directories(SQLiteCpp/include)

include_directories(${yaml-cpp_INCLUDE_DIRS})


add_subdirectory(SQLiteCpp)

FILE(GLOB CommonSources
        src/Utils.cpp  include/Utils.h
        src/CpuParams.cpp include/CpuParams.h
        src/MemoryParams.cpp include/MemoryParams.h
        src/DiskParams.cpp include/DiskParams.h
        src/GeneralParams.cpp include/GeneralParams.h
        src/StatsParam.cpp include/StatsParam.h
        src/DeviceConfig.cpp include/DeviceConfig.h)

FILE(GLOB RPCSources
        src/RPCServer.cpp include/RPCServer.h
        src/RPCHandler.cpp include/RPCHandler.h)

FILE(GLOB StatsSources
        include/Stats.h
        include/SystemStats.h src/SystemStats.cpp
        src/DiskStats.cpp include/DiskStats.h
        src/StatChecker.cpp include/StatChecker.h)

FILE(GLOB ApiSources
        src/RESTclient.cpp include/RESTclient.h)

FILE(GLOB DBSources
        include/StatusDatabase.h src/StatusDatabase.cpp)

FILE(GLOB JSON
        src/JsonBuilder.cpp include/JsonBuilder.h)

add_executable(px-org-remote-status-service src/main.cpp ${ApiSources} ${RPCSources} ${CommonSources} ${StatsSources} ${CapnpSources} ${CapnpHeaders} ${DBSources} ${JSON})
set(PROJECT_INCLUDE_DIR "src/include")
set(RESTCLIENTCPP_INCLUDE_DIR "libs/restclient-cpp/include")
set(HEADER_SEARCH_PATHS ${PROJECT_INCLUDE_DIR} ${RESTCLIENTCPP_INCLUDE_DIR})
set(RESTCLIENT_LIBRARY "librestclient-cpp.a")
set(LIBRARIES_SEARCH_PATHS ${RESTCLIENT_LIBRARY} )
include_directories(${HEADER_SEARCH_PATHS})
target_link_libraries(px-org-remote-status-service CapnProto::capnp-rpc SQLiteCpp sqlite3 dl yaml-cpp ${LIBRARIES_SEARCH_PATHS} curl pthread)
install(TARGETS px-org-remote-status-service DESTINATION bin)

#add_executable(Test_Stat test/Test_Stats.cpp ${CommonSources} ${StatsSources} ${DBSources} test/Test_Stats.cpp)
#target_link_libraries(Test_Stat  SQLiteCpp sqlite3 dl)

add_executable(px-org-remote-status-service-event-action src/StatEventAction.cpp ${CapnpSources} ${CapnpHeaders} ${CommonSources})

target_link_libraries(px-org-remote-status-service-event-action CapnProto::capnp-rpc)
install(TARGETS px-org-remote-status-service-event-action DESTINATION bin)

add_executable(Test_DB test/Test_Database.cpp  ${CommonSources} ${DBSources} ${JSON})
target_link_libraries(Test_DB  SQLiteCpp sqlite3 dl)

add_executable(Test_RestClient test/Test_RestClient.cpp ${ApiSources})
target_link_libraries(Test_RestClient ${LIBRARIES_SEARCH_PATHS} pthread curl)