// Copyright 2017 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#include "DolphinQt2/Config/Mapping/Hotkey3D.h"

#include <QGroupBox>
#include <QHBoxLayout>

#include "Core/HotkeyManager.h"

Hotkey3D::Hotkey3D(EmulatedControllerModel* model) : MappingWidget(model)
{
  CreateMainLayout();
}

void Hotkey3D::CreateMainLayout()
{
  m_main_layout = new QHBoxLayout();

  m_main_layout->addWidget(
      CreateGroupBox(tr("3D"), HotkeyManagerEmu::GetHotkeyGroup(HKGP_3D_TOGGLE)));
  m_main_layout->addWidget(
      CreateGroupBox(tr("3D Depth"), HotkeyManagerEmu::GetHotkeyGroup(HKGP_3D_DEPTH)));

  setLayout(m_main_layout);
}

InputConfig* Hotkey3D::GetConfig()
{
  return HotkeyManagerEmu::GetConfig();
}

void Hotkey3D::LoadSettings()
{
  HotkeyManagerEmu::LoadConfig();
}
