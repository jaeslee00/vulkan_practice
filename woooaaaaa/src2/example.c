/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 17:36:20 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/26 07:50:44 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

const char* g_debug_layers[] =
{
	"VK_LAYER_LUNARG_standard_validation"
};

void	create_renderpass(t_vulkan *vulkan)
{
	VkAttachmentDescription	attachments[1];
	attachments[0].flags =  0;
	attachments[0].format = vulkan->format;
	attachments[0].samples = VK_SAMPLE_COUNT_1_BIT;
	attachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	attachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	attachments[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	attachments[0].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference	color_attachments_ref = {};
	color_attachments_ref.attachment = 0; /* index of attachments */
	color_attachments_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription	subpass = {};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &color_attachments_ref;

	VkRenderPassCreateInfo	create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	create_info.attachmentCount = 1;
	create_info.pAttachments = attachments;
	create_info.subpassCount = 1;
	create_info.pSubpasses = &subpass;

	if (vkCreateRenderPass(vulkan->logical_device, &create_info, NULL, &vulkan->renderpass) != VK_SUCCESS)
		printf("failed to create renderpass\n");
}

void	create_imageviews(t_vulkan *vulkan)
{
	uint32_t				i;

	vkGetSwapchainImagesKHR(vulkan->logical_device, vulkan->swapchain, &vulkan->swapchain_image_count, NULL);
	printf("imagecount :: %u\n", vulkan->swapchain_image_count);
	vulkan->swapchain_images = (VkImage*)malloc(vulkan->swapchain_image_count * sizeof(VkImage));
	vkGetSwapchainImagesKHR(vulkan->logical_device, vulkan->swapchain, &vulkan->swapchain_image_count, vulkan->swapchain_images);
	vulkan->image_views = (VkImageView*)malloc(vulkan->swapchain_image_count * sizeof(VkImageView));

	i = 0;
	while (i < vulkan->swapchain_image_count)
	{
		VkImageViewCreateInfo	imageview_info = {};
		imageview_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		imageview_info.image = vulkan->swapchain_images[i];
		imageview_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
		imageview_info.format = vulkan->format;
		imageview_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		imageview_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		imageview_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		imageview_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		imageview_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		imageview_info.subresourceRange.baseMipLevel = 0;
		imageview_info.subresourceRange.levelCount = 1;
		imageview_info.subresourceRange.baseArrayLayer = 0;
		imageview_info.subresourceRange.layerCount = 1;
		if (vkCreateImageView(vulkan->logical_device, &imageview_info, NULL, &vulkan->image_views[i]) != VK_SUCCESS)
			printf("creating swapchain_imageview failed.\n");
		else
			printf("swapchain_imageview %u successfully created.\n", i);
		i++;
	}
}

void	create_framebuffers(t_vulkan *vulkan)
{
	uint32_t	index;

	index = 0;
	vulkan->frame_buffers = (VkFramebuffer*)malloc(vulkan->swapchain_image_count *sizeof(VkFramebuffer));

	while (index < vulkan->swapchain_image_count)
	{
		VkFramebufferCreateInfo	create_info = {};
		create_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		create_info.renderPass = vulkan->renderpass;
		create_info.attachmentCount = 1;
		create_info.pAttachments = &vulkan->image_views[index]; // 씨바ㅏ다아아아아알ㄹ 주소르 ㄹ제대ㅗㄹ 안정해줘서 망함
		create_info.width = vulkan->swapchain_extent.width;
		create_info.height = vulkan->swapchain_extent.height;
		create_info.layers = 1;
		if (vkCreateFramebuffer(vulkan->logical_device, &create_info, NULL, &vulkan->frame_buffers[index]) != VK_SUCCESS)
			printf("failed to create frame buffers");
		index++;
	}
}

void	create_semaphores(t_vulkan *vulkan)
{
	VkSemaphore	acquire_semaphore;
	VkSemaphore	release_semaphore;
	VkSemaphoreCreateInfo as_create_info = {};
	as_create_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	vkCreateSemaphore(vulkan->logical_device, &as_create_info, 0, &vulkan->image_available_semaphore);
	VkSemaphoreCreateInfo rs_create_info = {};
	rs_create_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	vkCreateSemaphore(vulkan->logical_device, &rs_create_info, 0, &vulkan->render_done_semaphore);
}

void	enabled_extensions_setting(t_vulkan *vulkan)
{
	uint32_t	required_extension_count;
	const char	**required_extension;
	uint32_t	i;

	required_extension_count = 0; /*TODO loading extensions. needs to change */
	required_extension = glfwGetRequiredInstanceExtensions(&required_extension_count);
	i = 0;

	vulkan->enabled_extension_count = 0;
	while (i < required_extension_count)
	{
		vulkan->extension_name[vulkan->enabled_extension_count] = required_extension[i];
		vulkan->enabled_extension_count++;
		i++;
	}
}

int		init_vulkan(t_visualizer *vis, t_vulkan *vulkan)
{
	VkApplicationInfo		app_info = {};
	VkInstanceCreateInfo	instance_info = {};

	app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	app_info.pApplicationName = "TRIANGLE!";
	app_info.applicationVersion = VK_MAKE_VERSION(1, 1, 101);
	app_info.pEngineName = "No Engine";
	app_info.engineVersion = VK_MAKE_VERSION(1, 1, 101);
	app_info.apiVersion = VK_API_VERSION_1_1;

	instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instance_info.pNext = NULL;
	instance_info.flags = 0;
	instance_info.pApplicationInfo = &app_info;

	enabled_extensions_setting(vulkan);

	instance_info.enabledExtensionCount = vulkan->enabled_extension_count;
	instance_info.ppEnabledExtensionNames = (const char *const *)vulkan->extension_name;
	instance_info.enabledLayerCount = sizeof(g_debug_layers) / sizeof(g_debug_layers[0]);
	instance_info.ppEnabledLayerNames = g_debug_layers;

	if (vkCreateInstance(&instance_info, NULL, &(vulkan->instance)) != VK_SUCCESS)
	{
		printf("initializing instance failed.\n");
		return (0);
	}
	return (1);

}

int		init_glfw(t_visualizer *vis)
{
	if (!glfwInit())
	{
		printf("GLFW initialize failed.\n");
		return (0);
	}
	else
	{
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		if (!(vis->window = glfwCreateWindow(WIDTH, HEIGHT, "VULKAN!", NULL, NULL)))
		{
			printf("creating GLFW window failed.\n");
			return (0);
		}
		glfwSetWindowUserPointer(vis->window, vis);
	}
	return (1);
}

int		main()
{
	t_visualizer	vis;
	t_vulkan		vulkan;
	if (!init_glfw(&vis))
	{
		printf("initializing GLFW failed.\n");
		return (0);
	}
	else if (!init_vulkan(&vis, &vulkan))
	{
		printf("initializing Vulkan failed.\n");
		return (0);
	}
	physical_device_select(&vulkan);
	create_logical_devices(&vulkan);
	create_surface(&vis, &vulkan);
	swapchain_query(&vis, &vulkan);
	create_semaphores(&vulkan);
	create_imageviews(&vulkan);
	create_renderpass(&vulkan);
	create_framebuffers(&vulkan);
	create_graphics_pipeline(&vulkan);

	vkGetDeviceQueue(vulkan.logical_device, vulkan.graphics_queue_family_index, 0, &vulkan.graphics_queue);
	vkGetDeviceQueue(vulkan.logical_device, vulkan.present_queue_family_index, 0, &vulkan.present_queue);

	create_command_pools(&vulkan);
	VkCommandBufferAllocateInfo	allocate_info = {};
	allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocate_info.commandPool = vulkan.command_pool;
	allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocate_info.commandBufferCount = 1;
	vkAllocateCommandBuffers(vulkan.logical_device, &allocate_info, &vulkan.command_buffers);

	while (!glfwWindowShouldClose(vis.window))
	{
		uint32_t		image_index = 0;
		glfwPollEvents();

		vkAcquireNextImageKHR(vulkan.logical_device, vulkan.swapchain,
								UINT64_MAX, vulkan.image_available_semaphore, NULL, &image_index);
		vkResetCommandPool(vulkan.logical_device, vulkan.command_pool, 0);

		VkCommandBufferBeginInfo	begin_info = {};
		begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		vkBeginCommandBuffer(vulkan.command_buffers, &begin_info);

		VkClearColorValue		color = {48.f / 255.f, 10.f / 255.f,  36.f / 255.f, 1};
		VkClearValue			clear_color = {color};

		VkRenderPassBeginInfo	begin_pass = {};
		begin_pass.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		begin_pass.renderPass = vulkan.renderpass;
		begin_pass.framebuffer = vulkan.frame_buffers[image_index];
		begin_pass.renderArea.extent.width = vulkan.swapchain_extent.width;
		begin_pass.renderArea.extent.height = vulkan.swapchain_extent.height;
		begin_pass.clearValueCount = 1;
		begin_pass.pClearValues = &clear_color;
			vkCmdBeginRenderPass(vulkan.command_buffers, &begin_pass, VK_SUBPASS_CONTENTS_INLINE);

		//DRAW
				vkCmdBindPipeline(vulkan.command_buffers, VK_PIPELINE_BIND_POINT_GRAPHICS, vulkan.graphics_pipeline);
			vkCmdDraw(vulkan.command_buffers, 3, 1, 0, 0);

			vkCmdEndRenderPass(vulkan.command_buffers);


		vkEndCommandBuffer(vulkan.command_buffers);

		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = &vulkan.image_available_semaphore;
		submitInfo.pWaitDstStageMask = waitStages;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &vulkan.command_buffers;
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = &vulkan.render_done_semaphore;
		if (vkQueueSubmit(vulkan.graphics_queue, 1, &submitInfo, NULL) != VK_SUCCESS)
			printf("ffuuk\n");

		VkPresentInfoKHR presentInfo = {};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = &vulkan.render_done_semaphore;
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = &vulkan.swapchain;
		presentInfo.pImageIndices = &image_index;
		presentInfo.pResults = NULL;
		vkQueuePresentKHR(vulkan.present_queue, &presentInfo);
		vkDeviceWaitIdle(vulkan.logical_device);
//		draw_frame(&vulkan);
	}
//	free_resource(&vis, &vulkan);
	return 0;
}
