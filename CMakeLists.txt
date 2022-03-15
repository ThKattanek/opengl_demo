#
# opengl demo by th.kattanek
#
###################################################
# Options
# -CMAKE_INSTALL_PREFIX=[INSTALL_PATH] --- Setzt den Installationspfad
# -DWIN32_STATIC_BUILD (TRUE or FLASE) --- Wenn TRUE wird ein Windows Static Binary erstellt
# -DCMAKE_BUILD_TYPE (Release or Debug) --- Build Typ welches erzeugt werden soll (Default is Release)

cmake_minimum_required(VERSION 3.2)


##################### PROJEKT #####################

project(opengl_demo LANGUAGES CXX)
message(STATUS "Project Name: " ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

################## CONFIGURATION ##################

# Standard Build Typ = Release
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
	message(STATUS "CMAKE_BUILD_TYPE NOT FOUND -- Default setting to Release")
endif()

# Standard WIN32_STATIC_BUILD = FALSE
if(NOT WIN32_STATIC_BUILD)
	set(WIN32_STATIC_BUILD FALSE CACHE STRING "Choose a static or shared win32 build (TRUE or FALSE)" FORCE)
	message(STATUS "WIN32_STATIC_BUILD NOT FOUND -- Default setting to FALSE")
endif()

if(WIN32)
    if(WIN32_STATIC_BUILD)
	message(STATUS "BUILD A W32 STATIC BINARY")
    endif()
endif()

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

############### COMPILER OPTIONEN #################

if(WIN32)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s -O2 -g2 -Wall")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s -O2 -g2 -Wall")
endif()

############ VERSIONSNUMMER via GIT ###############

# Holen des aktuellen Arbeitsbranches
execute_process(
  COMMAND git rev-parse --abbrev-ref HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_BRANCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Holen des Hashecodes vom letzten Commits
execute_process(
  COMMAND git log -1 --format=%h
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Version aus dem Tag ermitteln
execute_process(
  COMMAND git describe --always --tags
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE VERSION_STRING
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

add_definitions("-DVERSION_STRING=\"${VERSION_STRING}\"")

message(STATUS "Aktueller Git Hashcode : ${GIT_COMMIT_HASH}")
message(STATUS "Aktueller Arbeitsbranch: ${GIT_BRANCH}")
message(STATUS "Aktuelle ${PROJECT_NAME} Version : ${VERSION_STRING}")

############## ARCHITEKTUR ERMITTELN ##############

if ( "${CMAKE_SIZEOF_VOID_P}" EQUAL 4)
	set(ARCHITECTURE "32Bit")
elseif ( "${CMAKE_SIZEOF_VOID_P}" EQUAL 8)
	set(ARCHITECTURE "64Bit")
endif()

add_definitions("-DARCHITECTURE_STRING=\"${ARCHITECTURE}\"")

message(STATUS "Architektur: ${ARCHITECTURE}")

##################### SOURCES #####################

set(HEADERS
    defines.h
    vertex_buffer.h
    index_buffer.h
    shader.h
    texture.h
    camera.h
    libs/stb_image.h
)

set(SOURCES
    main.cpp
    vertex_buffer.cpp
    index_buffer.cpp
    shader.cpp
    texture.cpp
    camera.cpp
)

################### RESOURCEN #####################

if(WIN32)
   # set(WIN_RC ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}.rc)
endif()

##################### LIBRARY #####################

message(STATUS "checking for librarys ...")

find_package(PkgConfig REQUIRED)

# X11
if (UNIX)
    find_package(X11 REQUIRED)
    if(X11_FOUND)
	include_directories(${X11_INCLUDE_DIR})
    else()
	message(FATAL_ERROR "X11 wurde nicht gefunden!")
    endif()
endif()

# OpenGL
find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
    message(STATUS "OpenGL found!")
else()
    message(FATAL_ERROR "OpenGL not found!")
endif()

# GLFW
pkg_check_modules(GLEW REQUIRED glew)
if(GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIR})
    message(STATUS "GLEW found!")
else()
    message(FATAL_ERROR "GLEW not found!")
endif()

# GLFW
pkg_check_modules(GLFW REQUIRED glfw3)
if(GLFW_FOUND)
    include_directories(${GLFW_INCLUDE_DIR})
    message(STATUS "GLFW found!")
else()
    message(FATAL_ERROR "GLFW not found!")
endif()

# GLM
pkg_check_modules(GLM REQUIRED glm)
if(GLM_FOUND)
    include_directories(${GLM_INCLUDE_DIR})
    message(STATUS "GLM found!")
else()
    message(FATAL_ERROR "GLM not found!")
endif()

# OpenAL
find_package(OpenAL REQUIRED)
if(OPENAL_FOUND)
    message(STATUS "OpenAL found!")
else()
    message(FATAL_ERROR "OpenAL not found!")
endif()

################### EXECUTABLE ####################

if(NOT WIN32)
    add_executable(${PROJECT_NAME} ${SOURCES})
else()
    add_executable(${PROJECT_NAME} ${SOURCES})
endif()

################## LINK LIBRARYS ##################

if(WIN32)
    add_definitions(-DGLEW_STATIC)				# for GLEW static linking
    add_definitions(-DAL_LIBTYPE_STATIC)			# for OpenAL static linking
    target_link_libraries(opengl_demo ${OPENAL_LIBRARY}  winmm)	# winmm need openal32
endif(WIN32)

target_link_libraries(opengl_demo ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} ${GL_LIBRARIES} ${OPENAL_LIBRARY})

################### INSTALL #######################

# Set DataPath
if(WIN32)
    add_definitions("-DDATA_PATH=\"./data/\"")
else()
    add_definitions("-DDATA_PATH=\"${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}/data/\"")
endif()

############ Install Binary und Daten #############
if(WIN32)

    ################## Windows #################
    # Install Binary
    install(TARGETS ${PROJECT_NAME} DESTINATION ./)

    # Install all Datas
    install(DIRECTORY "data/shaders" DESTINATION ./data)
    install(DIRECTORY "data/graphics" DESTINATION ./data)

    # Sonstiges
    install(FILES "LICENSE" DESTINATION ./)

else()

    ################## Linux #################
    # Install Binary
    install(TARGETS ${PROJECT_NAME} DESTINATION bin)

    # Install all Datas
    install(DIRECTORY "data/shaders" DESTINATION share/${PROJECT_NAME}/data)
    install(DIRECTORY "data/graphics" DESTINATION share/${PROJECT_NAME}/data)

    # Install Startmenü Eintrag
    # install(FILES "src/${PROJECT_NAME}.desktop" DESTINATION share/applications)
    # install(FILES "data/${PROJECT_NAME}.png" DESTINATION share/icons/hicolor/64x64/apps)

    # Sonstiges
    install(FILES "LICENSE" DESTINATION share/${PROJECT_NAME})
endif()
