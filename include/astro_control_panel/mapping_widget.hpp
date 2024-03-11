#ifndef MAPPING_WIDGET_H
#define MAPPING_WIDGET_H

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
    class MappingWidget : public QWidget {
        Q_OBJECT
        public:
          MappingWidget(QWidget *parent);

        private:
          QPushButton* startMappingButton_;
          QPushButton* stopMappingButton_;
          QPushButton* saveMapButton_;

          bool mappingRunning_ = false;
          
          void startMapping_();
          void stopMapping_();
          void saveMap_();

          void findAndTerminateProcess(std::string name);
    };
}

#endif