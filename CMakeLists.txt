cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD  90)
set(CMAKE_C_STANDARD_REQUIRED True)

# set the project name
project(RT)

add_definitions(-DPLATFORM_MACOS)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk+-3.0)
pkg_check_modules(LIBPNG REQUIRED libpng16)

#  find src -type f -name '*.c' | sort | column -c 100
set(${PROJECT_NAME}_SOURCES
        src/cam/cam_init.c                              src/cmd/utils/cmd_read_png_buf.c                src/scn/add/scn_add_txr.c
        src/cmd/add/cmd_add.c                           src/cmd/utils/cmd_read_txr.c                    src/scn/get/scn_get_mat_by_name.c
        src/cmd/add/cmd_add_camera.c                    src/cmd/utils/cmd_read_txr_png.c                src/scn/get/scn_get_obj_by_id.c
        src/cmd/add/cmd_add_cone.c                      src/cmd/utils/cmd_set_read_attributes.c         src/scn/get/scn_get_obj_by_name.c
        src/cmd/add/cmd_add_copy.c                      src/cmd/utils/cmd_set_read_part.c               src/scn/get/scn_get_obj_num.c
        src/cmd/add/cmd_add_cylinder.c                  src/err/msg_err.c                               src/scn/get/scn_get_txr_by_name.c
        src/cmd/add/cmd_add_group.c                     src/err/msg_ok.c                                src/scn/move/scn_move_obj.c
        src/cmd/add/cmd_add_light.c                     src/err/msg_warn.c                              src/scn/print/scn_print.c
        src/cmd/add/cmd_add_material.c                  src/err/rt_err.c                                src/scn/print/scn_print_grp.c
        src/cmd/add/cmd_add_plane.c                     src/err/rt_warn.c                               src/scn/print/scn_print_mat.c
        src/cmd/add/cmd_add_sphere.c                    src/gpu/gpu_buffer_load.c                       src/scn/print/scn_print_obj.c
        src/cmd/add/cmd_add_txr.c                       src/gpu/gpu_buffer_objects.c                    src/scn/print/scn_print_txr.c
        src/cmd/add/cmd_add_txr_to_scn.c                src/gpu/gpu_init.c                              src/scn/remove/scn_remove_by_name_cam.c
        src/cmd/cmd_error.c                             src/gpu/gpu_kernel_run.c                        src/scn/remove/scn_remove_by_name_copy.c
        src/cmd/cmd_parce_command.c                     src/gpu/gpu_render.c                            src/scn/remove/scn_remove_by_name_grp.c
        src/cmd/cmd_parse.c                             src/grp/grp_init.c                              src/scn/remove/scn_remove_by_name_lgt.c
        src/cmd/ls/cmd_ls.c                             src/grp/grp_remove_by_name.c                    src/scn/remove/scn_remove_by_name_mat.c
        src/cmd/render/cmd_render.c                     src/gui/gui_builder.c                           src/scn/remove/scn_remove_by_name_obj.c
        src/cmd/rm/cmd_rm.c                             src/gui/gui_gtk_tree_view.c                     src/scn/remove/scn_remove_by_name_txr.c
        src/cmd/rm/cmd_rm_by_name.c                     src/gui/gui_init.c                              src/scn/scn_id.c
        src/cmd/rm/cmd_rm_material.c                    src/gui/gui_list_widgets.c                      src/scn/scn_init.c
        src/cmd/set/cmd_set.c                           src/gui/gui_singals.c                           src/scn/utils/scn_del_copies_of.c
        src/cmd/set/cmd_set_camera.c                    src/gui/gui_style.c                             src/scn/utils/scn_group_mem.c
        src/cmd/set/cmd_set_cone.c                      src/lgt/lgt_init.c                              src/scn/utils/scn_name.c
        src/cmd/set/cmd_set_copy.c                      src/main.c                                      src/srv/srv_deinit.c
        src/cmd/set/cmd_set_cylinder.c                  src/mat/mat_init.c                              src/srv/srv_ext.c
        src/cmd/set/cmd_set_group.c src/mtl/fio_png_write.c.old src/srv/srv_ext_data.c
        src/cmd/set/cmd_set_light.c                     src/obj/obj_container_init.c                    src/srv/srv_init.c
        src/cmd/set/cmd_set_material.c                  src/obj/obj_copy_init.c                         src/srv/srv_loop.c
        src/cmd/set/cmd_set_obj_to_scn.c                src/obj/obj_init.c                              src/srv/srv_parse.c
        src/cmd/set/cmd_set_object.c                    src/rt.c                                        src/srv/srv_utils.c
        src/cmd/set/cmd_set_plane.c                     src/scn/add/scn_add_cam.c                       src/tfm/tfm_apply.c
        src/cmd/set/cmd_set_prepare_obj.c               src/scn/add/scn_add_ligth.c                     src/tfm/tfm_init.c
        src/cmd/set/cmd_set_sphere.c                    src/scn/add/scn_add_mat.c                       src/tfm/tfm_move.c
        src/cmd/set/cmd_set_txr.c                       src/scn/add/scn_add_obj.c                       src/txr/txr_init.c
        src/cmd/utils/cmd_read.c                        src/scn/add/scn_add_to_group.c                  src/txr/txr_rgba_to_rgb.c
        src/cmd/utils/cmd_read_light.c                  src/scn/add/scn_add_to_group_copy.c             src/vlk/vlk_init.c
        src/cmd/utils/cmd_read_material.c               src/scn/add/scn_add_to_group_grp.c              src/gpu/gpu_buffer_materials.c
        src/cmd/utils/cmd_read_num.c                    src/scn/add/scn_add_to_group_obj.c
)

