cmake_minimum_required(VERSION 3.12)
project(px-org-remote-status-service)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

include_directories(include)
include_directories("interface")
include_directories("libs")


find_package(CapnProto CONFIG REQUIRED)

capnp_generate_cpp(CapnpSources CapnpHeaders
        interface/StatEvent.capnp)

include_directories(${CapnProto_INCLUDE_DIRS})

#add_subdirectory(SQLiteCpp)

FILE(GLOB CommonSources
        src/Utils.cpp  include/Utils.h)

FILE(GLOB RPCSources
        src/RPCServer.cpp include/RPCServer.h
        src/RPCHandler.cpp include/RPCHandler.h)

FILE(GLOB StatsSources
        include/Stats.h
        include/SystemStats.h src/SystemStats.cpp
        src/DiskStats.cpp include/DiskStats.h)


add_executable(px-org-remote-status-service src/main.cpp ${RPCSources} ${CommonSources} ${StatsSources} ${CapnpSources} ${CapnpHeaders})
target_link_libraries(px-org-remote-status-service CapnProto::capnp-rpc)
install(TARGETS px-org-remote-status-service DESTINATION bin)

add_executable(Test_Stat test/Test_Stats.cpp ${CommonSources} ${StatsSources} test/Test_Stats.cpp)
#target_link_libraries(px-org-remote-status-service SQLiteCpp sqlite3 )

add_executable(px-org-remote-status-service-event-action src/StatEventAction.cpp ${CapnpSources} ${CapnpHeaders} ${CommonSources})
target_link_libraries(px-org-remote-status-service-event-action CapnProto::capnp-rpc)
install(TARGETS px-org-remote-status-service-event-action DESTINATION bin)
