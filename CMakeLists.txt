cmake_minimum_required(VERSION 3.12)
project(px-org-remote-status-service)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

include_directories(include)

#add_subdirectory(SQLiteCpp)

FILE(GLOB CommonSources
        src/Utils.cpp  include/Utils.h)

FILE(GLOB StatsSources
        include/Stats.h
        include/SystemStats.h src/SystemStats.cpp )


add_executable(px-org-remote-status-service src/main.cpp ${CommonSources} ${StatsSources} test/Test_Stat.cpp)
#target_link_libraries(px-org-remote-status-service SQLiteCpp sqlite3 )
install(TARGETS px-org-remote-status-service DESTINATION bin)

add_executable(Test_Stat test/Test_Stat.cpp ${CommonSources} ${StatsSources} test/Test_Stat.cpp)
#target_link_libraries(px-org-remote-status-service SQLiteCpp sqlite3 )
install(TARGETS Test_Stat DESTINATION bin)