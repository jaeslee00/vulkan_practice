# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/11 00:05:36 by jaelee            #+#    #+#              #
#    Updated: 2019/06/28 10:50:20 by jaelee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = planet

SRCS = main.c \
		initialization.c \
		input_callbacks.c \
		phy_devices.c \
		create_logical_devices.c \
		image_objects.c \
		transition_image_layout.c \
		swapchain_query.c \
		swapchain_create.c \
		create_renderpass.c \
		create_surface.c \
		create_textures.c \
		icosahedron.c \
		create_depth_resource.c \
		command_buffer_utils.c \
		graphics_command_buffers.c \
		descriptor_set_layout.c \
		graphics_pipeline_framebuffers.c \
		get_shader_module.c \
		draw_frame.c \
		free_resources.c \
		get_triangle.c \
		cube_sphere.c \
		noise_filter.c \
		buffer_handlers.c \
		ubo_handler.c \
		vtx_buffer_description.c \
		mvp.c \
		sync.c \
		la/matrix_op.c \
		la/matrix_transformation.c \
		la/vector_op.c \
		simplex_noise/open-simplex-noise.c

OBJS = $(patsubst %.c, obj/%.o, $(SRCS))
SHADER = shader
CC = gcc

CFLAGS := -O3


GLFW_FLAGS = -framework Cocoa -framework IOKit \
		  		-framework CoreFoundation -framework CoreVideo

VK_SDK_PATH = /Users/jaelee/42/vv/vulkansdk/macOS

GLFW_PATH = /Users/jaelee/.brew/Cellar/glfw/HEAD-3461d1c

LDFLAGS = -L $(VK_SDK_PATH)/lib -lvulkan -L $(GLFW_PATH)/lib -lglfw -L libft -lft

STB_INCLUDE_PATH = -I ./stb
INCLUDES = ./include/visualizer.h \
	./libft/includes/libft.h \
	./include/matrix.h \
	./include/vector.h

INCLUDE_FOLDERS = -I $(VK_SDK_PATH)/include/vulkan -I $(GLFW_PATH)/include -I ./include -I ./libft/includes \

all: $(SHADER) $(NAME)

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(CFLAGS) $(INCLUDE_FOLDERS) $(LDFLAGS) $(OBJS) -o $(NAME)

$(SHADER) :
	/Users/jaelee/42/vv/vulkansdk/macOs/bin/glslangValidator -V /Users/jaelee/42/vv/shaders/triangle.vert
	/Users/jaelee/42/vv/vulkansdk/macOs/bin/glslangValidator -V /Users/jaelee/42/vv/shaders/triangle.frag

obj:
	mkdir -p obj
	mkdir -p obj/la
	mkdir -p obj/simplex_noise

obj/%.o: src/%.c $(INCLUDES) | obj
	$(CC) $(CFLAGS) $(INCLUDE_FOLDERS) $(STB_INCLUDE_PATH) -c $< -o $@

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
