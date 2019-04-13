/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 17:36:20 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/13 14:11:16 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"


void	free_resource(t_visualizer *vis, t_vulkan *vulkan)
{
	/* Order of free_resources important */
	vkDestroySurfaceKHR(vulkan->instance, vulkan->surf, NULL);
	vkDestroyDevice(vulkan->device, NULL);
	vkDestroyInstance(vulkan->instance, NULL);
	free(vulkan->gpu);
	free(vulkan->queue_props);
	glfwDestroyWindow(vis->window);
	glfwTerminate();
}

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

void	surface_support_check(t_vulkan *vulkan)
{
	uint32_t	index;
	VkBool32	surface_support;

	surface_support = VK_FALSE;
	index = 0;
	while (index < vulkan->queue_count)
	{
		vkGetPhysicalDeviceSurfaceSupportKHR(vulkan->gpu[0], index, vulkan->surf, &surface_support);
		if (surface_support != VK_FALSE)
		{
			printf("good surface is supported in the queue of the device\n");
			vulkan->present_queue_node_index = index;
			break ;
		}
		index++;
	}
	printf("index of present queue fimaly : %u\n", index);

	/* retrieve handle of the the queue */
	vkGetDeviceQueue(vulkan->device, vulkan->graphics_queue_node_index, 0, &vulkan->graphics_queue);
	vkGetDeviceQueue(vulkan->device, vulkan->present_queue_node_index, 0, &vulkan->present_queue);
}

void	create_surface(t_visualizer *vis, t_vulkan *vulkan)
{
	VkBool32	surfaceSupport;
	if (glfwCreateWindowSurface(vulkan->instance, vis->window, NULL, &vulkan->surf) != VK_SUCCESS)
		printf("failed to crate window surface!\n");
}

void	create_logical_device(t_vulkan *vulkan)
{
	float						queue_priority;
	VkPhysicalDeviceFeatures	features;
	VkDeviceQueueCreateInfo		queue = {};
	VkDeviceCreateInfo			device;

	queue_priority = 1.0f;
	queue.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queue.pNext = NULL;
	queue.queueFamilyIndex = vulkan->graphics_queue_node_index;
	queue.queueCount = 1;
	queue.pQueuePriorities = &queue_priority;


	ft_memset(&features, VK_FALSE, sizeof(features));

	device.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	device.pNext = NULL;
	device.queueCreateInfoCount = 1;
	device.pQueueCreateInfos = &queue;
	device.pEnabledFeatures = &features;
	device.enabledExtensionCount = 0;

	if (vkCreateDevice(vulkan->gpu[0], &device, NULL, &vulkan->device) != VK_SUCCESS)
		printf("failed to create logical device!\n");
	printf("createDevice Success\n");
}

void	check_devices(t_vulkan *vulkan)
{
	uint32_t	index;
	int			score;

	score = 0;
	index = 0;
	while(index < vulkan->gpu_count)
	{
		vkGetPhysicalDeviceProperties(vulkan->gpu[index], &vulkan->dv_props);
		vkGetPhysicalDeviceFeatures(vulkan->gpu[index], &vulkan->dv_feats);
		printf("%s\n", vulkan->dv_props.deviceName);
		index++;
	}
	if (vulkan->dv_props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		printf("good it's a GPU!!\n");
	if (!vulkan->dv_feats.tessellationShader)
		printf("doesn't support tessellation shader... bad..\n");
	score += vulkan->dv_props.limits.maxImageDimension2D;
	printf("score: %d\n", score);
	if (!vulkan->dv_feats.geometryShader)
		printf("doesn't support geometry shader... bad..\n");
}

void	get_queue_node_index(t_vulkan *vulkan)
{
	VkBool32	present_support;
	uint32_t	index;

	vulkan->queue_count = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(vulkan->gpu[0], &vulkan->queue_count, NULL);
	vulkan->queue_props = (VkQueueFamilyProperties*)malloc(vulkan->queue_count * sizeof(VkQueueFamilyProperties));
	vkGetPhysicalDeviceQueueFamilyProperties(vulkan->gpu[0], &vulkan->queue_count, vulkan->queue_props);

	present_support = 0;
	index = 0;
	while (index < vulkan->queue_count)
	{
		if (vulkan->queue_props[index].queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			vulkan->graphics_queue_node_index = index;
			break ;
		}
		index++;
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

	vis->glfwExtensionCount = 0; /*TODO loading glfw extensions needs to change */
	vis->glfwExtensions = glfwGetRequiredInstanceExtensions(&vis->glfwExtensionCount);
	vulkan->createInfo.enabledExtensionCount = vis->glfwExtensionCount;
	vulkan->createInfo.ppEnabledExtensionNames = vis->glfwExtensions;
	vulkan->createInfo.enabledLayerCount = 0;

	if (vkCreateInstance(&(vulkan->createInfo), NULL, &(vulkan->instance)) != VK_SUCCESS)
	{
		printf("initializing instance failed.\n");
		return (0);
	}

	/*TODO physical_devices */
	vulkan->gpu_count = 0;
	vkEnumeratePhysicalDevices(vulkan->instance, &vulkan->gpu_count, NULL);
	printf("FOUND %u\n", vulkan->gpu_count);

	vulkan->gpu = (VkPhysicalDevice*)malloc(sizeof(VkPhysicalDevice) * vulkan->gpu_count); /*TODO replace vector */
	vkEnumeratePhysicalDevices(vulkan->instance, &vulkan->gpu_count, vulkan->gpu);

	/*TODO recieve properties and features of the vulkan->gpu */
	check_devices(vulkan);

	/*TODO physical_devices queue_family */
	get_queue_node_index(vulkan);

	/*TODO initialize device*/
	create_logical_device(vulkan);
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
/*	 $(CC) -Wl,-search_paths_first -Wl,-headerpad_max_install_names $(OBJS) -o $@ \
          -Wl,-rpath, $(VULKAN_SDK_PATH)/lib ./glfw/src/libglfw3.a \
         ${VULKAN_SDK_PATH}/lib/libvulkan.1.dylib -framework Cocoa -framework IOKit \
		  -framework CoreFoundation -framework CoreVideo
*/
