/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 19:53:42 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/26 23:45:21 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	draw_frame(t_vulkan *vulkan)
{
	uint32_t	image_index;

	vkAcquireNextImageKHR(vulkan->logical_device, vulkan->swapchain,
							UINT64_MAX, vulkan->acquire_semaphore, NULL, &image_index);

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = &vulkan->acquire_semaphore;
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &vulkan->command_buffers[image_index];
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = &vulkan->release_semaphore;

	if (vkQueueSubmit(vulkan->graphics_queue, 1, &submitInfo, NULL) != VK_SUCCESS)
		printf("ffuuk\n");

	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = &vulkan->release_semaphore;
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = &vulkan->swapchain;
	presentInfo.pImageIndices = &image_index;
	presentInfo.pResults = NULL;
	vkQueuePresentKHR(vulkan->present_queue, &presentInfo);
}
