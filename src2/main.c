/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 17:36:20 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/13 15:35:08 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "vector.h"
#include "matrix.h"

void	recreate_swapchain(t_vulkan *vk)
{
	vkDeviceWaitIdle(vk->logical_device);
	clear_swapchain_objects(vk); /*TODO free resources of rendering related resources */
	create_swapchain(vk);
	reset_cam(vk->swapchain_extent.width, vk->swapchain_extent.height);
	create_renderpass(vk);
	//get_triangle_info(vk);
	//get_cube_info(vk);
	//get_icosahedron(vk);
	create_cube(vk, RESOLUTION);
	create_graphics_pipeline(vk);
	create_depth_resource(vk);
	create_framebuffers(vk);
	create_ubo(vk);
	create_descriptor_pool(vk);
	create_descriptor_sets(vk);
	create_command_buffers(vk);
}

static	VkBool32 VKAPI_CALL debug_report_callback(VkDebugReportFlagsEXT flags,
			VkDebugReportObjectTypeEXT objectType, uint64_t object,
				size_t location, int32_t messageCode, const char* pLayerPrefix,
					const char* pMessage, void* pUserData)
{
	(void)objectType;
	(void)object;
	(void)location;
	(void)messageCode;
	(void)pLayerPrefix;
	(void)pUserData;
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

static void	register_debug_callback(t_vulkan *vk, VkInstance instance)
{
	VkDebugReportCallbackCreateInfoEXT	create_info= {};

	create_info.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
	create_info.flags = VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_ERROR_BIT_EXT;
	create_info.pfnCallback = debug_report_callback;

	PFN_vkCreateDebugReportCallbackEXT	vkCreateDebugReportCallbackEXT =
		(PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance,
			"vkCreateDebugReportCallbackEXT");

	vk->debug_callback = 0;
	vkCreateDebugReportCallbackEXT(instance, &create_info, 0, &vk->debug_callback);
}

int		main()
{
	t_vulkan	vk;

	reset_cam(WIDTH, HEIGHT);
	if (!init_glfw(&vk))
	{
		printf("initializing GLFW failed.\n");
		return (0);
	}
	init_vulkan(&vk);
	register_debug_callback(&vk, vk.instance);
	create_surface(&vk);
	physical_device_select(&vk);
	create_logical_devices(&vk);

	/* retrieve handles for each queues */
	create_sync(&vk);
	/* swapchain recreation objects */
	//////////////////////////////////////////////////////////////////////////
	create_swapchain(&vk); // re-create swapchains
	create_renderpass(&vk); // re-create swapchains

	/* info to pass to vertex-buffer and index buffer */
	//get_triangle_info(&vk);  // re-create swapchains
	//get_cube_info(&vk);
	//get_icosahedron(&vk);
	create_cube(&vk, RESOLUTION);
	create_descriptor_set_layout(&vk);
	create_graphics_pipeline(&vk);  // re-create swapchains
	create_command_pools(&vk);
	create_depth_resource(&vk); // re-create swapchains
	create_framebuffers(&vk);  // re-create swapchains
	/////////////////////////////////////////////////////////////////////////
	create_texture_image(&vk);
	create_texture_imageview(&vk);
	create_texture_sampler(&vk);
	create_vertex_buffer(&vk);
	create_index_buffer(&vk);
	create_ubo(&vk);
	create_descriptor_pool(&vk);
	create_descriptor_sets(&vk);

	create_command_buffers(&vk);
	int i = 0;
	while (!glfwWindowShouldClose(vk.window))
	{
		float a;
		float b;
		float c;
		glfwPollEvents();
		if (i == 0)
			a = glfwGetTime();
		draw_frame(&vk);
		i++;
		if (i == 100)
		{
			b = glfwGetTime();
			c = b - a;
			printf("fps : %f\n", 100.f / c);
			i = 0;
		}
	}
	vkDeviceWaitIdle(vk.logical_device);
	free_resource(&vk);
	return 0;
}
