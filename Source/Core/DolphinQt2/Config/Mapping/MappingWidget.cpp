// Copyright 2017 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#include <QFormLayout>
#include <QGroupBox>
#include <QPushButton>

#include "DolphinQt2/Config/Mapping/MappingWidget.h"

#include "DolphinQt2/Config/Mapping/IOWindow.h"
#include "DolphinQt2/Config/Mapping/MappingBool.h"
#include "DolphinQt2/Config/Mapping/MappingButton.h"
#include "DolphinQt2/Config/Mapping/MappingNumeric.h"
#include "DolphinQt2/Config/Mapping/MappingWindow.h"
#include "InputCommon/ControlReference/ControlReference.h"
#include "InputCommon/ControllerEmu/Control/Control.h"
#include "InputCommon/ControllerEmu/ControlGroup/ControlGroup.h"
#include "InputCommon/ControllerEmu/Setting/BooleanSetting.h"
#include "InputCommon/ControllerEmu/Setting/NumericSetting.h"
#include "InputCommon/InputConfig.h"

MappingWidget::MappingWidget(EmulatedControllerModel* model) : m_model(model)
{
  connect(model, &EmulatedControllerModel::Update, this, &MappingWidget::Update);
}

void MappingWidget::SaveSettings()
{
  GetConfig()->SaveConfig();
}

EmulatedControllerModel* MappingWidget::GetModel() const
{
  return m_model;
}

int MappingWidget::GetPort() const
{
  return m_model->GetPort();
}

QGroupBox* MappingWidget::CreateGroupBox(const QString& name, ControllerEmu::ControlGroup* group)
{
  QGroupBox* group_box = new QGroupBox(name);
  QFormLayout* form_layout = new QFormLayout();

  group_box->setLayout(form_layout);

  for (auto& control : group->controls)
  {
    auto* control_ref = control->control_ref.get();
    auto* button = new MappingButton(m_model, control_ref);

    button->setMinimumWidth(100);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    form_layout->addRow(QString::fromStdString(control->name), button);

    connect(button, &MappingButton::AdvancedPressed, [this, button, control_ref] {
      IOWindow io(this, m_model->GetController(), control_ref,
                  control_ref->IsInput() ? IOWindow::Type::Input : IOWindow::Type::Output);
      io.exec();
      SaveSettings();
      button->Update();
    });

    m_buttons.push_back(button);
  }

  for (auto& numeric : group->numeric_settings)
  {
    auto* spinbox = new MappingNumeric(m_model, numeric.get());
    spinbox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    form_layout->addRow(QString::fromStdString(numeric->m_name), spinbox);
    m_numerics.push_back(spinbox);
  }

  for (auto& boolean : group->boolean_settings)
  {
    auto* checkbox = new MappingBool(m_model, boolean.get());
    checkbox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    form_layout->addRow(checkbox);
    m_bools.push_back(checkbox);
  }

  return group_box;
}

void MappingWidget::Update()
{
  for (auto* button : m_buttons)
    button->Update();

  for (auto* spinbox : m_numerics)
    spinbox->Update();

  for (auto* checkbox : m_bools)
    checkbox->Update();
}

ControllerEmu::EmulatedController* MappingWidget::GetController() const
{
  return m_model->GetController();
}
