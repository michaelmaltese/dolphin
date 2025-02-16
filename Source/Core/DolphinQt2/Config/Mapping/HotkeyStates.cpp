// Copyright 2017 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#include "DolphinQt2/Config/Mapping/HotkeyStates.h"

#include <QGroupBox>
#include <QHBoxLayout>

#include "Core/HotkeyManager.h"

HotkeyStates::HotkeyStates(EmulatedControllerModel* model) : MappingWidget(model)
{
  CreateMainLayout();
}

void HotkeyStates::CreateMainLayout()
{
  m_main_layout = new QHBoxLayout();

  m_main_layout->addWidget(
      CreateGroupBox(tr("Save"), HotkeyManagerEmu::GetHotkeyGroup(HKGP_SAVE_STATE)));
  m_main_layout->addWidget(
      CreateGroupBox(tr("Load"), HotkeyManagerEmu::GetHotkeyGroup(HKGP_LOAD_STATE)));

  setLayout(m_main_layout);
}

InputConfig* HotkeyStates::GetConfig()
{
  return HotkeyManagerEmu::GetConfig();
}

void HotkeyStates::LoadSettings()
{
  HotkeyManagerEmu::LoadConfig();
}
