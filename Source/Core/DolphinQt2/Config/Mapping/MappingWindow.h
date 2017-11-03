// Copyright 2017 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <QDialog>
#include <QString>
#include <memory>

#include "DolphinQt2/Config/Mapping/EmulatedControllerModel.h"

class InputConfig;
class QComboBox;
class QDialogButtonBox;
class QEvent;
class QHBoxLayout;
class QGroupBox;
class QVBoxLayout;
class QPushButton;
class QTabWidget;
class QWidget;

class MappingWindow final : public QDialog
{
  Q_OBJECT
public:
  enum class Type
  {
    // GameCube
    MAPPING_GC_BONGOS,
    MAPPING_GC_DANCEMAT,
    MAPPING_GC_KEYBOARD,
    MAPPING_GCPAD,
    MAPPING_GC_STEERINGWHEEL,
    // Wii
    MAPPING_WIIMOTE_EMU,
    MAPPING_WIIMOTE_HYBRID,
    // Hotkeys
    MAPPING_HOTKEYS
  };

  explicit MappingWindow(QWidget* parent, Type type, int port_num);

private:
  void SetMappingType(Type type);
  void CreateDevicesLayout();
  void CreateProfilesLayout();
  void CreateResetLayout();
  void CreateMainLayout();
  void ConnectWidgets();

  void AddWidget(const QString& name, QWidget* widget);

  void RefreshDevices();

  void OnDeleteProfilePressed();
  void OnLoadProfilePressed();
  void OnSaveProfilePressed();
  void OnDeviceChanged(int index);

  EmulatedControllerModel m_model;

  // Main
  QVBoxLayout* m_main_layout;
  QHBoxLayout* m_config_layout;
  QDialogButtonBox* m_button_box;

  // Devices
  QGroupBox* m_devices_box;
  QHBoxLayout* m_devices_layout;
  QComboBox* m_devices_combo;
  QPushButton* m_devices_refresh;

  // Profiles
  QGroupBox* m_profiles_box;
  QHBoxLayout* m_profiles_layout;
  QComboBox* m_profiles_combo;
  QPushButton* m_profiles_load;
  QPushButton* m_profiles_save;
  QPushButton* m_profiles_delete;

  // Reset
  QGroupBox* m_reset_box;
  QHBoxLayout* m_reset_layout;
  QPushButton* m_reset_default;
  QPushButton* m_reset_clear;

  QTabWidget* m_tab_widget;
};
