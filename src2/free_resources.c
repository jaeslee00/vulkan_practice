/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 15:09:17 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/27 13:58:11 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	free_resource(t_visualizer *vis, t_vulkan *vulkan)
{
	uint32_t i;

	/* Order of free_resources important */
	i = 0;
	while (i < MAX_FRAMES_IN_FLIGHT)
	{
		vkDestroySemaphore(vulkan->logical_device, vulkan->acquire_semaphore[i], NULL);
		vkDestroySemaphore(vulkan->logical_device, vulkan->release_semaphore[i], NULL);
		vkDestroyFence(vulkan->logical_device, vulkan->fence[i], NULL);
		i++;
	}
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
	vkDestroyCommandPool(vulkan->logical_device, vulkan->command_pool_transfer, NULL);
	vkDestroyCommandPool(vulkan->logical_device, vulkan->command_pool, NULL);
	vkDestroyPipeline(vulkan->logical_device, vulkan->graphics_pipeline, NULL);
	vkDestroyRenderPass(vulkan->logical_device, vulkan->renderpass, NULL);
	vkDestroyPipelineLayout(vulkan->logical_device, vulkan->pipeline_layout, NULL);
	vkDestroySwapchainKHR(vulkan->logical_device, vulkan->swapchain, NULL);
	vkDestroyBuffer(vulkan->logical_device, vulkan->index_buffer, NULL);
	vkFreeMemory(vulkan->logical_device, vulkan->index_buffer_memory, NULL);
	vkDestroyBuffer(vulkan->logical_device, vulkan->vertex_buffer, NULL);
	vkFreeMemory(vulkan->logical_device, vulkan->vertex_buffer_memory, NULL);
	vkDestroySurfaceKHR(vulkan->instance, vulkan->surf, NULL);
	vkDestroyDevice(vulkan->logical_device, NULL);
	vkDestroyInstance(vulkan->instance, NULL);
	free(vulkan->gpu);
	free(vulkan->queue_props);
	glfwDestroyWindow(vis->window);
	glfwTerminate();
}
