# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/23 23:15:49 by kcharla           #+#    #+#              #
#    Updated: 2020/12/14 18:19:02 by rtacos           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := RT
LIB         := lib

SRC_DIR		:= src
BUILD_DIR	:= build

### Directories search
SRC_DIRS	= $(shell find $(SRC_DIR) -type d)
BUILD_DIRS	= $(patsubst $(SRC_DIR)%, $(BUILD_DIR)%, $(SRC_DIRS))

### Libraries declarations
LIB_FT = $(LIB)/ft/libft.a
LIB_NUM = $(LIB)/num/libnum.a
LIB_FLAGS = -L $(LIB)/ft -lft -L $(LIB)/num -lnum $(GTK_LIB_FLAGS)
LIB_DEPENDENCY = $(LIB_FT) $(LIB_NUM)

# on Linux system gtk3 should be installed (for example with `apt-get install libgtk-3-dev`)
# on MacOS system gtk3 should be installed (for example with `brew install gtk+3`)
GTK_INCLUDE   = $(shell pkg-config gtk+-3.0 --cflags) $(shell pkg-config libpng --cflags)
GTK_LIB_FLAGS = $(shell pkg-config gtk+-3.0 --libs) $(shell pkg-config libpng --libs)

UNAME_SYSTEM := $(shell uname -s)
ifeq ($(UNAME_SYSTEM),Linux)
# on Linux system gtk3 should be installed (if not install with `apt-get install libgtk-3-dev`)
	# GTK_INCLUDE   = $(shell pkg-config gtk+-3.0 --cflags)
	# GTK_LIB_FLAGS = $(shell pkg-config gtk+-3.0 --libs)
	CFLAGS := $(CFLAGS) -no-pie -D PLATFORM_LINUX
	LIB_FLAGS := $(LIB_FLAGS) $(VLK_FLAGS)
	LIB_DEPENDENCY := $(LIB_DEPENDENCY) $(VLK_DYLIB)
endif
ifeq ($(UNAME_SYSTEM),Darwin)
    CFLAGS := $(CFLAGS) -D PLATFORM_MACOS
    MTL_DYLIB := build/mtl/libmtl.dylib
    LIB_FLAGS := $(LIB_FLAGS) -L build/mtl -lmtl
    LIB_DEPENDENCY := $(LIB_DEPENDENCY) $(MTL_DYLIB)
endif

### C Flags settings
INCLUDE := -I src -I lib/ft/inc -I lib/num/include \
-I src/cmd -I src/cam -I src/err -I src/gpu \
-I src/gui -I src/mat -I src/mtl \
-I src/obj -I src/scn -I src/shp \
-I src/srv -I src/tfm -I src/txr -I src/vlk \
-I src/grp -I src/lgt \
$(GTK_INCLUDE)

CFLAGS := -Wall -Wextra -Werror -g $(CFLAGS)
COMPILE = gcc $(CFLAGS) $(INCLUDE)
LINK = gcc $(CFLAGS) $(INCLUDE) $(LIB_FLAGS)

### Sources

# find src -type f -name '*.h' | sort | column -c 100 | sed 's/$/ \/'
HEADERS	:= \
src/cam/cam.h           src/gpu/gpu_types.h     src/obj/obj_types.h     src/srv/srv.h \
src/cam/cam_types.h     src/grp/grp.h           src/rt.h                src/srv/srv_types.h \
src/cmd/cmd.h           src/gui/gui.h           src/rt_types.h          src/tfm/tfm.h \
src/cmd/cmd_add.h       src/gui/gui_types.h     src/scn/scn.h           src/tfm/tfm_types.h \
src/cmd/cmd_set.h       src/lgt/lgt_types.h     src/scn/scn_add.h       src/txr/txr.h \
src/cmd/cmd_types.h     src/mat/mat.h           src/scn/scn_id.h        src/txr/txr_types.h \
src/err/err.h           src/mat/mat_types.h     src/scn/scn_types.h     src/vlk/vlk.h \
src/gpu/gpu.h           src/mtl/mtl.h           src/shp/shp.h \
src/gpu/gpu_objects.h   src/obj/obj.h           src/shp/shp_types.h \

