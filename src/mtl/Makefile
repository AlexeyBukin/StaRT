# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/09 16:52:07 by kcharla           #+#    #+#              #
#    Updated: 2020/11/10 03:02:04 by kcharla          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MTL_DIR_EXT			:= ./
MTL_BUILD_EXT		:= ../../build/mtl

MTL_DYLIB_EXT		:= $(MTL_BUILD_EXT)/libmtl.dylib
# MTL_FLAGS				:= -L $(MTL_BUILD_EXT) -lmtl

MTL_INCLUDE			= -I $(MTL_DIR_EXT)
MTL_INCLUDE_SWIFT	= -I $(MTL_BUILD_EXT)

# TODO: collect using find
MTL_MODULE_SRC	= $(MTL_DIR_EXT)/mtl_start.swift $(MTL_DIR_EXT)/mtl_texture.swift $(MTL_DIR_EXT)/mtl_buffer.swift
MTL_MODULE_OBJ	= $(MTL_MODULE_SRC:$(MTL_DIR_EXT)/%.swift=$(MTL_BUILD_EXT)/%.swiftmodule)

# TODO: collect using find
MTL_SRC			= $(MTL_DIR_EXT)/mtl.swift $(MTL_MODULE_SRC)
MTL_OBJ			= $(MTL_SRC:$(MTL_DIR_EXT)/%.swift=$(MTL_BUILD_EXT)/%.o)

.PRECIOUS: $(MTL_MODULE_OBJ)

all: $(MTL_DYLIB_EXT)

$(MTL_DYLIB_EXT): $(MTL_BUILD_EXT) $(MTL_OBJ)
	swiftc $(MTL_INCLUDE_SWIFT) -o $(MTL_DYLIB_EXT) -emit-library $(MTL_OBJ) -lz
	install_name_tool -id libmtl.dylib $(MTL_DYLIB_EXT)

$(MTL_BUILD_EXT):
	mkdir -vp $(MTL_BUILD_EXT)

$(MTL_BUILD_EXT)/%.o: $(MTL_DIR_EXT)/%.swift $(MTL_MODULE_OBJ)
	swiftc $(MTL_INCLUDE_SWIFT) -parse-as-library -c $< -o $@
	@touch $@

$(MTL_BUILD_EXT)/%.swiftmodule: $(MTL_DIR_EXT)/%.swift
	swiftc $(MTL_INCLUDE_SWIFT) -parse-as-library -c $< -o $@ -emit-module -module-link-name $(patsubst $(MTL_DIR_EXT)/%.swift,%,$<)
	@touch $@

### DEMO PART ###

demo_mat.exe: all
	gcc -x c _mtl_materials.c.demo fio_png_write.c -L ../../build/mtl -lmtl \
	-I . -I ../gpu -I ../ -I ../scn -I ../../lib/num/include \
	-I ../txr -I ../mat -I ../obj -I ../tfm -I ../shp -I ../cam -I ../lgt \
	-I ~/.brew/Cellar/libpng/1.6.37/include -lz -L/Users/wpoudre/.brew/Cellar/libpng/1.6.37/lib -lpng \
	-I ../vlk -I ../../lib/ft/inc -L ../../lib/num -lnum -L ../../lib/ft -lft -o demo_mat.exe
	install_name_tool -change libmtl.dylib "@rpath/libmtl.dylib" demo_mat.exe
	install_name_tool -add_rpath "@executable_path/../../build/mtl/" demo_mat.exe
