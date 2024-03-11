#ifndef NAVIGATION_WIDGET_H
#define NAVIGATION_WIDGET_H

#include <rclcpp/rclcpp.hpp>

#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>

#include <array>
#include <stdexcept>
#include <memory>

namespace astro_control_panel {
    class NavigationWidget : public QWidget {
        Q_OBJECT
        public:
          NavigationWidget(
            QWidget *parent
          );

        private:
          QPushButton* startNavigationButton_;
          QPushButton* stopNavigationButton_;

          bool navigationRunning_ = false;
          
          void startNavigation_();
          void stopNavigation_();

          void findAndTerminateProcess(std::string name);
    };
}

#endif