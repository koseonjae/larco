#pragma once

#include <Graphics/Model/Device.h>
#include <Graphics/Utility/MetalRef.h>

#include <Metal/MTLDevice.hpp>

namespace goala {

class MetalDevice : public Device {
 public:
  explicit MetalDevice(MTL::Device* device);
  MTL::Device* getMTLDevice();
  const MTL::Device* getMTLDevice() const;

 private:
  MetalRef<MTL::Device> m_device;
};

} // namespace goala
