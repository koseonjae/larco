#include <Graphics/Metal/MetalCommandBuffer.h>
#include <Graphics/Metal/MetalCommandEncoder.h>
#include <Graphics/Metal/MetalDevice.h>
#include <Graphics/Metal/MetalFence.h>
#include <Graphics/Metal/MetalTexture.h>
#include <Graphics/Metal/MetalPipeline.h>
#include <Graphics/Metal/MetalRenderPass.h>

#include <Metal/Metal.hpp>

using namespace goala;

MetalCommandBuffer::MetalCommandBuffer(MetalDevice* device, MTL::CommandBuffer* cmdBuf)
  : m_device(device)
  , m_cmdBuf(makeMetalRef(cmdBuf)) {}

void MetalCommandBuffer::encode(RenderPass* renderPass, Pipeline* pipeline) {
  auto encoder = std::make_shared<MetalCommandEncoder>(this, renderPass);
  encoder->encode(pipeline);
  encoder->updateDependency(m_signalFences, m_waitFences);
}

void MetalCommandBuffer::present(Texture* texture) {
  assert(false && "Only offscreen rendering is supported");
  // auto metalTexture = dynamic_cast<MetalTexture*>(texture);
  // m_cmdBuf->presentDrawable(metalTexture->getHandle());
}

void MetalCommandBuffer::commit() {
  m_cmdBuf->commit();
}

void MetalCommandBuffer::addDependency(CommandBuffer* cmdBuf) {
  auto fence = std::make_shared<MetalFence>(m_device->getMTLDevice()->newFence());
  _addWaitFence(fence);
  dynamic_cast<MetalCommandBuffer*>(cmdBuf)->_addSignalFence(fence);
}

void MetalCommandBuffer::_addSignalFence(std::shared_ptr<Fence> fence) {
  m_signalFences.push_back(std::move(fence));
}

void MetalCommandBuffer::_addWaitFence(std::shared_ptr<Fence> fence) {
  m_waitFences.push_back(std::move(fence));
}

MTL::CommandBuffer* MetalCommandBuffer::getCommandBuffer() {
  return m_cmdBuf.get();
}

const MTL::CommandBuffer* MetalCommandBuffer::getCommandBuffer() const {
  return m_cmdBuf.get();
}
