#ifndef ASTRO_CONTROL_PANEL_H
#define ASTRO_CONTROL_PANEL_H

#include "astro_control_panel/visibility_control.hpp"

#include <rclcpp/rclcpp.hpp>
#include <rviz_common/panel.hpp>

namespace astro_control_panel {
    class AstroControlPanel : public rviz_common::Panel {
        public:
            AstroControlPanel();
    };
}

#endif