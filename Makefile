# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/23 23:15:49 by kcharla           #+#    #+#              #
#    Updated: 2020/11/09 17:32:48 by kcharla          ###   ########.fr        #
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
LIB_FLAGS = -L $(LIB)/ft -lft $(GTK_LIB_FLAGS)
LIB_DEPENDENCY = $(LIB_FT)

UNAME_SYSTEM := $(shell uname -s)
ifeq ($(UNAME_SYSTEM),Linux)
# on Linux system gtk3 should be installed (if not install with `apt-get install libgtk-3-dev`)
	GTK_INCLUDE   = $(shell pkg-config gtk+-3.0 --cflags)
	GTK_LIB_FLAGS = $(shell pkg-config gtk+-3.0 --libs)
	CFLAGS := $(CFLAGS) -no-pie -D PLATFORM_LINUX
	LIB_FLAGS := $(LIB_FLAGS) $(VLK_FLAGS)
	LIB_DEPENDENCY := $(LIB_DEPENDENCY) $(VLK_DYLIB)
endif
ifeq ($(UNAME_SYSTEM),Darwin)
GTK_BUNDLE   := gtk_bundle_42
GTK_INC_DIR   = $(GTK_BUNDLE)/include
GTK_LIB_DIR   = $(GTK_BUNDLE)/lib

GTK_INCLUDE   = -I$(GTK_INC_DIR) -I$(GTK_INC_DIR)/gtk-3.0 \
                    -I$(GTK_INC_DIR)/glib-2.0 -I$(GTK_INC_DIR)/harfbuzz \
                    -I$(GTK_INC_DIR)/cairo

GTK_LIB_FLAGS = -L$(GTK_LIB_DIR) -lgtk-3.0 -lgdk-3.0 -Wl,-framework,Cocoa \
                    -Wl,-framework,Carbon -Wl,-framework,CoreGraphics \
                    -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -latk-1.0 \
                    -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 \
                    -lgobject-2.0 -lglib-2.0 -lintl

MTL_DYLIB := build/mtl/libmtl.dylib

CFLAGS := $(CFLAGS) -D PLATFORM_MACOS
LIB_FLAGS := $(LIB_FLAGS) -L build/mtl -lmtl

LIB_DEPENDENCY := $(LIB_DEPENDENCY) $(MTL_DYLIB)

endif

### C Flags settings
INCLUDE   = 	-I src -I src/err -I src/gui -I lib/ft/inc -I src/gpu -I src/srv \
				-I src/cmd -I src/scn \
				-I src/mtl -I src/vlk $(GTK_INCLUDE)

CFLAGS := -Wall -Wextra -Werror -g $(CFLAGS)
COMPILE = gcc $(CFLAGS) $(INCLUDE)
LINK = gcc $(CFLAGS) $(INCLUDE) $(LIB_FLAGS)

### Sources

# find src -type f -name '*.h' | sort | column -c 100 | sed 's/$/ \\/'
HEADERS	:= src/cmd/cmd.h           src/gui/gui.h           src/scn/scn.h           src/vlk/vlk.h \
           src/err/err.h           src/mtl/mtl.h           src/scn/scn_types.h \
           src/gpu/gpu.h           src/rt.h                src/srv/srv.h \
           src/gpu/gpu_types.h     src/rt_types.h          src/srv/srv_types.h

# no main.c!
# find src -type f -name '*.c' ! -name "main.c" | sort | column -c 100 | sed 's/$/ \\/'
SRC_SHARED	:= src/cmd/cmd_parse.c             src/gui/gui_init.c              src/srv/srv_loop.c \
               src/err/rt_err.c                src/rt.c                        src/srv/srv_parse.c \
               src/err/rt_warn.c               src/scn/scn_init.c              src/srv/srv_request.c \
               src/gpu/gpu_buffer_load.c       src/srv/srv_ext.c               src/srv/srv_shutdown.c \
               src/gpu/gpu_init.c              src/srv/srv_ext_data.c          src/srv/srv_utils.c \
               src/gpu/gpu_kernel_run.c        src/srv/srv_init.c              src/vlk/vlk_init.c \

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
	$(COMPILE) $(OBJ) -o $(NAME) $(LIB_FLAGS)
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

$(GTK_BUNDLE):
	zsh rt_school21_get_bundle.sh

#------------------------------------------#
#----------- DEMO_PART      ---------------#
#------------------------------------------#

# DEMO_DIR 		:= demo
# DEMO_COMPILE 	= gcc -Wall -Wextra -Werror -x c $(INCLUDE) $(LIB_FLAGS)
# DEMO_DIRS		= $(patsubst $(SRC_DIR)%, $(DEMO_DIR)%, $(SRC_DIRS))
#
# demo_clean:
# 	rm -rf $(DEMO_DIR)
#
# $(DEMO_DIRS):
# 	@mkdir -vp $(DEMO_DIRS)
#
# ### MTL DEMOS
# DEMO_MTL = demo/gpu/mtl
#
# $(DEMO_MTL)/lib_load: $(DEMO_DIRS) $(MTL_DYLIB) $(MTL_DIR)/_mtl_lib_load.c.demo
# 	 gcc -Wall -Wextra -Werror $(MTL_FLAGS) -x c $(MTL_DIR)/_mtl_lib_load.c.demo -o $@
#
# ### GPU DEMOS
# DEMO_GPU = $(DEMO_DIR)/gpu
#
# $(DEMO_GPU)/gpu: $(DEMO_DIRS) $(GTK_BUNDLE) $(BUILD_DIRS) $(OBJ) $(MTL_DYLIB) src/gpu/gpu.c.demo
# 	 gcc $(CFLAGS) $(INCLUDE) $(LIB_FLAGS) $(MTL_FLAGS) $(OBJ) -x c src/gpu/gpu.c.demo -o $@
# 	 zsh rt_school21_linking.sh $(DEMO_GPU)/gpu
#
# ### GUI DEMOS
# DEMO_GUI = $(DEMO_DIR)/gui
#
# $(DEMO_GUI)/css: $(DEMO_DIRS) $(GTK_BUNDLE) $(BUILD_DIRS) $(OBJ) $(MTL_DYLIB) src/gui/gui_css.c.demo
# 	 gcc $(CFLAGS) $(INCLUDE) $(LIB_FLAGS) $(MTL_FLAGS) $(OBJ) -x c src/gui/gui_css.c.demo -o $@
# 	 zsh rt_school21_linking.sh $(DEMO_GUI)/css
#
# ### Server Demo
# $(DEMO_DIR)/srv/srv: $(DEMO_DIRS)
# 	$(DEMO_COMPILE) src/srv/srv_init.c src/srv/srv_loop.c src/srv/srv.c.demo src/err/*.c -o $@
# 	zsh rt_school21_linking.sh $(DEMO_DIR)/srv/srv
#
# ### ERR Demo
# $(DEMO_DIR)/err/err: $(DEMO_DIRS)
# 	$(DEMO_COMPILE) src/err/rt_err.c src/err/rt_warn.c src/err/err.c.demo -o $@
