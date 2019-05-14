/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 15:09:17 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/14 01:41:22 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	clear_swapchain_objects(t_vulkan *vulkan)
{
	uint32_t	i;

	i = 0;
	while (i < vulkan->swapchain_image_count)
	{
		vkDestroyFramebuffer(vulkan->logical_device, vulkan->frame_buffers[i], NULL);
		i++;
	}
	vkFreeCommandBuffers(vulkan->logical_device, vulkan->command_pool,
		vulkan->swapchain_image_count, vulkan->command_buffers);
	vkDestroyPipeline(vulkan->logical_device, vulkan->graphics_pipeline, NULL); //order
	vkDestroyPipelineLayout(vulkan->logical_device, vulkan->pipeline_layout, NULL); //order
	vkDestroyRenderPass(vulkan->logical_device, vulkan->renderpass, NULL);
	i = 0;
	while (i < vulkan->swapchain_image_count)
	{
		vkDestroyImageView(vulkan->logical_device, vulkan->image_views[i], NULL);
		i++;
	}
	vkDestroySwapchainKHR(vulkan->logical_device, vulkan->swapchain, NULL);
	i = 0;
	while (i < vulkan->swapchain_image_count)
	{
		vkDestroyBuffer(vulkan->logical_device, vulkan->uniform_buffers[i], NULL);
		vkFreeMemory(vulkan->logical_device, vulkan->uniform_buffers_memory[i], NULL);
		i++;
	}
	vkDestroyDescriptorPool(vulkan->logical_device, vulkan->descriptor_pool, NULL);
}

void	free_resource(t_vulkan *vulkan)
{
	uint32_t i;

	/* Order of free_resources important */
	clear_swapchain_objects(vulkan);
	i = 0;
	while (i < MAX_FRAMES_IN_FLIGHT)
	{
		vkDestroySemaphore(vulkan->logical_device, vulkan->acquire_semaphore[i], NULL);
		vkDestroySemaphore(vulkan->logical_device, vulkan->release_semaphore[i], NULL);
		vkDestroyFence(vulkan->logical_device, vulkan->fence[i], NULL);
		i++;
	}
	vkDestroyDescriptorSetLayout(vulkan->logical_device, vulkan->descriptor_set_layout, NULL);
	vkDestroyCommandPool(vulkan->logical_device, vulkan->command_pool_transfer, NULL);
	vkDestroyCommandPool(vulkan->logical_device, vulkan->command_pool, NULL);
	vkDestroyBuffer(vulkan->logical_device, vulkan->index_buffer, NULL);
	vkFreeMemory(vulkan->logical_device, vulkan->index_buffer_memory, NULL);
	vkDestroyBuffer(vulkan->logical_device, vulkan->vertex_buffer, NULL);
	vkFreeMemory(vulkan->logical_device, vulkan->vertex_buffer_memory, NULL);
	vkDestroySurfaceKHR(vulkan->instance, vulkan->surf, NULL);
	vkDestroyDevice(vulkan->logical_device, NULL);
	vkDestroyInstance(vulkan->instance, NULL);
	free(vulkan->gpu);
	free(vulkan->queue_props);
	glfwDestroyWindow(vulkan->window);
	glfwTerminate();
}
