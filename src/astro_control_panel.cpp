#include "astro_control_panel/astro_control_panel.hpp"

namespace astro_control_panel {
    AstroControlPanel::AstroControlPanel(QWidget* parent) : rviz_common::Panel(parent) {
        QVBoxLayout* layout = new QVBoxLayout;

        localizationSection_ = new LocalizationSection(this);
        layout->addWidget(localizationSection_);

        setLayout(layout);
    }

    void AstroControlPanel::save(rviz_common::Config config) const {
        rviz_common::Panel::save(config);
    }

    void AstroControlPanel::load(const rviz_common::Config& config) {
        rviz_common::Panel::load(config);
    }
}

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(astro_control_panel::AstroControlPanel, rviz_common::Panel)