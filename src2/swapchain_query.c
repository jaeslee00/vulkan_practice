/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swapchain_query.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:30:22 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/29 21:11:24 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	check_available_present_mode(t_vulkan *vulkan)
{
	uint32_t	present_mode_count;
	uint32_t	i;

	vkGetPhysicalDeviceSurfacePresentModesKHR(vulkan->gpu[0], vulkan->surf, &present_mode_count, NULL);
	ft_assert(present_mode_count != 0, "present mode is missing", "swapchain_query.c", 36);
	vulkan->present_modes = (VkPresentModeKHR*)malloc(present_mode_count * sizeof(VkPresentModeKHR)); /*TODO MALLOC */
	if (vkGetPhysicalDeviceSurfacePresentModesKHR(vulkan->gpu[0], vulkan->surf, &present_mode_count, vulkan->present_modes) != VK_SUCCESS)
		printf("get physicaldevice surface presenmode failed\n");
	i = 0;
	while (i < present_mode_count)
	{
		if (vulkan->present_modes[i] == VK_PRESENT_MODE_IMMEDIATE_KHR ||
				vulkan->present_modes[i] == VK_PRESENT_MODE_MAILBOX_KHR ||
					vulkan->present_modes[i] == VK_PRESENT_MODE_FIFO_KHR)
		{
			vulkan->present_mode = vulkan->present_modes[i];
			break ;
		}
		i++;
	}
	ft_assert(i < present_mode_count, "no present mode available", "swapchain_query.c", 26);
	free(vulkan->present_modes);
}

static void	check_available_format_colorspace(t_vulkan *vulkan)
{
	uint32_t					format_count;

	vkGetPhysicalDeviceSurfaceFormatsKHR(vulkan->gpu[0], vulkan->surf, &format_count, NULL);
	ft_assert(format_count != 0, "surface format missing", "swapchain_query.c", 28);
	vulkan->surf_formats = (VkSurfaceFormatKHR*)malloc(format_count * sizeof(VkSurfaceFormatKHR)); /*TODO MALLOC */
	vkGetPhysicalDeviceSurfaceFormatsKHR(vulkan->gpu[0], vulkan->surf, &format_count, vulkan->surf_formats);
	/*TODO loops to check over all the available formats and colorspaces */
	vulkan->format = vulkan->surf_formats[0].format;
	vulkan->color_space = vulkan->surf_formats[0].colorSpace;

	free(vulkan->surf_formats);
}

static uint32_t	max_uint32(uint32_t a, uint32_t b)
{
	return (a > b ? a : b);
}

static uint32_t	min_uint32(uint32_t a, uint32_t b)
{
	return (a > b ? b : a);
}

static VkExtent2D	resize_swapchain_extent(GLFWwindow *window, VkSurfaceCapabilitiesKHR capabilities)
{
	VkExtent2D	curr_extent;
	int			width;
	int			height;

	if (capabilities.currentExtent.width != UINT32_MAX)
		return capabilities.currentExtent;
	else
	{
		glfwGetFramebufferSize(window, &width, &height);
		curr_extent.width = (uint32_t)width;
		curr_extent.height = (uint32_t)height;
		curr_extent.width = max_uint32(capabilities.minImageExtent.width,
			min_uint32(capabilities.maxImageExtent.width, curr_extent.width));
		curr_extent.height = max_uint32(capabilities.minImageExtent.height,
			min_uint32(capabilities.maxImageExtent.height, curr_extent.height));
	}
	printf("width : %u\n", curr_extent.width);
	printf("height : %u\n", curr_extent.height);
	return (curr_extent);
}

void	swapchain_query(t_vulkan *vulkan)
{
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vulkan->gpu[0], vulkan->surf, &vulkan->surf_capabilities);
	check_available_format_colorspace(vulkan);
	check_available_present_mode(vulkan);
	vulkan->swapchain_extent = resize_swapchain_extent(vulkan->window, vulkan->surf_capabilities);
	printf("width : %u\n", vulkan->swapchain_extent.width);
	printf("height : %u\n", vulkan->swapchain_extent.height);
}
