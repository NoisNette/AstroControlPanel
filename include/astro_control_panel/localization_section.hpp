#ifndef LOCALIZATION_SECTION_H
#define LOCALIZATION_SECTION_H

#include <rclcpp/rclcpp.hpp>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFileDialog>

namespace astro_control_panel {
    class LocalizationSection : public QGroupBox {
        Q_OBJECT
        public:
          LocalizationSection(QWidget *parent = 0);

        private:
          QPushButton* startLocalizationButton_;
          QPushButton* stopLocalizationButton_;
          QPushButton* saveMapButton_;
          
          void startLocalization_();
          void stopLocalization_();
          void saveMap_();
    };
}

#endif