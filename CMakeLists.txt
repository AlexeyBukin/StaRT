cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD  90)
set(CMAKE_C_STANDARD_REQUIRED True)

# set the project name
project(RT)

add_definitions(-DPLATFORM_MACOS)

#  find src -type f -name '*.c' | sort | column -c 100
set(${PROJECT_NAME}_SOURCES
        src/cmd/cmd_add.c               src/err/rt_err.c                src/scn/scn_add_material.c
        src/cmd/cmd_ls.c                src/err/rt_warn.c               src/scn/scn_add_sphere.c
        src/cmd/cmd_parse.c             src/gpu/gpu_buffer_load.c       src/scn/scn_id.c
        src/cmd/cmd_parse_tree.c        src/gpu/gpu_init.c              src/scn/scn_init.c
        src/cmd/cmd_read.c              src/gpu/gpu_kernel_run.c        src/srv/srv_deinit.c
        src/cmd/cmd_read_num.c          src/gui/gui_init.c              src/srv/srv_ext.c
        src/cmd/cmd_set_sphere.c        src/main.c                      src/srv/srv_ext_data.c
        src/cmd/cmd_utils.c             src/rt.c                        src/srv/srv_init.c
        src/cmd/cmd_valid.c             src/scn/check_arguments.c       src/srv/srv_loop.c
        src/err/msg_err.c               src/scn/cone.c                  src/srv/srv_parse.c
        src/err/msg_ok.c                src/scn/cylinder.c              src/srv/srv_utils.c
        src/err/msg_warn.c              src/scn/plane.c                 src/vlk/vlk_init.c
        )

add_executable(${PROJECT_NAME}  ${${PROJECT_NAME}_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
        ${PROJECT_SOURCE_DIR}/src              ${PROJECT_SOURCE_DIR}/src/err
        ${PROJECT_SOURCE_DIR}/src/gui          ${PROJECT_SOURCE_DIR}/src/srv
        ${PROJECT_SOURCE_DIR}/src/cmd          ${PROJECT_SOURCE_DIR}/src/gpu
        ${PROJECT_SOURCE_DIR}/src/mtl          ${PROJECT_SOURCE_DIR}/src/scn
        ${PROJECT_SOURCE_DIR}/src/vlk
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        ${PROJECT_SOURCE_DIR}/lib/ft/inc		)

target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/ft/libft.a)

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
        