add_executable(${PROJECT_NAME}  ${${PROJECT_NAME}_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
        ${PROJECT_SOURCE_DIR}/src       ${PROJECT_SOURCE_DIR}/src/err
        ${PROJECT_SOURCE_DIR}/src/gui   ${PROJECT_SOURCE_DIR}/src/srv
        ${PROJECT_SOURCE_DIR}/src/cmd   ${PROJECT_SOURCE_DIR}/src/gpu
        ${PROJECT_SOURCE_DIR}/src/mtl   ${PROJECT_SOURCE_DIR}/src/scn
        ${PROJECT_SOURCE_DIR}/src/vlk   ${PROJECT_SOURCE_DIR}/src/txr
        ${PROJECT_SOURCE_DIR}/src/mat   ${PROJECT_SOURCE_DIR}/src/cam
        ${PROJECT_SOURCE_DIR}/src/obj   ${PROJECT_SOURCE_DIR}/src/tfm
        ${PROJECT_SOURCE_DIR}/src/shp   ${PROJECT_SOURCE_DIR}/src/txr
        ${PROJECT_SOURCE_DIR}/src/lgt
        )

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/lib/ft/include )
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/lib/num/include )
target_include_directories(${PROJECT_NAME} PUBLIC ${GTK_INCLUDE_DIRS} )
target_include_directories(${PROJECT_NAME} PUBLIC ${LIBPNG_INCLUDE_DIRS} )

target_link_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/build/mtl )
target_link_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/lib/ft )
target_link_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/lib/num )
target_link_directories(${PROJECT_NAME} PUBLIC ${GTK_LIBRARY_DIRS} )
target_link_directories(${PROJECT_NAME} PUBLIC ${LIBPNG_LIBRARY_DIRS} )

target_link_libraries(${PROJECT_NAME} "ft" )
target_link_libraries(${PROJECT_NAME} "num" )
target_link_libraries(${PROJECT_NAME} "mtl" )
target_link_libraries(${PROJECT_NAME} ${GTK_LIBRARIES} )
target_link_libraries(${PROJECT_NAME} ${LIBPNG_LIBRARIES} )

add_definitions(${GTK_CFLAGS_OTHER})
add_definitions(${LIBPNG_CFLAGS_OTHER})

add_custom_command(TARGET RT
        POST_BUILD
        COMMAND "${PROJECT_SOURCE_DIR}/rt_school21_linking.sh" RT
        COMMENT "Linking RT..."
        VERBATIM
        )
        
