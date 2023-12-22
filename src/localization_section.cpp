#include "astro_control_panel/localization_section.hpp"
#include <iostream>

namespace astro_control_panel {
    LocalizationSection::LocalizationSection(QWidget *parent) : QGroupBox("Localization", parent) {
        QVBoxLayout* layout = new QVBoxLayout;

        QHBoxLayout* startStopLayout = new QHBoxLayout;

        startLocalizationButton_ = new QPushButton("Start");
        stopLocalizationButton_ = new QPushButton("Stop");
        saveMapButton_ = new QPushButton("Save Map");


        startStopLayout->addWidget(startLocalizationButton_);
        startStopLayout->addWidget(stopLocalizationButton_);

        layout->addLayout(startStopLayout);
        layout->addWidget(saveMapButton_);

        setLayout(layout);

        connect(startLocalizationButton_, &QPushButton::clicked, [this](void) { startLocalization_(); });
        connect(stopLocalizationButton_, &QPushButton::clicked, [this](void) { stopLocalization_(); });
        connect(saveMapButton_, &QPushButton::clicked, [this](void) { saveMap_(); });
    }

    void LocalizationSection::startLocalization_() {
        std::cout << "Start\n";
    }

    void LocalizationSection::stopLocalization_() {
        std::cout << "Stop\n";
    }

    void LocalizationSection::saveMap_() {
        std::cout << "Save\n";
    }
}