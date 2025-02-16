// Copyright 2017 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#include "DolphinQt2/Config/Mapping/HotkeyWii.h"

#include <QGroupBox>
#include <QHBoxLayout>

#include "Core/HotkeyManager.h"

HotkeyWii::HotkeyWii(EmulatedControllerModel* model) : MappingWidget(model)
{
  CreateMainLayout();
}

void HotkeyWii::CreateMainLayout()
{
  m_main_layout = new QHBoxLayout();

  m_main_layout->addWidget(CreateGroupBox(tr("Wii"), HotkeyManagerEmu::GetHotkeyGroup(HKGP_WII)));

  setLayout(m_main_layout);
}

InputConfig* HotkeyWii::GetConfig()
{
  return HotkeyManagerEmu::GetConfig();
}

void HotkeyWii::LoadSettings()
{
  HotkeyManagerEmu::LoadConfig();
}
