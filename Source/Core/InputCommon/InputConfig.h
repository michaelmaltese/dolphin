// Copyright 2010 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace ControllerEmu
{
class EmulatedController;
}

class InputConfig
{
public:
  InputConfig(const std::string& ini_name, const std::string& gui_name,
              const std::string& profile_name, bool is_gamecube);

  ~InputConfig();

  bool LoadConfig();
  void SaveConfig();

  template <typename T, typename... Args>
  void CreateController(Args&&... args)
  {
    m_controllers.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
  }

  ControllerEmu::EmulatedController* GetController(int index);
  void ClearControllers();
  bool ControllersNeedToBeCreated() const;
  bool IsControllerControlledByGamepadDevice(int index) const;

  std::string GetGUIName() const { return m_gui_name; }
  std::string GetProfileName() const { return m_profile_name; }
private:
  std::vector<std::unique_ptr<ControllerEmu::EmulatedController>> m_controllers;
  const std::string m_ini_name;
  const std::string m_gui_name;
  const std::string m_profile_name;
  bool m_is_gamecube;
};
