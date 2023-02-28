CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(M5Stack_emu)

SET(CMAKE_CXX_STANDARD 20)

FIND_PACKAGE(Qt5 COMPONENTS Core Widgets)
FIND_PACKAGE(Python COMPONENTS Interpreter Development)
FIND_PACKAGE(Boost COMPONENTS python38)

ADD_DEFINITIONS(-DBOOST_ALL_NO_LIB -DBOOST_PYTHON_STATIC_LIB)

FILE(GLOB src_base src/*.cpp src/*.h src/*.c src/*.hpp)
FILE(GLOB_RECURSE src_widgets src/Widgets/*.cpp src/Widgets/*.h src/Widgets/*.c src/Widgets/*.hpp)
FILE(GLOB_RECURSE src_m5stack src/M5Stack/*.cpp src/M5Stack/*.h src/M5Stack/*.c src/M5Stack/*.hpp)

SOURCE_GROUP("src" FILES ${src_base})
SOURCE_GROUP("src\\Widgets" FILES ${src_widgets})
SOURCE_GROUP("src\\M5Stack" FILES ${src_m5stack})

ADD_EXECUTABLE(M5Stack_emu ${src_base} ${src_widgets} ${src_m5stack})

TARGET_INCLUDE_DIRECTORIES(M5Stack_emu PUBLIC ${Qt5_INCLUDE_DIRS} ${Python_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
TARGET_LINK_DIRECTORIES(M5Stack_emu PUBLIC ${BOOST_LIBRARYDIR})
SET_PROPERTY(TARGET M5Stack_emu PROPERTY AUTOMOC ON)
SET_PROPERTY(TARGET M5Stack_emu PROPERTY AUTORCC ON)

TARGET_LINK_LIBRARIES(M5Stack_emu Qt5::Core Qt5::Widgets ${Python_LIBRARIES} Boost::python)
