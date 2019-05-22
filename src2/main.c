/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 17:36:20 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/22 10:28:23 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "vector.h"
#include "matrix.h"
#include <math.h>

void	reset_cam(uint32_t width, uint32_t height)
{
	g_cam.cam_pos[0] = 0.0f;
	g_cam.cam_pos[1] = 0.0f;
	g_cam.cam_pos[2] = 0.0f;
	g_cam.cam_front[0] = 0.0f;
	g_cam.cam_front[1] = 0.0f;
	g_cam.cam_front[2] = -1.0f;
			g_cam.last_x = WIDTH / 2;
			g_cam.last_y = HEIGHT / 2;
	g_cam.yaw = -90.0f;
	g_cam.pitch = 0.0f;
}

void	recreate_swapchain(t_vulkan *vk)
{
	vkDeviceWaitIdle(vk->logical_device);
	clear_swapchain_objects(vk); /*TODO free resources of rendering related resources */
	swapchain_create(vk);
	create_imageviews(vk);
	//reset_cam(vk->swapchain_extent.width, vk->swapchain_extent.height);
	create_renderpass(vk);
	/* info to pass to vertex-buffer and index buffer */
	get_triangle_info(vk);
	create_graphics_pipeline(vk);
	create_framebuffers(vk);
	create_ubo(vk);
	create_descriptor_pool(vk);
	create_descriptor_sets(vk);
	create_command_buffers(vk);
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

static void	register_debug_callback(t_vulkan *vk, VkInstance instance)
{
	VkDebugReportCallbackCreateInfoEXT	create_info= {};

	create_info.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
	create_info.flags = VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_ERROR_BIT_EXT;
	create_info.pfnCallback = debug_report_callback;

	PFN_vkCreateDebugReportCallbackEXT	vkCreateDebugReportCallbackEXT =
		(PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");

	vk->debug_callback = 0;
	vkCreateDebugReportCallbackEXT(instance, &create_info, 0, &vk->debug_callback);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	float	camera_speed;
	float	up_vec[3];
	float	tmp[3];

	camera_speed = 0.05f;
	up_vec[0] = 0.0f;
	up_vec[1] = 1.0f;
	up_vec[2] = 0.0f;
	if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		vec3_cross(tmp, g_cam.cam_front, up_vec);
		vec3_normalize(tmp);
		g_cam.cam_pos[0] += camera_speed * tmp[0];
		g_cam.cam_pos[1] += camera_speed * tmp[1];
		g_cam.cam_pos[2] += camera_speed * tmp[2];
	}
	// else if (key == GLFW_KEY_D && action == GLFW_RELEASE)
	// 	g_cam.velocity[0] = 0.0f;
	if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		vec3_cross(tmp, g_cam.cam_front, up_vec);
		vec3_normalize(tmp);
		g_cam.cam_pos[0] -= camera_speed * tmp[0];
		g_cam.cam_pos[1] -= camera_speed * tmp[1];
		g_cam.cam_pos[2] -= camera_speed * tmp[2];
	}
	// else if (key == GLFW_KEY_A && action == GLFW_RELEASE)
	// 	g_cam.velocity[0] = 0.0f;
	if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		g_cam.cam_pos[0] += camera_speed * g_cam.cam_front[0];
		g_cam.cam_pos[1] += camera_speed * g_cam.cam_front[1];
		g_cam.cam_pos[2] += camera_speed * g_cam.cam_front[2];
	}
	// else if (key == GLFW_KEY_W && action == GLFW_RELEASE)
	// 	g_cam.velocity[2] = 0.0f;
	if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		g_cam.cam_pos[0] -= camera_speed * g_cam.cam_front[0];
		g_cam.cam_pos[1] -= camera_speed * g_cam.cam_front[1];
		g_cam.cam_pos[2] -= camera_speed * g_cam.cam_front[2];
	}
	// else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
	// 	g_cam.velocity[2] = 0.0f;
	if (key == GLFW_KEY_R)
	{
		reset_cam(WIDTH, HEIGHT);
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	float	x_offset;
	float	y_offset;
	float	sensitivity;

	sensitivity = 0.03f;
	x_offset = xpos - g_cam.last_x;
	y_offset = g_cam.last_y - ypos;
	g_cam.last_x = xpos;
	g_cam.last_y = ypos;
	g_cam.yaw += x_offset * sensitivity;
	g_cam.pitch += y_offset * sensitivity;
	if (g_cam.pitch > 89.0f)
		g_cam.pitch = 89.0f;
	if (g_cam.pitch < -89.0f)
		g_cam.pitch = -89.0f;

	g_cam.rad_yaw = (g_cam.yaw * PI) / 180.f;
	g_cam.rad_pitch = (g_cam.pitch * PI) / 180.f;

	g_cam.cam_front[0] = cos(g_cam.rad_pitch) * cos(g_cam.rad_yaw);
	g_cam.cam_front[1] = sin(g_cam.rad_pitch);
	g_cam.cam_front[2] = cos(g_cam.rad_pitch) * sin(g_cam.rad_yaw);
	vec3_normalize(g_cam.cam_front);
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

	physical_device_select(&vk);
	create_logical_devices(&vk);
	create_surface(&vk);
	/* retrieve handles for each queues */
	vkGetDeviceQueue(vk.logical_device, vk.graphics_queue_family_index, 0, &vk.graphics_queue);
	vkGetDeviceQueue(vk.logical_device, vk.present_queue_family_index, 0, &vk.present_queue);
	vkGetDeviceQueue(vk.logical_device, vk.transfer_queue_family_index, 0, &vk.transfer_queue);

	create_sync(&vk);
	/* swapchain recreation objects */
	//////////////////////////////////////////////////////////////////////////
	swapchain_create(&vk); // re-create swapchains
	create_imageviews(&vk); // re-create swapchains
	create_renderpass(&vk); // re-create swapchains

	/* info to pass to vertex-buffer and index buffer */
	get_triangle_info(&vk);  // re-create swapchains
	create_descriptor_set_layout(&vk);
	create_graphics_pipeline(&vk);  // re-create swapchains
	create_framebuffers(&vk);  // re-create swapchains
	/////////////////////////////////////////////////////////////////////////
	create_command_pools(&vk);
	create_command_pool_transfer(&vk);
	//create_depth_resource(&vk);

	create_vertex_buffer(&vk);
	create_index_buffer(&vk);

	create_ubo(&vk);
	create_descriptor_pool(&vk);
	create_descriptor_sets(&vk);

	create_command_buffers(&vk);

	while (!glfwWindowShouldClose(vk.window))
	{
		glfwPollEvents();
		draw_frame(&vk);
	}
	vkDeviceWaitIdle(vk.logical_device);
	free_resource(&vk);
	return 0;
}
