// Copyright 2017 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include "DolphinQt2/Config/Mapping/MappingWidget.h"

class QCheckBox;
class QFormLayout;
class QGroupBox;
class QHBoxLayout;
class QLabel;
class QVBoxLayout;

class GCPadEmu final : public MappingWidget
{
public:
  explicit GCPadEmu(EmulatedControllerModel* model);

  InputConfig* GetConfig() override;

private:
  void LoadSettings() override;
  void CreateMainLayout();

  QHBoxLayout* m_main_layout;
};
