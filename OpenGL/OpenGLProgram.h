#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string_view>
#include <functional>

class OpenGLProgram {
 public:
  OpenGLProgram() = default;
  ~OpenGLProgram();

  void initialize(std::string_view vsPath, std::string_view fsPath);

  void bind();

  void setUniform(const std::string& name, const glm::mat4 &mat4);

 private:
  GLuint m_program = -1;
  std::mutex m_taskLock;
  std::vector<std::function<void()>> m_tasks;
};
