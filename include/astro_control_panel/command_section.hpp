#ifndef COMMAND_SECTION_H
#define COMMAND_SECTION_H

#include <rclcpp/rclcpp.hpp>

#include "astro_control_panel/mapping_widget.hpp"
#include "astro_control_panel/localization_widget.hpp"
#include "astro_control_panel/navigation_widget.hpp"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QComboBox>

namespace astro_control_panel {
    class CommandSection : public QGroupBox {
        Q_OBJECT
        public:
          CommandSection(
            QWidget *parent
          );

        private:
          QComboBox* commandPicker_;
          QVBoxLayout* mainLayout_;

          int selectedCommandIndex = 0;

          QWidget* mappingWidget_;
          QWidget* localizationWidget_;
          QWidget* navigationWidget_;

          void changeCommand_(int index);
    };
}

#endif