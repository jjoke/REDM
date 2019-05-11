#-------------------------------------------------------
# Copyright (c) DuiMagic
# All rights reserved.
# History:
# 		<Author>	<Time>		<Version>	  <Des>
#-------------------------------------------------------
PROJECT(DMProject) 

# 文件分组（过滤），同时必须加入到ADD_LIBRARY中才能显示
FILE(GLOB ROOT_HEADER 		${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h)
FILE(GLOB ROOT_SOURCE 		${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp;src/*.c)

SOURCE_GROUP("inc" 				FILES 	${ROOT_HEADER})
SOURCE_GROUP("src"				FILES 	${ROOT_SOURCE})

# 增加预编译头
use_precompiled_header(DMProject
   "${CMAKE_CURRENT_SOURCE_DIR}/inc/StdAfx.h"
   "${CMAKE_CURRENT_SOURCE_DIR}/src/StdAfx.cpp"
  )
  
 # 增加头文件搜索路径
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/inc
					${CMAKE_CURRENT_SOURCE_DIR}/)

# 引用DmMain的头文件
INCLUDE_DIRECTORIES(${DMTools_SOURCE_DIR}/DmMain/inc
					${DMTools_SOURCE_DIR}/DmMain/inc/Common;
					${DMTools_SOURCE_DIR}/DmMain/inc/Common/Template;
					${DMTools_SOURCE_DIR}/DmMain/inc/Core;
					${DMTools_SOURCE_DIR}/DmMain/inc/Core/Msg;
					${DMTools_SOURCE_DIR}/DmMain/inc/Core/Dui;
					${DMTools_SOURCE_DIR}/DmMain/inc/Core/Event;
					${DMTools_SOURCE_DIR}/DmMain/inc/IDmMain;
					${DMTools_SOURCE_DIR}/DmMain/inc/Modules;
					${DMTools_SOURCE_DIR}/DmMain/inc/Widgets;)
					
				
# 输出设置
if(USE_ALLMT_)
SET(CMAKE_CXX_FLAGS_DEBUG "/D_DEBUG /MTd /Zi /Ob0 /Od /RTC1")# 直接抄gui的默认，然后 改成mtd
SET(CMAKE_CXX_FLAGS_RELEASE "/MT /O2 /Ob2 /D NDEBUG")
SET(CMAKE_CXX_FLAGS_MINSIZEREL "/MT /O1 /Ob1 /D NDEBUG")
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MT /Zi /O2 /Ob1 /D NDEBUG")
endif()
ADD_DEFINITIONS(-DUNICODE -D_UNICODE)  # unicode版本
ADD_EXECUTABLE(DMProject  WIN32 ${ROOT};${ROOT_HEADER};${ROOT_SOURCE};)
SET_TARGET_PROPERTIES(DMProject PROPERTIES OUTPUT_NAME "DMProject")

# 增加项目依赖项
add_dependencies(DMProject  DmMain)

 