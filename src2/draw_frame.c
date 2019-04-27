/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 19:53:42 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/27 13:18:01 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

size_t		current_frame = 0;

void	draw_frame(t_vulkan *vulkan)
{
	uint32_t			image_index;
	vkWaitForFences(vulkan->logical_device, 1, &vulkan->fence[current_frame], VK_TRUE, UINT64_MAX);
	vkResetFences(vulkan->logical_device, 1, &vulkan->fence[current_frame]);

	vkAcquireNextImageKHR(vulkan->logical_device, vulkan->swapchain,
							UINT64_MAX, vulkan->acquire_semaphore[current_frame], NULL, &image_index);

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = &vulkan->acquire_semaphore[current_frame];
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &vulkan->command_buffers[image_index];
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = &vulkan->release_semaphore[current_frame];

	ft_assert((vkQueueSubmit(vulkan->graphics_queue, 1, &submitInfo, vulkan->fence[current_frame]) == VK_SUCCESS),
				"failed to submit commands to queue", "draw_frame.c", 37);
	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = &vulkan->release_semaphore[current_frame];
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = &vulkan->swapchain;
	presentInfo.pImageIndices = &image_index;
	presentInfo.pResults = NULL;
	vkQueuePresentKHR(vulkan->present_queue, &presentInfo);

	current_frame = (current_frame + 1) % MAX_FRAMES_IN_FLIGHT;
}
