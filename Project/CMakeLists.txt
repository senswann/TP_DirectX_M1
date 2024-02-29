cmake_minimum_required(VERSION 3.10)

project("TP_Project" VERSION 1.0)

add_subdirectory(App)
add_subdirectory(Tools)

set_property(DIRECTORY ${PROJECT_BINARY_DIR} PROPERTY VS_STARTUP_PROJECT "App") # Pour start dans le projet App