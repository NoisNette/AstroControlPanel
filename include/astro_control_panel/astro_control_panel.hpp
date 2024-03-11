#ifndef ASTRO_CONTROL_PANEL_H
#define ASTRO_CONTROL_PANEL_H

#include "astro_control_panel/visibility_control.hpp"
#include "astro_control_panel/localization_section.hpp"
#include "astro_control_panel/teleop_section.hpp"
#include "astro_control_panel/info_section.hpp"
#include "astro_control_panel/command_section.hpp"

#include <rclcpp/rclcpp.hpp>
#include <rviz_common/panel.hpp>
#include <rviz_common/display_context.hpp>

#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSizePolicy>

class QLineEdit;

namespace astro_control_panel {
    class AstroControlPanel : public rviz_common::Panel {
        Q_OBJECT
        public:
          AstroControlPanel(QWidget* parent = 0);

          virtual void save( rviz_common::Config config ) const;
          virtual void load( const rviz_common::Config& config );
          void onInitialize() override;

        private:
          rviz_common::DisplayContext* context_;

          CommandSection* commandSection_;
          InfoSection* infoSection_;
          TeleopSection* teleopSection_;

          rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmdVelSubscription_;
    };
}

#endif