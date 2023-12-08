#include "astro_control_panel/astro_control_panel.hpp"
#include <iostream>

namespace astro_control_panel {
    AstroControlPanel::AstroControlPanel(QWidget* parent) : rviz_common::Panel(parent) {
        QVBoxLayout* layout = new QVBoxLayout;

        label_ = new QLabel("Label");
        layout->addWidget(label_);

        button_ = new QPushButton("Button");
        layout->addWidget(button_);

        input_ = new QLineEdit;
        layout->addWidget(input_);

        setLayout(layout);

        connect(button_, &QPushButton::clicked, [this](void) { std::cout << "click\n"; });
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