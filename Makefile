# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/23 23:15:49 by kcharla           #+#    #+#              #
#    Updated: 2020/10/23 23:47:15 by kcharla          ###   ########.fr        #
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

### GTK_BUNDLE configs
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

### C Flags settings
INCLUDE   = -I include -I src/err -I src/gui -I lib/ft/inc $(GTK_INCLUDE)
LIB_FLAGS = -L $(LIB)/ft -lft $(GTK_LIB_FLAGS)

CFLAGS := -Wall -Wextra -Werror -g
COMPILE = gcc $(CFLAGS) $(INCLUDE)
LINK = gcc $(CFLAGS) $(INCLUDE) $(LIB_FLAGS)

### Sources

# find include -type f -name '*.h' | sort | column -c 100 | sed 's/$/ \\/'
HEADERS		:= src/err/err.h include/rt.h

# find src -type f -name '*.c' | sort | column -c 100 | sed 's/$/ \\/'
SRC			:= src/err/rt_err.c        src/err/rt_warn.c       src/gui/gui_init.c      src/main.c

OBJ			= $(patsubst $(SRC_DIR)%.c, $(BUILD_DIR)%.o, $(SRC))

### Rules
.PHONY: all clean fclean re relink

all: $(NAME)

$(NAME): $(BUILD_DIRS) $(OBJ)
	$(LINK) $(OBJ) -o $(NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(COMPILE) -c $< -o $@

$(BUILD_DIRS):
	@mkdir -vp $(BUILD_DIRS)

clean:
	rm -rf $(BUILD_DIR)

fclean:
	rm -rf $(DEMO_DIR)
	rm $(NAME)

re: fclean all

relink:
	rm -f $(NAME)
	make all

$(LIB_FT):
	@make -C $(LIB)/ft

#------------------------------------------#
#----------- DEMO_PART      ---------------#
#------------------------------------------#

DEMO_DIR := demo
DEMO_COMPILE = gcc -Wall -Wextra -Werror -x c $(INCLUDE) $(LIB_FLAGS)

demo_clean:
	rm -rf $(DEMO_DIR)

$(DEMO_DIR):
	mkdir -vp $(DEMO_DIR)

$(DEMO_DIR)/err: $(DEMO_DIR)
	$(DEMO_COMPILE) src/err/rt_err.c src/err/rt_warn.c src/err/err.c.demo -o $(DEMO_DIR)/err
