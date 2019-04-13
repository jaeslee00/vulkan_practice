/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 17:36:20 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/13 19:33:13 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	swapchain_create(t_visualizer *vis, t_vulkan *vulkan)
{

}

void	swapchain_query(t_visualizer *vis, t_vulkan *vulkan)
{
	VkSurfaceCapabilitiesKHR	surf_capabilities;
	VkSurfaceFormatKHR			*surf_formats;
	uint32_t					format_count;
	VkPresentModeKHR			*present_modes;
	uint32_t					present_mode_count;

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vulkan->gpu[0], vulkan->surf, &surf_capabilities);
	vkGetPhysicalDeviceSurfaceFormatsKHR(vulkan->gpu[0], vulkan->surf, &format_count, NULL);
	if (format_count == 0)
	{
		printf("surface formats missing\n");
		exit(0);
	}
	surf_formats = (VkSurfaceFormatKHR*)malloc(format_count * sizeof(VkSurfaceFormatKHR)); /*TODO replace vector */
	vkGetPhysicalDeviceSurfaceFormatsKHR(vulkan->gpu[0], vulkan->surf, &format_count, surf_formats);
	vulkan->format = surf_formats[0].format;
	vulkan->color_space = surf_formats[0].colorSpace;

	vkGetPhysicalDeviceSurfacePresentModesKHR(vulkan->gpu[0], vulkan->surf, &present_mode_count, NULL);
	present_modes = (VkPresentModeKHR*)malloc(present_mode_count * sizeof(VkPresentModeKHR)); /*TODO replace vector */
	vkGetPhysicalDeviceSurfacePresentModesKHR(vulkan->gpu[0], vulkan->surf, &present_mode_count, present_modes);
	vulkan->present_mode = present_modes[0];

}

void	create_surface(t_visualizer *vis, t_vulkan *vulkan)
{
	VkBool32	surfaceSupport;
	if (glfwCreateWindowSurface(vulkan->instance, vis->window, NULL, &vulkan->surf) != VK_SUCCESS)
		printf("failed to crate window surface!\n");
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
}

int		init_vulkan(t_visualizer *vis, t_vulkan *vulkan)
{

	vulkan->appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	vulkan->appInfo.pApplicationName = "TRIANGLE BITCH!";
	vulkan->appInfo.applicationVersion = VK_MAKE_VERSION(1, 1, 101);
	vulkan->appInfo.pEngineName = "No Engine";
	vulkan->appInfo.engineVersion = VK_MAKE_VERSION(1, 1, 101);
	vulkan->appInfo.apiVersion = VK_API_VERSION_1_1;

	vulkan->createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	vulkan->createInfo.pNext = NULL;
	vulkan->createInfo.flags = 0;
	vulkan->createInfo.pApplicationInfo = &vulkan->appInfo;

	enabled_extensions_setting(vulkan);

	vulkan->createInfo.enabledExtensionCount = vulkan->enabled_extension_count;
	vulkan->createInfo.ppEnabledExtensionNames = (const char *const *)vulkan->extension_name;
	vulkan->createInfo.enabledLayerCount = 0;

	if (vkCreateInstance(&(vulkan->createInfo), NULL, &(vulkan->instance)) != VK_SUCCESS)
	{
		printf("initializing instance failed.\n");
		return (0);
	}

	/*TODO initialize device*/
	physical_device_select(vulkan);
	create_logical_devices(vulkan);
	create_surface(vis, vulkan);
	surface_support_check(vulkan);
	swapchain_query(vis, vulkan);
	swapchain_create(vis, vulkan);
	return (1);

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

int		main()
{
	t_visualizer	vis;
	t_vulkan		vulkan;

	ft_bzero(&vulkan.instance, sizeof(vulkan.instance));
	ft_bzero(&vulkan.appInfo, sizeof(vulkan.appInfo));
	ft_bzero(&vulkan.createInfo, sizeof(vulkan.createInfo));
	if (!init_glfw(&vis))
	{
		printf("initializing GLFW failed.\n");
		return (0);
	}
	else if (!init_vulkan(&vis, &vulkan))
	{
		printf("initializing Vulkan failed.\n");
		return (0);
	}
	else
	{
		while (!glfwWindowShouldClose(vis.window))
			glfwPollEvents();
	}
	free_resource(&vis, &vulkan);

//   vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, NULL);
	return 0;
}
