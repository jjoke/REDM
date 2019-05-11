#-------------------------------------------------------
# Copyright (c) DuiMagic
# All rights reserved.
# History:
# 		<Author>	<Time>		<Version>	  <Des>
#-------------------------------------------------------
cmake_minimum_required(VERSION 2.8)

PROJECT(DMTools)   # 工程名
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true) # 支持简版if else

# 设置输出路径,SET(EXECUTABLE_OUTPUT_PATH <新路径>)并不会对此变量有影响,只是改变了最终目标文件的存储路径
set(EXECUTABLE_OUTPUT_PATH ${DMTools_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH  ${DMTools_BINARY_DIR}/bin)

# 设置引用库路径
set(LIBS ${LIBRARY_OUTPUT_PATH})
LINK_DIRECTORIES(${LIBS})

OPTION(USE_DMDLL_ "Compile DMMain as dll"   ON) # 开启DMMain默认为编译成dll 
if(USE_DMDLL_)
	ADD_DEFINITIONS(-DDLL_DMMAIN)# 给解决方案中所有工程增加宏定义DLL_DMMAIN
endif()

# 开启MT模式
OPTION(USE_ALLMT_ "Compile all projects as mt"   ON)

OPTION(USE_DMLOG_  "DM open log"    ON)# 开启LOG功能
if(USE_DMLOG_)
	ADD_DEFINITIONS(-DDMLOG_ON)# 给解决方案中所有工程增加宏定义LOG_ON
endif()

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)
INCLUDE(PrecompiledHeader)# 增加预编译头文件

# 增加子文件夹
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/DMMain)
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/DMProject)
