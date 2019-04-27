# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/11 00:05:36 by jaelee            #+#    #+#              #
#    Updated: 2019/04/27 15:41:46 by jaelee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = triangle

SRCS = example.c \
		phy_devices.c \
		create_logical_devices.c \
		swapchain.c \
		create_renderpass.c \
		surface_create.c \
		command_buffers.c \
		descriptor_set_layout.c \
		graphics_pipeline.c \
		get_shader_module.c \
		draw_frame.c \
		free_resources.c \
		get_triangle.c \
		create_vertex_buffer.c \
		sync.c

OBJS = $(patsubst %.c, obj/%.o, $(SRCS))

CC = gcc

CLFAGS := $(FLAGS) -g

GLFW_FLAGS = -framework Cocoa -framework IOKit \
		  		-framework CoreFoundation -framework CoreVideo

VK_SDK_PATH = /Users/jaelee/42/vv/vulkansdk/macOS

GLFW_PATH = /sgoinfre/goinfre/Perso/jaelee/glfw

INCLUDES = ./include/visualizer.h \
	./libft/includes/libft.h

INCLUDE_FOLDERS = -I $(VK_SDK_PATH)/include/vulkan -I $(GLFW_PATH)/include -I ./include -I ./libft/includes \

LIBRARY_PATH = -L libft

all: $(NAME)

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(CLFAGS) -Wl,-search_paths_first -Wl,-headerpad_max_install_names $(OBJS) -o $@ \
	-Wl,-rpath, $(VK_SDK_PATH)/lib $(GLFW_PATH)/src/libglfw3.a \
	${VK_SDK_PATH}/lib/libvulkan.1.dylib -I /Users/jaelee/42/vv/volk $(GLFW_FLAGS) $(LIBRARY_PATH) -lft

obj:
	mkdir -p obj

obj/%.o: src2/%.c $(INCLUDES) | obj
	$(CC) -g $(CFLAGS) $(INCLUDE_FOLDERS) -c $< -o $@

libft/libft.a: $(INCLUDES)
	make -C libft

clean:
	rm -f $(OBJS)
	make -C libft clean
	rm -rf obj

fclean: clean
	make -C libft fclean
	rm -rf $(NAME)

re: fclean
	make all
