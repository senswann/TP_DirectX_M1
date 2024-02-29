### 	VARIABLES	 ###
set(APP_NAME "App")

set(APP_PRIVATE "Source/Private/${APP_NAME}/")
set(APP_PUBLIC "Source/Public/${APP_NAME}/")

# pour gérer si l'on veut ajouter les debugs ou non
option(USE_DEBUG "use debug system" ON)

#debug source files
set (APP_DEBUG_SOURCES
    ${APP_PUBLIC}/Tools/Debug/AYCDebugLayer.h		${APP_PRIVATE}/Tools/Debug/AYCDebugLayer.cpp
	${APP_PUBLIC}/Tools/Debug/AYCLog.h		${APP_PRIVATE}/Tools/Debug/AYCLog.cpp
)

#App source files
set(APP_SOURCES
	${APP_PRIVATE}main.cpp
    ${APP_PUBLIC}pch.h
	${APP_PUBLIC}/Handler/WindowHandler.h		${APP_PRIVATE}/Handler/WindowHandler.cpp
)

### 	FONCTION	 ###
add_executable(${APP_NAME} ${APP_SOURCES}) # pour ajouter l'executable

if(USE_DEBUG)# pour ajouter l'executable si USE_DEBUG
	add_compile_definitions(USE_DEBUG)
	target_sources(${APP_NAME} PRIVATE ${APP_DEBUG_SOURCES})
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET ${APP_NAME} PROPERTY CXX_STANDARD 20)
endif() # pour etre sur d'utiliser le standard CPP 20

configure_file("CMake_Source/Public/Gen_App/Config/AppConfig.h.in" "Gen_SRC/Public/Gen_App/Config/AppConfig.h")

target_link_libraries(${APP_NAME} PUBLIC "Tools" "d3d12.lib" "dxgi.lib" "dxguid.lib") # pour rajouter la librairie a l'executable

target_include_directories(${APP_NAME} PUBLIC "${PROJECT_BINARY_DIR}/${APP_NAME}/Gen_SRC/Public/"
												 "${CMAKE_CURRENT_SOURCE_DIR}/Source/Public/"
										 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Source/Private/") # pour pouvoir faire les includes dans le projet