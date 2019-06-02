/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 21:42:45 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/02 19:53:15 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _VISUALIZER_H
# define _VISUALIZER_H
# include "vulkan.h"
# include "GLFW/glfw3.h"
# include <stdio.h>
# include <math.h>
# include "ft_assert.h"
# include "libft.h"
# include "array.h"
# include "vector.h"
# include <math.h>
# define GLFW_INCLUDE_VULKAN
# define WIDTH 1200
# define HEIGHT 1200
# define MAX_FRAMES_IN_FLIGHT 2
# define PI 3.1415926535f
# define NEAR_Z 0.001f
# define FAR_Z 100.f
# define FOV PI/3.f

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
	- Most of the commands i./n VULKAN (drawing, texturing, memory transfer and etc)
		are saved in the command buffer and then submitted to QUEUE to execute


*/

# define DIMENSION 3
# define TEXEL_DIMENSION 2
# define COLOR_FORMAT 3
# define FT_FALSE 0
# define FT_TRUE 1

typedef struct	s_vertex
{
	float	pos[DIMENSION];
	float	color[COLOR_FORMAT];
	float	tex_coord[TEXEL_DIMENSION];
}				t_vertex;

typedef struct	s_renderer
{
	t_array		vtx_buffer;
	t_array		frag_buffer;
}				t_renderer;

typedef struct	s_ubo
{
	float	model[16]; /* translation * rotation * scale */
	float	view[16]; /* rotate camera poition and adds translation */
	float	proj[16]; /* perspective distortion, FOV, clipping */
}				t_ubo;

typedef struct	s_cam
{
	float	cam_pos[3];
	float	cam_front[3];
	float	last_x;
	float	last_y;
	float	yaw;
	float	pitch;
	float	rad_yaw;
	float	rad_pitch;
}				t_cam;

t_cam		g_cam;
float		g_camera[3];

typedef struct	s_vulkan
{
	/*global_scale... in C++ */
	GLFWwindow					*window;
	VkInstance					instance;
	VkDebugReportCallbackEXT	debug_callback; /*TODO Erase when finished */
	VkDevice					logical_device; /* logical device */
	VkSurfaceKHR				surf;

	/* Instance extensions */
	uint32_t					enabled_extension_count;
	const char					*extension_name[64];

	/* Device extensions */
	uint32_t					device_extension_count;
	const char					*device_extension_name[64];

	/* Physical device */
	VkPhysicalDevice			*gpu; /*TODO MALLOC */
	uint32_t					gpu_count;
	VkPhysicalDeviceProperties 	dv_props;
	VkPhysicalDeviceFeatures	dv_feats;

	/* Queue */
	VkQueueFamilyProperties		*queue_props; /*TODO MALLOC */
	VkQueue						graphics_queue;
	VkQueue						present_queue;
	uint32_t					queue_family_count;
	uint32_t					graphics_queue_family_index;
	uint32_t					present_queue_family_index;

	/* details of the swapchain support */
	VkSwapchainKHR 				swapchain;
	VkSurfaceCapabilitiesKHR	surf_capabilities;
	VkSurfaceFormatKHR			*surf_formats; /*TODO MALLOC */
	VkPresentModeKHR			*present_modes; /*TODO MALLOC */
	VkFormat 					swapchain_image_format;
	VkColorSpaceKHR				color_space;
	VkPresentModeKHR			present_mode;
	VkExtent2D					swapchain_extent;
	VkImage						*swapchain_images; // same number
	VkImageView					*swapchain_imageviews; // same number
	uint32_t					swapchain_image_count; // same number
	VkFramebuffer				*frame_buffers; // same number /*TODO MALLOC */

	/* Depth-related */
	VkImage						depth_image;
	VkDeviceMemory				depth_image_memory;
	VkImageView					depth_image_view;

	/* texture-related */
	VkImage						texture_image;
	VkDeviceMemory				texture_image_memory;
	VkImageView					texture_image_view;
	VkSampler					texture_sampler;

	/*command bufffers */
	VkCommandPool				command_pool;
	VkCommandPool				command_pool_transfer;
	VkCommandBuffer				*command_buffers; //same number
	/* command_buffers for 'stage_buffer' is created and destroyed separately in
	copy_buffer() function */

	/* pipeline */
	VkDescriptorSetLayout		descriptor_set_layout;
	VkDescriptorPool			descriptor_pool;
	VkDescriptorSet				*descriptor_sets; /*TODO MALLOC */
	VkPipelineLayout			pipeline_layout;
	VkPipeline					graphics_pipeline;
	VkRenderPass				renderpass;

	/*sync objects!! */
	VkSemaphore					*acquire_semaphore; // MALLOC frames in flight
	VkSemaphore					*release_semaphore; // MALLOC frames in flight
	VkFence						*fence;

	t_array						triangle;
	uint32_t					*vertices_index; /*TODO MALLOC */
	VkBuffer					vertex_buffer;
	VkDeviceMemory				vertex_buffer_memory;
	VkBuffer					index_buffer;
	VkDeviceMemory 				index_buffer_memory;
	t_ubo						ubo;
	VkBuffer					*uniform_buffers; /* needs uniform buffers for each frame_buffers */
	VkDeviceMemory				*uniform_buffers_memory;
}				t_vulkan;

