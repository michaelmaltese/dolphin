// Copyright 2010 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <atomic>
#include <functional>
#include <memory>
#include <mutex>
#include <vector>

#include "InputCommon/ControllerInterface/Device.h"

// enable disable sources
#ifdef _WIN32
#define CIFACE_USE_WIN32
#endif
#if defined(HAVE_X11) && HAVE_X11
#define CIFACE_USE_XLIB
#endif
#if defined(__APPLE__)
#define CIFACE_USE_OSX
#endif
#if defined(HAVE_LIBEVDEV) && defined(HAVE_LIBUDEV)
#define CIFACE_USE_EVDEV
#endif
#if defined(USE_PIPES)
#define CIFACE_USE_PIPES
#endif

//
// ControllerInterface
//
// Some crazy shit I made to control different device inputs and outputs
// from lots of different sources, hopefully more easily.
//
class ControllerInterface : public ciface::Core::DeviceContainer
{
public:
  ControllerInterface() : m_is_init(false), m_hwnd(nullptr) {}
  void Initialize(void* const hwnd);
  void RefreshDevices();
  void Shutdown();
  void AddDevice(std::shared_ptr<ciface::Core::Device> device);
  void RemoveDevice(std::function<bool(const ciface::Core::Device*)> callback);
  bool IsInit() const { return m_is_init; }
  void UpdateInput();

  void RegisterDevicesChangedCallback(std::function<void(void)> callback);
  void InvokeDevicesChangedCallbacks() const;

private:
  std::vector<std::function<void()>> m_devices_changed_callbacks;
  mutable std::mutex m_callbacks_mutex;
  bool m_is_init;
  std::atomic<bool> m_is_populating_devices{false};
  void* m_hwnd;
};

extern ControllerInterface g_controller_interface;
