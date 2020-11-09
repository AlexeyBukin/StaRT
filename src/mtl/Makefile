# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/09 16:52:07 by kcharla           #+#    #+#              #
#    Updated: 2020/11/09 17:23:18 by kcharla          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MTL_DIR			:= ./
MTL_BUILD		:= ../../build/mtl

MTL_DYLIB		:= $(MTL_BUILD)/libmtl.dylib
MTL_FLAGS		:= -L $(MTL_BUILD) -lmtl

MTL_INCLUDE			= -I $(MTL_DIR)
MTL_INCLUDE_SWIFT	= -I $(MTL_BUILD)

# TODO: collect using find
MTL_MODULE_SRC	= $(MTL_DIR)/mtl_start.swift $(MTL_DIR)/mtl_texture.swift $(MTL_DIR)/mtl_buffer.swift
MTL_MODULE_OBJ	= $(MTL_MODULE_SRC:$(MTL_DIR)/%.swift=$(MTL_BUILD)/%.swiftmodule)

# TODO: collect using find
MTL_SRC			= $(MTL_DIR)/mtl.swift $(MTL_MODULE_SRC)
MTL_OBJ			= $(MTL_SRC:$(MTL_DIR)/%.swift=$(MTL_BUILD)/%.o)

.PRECIOUS: $(MTL_MODULE_OBJ)

all: $(MTL_DYLIB)

$(MTL_DYLIB): $(MTL_BUILD) $(MTL_OBJ)
	swiftc $(MTL_INCLUDE_SWIFT) -o $(MTL_DYLIB) -emit-library $(MTL_OBJ) -lz

$(MTL_BUILD):
	mkdir -vp $(MTL_BUILD)

$(MTL_BUILD)/%.o: $(MTL_DIR)/%.swift $(MTL_MODULE_OBJ)
	swiftc $(MTL_INCLUDE_SWIFT) -parse-as-library -c $< -o $@
	@touch $@

$(MTL_BUILD)/%.swiftmodule: $(MTL_DIR)/%.swift
	swiftc $(MTL_INCLUDE_SWIFT) -parse-as-library -c $< -o $@ -emit-module -module-link-name $(patsubst $(MTL_DIR)/%.swift,%,$<)
	@touch $@
