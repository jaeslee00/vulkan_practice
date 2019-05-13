/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 17:36:20 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/14 00:52:37 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	recreate_swapchain(t_vulkan *vulkan)
{
	vkDeviceWaitIdle(vulkan->logical_device);
	clear_swapchain_objects(vulkan); /*TODO free resources of rendering related resources */
	swapchain_create(vulkan);
	create_imageviews(vulkan);
	create_renderpass(vulkan);
	/* info to pass to vertex-buffer and index buffer */
	get_triangle_info(vulkan);
	create_graphics_pipeline(vulkan);
	create_framebuffers(vulkan);
	create_ubo(vulkan);
	create_descriptor_pool(vulkan);
	create_descriptor_sets(vulkan);
	create_command_buffers(vulkan);
}

static VkBool32 VKAPI_CALL debug_report_callback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType,
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

static void	register_debug_callback(t_vulkan *vulkan, VkInstance instance)
{
	VkDebugReportCallbackCreateInfoEXT	create_info= {};

	create_info.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
	create_info.flags = VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_ERROR_BIT_EXT;
	create_info.pfnCallback = debug_report_callback;

	PFN_vkCreateDebugReportCallbackEXT	vkCreateDebugReportCallbackEXT =
		(PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");

	vulkan->debug_callback = 0;
	vkCreateDebugReportCallbackEXT(instance, &create_info, 0, &vulkan->debug_callback);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{

	if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
		g_camera[0] = 0.5f;
	else if (key == GLFW_KEY_D && action == GLFW_RELEASE)
		g_camera[0] = 0.0f;
	if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
		g_camera[0] = -0.5f;
	else if (key == GLFW_KEY_A && action == GLFW_RELEASE)
		g_camera[0] = 0.0f;
	if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
		g_camera[2] = -0.5f;
	else if (key == GLFW_KEY_W && action == GLFW_RELEASE)
		g_camera[2] = 0.0f;
	if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
		g_camera[2] = 0.5f;
	else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
		g_camera[2] = 0.0f;
}

int		main()
{
	t_vulkan		vulkan;

	ft_bzero(&g_camera, sizeof(g_camera));
	if (!init_glfw(&vulkan))
	{
		printf("initializing GLFW failed.\n");
		return (0);
	}

	init_vulkan(&vulkan);
	register_debug_callback(&vulkan, vulkan.instance);

	physical_device_select(&vulkan);
	create_logical_devices(&vulkan);
	create_surface(&vulkan);
	/* retrieve handles for each queues */
	vkGetDeviceQueue(vulkan.logical_device, vulkan.graphics_queue_family_index, 0, &vulkan.graphics_queue);
	vkGetDeviceQueue(vulkan.logical_device, vulkan.present_queue_family_index, 0, &vulkan.present_queue);
	vkGetDeviceQueue(vulkan.logical_device, vulkan.transfer_queue_family_index, 0, &vulkan.transfer_queue);

	create_sync(&vulkan);
	/* swapchain recreation objects */
	//////////////////////////////////////////////////////////////////////////
	swapchain_create(&vulkan); // re-create swapchains
	create_imageviews(&vulkan); // re-create swapchains
	create_renderpass(&vulkan); // re-create swapchains

	/* info to pass to vertex-buffer and index buffer */
	get_triangle_info(&vulkan);  // re-create swapchains
	create_descriptor_set_layout(&vulkan);
	create_graphics_pipeline(&vulkan);  // re-create swapchains
	create_framebuffers(&vulkan);  // re-create swapchains
	/////////////////////////////////////////////////////////////////////////
	create_command_pools(&vulkan);
	create_command_pool_transfer(&vulkan);

	create_vertex_buffer(&vulkan);
	create_index_buffer(&vulkan);

	create_ubo(&vulkan);
	create_descriptor_pool(&vulkan);
	create_descriptor_sets(&vulkan);

	create_command_buffers(&vulkan);

	while (!glfwWindowShouldClose(vulkan.window))
	{
		glfwPollEvents();
		draw_frame(&vulkan);
	}
	vkDeviceWaitIdle(vulkan.logical_device);
	free_resource(&vulkan);
	return 0;
}