int				init_glfw(t_vulkan *vk);
void 			key_callback(GLFWwindow *window, int key, int scancode,
								int action, int mods);
void 			mouse_callback(GLFWwindow* window, double xpos, double ypos);
void			reset_cam(uint32_t width, uint32_t height);
void			init_vulkan(t_vulkan *vk);
int				physical_device_select(t_vulkan *vk);
void			check_devices(t_vulkan *vk);
void			check_queue_family(t_vulkan *vk);
void			create_logical_devices(t_vulkan *vk);
void			create_surface(t_vulkan *vk);
void			recreate_swapchain(t_vulkan *vk);

/* create image_objects : VkImage & VkImageView */
void			create_image(t_vulkan *vk, uint32_t width, uint32_t height, VkFormat format,
					VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties,
					VkImage *image, VkDeviceMemory *image_memory);
VkImageView		create_imageview(t_vulkan *vk, VkImage image, uint32_t levels,
					VkFormat format, VkImageAspectFlags flags);

/* create swapchain */
void			swapchain_query(t_vulkan *vk);
void			create_swapchain(t_vulkan *vk);

VkShaderModule	get_shader_module(t_vulkan *vk, const char *path);

void			create_descriptor_set_layout(t_vulkan *vk);
void			create_graphics_pipeline(t_vulkan *vk);
void			create_renderpass(t_vulkan *vk);
void			create_framebuffers(t_vulkan *vk);
void			create_command_pools(t_vulkan *vk);
void			create_command_pool_transfer(t_vulkan *vk);
void			create_command_buffers(t_vulkan *vk);
void			create_sync(t_vulkan *vk);
void			draw_frame(t_vulkan *vk);

/* vertex info generator */
void			get_triangle_info(t_vulkan *vk);
void			get_vtx_info(t_vertex *vertex, float vtx1, float vtx2, float vtx3,
								float r, float g, float b, float tex1, float tex2);

/* VkBuffer handlers */
void			create_buffer(t_vulkan *vk, VkDeviceSize size, VkBufferUsageFlags usage,
								VkMemoryPropertyFlags properties,
									VkBuffer *buffer, VkDeviceMemory *buffer_memory);

/* buffers to be used */
void			create_vertex_buffer(t_vulkan *vk);
void			create_index_buffer(t_vulkan *vk);

uint32_t		find_memory_type(t_vulkan *vk, uint32_t type_filter,
									VkMemoryPropertyFlags properties);

/* bining and attribute description of vertex buffer */
VkVertexInputBindingDescription		get_binding_description(void);
VkVertexInputBindingDescription		get_binding_description(void);
VkVertexInputAttributeDescription	get_position_attirbutes(void);
VkVertexInputAttributeDescription	get_color_attributes(void);
VkVertexInputAttributeDescription	get_tex_coord_attirbutes(void);

/* create texture */
void			create_texture_image(t_vulkan *vk);
void			create_texture_imageview(t_vulkan *vk);
void			create_texture_sampler(t_vulkan *vk);

void			copy_buffer_to_image(t_vulkan *vk, VkBuffer buffer, VkImage image,
					uint32_t width, uint32_t height);

/* util for recording single-time commands */
VkCommandBuffer	begin_singletime_commands(t_vulkan *vk);
void			end_singletime_commands(t_vulkan *vk, VkCommandBuffer command_buffer);

void			transition_image_layout(t_vulkan *vk, VkImage image, VkFormat format,
					VkImageLayout old_layout, VkImageLayout new_layout);

void			create_ubo(t_vulkan *vk);
void 			create_descriptor_sets(t_vulkan *vk);
void			create_descriptor_pool(t_vulkan *vk);

void			update_model(t_ubo *ubo);
void			update_view(t_ubo *ubo);
void			update_proj(t_ubo *ubo);

void			clear_swapchain_objects(t_vulkan *vk);
void			free_resource(t_vulkan *vk);



void	model_updates(t_ubo *ubo);
void	view_updates(t_ubo *ubo);
void	proj_updates(t_ubo *ubo);

#endif
