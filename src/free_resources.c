/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 15:09:17 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/14 22:42:31 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	free_resource(t_visualizer *vis, t_vulkan *vulkan)
{
	/* Order of free_resources important */
	vkDestroyPipeline(vulkan->logical_device, vulkan->graphics_pipeline, NULL);
	vkDestroyRenderPass(vulkan->logical_device, vulkan->render_pass, NULL);
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