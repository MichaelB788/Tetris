#ifndef IPLATFORM_HPP
#define IPLATFORM_HPP
#include "IRenderer.hpp"
#include "IWindow.hpp"
#include <memory>

struct Backends {
  std::unique_ptr<IWindow> window;
  std::unique_ptr<IRenderer> renderer;
};

class IPlatform {
public:
  IPlatform() = default;

  virtual ~IPlatform() = default;

  virtual Backends create_backends() = 0;

  IPlatform(const IPlatform &) = delete;
  IPlatform &operator=(const IPlatform &) = delete;
  IPlatform(IPlatform &&) = delete;
  IPlatform &operator=(IPlatform &&) = delete;
};

#endif
