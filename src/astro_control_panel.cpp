#include "astro_control_panel/astro_control_panel.hpp"

namespace astro_control_panel {
    AstroControlPanel::AstroControlPanel() {
        
    }
}

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(astro_control_panel::AstroControlPanel, rviz_common::Panel)