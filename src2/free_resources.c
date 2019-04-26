/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 15:09:17 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/26 20:07:26 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	free_resource(t_visualizer *vis, t_vulkan *vulkan)
{
	uint32_t i;

	/* Order of free_resources important */
	vkDestroySemaphore(vulkan->logical_device, vulkan->acquire_semaphore, NULL);
	vkDestroySemaphore(vulkan->logical_device, vulkan->release_semaphore, NULL);
	i = 0;
	while (i < vulkan->swapchain_image_count)
	{
		vkDestroyFramebuffer(vulkan->logical_device, vulkan->frame_buffers[i], NULL);
		i++;
	}
	i = 0;
	while (i < vulkan->swapchain_image_count)
	{
		vkDestroyImageView(vulkan->logical_device, vulkan->image_views[i], NULL);
		i++;
	}
	vkDestroyCommandPool(vulkan->logical_device, vulkan->command_pool, NULL);
	vkDestroyPipeline(vulkan->logical_device, vulkan->graphics_pipeline, NULL);
	vkDestroyRenderPass(vulkan->logical_device, vulkan->renderpass, NULL);
	vkDestroyPipelineLayout(vulkan->logical_device, vulkan->pipeline_layout, NULL);
	vkDestroySwapchainKHR(vulkan->logical_device, vulkan->swapchain, NULL);
	vkDestroySurfaceKHR(vulkan->instance, vulkan->surf, NULL);
	vkDestroyDevice(vulkan->logical_device, NULL);
	vkDestroyInstance(vulkan->instance, NULL);
	free(vulkan->gpu);
	free(vulkan->queue_props);
	glfwDestroyWindow(vis->window);
	glfwTerminate();
}
