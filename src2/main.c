/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 17:36:20 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/16 18:33:59 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "vector.h"
#include "matrix.h"
#include <math.h>
#include "vector.h"

void	reset_cam(uint32_t width, uint32_t height)
{
	g_cam.cam_pos[0] = 0.0f;
	g_cam.cam_pos[1] = 0.0f;
	g_cam.cam_pos[2] = 1.0f;
	g_cam.cam_front[0] = 0.0f;
	g_cam.cam_front[1] = 0.0f;
	g_cam.cam_front[2] = -1.0f;

	g_cam.last_x = 600;
	g_cam.last_y = 600;
	g_cam.yaw = 0.0f;
	g_cam.pitch = 0.0f;
}

void	recreate_swapchain(t_vulkan *vulkan)
{
	vkDeviceWaitIdle(vulkan->logical_device);
	clear_swapchain_objects(vulkan); /*TODO free resources of rendering related resources */
	swapchain_create(vulkan);
	create_imageviews(vulkan);
	//reset_cam(vulkan->swapchain_extent.width, vulkan->swapchain_extent.height);
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
	float	camera_speed;
	float	up_vec[3];
	float	tmp[3];

	camera_speed = 0.1f;
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
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	float	x_offset;
	float	y_offset;
	float	sensitivity;

	sensitivity = 0.1f;
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
	printf("%f %f\n", g_cam.yaw, g_cam.pitch);
	vec3_normalize(g_cam.cam_front);
}

int		main()
{
	t_vulkan		vulkan;

	reset_cam(WIDTH, HEIGHT);
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
