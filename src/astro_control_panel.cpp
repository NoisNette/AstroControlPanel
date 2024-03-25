#include "astro_control_panel/astro_control_panel.hpp"

namespace astro_control_panel {
    AstroControlPanel::AstroControlPanel(QWidget* parent) : rviz_common::Panel(parent) {
        setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
    }

    void AstroControlPanel::save(rviz_common::Config config) const {
        rviz_common::Panel::save(config);
    }

    void AstroControlPanel::load(const rviz_common::Config& config) {
        rviz_common::Panel::load(config);
    }

    void AstroControlPanel::setupSubscriptions_(rclcpp::Node::SharedPtr node) {
        rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmdVelSubscription_ = node->create_subscription<geometry_msgs::msg::Twist>(
            "/cmd_vel",
            1,
            [this](const geometry_msgs::msg::Twist::SharedPtr msg) { infoSection_->updateCmdVel_(msg); }
        );
    }

    void AstroControlPanel::onInitialize() {
        rviz_common::DisplayContext* context_ = this->getDisplayContext();

        auto rviz_ros_node = context_->getRosNodeAbstraction().lock()->get_raw_node();
        
        setupSubscriptions_(rviz_ros_node);

        QVBoxLayout* layout = new QVBoxLayout;

        commandSection_ = new CommandSection(this);
        layout->addWidget(commandSection_);

        infoSection_ = new InfoSection(this);
        layout->addWidget(infoSection_);

        // teleopSection_ = new TeleopSection(this);
        // layout->addWidget(teleopSection_);

        setLayout(layout);
    }
}

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(astro_control_panel::AstroControlPanel, rviz_common::Panel)