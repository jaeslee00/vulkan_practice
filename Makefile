# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/11 00:05:36 by jaelee            #+#    #+#              #
#    Updated: 2019/05/14 02:24:23 by jaelee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = triangle

SRCS = main.c \
		initialization.c \
		phy_devices.c \
		create_logical_devices.c \
		swapchain_query.c \
		swapchain_create.c \
		create_renderpass.c \
		surface_create.c \
		graphics_command_buffers.c \
		descriptor_set_layout.c \
		graphics_pipeline_framebuffers.c \
		get_shader_module.c \
		draw_frame.c \
		free_resources.c \
		get_triangle.c \
		buffer_handlers.c \
		buffer_objects.c \
		ubo_handler.c \
		vertex_buffer.c \
		mvp.c \
		sync.c \
		la/matrix_op.c \
		la/matrix_transformation.c \
		la/vector_op.c

OBJS = $(patsubst %.c, obj/%.o, $(SRCS))

CC = gcc

CLFAGS := $(FLAGS) -fsanitize=address -g

GLFW_FLAGS = -framework Cocoa -framework IOKit \
		  		-framework CoreFoundation -framework CoreVideo

VK_SDK_PATH = /Users/jaelee/42/vv/vulkansdk/macOS

GLFW_PATH = /Users/jaelee/42/vv/glfw

INCLUDES = ./include/visualizer.h \
	./libft/includes/libft.h

INCLUDE_FOLDERS = -I $(VK_SDK_PATH)/include/vulkan -I $(GLFW_PATH)/include -I ./include -I ./libft/includes \

LIBRARY_PATH = -L libft

all: $(NAME)

$(NAME): $(OBJS) libft/libft.a
	$(CC) -fsanitize=address -g -Wl,-search_paths_first -Wl,-headerpad_max_install_names $(OBJS) -o $@ \
	-Wl,-rpath, $(VK_SDK_PATH)/lib $(GLFW_PATH)/src/libglfw3.a \
	${VK_SDK_PATH}/lib/libvulkan.1.dylib -I /Users/jaelee/42/vv/volk $(GLFW_FLAGS) $(LIBRARY_PATH) -lft

obj:
	mkdir -p obj
	mkdir -p obj/la

obj/%.o: src2/%.c $(INCLUDES) | obj
	$(CC) -fsanitize=address -g $(INCLUDE_FOLDERS) -c $< -o $@

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
