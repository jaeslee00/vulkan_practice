/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 17:36:20 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/27 15:44:25 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

const char* g_debug_layers[] =
{
	"VK_LAYER_LUNARG_standard_validation"
};



void	create_imageviews(t_vulkan *vulkan)
{
	uint32_t				i;

	vkGetSwapchainImagesKHR(vulkan->logical_device, vulkan->swapchain, &vulkan->swapchain_image_count, NULL);
	printf("imagecount :: %u\n", vulkan->swapchain_image_count);
	vulkan->swapchain_images = (VkImage*)malloc(vulkan->swapchain_image_count * sizeof(VkImage));
	vkGetSwapchainImagesKHR(vulkan->logical_device, vulkan->swapchain, &vulkan->swapchain_image_count, vulkan->swapchain_images);
	vulkan->image_views = (VkImageView*)malloc(vulkan->swapchain_image_count * sizeof(VkImageView));

	i = 0;
	while (i < vulkan->swapchain_image_count)
	{
		VkImageViewCreateInfo	imageview_info = {};
		imageview_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		imageview_info.image = vulkan->swapchain_images[i];
		imageview_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
		imageview_info.format = vulkan->format;
		imageview_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		imageview_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		imageview_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		imageview_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		imageview_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		imageview_info.subresourceRange.baseMipLevel = 0;
		imageview_info.subresourceRange.levelCount = 1;
		imageview_info.subresourceRange.baseArrayLayer = 0;
		imageview_info.subresourceRange.layerCount = 1;
		ft_assert((vkCreateImageView(vulkan->logical_device, &imageview_info, NULL, &vulkan->image_views[i]) == VK_SUCCESS),
			"creating swapchain_imageview failed.\n", "example.c", 48);
		i++;
	}
}

void	create_framebuffers(t_vulkan *vulkan)
{
	uint32_t	index;

	index = 0;
	vulkan->frame_buffers = (VkFramebuffer*)malloc(vulkan->swapchain_image_count *sizeof(VkFramebuffer));

	while (index < vulkan->swapchain_image_count)
	{
		VkFramebufferCreateInfo	create_info = {};
		create_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		create_info.renderPass = vulkan->renderpass;
		create_info.attachmentCount = 1;
		create_info.pAttachments = &vulkan->image_views[index]; // 씨바ㅏ다아아아아알ㄹ 주소르 ㄹ제대ㅗㄹ 안정해줘서 망함
		create_info.width = vulkan->swapchain_extent.width;
		create_info.height = vulkan->swapchain_extent.height;
		create_info.layers = 1;
		ft_assert((vkCreateFramebuffer(vulkan->logical_device, &create_info, NULL, &vulkan->frame_buffers[index]) == VK_SUCCESS),
			"failed to create frame buffers", "example.c", 73);
		index++;
	}
}

void	enabled_extensions_setting(t_vulkan *vulkan)
{
	uint32_t	required_extension_count;
	const char	**required_extension;
	uint32_t	i;

	required_extension_count = 0; /*TODO loading extensions. needs to change */
	required_extension = glfwGetRequiredInstanceExtensions(&required_extension_count);
	i = 0;

	vulkan->enabled_extension_count = 0;
	while (i < required_extension_count)
	{
		vulkan->extension_name[vulkan->enabled_extension_count] = required_extension[i];
		vulkan->enabled_extension_count++;
		i++;
	}
	vulkan->extension_name[vulkan->enabled_extension_count] = VK_EXT_DEBUG_REPORT_EXTENSION_NAME;
	vulkan->enabled_extension_count++;
	for (int j=0; j < vulkan->enabled_extension_count; j++)
	printf("[%d] : %s\n", j, vulkan->extension_name[j]);
}

void	init_vulkan(t_visualizer *vis, t_vulkan *vulkan)
{
	VkApplicationInfo		app_info = {};
	VkInstanceCreateInfo	instance_info = {};

	app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	app_info.pApplicationName = "TRIANGLE!";
	app_info.applicationVersion = VK_MAKE_VERSION(1, 1, 101);
	app_info.pEngineName = "No Engine";
	app_info.engineVersion = VK_MAKE_VERSION(1, 1, 101);
	app_info.apiVersion = VK_API_VERSION_1_1;

	instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instance_info.pNext = NULL;
	instance_info.flags = 0;
	instance_info.pApplicationInfo = &app_info;

	enabled_extensions_setting(vulkan);

	instance_info.enabledExtensionCount = vulkan->enabled_extension_count;
	instance_info.ppEnabledExtensionNames = (const char *const *)vulkan->extension_name;
	instance_info.enabledLayerCount = sizeof(g_debug_layers) / sizeof(g_debug_layers[0]);
	instance_info.ppEnabledLayerNames = g_debug_layers;

	ft_assert((vkCreateInstance(&instance_info, NULL, &(vulkan->instance)) == VK_SUCCESS),
			"create instance failed", "example.c", 125);
}

