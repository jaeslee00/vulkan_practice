/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:24:56 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/10 18:53:27 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	enabled_extensions_setting(t_vulkan *vulkan)
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

void	init_vulkan(t_vulkan *vulkan)
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
	const char* debug_layers[] =
	{
		"VK_LAYER_LUNARG_standard_validation"
	};

	instance_info.enabledExtensionCount = vulkan->enabled_extension_count;
	instance_info.ppEnabledExtensionNames = (const char *const *)vulkan->extension_name;
	instance_info.enabledLayerCount = sizeof(debug_layers) / sizeof(debug_layers[0]);
	instance_info.ppEnabledLayerNames = debug_layers;

	ft_assert((vkCreateInstance(&instance_info, NULL, &(vulkan->instance)) == VK_SUCCESS),
			"create instance failed", "example.c", 125);
}

int		init_glfw(t_vulkan *vulkan, GLFWwindow **window)
{
	if (!glfwInit())
	{
		printf("GLFW initialize failed.\n");
		return (0);
	}
	else
	{
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		if (!(*window = glfwCreateWindow(WIDTH, HEIGHT, "VULKAN!", NULL, NULL)))
		{
			printf("creating GLFW window failed.\n");
			return (0);
		}
		glfwSetKeyCallback(*window, key_callback);
		glfwSetCursorPosCallback(*window, mouse_callback);
	}
	return (1);
}
