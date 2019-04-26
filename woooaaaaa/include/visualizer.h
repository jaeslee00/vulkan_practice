/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 21:42:45 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/26 04:07:26 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _VISUALIZER_H
# define _VISUALIZER_H
# include "vulkan.h"
#include "GLFW/glfw3.h"
#include <stdio.h>
#include "libft.h"
#define GLFW_INCLUDE_VULKAN
#define WIDTH 1200
#define HEIGHT 900

/* Initialization

INSTANCE
	- Connection between VULKAN and APPLICATION
	- application info + instance layer + instance exention infos

PHYSICAL DEVICE
	- Physical device chosen through the 'INSTANCE'
	- available GPU within the system
	- can be multiple if there are multiple devices available

LOGICAL DEVICE
	- Logical device is created through 'PHYSICAL DEVICE'
	- logical connection between GPU(PHYSICAL DEVICE) and VULKAN (main handle)
	- Multiple LOGICAL DEVICES can be created from a PHYSICAL DEVICE
	- Creating Logical device
		1) decalre the 'QUEUE' to utilize from QUEUE_FAMILY
		2) declare DEVICE_EXTENSIONS to utilize
		3) declare DEVICE_FEATURES to utilize
		4) create LOGICAL DEVICE

Queue
	- Most of the commands in VULKAN (drawing, texturing, memory transfer and etc)
		are saved in the command buffer and then submitted to QUEUE to execute


*/
typedef struct	s_visualizer
{
	GLFWwindow	*window;

}				t_visualizer;

typedef struct	s_swapchain_buffer
{
	VkImage			swapchain_image;
	VkCommandBuffer	cmd;
	VkImageView		view;

}				t_swapchain_buffer;

typedef struct	s_vulkan
{
	/*global_scale... in C++ */
	VkInstance					instance;
	VkDevice					logical_device; /* logical device */
	VkQueue						graphics_queue;
	VkQueue						present_queue;
	VkSurfaceKHR				surf;
	/* Instance extensions */
	uint32_t					enabled_extension_count;
	const char					*extension_name[64];
	/* Device extensions */
	uint32_t					device_extension_count;
	const char					*device_extension_name[64];
	/* Physical device */
	VkPhysicalDevice			*gpu; /* MALLOC */
	uint32_t					gpu_count;
	VkPhysicalDeviceProperties 	dv_props;
	VkPhysicalDeviceFeatures	dv_feats;

	/* Queue */
	VkQueueFamilyProperties		*queue_props; /* MALLOC */
	uint32_t					queue_family_count;
	uint32_t					graphics_queue_family_index;
	uint32_t					present_queue_family_index;

	/* details of the swapchain support */
	VkSwapchainKHR 				swapchain;
	VkSurfaceCapabilitiesKHR	surf_capabilities;
	VkSurfaceFormatKHR			*surf_formats; /* MALLOC */
	VkPresentModeKHR			*present_modes; /* MALLOC */
	VkFormat 					format;
	VkColorSpaceKHR				color_space;
	VkPresentModeKHR			present_mode;
	VkExtent2D					swapchain_extent;
	VkImage						*swapchain_images;
	VkImageView					*image_views;

	/* details of swapchain imageviews */
	uint32_t					swapchain_image_count;
	t_swapchain_buffer			*buffer;
	VkFramebuffer				*frame_buffers;
	/*command bufffers */
	VkCommandPool				command_pool;
	VkCommandBuffer				command_buffers;

	/* pipeline */
	VkPipelineLayout			pipeline_layout;
	VkPipeline					graphics_pipeline;
	VkRenderPass				renderpass;

	/*draw frames!! */
	VkSemaphore					image_available_semaphore;
	VkSemaphore					render_done_semaphore;
}				t_vulkan;

int		physical_device_select(t_vulkan *vulkan);
void	check_devices(t_vulkan *vulkan);
void	find_graphics_queue_family(t_vulkan *vulkan);
void	create_logical_devices(t_vulkan *vulkan);
void	surface_support_check(t_vulkan *vulkan);
void	create_surface(t_visualizer *vis, t_vulkan *vulkan);
void	swapchain_query(t_visualizer *vis, t_vulkan *vulkan);
void	swapchain_create(t_vulkan *vulkan);
void	create_graphics_pipeline(t_vulkan *vulkan);
void	create_renderpass(t_vulkan *vulkan);
void	create_framebuffers(t_vulkan *vulkan);
void	create_command_pools(t_vulkan *vulkan);
void	create_command_buffers(t_vulkan *vulkan);
void	create_semaphores(t_vulkan *vulkan);
void	draw_frame(t_vulkan *vulkan);
void	free_resource(t_visualizer *vis, t_vulkan *vulkan);
#endif
