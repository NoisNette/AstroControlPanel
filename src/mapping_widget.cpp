#include "astro_control_panel/mapping_widget.hpp"

namespace astro_control_panel {
    MappingWidget::MappingWidget(
            QWidget *parent
        ) : QWidget(parent) {
        QVBoxLayout* layout = new QVBoxLayout;

        QHBoxLayout* startStopLayout = new QHBoxLayout;

        startMappingButton_ = new QPushButton("Start");
        stopMappingButton_ = new QPushButton("Stop");
        saveMapButton_ = new QPushButton("Save Map");

        startStopLayout->addWidget(startMappingButton_);
        startStopLayout->addWidget(stopMappingButton_);

        layout->addLayout(startStopLayout);
        layout->addWidget(saveMapButton_);

        setLayout(layout);

        connect(startMappingButton_, &QPushButton::clicked, [this](void) { startMapping_(); });
        connect(stopMappingButton_, &QPushButton::clicked, [this](void) { stopMapping_(); });
        connect(saveMapButton_, &QPushButton::clicked, [this](void) { saveMap_(); });
    }

    void MappingWidget::startMapping_() {
        if (mappingRunning_)
            return;
        mappingRunning_ = true;
    }

    void MappingWidget::stopMapping_() {
        if (!mappingRunning_)
            return;
        mappingRunning_ = false;
    }

    void MappingWidget::saveMap_() {
        if (!mappingRunning_)
            return;
        
        QString dir = QFileDialog::getExistingDirectory(this, tr("Save Map"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        if (dir == "")
            return;
    }

    void MappingWidget::findAndTerminateProcess(std::string name) {
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