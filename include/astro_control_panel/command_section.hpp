#ifndef COMMAND_SECTION_H
#define COMMAND_SECTION_H

#include <rclcpp/rclcpp.hpp>
#include <rviz_common/display.hpp>
#include <rviz_common/display_group.hpp>

#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFileDialog>

#include <array>
#include <stdexcept>
#include <memory>

namespace astro_control_panel {
    class CommandSection : public QGroupBox {
        Q_OBJECT
        public:
          CommandSection(
            QWidget *parent
          );
    };
}

#endif