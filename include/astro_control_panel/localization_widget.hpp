#ifndef LOCALIZATION_WIDGET_H
#define LOCALIZATION_WIDGET_H

#include <rclcpp/rclcpp.hpp>

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFileDialog>

#include <array>
#include <stdexcept>
#include <memory>

namespace astro_control_panel {
    class LocalizationWidget : public QWidget {
        Q_OBJECT
        public:
          LocalizationWidget(QWidget *parent);

        private:
          QPushButton* startLocalizationButton_;
          QPushButton* stopLocalizationButton_;
          QPushButton* loadMapButton_;

          bool localizationRunning_ = false;
          
          void startLocalization_();
          void stopLocalization_();
          void loadMap_();

          void findAndTerminateProcess(std::string name);
    };
}

#endif