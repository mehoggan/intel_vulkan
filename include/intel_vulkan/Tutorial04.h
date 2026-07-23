#if !defined(TUTORIAL_04_HEADER)
#define TUTORIAL_04_HEADER

#include "Tools.h"
#include "VulkanCommon.h"

namespace ApiWithoutSecrets {

// ************************************************************ //
// VertexData                                                   //
//                                                              //
// Struct describing data type and format of vertex attributes  //
// ************************************************************ //
struct VertexData {
  float x, y, z, w;
  float r, g, b, a;
};

// ************************************************************ //
// RenderingResourcesData                                       //
//                                                              //
// Struct containing data used during rendering process         //
// ************************************************************ //
struct RenderingResourcesData {
  VkFramebuffer Framebuffer;
  VkCommandBuffer CommandBuffer;
  VkSemaphore ImageAvailableSemaphore;
  VkSemaphore FinishedRenderingSemaphore;
  VkFence Fence;

  RenderingResourcesData()
      : Framebuffer(VK_NULL_HANDLE),
        CommandBuffer(VK_NULL_HANDLE),
        ImageAvailableSemaphore(VK_NULL_HANDLE),
        FinishedRenderingSemaphore(VK_NULL_HANDLE),
        Fence(VK_NULL_HANDLE) {}
};

// ************************************************************ //
// VulkanTutorial04Parameters                                   //
//                                                              //
// Vulkan specific parameters                                   //
// ************************************************************ //
struct VulkanTutorial04Parameters {
  VkRenderPass RenderPass;
  VkPipeline GraphicsPipeline;
  BufferParameters VertexBuffer;
  VkCommandPool CommandPool;
  std::vector<RenderingResourcesData> RenderingResources;

  static const size_t ResourcesCount = 3;

  VulkanTutorial04Parameters()
      : RenderPass(VK_NULL_HANDLE),
        GraphicsPipeline(VK_NULL_HANDLE),
        VertexBuffer(),
        CommandPool(VK_NULL_HANDLE),
        RenderingResources(ResourcesCount) {}
};

// ************************************************************ //
// Tutorial04                                                   //
//                                                              //
// Class for presenting Vulkan usage topics                     //
// ************************************************************ //
class Tutorial04 : public VulkanCommon {
 public:
  Tutorial04();
  ~Tutorial04();

  bool CreateRenderPass();
  bool CreatePipeline();
  bool CreateVertexBuffer();
  bool CreateRenderingResources();

  bool Draw() override;

 private:
  VulkanTutorial04Parameters Vulkan;

  Tools::AutoDeleter<VkShaderModule, PFN_vkDestroyShaderModule>
  CreateShaderModule(const char *filename);
  Tools::AutoDeleter<VkPipelineLayout, PFN_vkDestroyPipelineLayout>
  CreatePipelineLayout();
  bool AllocateBufferMemory(VkBuffer buffer, VkDeviceMemory *memory);
  bool CreateCommandPool(uint32_t queue_family_index, VkCommandPool *pool);
  bool AllocateCommandBuffers(VkCommandPool pool, uint32_t count,
                              VkCommandBuffer *command_buffers);
  bool CreateCommandBuffers();
  bool CreateSemaphores();
  bool CreateFences();
  bool PrepareFrame(VkCommandBuffer command_buffer,
                    const ImageParameters &image_parameters,
                    VkFramebuffer &framebuffer);
  bool CreateFramebuffer(VkFramebuffer &framebuffer, VkImageView image_view);

  void ChildClear() override;
  bool ChildOnWindowSizeChanged() override;
};

}  // namespace ApiWithoutSecrets

#endif  // TUTORIAL_04_HEADER
