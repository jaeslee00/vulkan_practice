/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 19:53:42 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/14 00:40:45 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

size_t		g_current_frame = 0;

void	update_ubo(t_vulkan *vulkan, uint32_t image_index)
{
	t_ubo	ubo = {};
	update_model(&ubo);
	update_view(&ubo);
	update_proj(&ubo);

	void* data;
	vkMapMemory(vulkan->logical_device, vulkan->uniform_buffers_memory[image_index], 0, sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
	vkUnmapMemory(vulkan->logical_device, vulkan->uniform_buffers_memory[image_index]);
}

void	draw_frame(t_vulkan *vulkan)
{
	uint32_t			image_index;
	VkResult			result;

	vkWaitForFences(vulkan->logical_device, 1, &vulkan->fence[g_current_frame], VK_TRUE, UINT64_MAX);

	result = vkAcquireNextImageKHR(vulkan->logical_device, vulkan->swapchain,
							UINT64_MAX, vulkan->acquire_semaphore[g_current_frame], NULL, &image_index);
	if (result == VK_ERROR_OUT_OF_DATE_KHR)
	{
		recreate_swapchain(vulkan);
		return ;
	}
	else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
		printf("failed to acquire swapchain image");

	update_ubo(vulkan, image_index);

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = &vulkan->acquire_semaphore[g_current_frame];
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &vulkan->command_buffers[image_index];
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = &vulkan->release_semaphore[g_current_frame];

	vkResetFences(vulkan->logical_device, 1, &vulkan->fence[g_current_frame]);

	ft_assert((vkQueueSubmit(vulkan->graphics_queue, 1, &submitInfo, vulkan->fence[g_current_frame]) == VK_SUCCESS),
				"failed to submit commands to queue", "draw_frame.c", 37);

	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = &vulkan->release_semaphore[g_current_frame];
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = &vulkan->swapchain;
	presentInfo.pImageIndices = &image_index;
	presentInfo.pResults = NULL;

	result = vkQueuePresentKHR(vulkan->present_queue, &presentInfo);

	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
		recreate_swapchain(vulkan);
	else if (result != VK_SUCCESS)
		printf("failed to present swapchain image to window");

	g_current_frame = (g_current_frame + 1) % MAX_FRAMES_IN_FLIGHT;
}
