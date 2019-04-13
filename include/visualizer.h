/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 21:42:45 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/13 14:13:54 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _VISUALIZER_H
# define _VISUALIZER_H
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <vulkan.h>
#include "libft.h"
#define GLFW_INCLUDE_VULKAN
#define WIDTH 1200
#define HEIGHT 900

typedef struct	s_visualizer
{
	GLFWwindow	*window;
	uint32_t	glfwExtensionCount;
	const char	**glfwExtensions;
}				t_visualizer;

typedef struct	s_vulkan
{
	/*global_scale... in C++ */
	VkInstance					instance;
	VkApplicationInfo			appInfo;
	VkInstanceCreateInfo		createInfo;
	VkDevice					device; /* logical device */
	VkQueue						graphics_queue;
	VkQueue						present_queue;
	VkSurfaceKHR				surf;

	/* Physical device */
	VkPhysicalDevice			*gpu;
	uint32_t					gpu_count;
	VkPhysicalDeviceProperties 	dv_props;
	VkPhysicalDeviceFeatures	dv_feats;

	/* Queue */
	VkQueueFamilyProperties		*queue_props;
	uint32_t					graphics_queue_node_index;
	uint32_t					present_queue_node_index;
	uint32_t					queue_count;

	VkFormat 					format;
	VkColorSpaceKHR				color_space;
	VkPresentModeKHR			present_mode;

	VkExtent2D					swapchainExtent;
	VkFramebuffer				*framebuffers;
	VkCommandBuffer				*commandBuffers;
}				t_vulkan;
#endif
