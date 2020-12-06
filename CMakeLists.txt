cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD  90)
set(CMAKE_C_STANDARD_REQUIRED True)

# set the project name
project(RT)

add_definitions(-DPLATFORM_MACOS)

#  find src -type f -name '*.c' | sort | column -c 100
set(${PROJECT_NAME}_SOURCE
)

add_executable(${PROJECT_NAME}  ${${PROJECT_NAME}_SOURCES} lib/ft/src/file/ft_read_files.c lib/ft/src/file/ft_read_files.h)

target_include_directories(${PROJECT_NAME} PUBLIC
<<<<<<< HEAD
        ${PROJECT_SOURCE_DIR}/src              ${PROJECT_SOURCE_DIR}/src/err
        ${PROJECT_SOURCE_DIR}/src/gui          ${PROJECT_SOURCE_DIR}/src/srv
        ${PROJECT_SOURCE_DIR}/src/cmd          ${PROJECT_SOURCE_DIR}/src/gpu
        ${PROJECT_SOURCE_DIR}/src/mtl          ${PROJECT_SOURCE_DIR}/src/scn
        ${PROJECT_SOURCE_DIR}/src/mat          ${PROJECT_SOURCE_DIR}/src/txr
        ${PROJECT_SOURCE_DIR}/src/tfm          ${PROJECT_SOURCE_DIR}/src/obj
        ${PROJECT_SOURCE_DIR}/src/shp          ${PROJECT_SOURCE_DIR}/src/cam
        ${PROJECT_SOURCE_DIR}/src/vlk
=======
        ${PROJECT_SOURCE_DIR}/src       ${PROJECT_SOURCE_DIR}/src/err
        ${PROJECT_SOURCE_DIR}/src/gui   ${PROJECT_SOURCE_DIR}/src/srv
        ${PROJECT_SOURCE_DIR}/src/cmd   ${PROJECT_SOURCE_DIR}/src/gpu
        ${PROJECT_SOURCE_DIR}/src/mtl   ${PROJECT_SOURCE_DIR}/src/scn
        ${PROJECT_SOURCE_DIR}/src/vlk   ${PROJECT_SOURCE_DIR}/src/txr
        ${PROJECT_SOURCE_DIR}/src/mat   ${PROJECT_SOURCE_DIR}/src/cam
        ${PROJECT_SOURCE_DIR}/src/obj   ${PROJECT_SOURCE_DIR}/src/tfm
        ${PROJECT_SOURCE_DIR}/src/shp   ${PROJECT_SOURCE_DIR}/src/txr
>>>>>>> 04b620ed443469cd16a4ff6214ee6675bbc7b680
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        ${PROJECT_SOURCE_DIR}/lib/ft/inc		)
target_include_directories(${PROJECT_NAME} PUBLIC
        ${PROJECT_SOURCE_DIR}/lib/num/include		)

target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/ft/libft.a)
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/num/libnum.a)

set (GTK_BUNDLE_DIR ${PROJECT_SOURCE_DIR}/gtk_bundle_42)
set (GTK_INCLUDE_DIR ${GTK_BUNDLE_DIR}/include)
set (GTK_LIB_DIR ${GTK_BUNDLE_DIR}/lib)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${GTK_INCLUDE_DIR}
        ${GTK_INCLUDE_DIR}/gtk-3.0
        ${GTK_INCLUDE_DIR}/glib-2.0
        ${GTK_INCLUDE_DIR}/harfbuzz
        ${GTK_INCLUDE_DIR}/cairo
        )

target_link_directories(${PROJECT_NAME} PUBLIC ${GTK_LIB_DIR} )
target_link_libraries(${PROJECT_NAME} "gtk-3.0" "gdk-3.0" "glib-2.0" "gobject-2.0" "gio-2.0")

target_link_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/build/mtl)
target_link_libraries(${PROJECT_NAME} "mtl")

add_custom_command(TARGET RT
        POST_BUILD
        COMMAND "${CMAKE_CURRENT_BINARY_DIR}/../rt_school21_linking.sh" RT
        COMMENT "Linking RT..."
        VERBATIM
        )
        