# no main.c!
# find src -type f -name '*.c' ! -name "main.c" | sort | column -c 180 | sed "s/$/ \\\/" # for Mary
# find src -type f -name '*.c' ! -name "main.c" | sort | column -c 120 | sed 's/$/ \/'
SRC_SHARED	:= \
src/cam/cam_init.c                              src/cmd/utils/cmd_read_num.c                    src/scn/add/scn_add_to_group_obj.c \
src/cmd/add/cmd_add.c                           src/cmd/utils/cmd_read_png_buf.c                src/scn/add/scn_add_txr.c \
src/cmd/add/cmd_add_camera.c                    src/cmd/utils/cmd_read_txr.c                    src/scn/get/scn_get_mat_by_name.c \
src/cmd/add/cmd_add_cone.c                      src/cmd/utils/cmd_read_txr_png.c                src/scn/get/scn_get_obj_by_id.c \
src/cmd/add/cmd_add_copy.c                      src/cmd/utils/cmd_set_read_attributes.c         src/scn/get/scn_get_obj_by_name.c \
src/cmd/add/cmd_add_cylinder.c                  src/cmd/utils/cmd_set_read_part.c               src/scn/get/scn_get_txr_by_name.c \
src/cmd/add/cmd_add_group.c                     src/err/msg_err.c                               src/scn/move/scn_move_obj.c \
src/cmd/add/cmd_add_light.c                     src/err/msg_ok.c                                src/scn/print/scn_print.c \
src/cmd/add/cmd_add_material.c                  src/err/msg_warn.c                              src/scn/print/scn_print_grp.c \
src/cmd/add/cmd_add_plane.c                     src/err/rt_err.c                                src/scn/print/scn_print_mat.c \
src/cmd/add/cmd_add_sphere.c                    src/err/rt_warn.c                               src/scn/print/scn_print_obj.c \
src/cmd/add/cmd_add_txr.c                       src/gpu/gpu_buffer_load.c                       src/scn/print/scn_print_txr.c \
src/cmd/add/cmd_add_txr_to_scn.c                src/gpu/gpu_buffer_objects.c                    src/scn/remove/scn_remove_by_name_cam.c \
src/cmd/cmd_error.c                             src/gpu/gpu_init.c                              src/scn/remove/scn_remove_by_name_copy.c \
src/cmd/cmd_parce_command.c                     src/gpu/gpu_kernel_run.c                        src/scn/remove/scn_remove_by_name_grp.c \
src/cmd/cmd_parse.c                             src/gpu/gpu_render.c                            src/scn/remove/scn_remove_by_name_lgt.c \
src/cmd/ls/cmd_ls.c                             src/grp/grp_init.c                              src/scn/remove/scn_remove_by_name_mat.c \
src/cmd/render/cmd_render.c                     src/grp/grp_remove_by_name.c                    src/scn/remove/scn_remove_by_name_obj.c \
src/cmd/rm/cmd_rm.c                             src/gui/gui_builder.c                           src/scn/remove/scn_remove_by_name_txr.c \
src/cmd/rm/cmd_rm_by_name.c                     src/gui/gui_gtk_tree_view.c                     src/scn/scn_id.c \
src/cmd/rm/cmd_rm_material.c                    src/gui/gui_init.c                              src/scn/scn_init.c \
src/cmd/set/cmd_set.c                           src/gui/gui_list_widgets.c                      src/scn/utils/scn_del_copies_of.c \
src/cmd/set/cmd_set_camera.c                    src/gui/gui_singals.c                           src/scn/utils/scn_group_mem.c \
src/cmd/set/cmd_set_cone.c                      src/gui/gui_style.c                             src/scn/utils/scn_name.c \
src/cmd/set/cmd_set_copy.c                      src/lgt/lgt_init.c                              src/srv/srv_deinit.c \
src/cmd/set/cmd_set_cylinder.c                  src/mat/mat_init.c                              src/srv/srv_ext.c \
src/cmd/set/cmd_set_group.c                     src/mtl/fio_png_write.c                         src/srv/srv_ext_data.c \
src/cmd/set/cmd_set_light.c                      src/obj/obj_container_init.c                    src/srv/srv_init.c \
src/cmd/set/cmd_set_material.c                  src/obj/obj_copy_init.c                         src/srv/srv_loop.c \
src/cmd/set/cmd_set_obj_to_scn.c                src/obj/obj_init.c                              src/srv/srv_parse.c \
src/cmd/set/cmd_set_object.c                    src/rt.c                                        src/srv/srv_utils.c \
src/cmd/set/cmd_set_plane.c                     src/scn/add/scn_add_cam.c                       src/tfm/tfm_apply.c \
src/cmd/set/cmd_set_prepare_obj.c               src/scn/add/scn_add_ligth.c                     src/tfm/tfm_init.c \
src/cmd/set/cmd_set_sphere.c                    src/scn/add/scn_add_mat.c                       src/tfm/tfm_move.c \
src/cmd/set/cmd_set_txr.c                       src/scn/add/scn_add_obj.c                       src/txr/txr_init.c \
src/cmd/utils/cmd_read.c                        src/scn/add/scn_add_to_group.c                  src/txr/txr_rgba_to_rgb.c \
src/cmd/utils/cmd_read_light.c                  src/scn/add/scn_add_to_group_copy.c             src/vlk/vlk_init.c \
src/cmd/utils/cmd_read_material.c               src/scn/add/scn_add_to_group_grp.c              src/scn/get/scn_get_obj_num.c

SRC 		= $(SRC_SHARED) src/main.c

OBJ_SHARED  = $(patsubst $(SRC_DIR)%.c, $(BUILD_DIR)%.o, $(SRC_SHARED))
OBJ			= $(patsubst $(SRC_DIR)%.c, $(BUILD_DIR)%.o, $(SRC))

