/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_surface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 00:45:21 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/17 19:09:51 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	create_surface(t_vulkan *vk)
{
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	if (!(vk->window = glfwCreateWindow(WIDTH, HEIGHT, "VULKAN!", NULL, NULL)))
	{
		printf("creating GLFW window failed.\n");
	}
	glfwSetKeyCallback(vk->window, key_callback);
	glfwSetCursorPosCallback(vk->window, mouse_callback);
	vk->surf = NULL;
	if (glfwCreateWindowSurface(vk->instance, vk->window, NULL, &vk->surf) != VK_SUCCESS)
		printf("failed to crate window surface!\n");
}
