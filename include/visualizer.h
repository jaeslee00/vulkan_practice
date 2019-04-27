/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 21:42:45 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/27 15:41:32 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _VISUALIZER_H
# define _VISUALIZER_H
# include "vulkan.h"
# include "GLFW/glfw3.h"
# include <stdio.h>
# include "ft_assert.h"
# include "libft.h"
# include "array.h"
# define GLFW_INCLUDE_VULKAN
# define WIDTH 1200
# define HEIGHT 900
# define MAX_FRAMES_IN_FLIGHT 2

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

# define DIMENSION 2
# define COLOR_FORMAT 3

typedef struct	s_visualizer
{
	GLFWwindow	*window;

}				t_visualizer;

typedef struct	s_vertex
{
	float	pos[DIMENSION];
	float	color[COLOR_FORMAT];
}				t_vertex;

typedef struct	s_renderer
{
	t_array		vtx_buffer;
	t_array		frag_buffer;
}				t_renderer;

typedef struct	s_ubo
{
	float	model[16];
	float	view[16];
	float	proj[16];
}				t_ubo;

typedef struct	s_vulkan
{
	/*global_scale... in C++ */
	VkInstance					instance;
	VkDevice					logical_device; /* logical device */
	VkQueue						graphics_queue;
	VkQueue						present_queue;
	VkQueue						transfer_queue;
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
	uint32_t					transfer_queue_family_index;
	uint32_t					queue_family_indices[2];

	/* details of the swapchain support */
	VkSwapchainKHR 				swapchain;
	VkSurfaceCapabilitiesKHR	surf_capabilities;
	VkSurfaceFormatKHR			*surf_formats; /* MALLOC */
	VkPresentModeKHR			*present_modes; /* MALLOC */
	VkFormat 					format;
	VkColorSpaceKHR				color_space;
	VkPresentModeKHR			present_mode;
	VkExtent2D					swapchain_extent;
	VkImage						*swapchain_images; // same number
	VkImageView					*image_views; // same number
	uint32_t					swapchain_image_count; // same number
	VkFramebuffer				*frame_buffers; // same number

	/*command bufffers */
	VkCommandPool				command_pool;
	VkCommandPool				command_pool_transfer;
	VkCommandBuffer				*command_buffers; //same number

	/* pipeline */
	VkDescriptorSetLayout		descriptor_set_layout;
	VkPipelineLayout			pipeline_layout;
	VkPipeline					graphics_pipeline;
	VkRenderPass				renderpass;

	/*sync objects!! */
	VkSemaphore					*acquire_semaphore; // MALLOC frames in flight
	VkSemaphore					*release_semaphore; // MALLOC frames in flight
	VkFence						*fence;

	t_array						triangle;
	uint32_t					*vertices_index;
	VkBuffer					vertex_buffer;
	VkDeviceMemory				vertex_buffer_memory;
	VkBuffer					index_buffer;
	VkDeviceMemory 				index_buffer_memory;


}				t_vulkan;

int		physical_device_select(t_vulkan *vulkan);
void	check_devices(t_vulkan *vulkan);
void	find_graphics_queue_family(t_vulkan *vulkan);
void	create_logical_devices(t_vulkan *vulkan);
void	surface_support_check(t_vulkan *vulkan);
void	create_surface(t_visualizer *vis, t_vulkan *vulkan);
void	swapchain_query(t_visualizer *vis, t_vulkan *vulkan);
void	swapchain_create(t_vulkan *vulkan);
VkShaderModule	get_shader_module(t_vulkan *vulkan, const char *path);

void	create_descriptor_set_layout(t_vulkan *vulkan);
void	create_graphics_pipeline(t_vulkan *vulkan);
void	create_renderpass(t_vulkan *vulkan);
void	create_framebuffers(t_vulkan *vulkan);
void	create_command_pools(t_vulkan *vulkan);
void	create_command_pool_transfer(t_vulkan *vulkan);
void	create_command_buffers(t_vulkan *vulkan);
void	create_sync(t_vulkan *vulkan);
void	draw_frame(t_vulkan *vulkan);

void	get_triangle_info(t_vulkan *vulkan);
void	get_vtx_info(t_vertex *vertex, float vtx1, float vtx2, float r, float g, float b);
void	create_vertex_buffer(t_vulkan *vulkan);
void	create_index_buffer(t_vulkan *vulkan);
void	free_resource(t_visualizer *vis, t_vulkan *vulkan);
#endif
