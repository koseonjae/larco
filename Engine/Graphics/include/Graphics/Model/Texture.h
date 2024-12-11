#pragma once

#include <Base/ImageData.h>
#include <Base/Utility/EnumBitMask.h>

namespace goala {
enum class TextureLoadType {
  EAGER, LAZY, UNDEFINED
};

enum class TextureFilter {
  LINEAR, NEAREST, UNDEFINED
};

enum class TextureWrap {
  CLAMP_TO_EDGE, UNDEFINED
};

struct TextureSampler {
  TextureFilter minFilter = TextureFilter::UNDEFINED;
  TextureFilter magFilter = TextureFilter::UNDEFINED;
  TextureFilter mipFilter = TextureFilter::UNDEFINED;
  TextureWrap wrapS = TextureWrap::UNDEFINED;
  TextureWrap wrapT = TextureWrap::UNDEFINED;
};

enum class TextureUsage {
  UNDEFINED     = 1 << 0,
  READ          = 1 << 1, // CPU에서 값을 초기화 할 필요가 있는 경우
  WRITE         = 1 << 2, // Compute Shader or 렌더패스에 사용되지 않는 graphics shader write
  RENDER_TARGET = 1 << 3, // 렌더패스에 사용되는 목적
};

ENABLE_BITMASK(TextureUsage);

enum class TextureStorage {
  UNDEFINED,
  SHARED,     // CPU, GPU 모두 접근 가능
  PRIVATE,    // GPU only
  MEMORYLESS, // CPU, GPU 모두 접근 불가. 렌더링 도중에만 유효한 메모리
  MANAGED,    // CPU와 GPU 간에 자동으로 데이터가 관리
};

enum class TexturePipeline {
  UNDEFINED, VERTEX, FRAGMENT, COMPUTE
};

ENABLE_BITMASK(TexturePipeline);

struct TextureDescription {
  ImageData imageData{};
  TextureSampler sampler{};
  TextureUsage usage = TextureUsage::UNDEFINED;
  TextureStorage storage = TextureStorage::UNDEFINED;
  TextureLoadType loadType = TextureLoadType::UNDEFINED;
  TexturePipeline pipeline = TexturePipeline::UNDEFINED;
};

class Texture {
public:
  Texture(TextureDescription desc) : m_desc(std::move(desc)) {}
  virtual ~Texture() = default;

  virtual void bind() = 0;
protected:
  TextureDescription m_desc{};
};
} // namespace goala
