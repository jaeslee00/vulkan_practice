# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/11 00:05:36 by jaelee            #+#    #+#              #
#    Updated: 2019/04/14 22:33:40 by jaelee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = triangle

SRCS = example.c \
		phy_devices.c \
		create_logical_devices.c \
		surface_create.c \
		swapchain.c \
		graphics_pipeline.c \
		render_pass.c \
		create_framebuffers.c \
		free_resources.c

OBJS = $(patsubst %.c, obj/%.o, $(SRCS))
CC = gcc
CLFAGS := $(FLAGS) -fsanitize=address -g
GLFW_FLAGS = -framework Cocoa -framework IOKit \
		  		-framework CoreFoundation -framework CoreVideo
VK_SDK_PATH = ~/42/vulkanSDK/macOS
INCLUDES = ./include/visualizer.h \
			./libft/includes/libft.h
INCLUDE_FOLDERS = -I $(VK_SDK_PATH)/include/vulkan -I ./glfw/include -I ./include -I ./libft/includes
LIBRARY_PATH = -L libft
all: $(NAME)

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(CLFAGS) -Wl,-search_paths_first -Wl,-headerpad_max_install_names $(OBJS) -o $@ \
	-Wl,-rpath, $(VK_SDK_PATH)/lib ./glfw/src/libglfw3.a \
	${VK_SDK_PATH}/lib/libvulkan.1.dylib $(GLFW_FLAGS) $(LIBRARY_PATH) -lft

obj:
	mkdir -p obj

obj/%.o: src/%.c $(INCLUDES) | obj
	$(CC) $(CFLAGS) $(INCLUDE_FOLDERS) -c $< -o $@

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