### Rules
.PHONY: all clean fclean re relink

all: $(NAME)

# switch "$(NAME): $(GTK_BUNDLE)" only on 42/21 MACs
# switch "zsh rt_school21_linking.sh" only on 42/21 MACs
ifeq ($(UNAME_SYSTEM),Darwin)
$(NAME): $(GTK_BUNDLE) $(BUILD_DIRS) $(OBJ) $(LIB_DEPENDENCY)
	echo "makefile: making MacOS executable"
	$(COMPILE) -Wl,-rpath,$(GTK_BUNDLE)/lib $(OBJ) -o $(NAME) $(LIB_FLAGS)
	install_name_tool -add_rpath "build/mtl" $(NAME)
	sh rt_school21_linking.sh

$(MTL_DYLIB):
	make -C src/mtl
endif
ifeq ($(UNAME_SYSTEM),Linux)
$(NAME): $(BUILD_DIRS) $(OBJ) $(LIB_DEPENDENCY)
	$(COMPILE) $(OBJ) -o $(NAME) $(LIB_FLAGS)
endif

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(COMPILE) -c $< -o $@

$(BUILD_DIRS):
	@mkdir -vp $(BUILD_DIRS)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf $(GTK_BUNDLE)
	rm -rf $(DEMO_DIR)
	rm -f $(NAME)

re: fclean all

relink:
	rm -f $(NAME)
	make all

rebuild: clean
	rm -f $(NAME)
	make all

$(LIB_FT):
	make -C $(LIB)/ft

$(LIB_NUM):
	make -C $(LIB)/num

$(GTK_BUNDLE):
	zsh rt_school21_get_bundle.sh

#------------------------------------------#
#----------- DEMO_PART      ---------------#
#------------------------------------------#

DEMO_DIR 		:= demo
DEMO_COMPILE 	= gcc -Wall -Wextra -Werror -x c $(INCLUDE) $(LIB_FLAGS)
DEMO_DIRS		= $(patsubst $(SRC_DIR)%, $(DEMO_DIR)%, $(SRC_DIRS))

demo_clean:
	rm -rf $(DEMO_DIR)

$(DEMO_DIRS):
	@mkdir -vp $(DEMO_DIRS)

### MTL DEMOS
DEMO_MTL = demo/gpu/mtl

$(DEMO_MTL)/lib_load: $(DEMO_DIRS) $(MTL_DYLIB) $(MTL_DIR)/_mtl_lib_load.c.demo
	 gcc -Wall -Wextra -Werror $(MTL_FLAGS) -x c $(MTL_DIR)/_mtl_lib_load.c.demo -o $@

### GPU DEMOS
DEMO_GPU = $(DEMO_DIR)/gpu

$(DEMO_GPU)/gpu: $(DEMO_DIRS) $(GTK_BUNDLE) $(BUILD_DIRS) $(OBJ) $(MTL_DYLIB) src/gpu/gpu.c.demo
	 gcc $(CFLAGS) $(INCLUDE) $(LIB_FLAGS) $(MTL_FLAGS) $(OBJ) -x c src/gpu/gpu.c.demo -o $@
	 zsh rt_school21_linking.sh $(DEMO_GPU)/gpu

### GUI DEMOS
DEMO_GUI = $(DEMO_DIR)/gui

$(DEMO_GUI)/css: $(DEMO_DIRS) $(GTK_BUNDLE) $(BUILD_DIRS) $(OBJ) $(MTL_DYLIB) src/gui/gui_css.c.demo
	 gcc $(CFLAGS) $(INCLUDE) $(LIB_FLAGS) $(MTL_FLAGS) $(OBJ) -x c src/gui/gui_css.c.demo -o $@
	 zsh rt_school21_linking.sh $(DEMO_GUI)/css

### Server Demo
$(DEMO_DIR)/srv/srv: $(DEMO_DIRS)
	$(DEMO_COMPILE) src/srv/srv_init.c src/srv/srv_loop.c src/srv/srv.c.demo src/err/*.c -o $@
	zsh rt_school21_linking.sh $(DEMO_DIR)/srv/srv

### ERR Demo
$(DEMO_DIR)/err/err: $(DEMO_DIRS)
	$(DEMO_COMPILE) src/err/rt_err.c src/err/rt_warn.c src/err/err.c.demo -o $@

### Scene demo
$(DEMO_DIR)/scn/scn: $(DEMO_DIRS) $(OBJ_SHARED) $(MTL_DYLIB)
	 gcc $(CFLAGS) $(INCLUDE) $(LIB_FLAGS) $(MTL_FLAGS) $(INCLUDE) -L build/mtl -lmtl $(OBJ_SHARED) -x c src/scn/scn_demo_1.c.demo -o $@
	 zsh rt_school21_linking.sh $(DEMO_DIR)/scn/scn
	 install_name_tool -change "../../build/mtl/libmtl.dylib" "build/mtl/libmtl.dylib" $@
   
   
