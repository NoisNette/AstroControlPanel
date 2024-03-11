#include "astro_control_panel/localization_widget.hpp"

namespace astro_control_panel {
    LocalizationWidget::LocalizationWidget(
            QWidget *parent
        ) : QWidget(parent) {
        QVBoxLayout* layout = new QVBoxLayout;

        QHBoxLayout* startStopLayout = new QHBoxLayout;

        startLocalizationButton_ = new QPushButton("Start");
        stopLocalizationButton_ = new QPushButton("Stop");
        loadMapButton_ = new QPushButton("Load Map");

        startStopLayout->addWidget(startLocalizationButton_);
        startStopLayout->addWidget(stopLocalizationButton_);

        layout->addLayout(startStopLayout);
        layout->addWidget(loadMapButton_);

        setLayout(layout);

        connect(startLocalizationButton_, &QPushButton::clicked, [this](void) { startLocalization_(); });
        connect(stopLocalizationButton_, &QPushButton::clicked, [this](void) { stopLocalization_(); });
        connect(loadMapButton_, &QPushButton::clicked, [this](void) { loadMap_(); });
    }

    void LocalizationWidget::startLocalization_() {
        if (localizationRunning_)
            return;
        localizationRunning_ = true;
    }

    void LocalizationWidget::stopLocalization_() {
        if (!localizationRunning_)
            return;
        localizationRunning_ = false;
    }

    void LocalizationWidget::loadMap_() {
        if (!localizationRunning_)
            return;
    }

    void LocalizationWidget::findAndTerminateProcess(std::string name) {
        std::array<char, 128> buffer;
        std::string result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(("ps -aux | grep " + name).c_str(), "r"), pclose);
        if (!pipe)
            throw std::runtime_error("popen() failed...");
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
            result += buffer.data();

        int i = 0;
        bool gotSpace = false;
        while (i < (int)result.length()) {
            if (result[i] == ' ')
                gotSpace = true;
            else if (gotSpace)
                break;
            i += 1;
        }        
        std::string pid = result.substr(i, result.find(" ", i)-i);
        system(("kill " + pid).c_str());
    }
}