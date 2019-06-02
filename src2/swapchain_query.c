/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swapchain_query.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:30:22 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/02 17:51:25 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	check_available_present_mode(t_vulkan *vk)
{
	uint32_t	present_mode_count;
	uint32_t	i;

	vkGetPhysicalDeviceSurfacePresentModesKHR(vk->gpu[0], vk->surf, &present_mode_count, NULL);
	ft_assert(present_mode_count != 0, "present mode is missing", "swapchain_query.c", 36);
	vk->present_modes = (VkPresentModeKHR*)malloc(present_mode_count * sizeof(VkPresentModeKHR)); /*TODO MALLOC */
	if (vkGetPhysicalDeviceSurfacePresentModesKHR(vk->gpu[0], vk->surf, &present_mode_count, vk->present_modes) != VK_SUCCESS)
		printf("get physicaldevice surface presenmode failed\n");
	i = 0;
	while (i < present_mode_count)
	{
		if (vk->present_modes[i] == VK_PRESENT_MODE_IMMEDIATE_KHR ||
				vk->present_modes[i] == VK_PRESENT_MODE_MAILBOX_KHR ||
					vk->present_modes[i] == VK_PRESENT_MODE_FIFO_KHR)
		{
			vk->present_mode = vk->present_modes[i];
			break ;
		}
		i++;
	}
	ft_assert(i < present_mode_count, "no present mode available", "swapchain_query.c", 26);
	free(vk->present_modes);
}

static void	check_available_format_colorspace(t_vulkan *vk)
{
	uint32_t					format_count;

	vkGetPhysicalDeviceSurfaceFormatsKHR(vk->gpu[0], vk->surf, &format_count, NULL);
	ft_assert(format_count != 0, "surface format missing", "swapchain_query.c", 28);
	vk->surf_formats = (VkSurfaceFormatKHR*)malloc(format_count * sizeof(VkSurfaceFormatKHR)); /*TODO MALLOC */
	vkGetPhysicalDeviceSurfaceFormatsKHR(vk->gpu[0], vk->surf, &format_count, vk->surf_formats);
	/*TODO loops to check over all the available formats and colorspaces */
	vk->swapchain_image_format = vk->surf_formats[0].format;
	vk->color_space = vk->surf_formats[0].colorSpace;

	free(vk->surf_formats);
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
	{
		printf("width %u , height : %u\n", capabilities.currentExtent.width, capabilities.currentExtent.height);
		return capabilities.currentExtent;
	}
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
	return (curr_extent);
}

void	swapchain_query(t_vulkan *vk)
{
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vk->gpu[0], vk->surf, &vk->surf_capabilities);
	check_available_format_colorspace(vk);
	check_available_present_mode(vk);
	vk->swapchain_extent = resize_swapchain_extent(vk->window, vk->surf_capabilities);
}
