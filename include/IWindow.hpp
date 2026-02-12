#ifndef IWINDOW_HPP
#define IWINDOW_HPP

struct WinSize {
  int w, h;
};

class IWindow {
public:
  virtual bool initialized() const = 0;

  virtual void cache_window_size() = 0;

  virtual WinSize get_window_size() const = 0;

  virtual ~IWindow() = default;
};

#endif
