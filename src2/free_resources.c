/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 15:09:17 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/02 19:47:21 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	clear_swapchain_objects(t_vulkan *vk)
{
	uint32_t	i;

	i = 0;
	while (i < vk->swapchain_image_count)
	{
		vkDestroyFramebuffer(vk->logical_device, vk->frame_buffers[i], NULL);
		i++;
	}
	vkFreeCommandBuffers(vk->logical_device, vk->command_pool,
		vk->swapchain_image_count, vk->command_buffers);
	vkDestroyPipeline(vk->logical_device, vk->graphics_pipeline, NULL); //order
	vkDestroyPipelineLayout(vk->logical_device, vk->pipeline_layout, NULL); //order
	vkDestroyRenderPass(vk->logical_device, vk->renderpass, NULL);
	i = 0;
	while (i < vk->swapchain_image_count)
	{
		vkDestroyImageView(vk->logical_device, vk->swapchain_imageviews[i], NULL);
		i++;
	}
	vkDestroySwapchainKHR(vk->logical_device, vk->swapchain, NULL);
	i = 0;
	while (i < vk->swapchain_image_count)
	{
		vkDestroyBuffer(vk->logical_device, vk->uniform_buffers[i], NULL);
		vkFreeMemory(vk->logical_device, vk->uniform_buffers_memory[i], NULL);
		i++;
	}
	vkDestroyDescriptorPool(vk->logical_device, vk->descriptor_pool, NULL);
}

void	free_resource(t_vulkan *vk)
{
	uint32_t i;

	/* Order of free_resources important */
	clear_swapchain_objects(vk);
	i = 0;
	while (i < MAX_FRAMES_IN_FLIGHT)
	{
		vkDestroySemaphore(vk->logical_device, vk->acquire_semaphore[i], NULL);
		vkDestroySemaphore(vk->logical_device, vk->release_semaphore[i], NULL);
		vkDestroyFence(vk->logical_device, vk->fence[i], NULL);
		i++;
	}
	/* destroy texture resources */
	vkDestroySampler(vk->logical_device, vk->texture_sampler, NULL);
	vkDestroyImageView(vk->logical_device, vk->texture_image_view, NULL);
	vkDestroyImage(vk->logical_device, vk->texture_image, NULL);
	vkFreeMemory(vk->logical_device, vk->texture_image_memory, NULL);

	vkDestroyDescriptorSetLayout(vk->logical_device, vk->descriptor_set_layout, NULL);
	vkDestroyCommandPool(vk->logical_device, vk->command_pool_transfer, NULL);
	vkDestroyCommandPool(vk->logical_device, vk->command_pool, NULL);

	vkDestroyBuffer(vk->logical_device, vk->index_buffer, NULL);
	vkFreeMemory(vk->logical_device, vk->index_buffer_memory, NULL);

	vkDestroyBuffer(vk->logical_device, vk->vertex_buffer, NULL);
	vkFreeMemory(vk->logical_device, vk->vertex_buffer_memory, NULL);

	vkDestroySurfaceKHR(vk->instance, vk->surf, NULL);
	vkDestroyDevice(vk->logical_device, NULL);
	vkDestroyInstance(vk->instance, NULL);
	free(vk->gpu);
	free(vk->queue_props);
	glfwDestroyWindow(vk->window);
	glfwTerminate();
}