int		init_glfw(t_visualizer *vis)
{
	if (!glfwInit())
	{
		printf("GLFW initialize failed.\n");
		return (0);
	}
	else
	{
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		if (!(vis->window = glfwCreateWindow(WIDTH, HEIGHT, "VULKAN!", NULL, NULL)))
		{
			printf("creating GLFW window failed.\n");
			return (0);
		}
		glfwSetWindowUserPointer(vis->window, vis);
	}
	return (1);
}

VkBool32 VKAPI_CALL debug_report_callback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType,
		uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage, void* pUserData)
{
	if (flags & VK_DEBUG_REPORT_WARNING_BIT_EXT)
	{
		printf("%s\n", pMessage);
		return (VK_FALSE);
	}
	if (flags & VK_DEBUG_REPORT_ERROR_BIT_EXT)
	{
		printf("%s\n", pMessage);
		return (VK_FALSE);
	}
	return (VK_FALSE);
}

VkDebugReportCallbackEXT	register_debug_callback(VkInstance instance)
{
	VkDebugReportCallbackCreateInfoEXT	create_info= {};

	create_info.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
	create_info.flags = VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_ERROR_BIT_EXT;
	create_info.pfnCallback = debug_report_callback;

	PFN_vkCreateDebugReportCallbackEXT	vkCreateDebugReportCallbackEXT =
		(PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");

	VkDebugReportCallbackEXT callback = 0;
	vkCreateDebugReportCallbackEXT(instance, &create_info, 0, &callback);

	return (callback);
}

int		main()
{
	t_visualizer	vis;
	t_vulkan		vulkan;
	VkDebugReportCallbackEXT	debug_callback;



	if (!init_glfw(&vis))
	{
		printf("initializing GLFW failed.\n");
		return (0);
	}

	init_vulkan(&vis, &vulkan);


	debug_callback = register_debug_callback(vulkan.instance);

	physical_device_select(&vulkan);
	create_logical_devices(&vulkan);

	create_surface(&vis, &vulkan);
	swapchain_query(&vis, &vulkan);
	create_sync(&vulkan);
	create_imageviews(&vulkan);
	create_renderpass(&vulkan);
	create_framebuffers(&vulkan);

	get_triangle_info(&vulkan);
//	create_descriptor_set_layout(&vulkan);
	create_graphics_pipeline(&vulkan);

	create_command_pools(&vulkan);
	create_command_pool_transfer(&vulkan);

	vkGetDeviceQueue(vulkan.logical_device, vulkan.graphics_queue_family_index, 0, &vulkan.graphics_queue);
	vkGetDeviceQueue(vulkan.logical_device, vulkan.present_queue_family_index, 0, &vulkan.present_queue);
	vkGetDeviceQueue(vulkan.logical_device, vulkan.transfer_queue_family_index, 0, &vulkan.transfer_queue);

	create_vertex_buffer(&vulkan);
	create_index_buffer(&vulkan);

	create_command_buffers(&vulkan);
// 	vulkan.command_buffers = (VkCommandBuffer*)malloc(vulkan.swapchain_image_count * sizeof(VkCommandBuffer));
// 	VkCommandBufferAllocateInfo	allocate_info = {};
// 	allocate_info.sType = VK_SsTRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
// 	allocate_info.commandPool = vulkan.command_pool;
// 	allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
// 	allocate_info.commandBufferCount = vulkan.swapchain_image_count;
// 	vkAllocateCommandBuffers(vulkan.logical_device, &allocate_info, vulkan.command_buffers);

// 	for (int i=0; i < vulkan.swapchain_image_count; i++) {
// 	VkCommandBufferBeginInfo	begin_info = {};
// 	begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
// // 	begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
// 	begin_info.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
// 	vkBeginCommandBuffer(vulkan.command_buffers[i], &begin_info);
// 	VkClearColorValue		color = {48.f / 255.f, 10.f / 255.f,  36.f / 255.f, 1};

// 	VkClearValue			clear_color = {color};
// 	VkRenderPassBeginInfo	begin_pass = {};
// 	begin_pass.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
// 	begin_pass.renderPass = vulkan.renderpass;
// 	begin_pass.framebuffer = vulkan.frame_buffers[i];
// 	begin_pass.renderArea.extent.width = vulkan.swapchain_extent.width;
// 	begin_pass.renderArea.extent.height = vulkan.swapchain_extent.height;
// 	begin_pass.clearValueCount = 1;
// 	begin_pass.pClearValues = &clear_color;
// 		vkCmdBeginRenderPass(vulkan.command_buffers[i], &begin_pass, VK_SUBPASS_CONTENTS_INLINE);

// 			vkCmdBindPipeline(vulkan.command_buffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, vulkan.graphics_pipeline);
// 			vkCmdDraw(vulkan.command_buffers[i], 3, 1, 0, 0);

// 		vkCmdEndRenderPass(vulkan.command_buffers[i]);

// 	vkEndCommandBuffer(vulkan.command_buffers[i]); }

	while (!glfwWindowShouldClose(vis.window))
	{
		glfwPollEvents();
		draw_frame(&vulkan);
		vkDeviceWaitIdle(vulkan.logical_device);
	}
	free_resource(&vis, &vulkan);
	return 0;
}
