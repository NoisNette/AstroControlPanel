#include "astro_control_panel/navigation_widget.hpp"

namespace astro_control_panel {
    NavigationWidget::NavigationWidget(
            QWidget *parent
        ) : QWidget(parent) {
        QVBoxLayout* layout = new QVBoxLayout;

        QHBoxLayout* startStopLayout = new QHBoxLayout;

        startNavigationButton_ = new QPushButton("Start");
        stopNavigationButton_ = new QPushButton("Stop");

        startStopLayout->addWidget(startNavigationButton_);
        startStopLayout->addWidget(stopNavigationButton_);

        layout->addLayout(startStopLayout);

        QHBoxLayout* launchFileDirLayout = new QHBoxLayout;
        launchFileDirLayout->addWidget(new QLabel("Launch file:"));
        launchFileAskPathButton_ = new QPushButton("Choose file");
        launchFileDirLayout->addWidget(launchFileAskPathButton_);
        layout->addLayout(launchFileDirLayout);

        QHBoxLayout* configFileDirLayout = new QHBoxLayout;
        configFileDirLayout->addWidget(new QLabel("Config file:"));
        configFileAskPathButton_ = new QPushButton("Choose file");
        configFileDirLayout->addWidget(configFileAskPathButton_);
        layout->addLayout(configFileDirLayout);

        setLayout(layout);

        connect(startNavigationButton_, &QPushButton::clicked, [this](void) { startNavigation_(); });
        connect(stopNavigationButton_, &QPushButton::clicked, [this](void) { stopNavigation_(); });
        connect(launchFileAskPathButton_, &QPushButton::clicked, [this](void) { chooseLaunchFile_(); });
        connect(configFileAskPathButton_, &QPushButton::clicked, [this](void) { chooseConfigFile_(); });
    }

    void NavigationWidget::startNavigation_() {
        if (navigationRunning_)
            return;
        navigationRunning_ = true;
    }

    void NavigationWidget::stopNavigation_() {
        if (!navigationRunning_)
            return;
        navigationRunning_ = false;
    }

    void NavigationWidget::chooseLaunchFile_() {
        QString dir = QFileDialog::getOpenFileName(this, tr("Choose launch file"), "/home", tr("(*.py *.xml *.yaml)"));
        if (dir == "")
            return;

        std::string path = dir.toStdString();
        std::string filename = path.substr(path.rfind("/")+1);
        launchFileAskPathButton_->setText(filename.c_str());
    }

    void NavigationWidget::chooseConfigFile_() {
        QString dir = QFileDialog::getOpenFileName(this, tr("Choose config file"), "/home", tr("(*.yaml)"));
        if (dir == "")
            return;

        std::string path = dir.toStdString();
        std::string filename = path.substr(path.rfind("/")+1);
        launchFileAskPathButton_->setText(filename.c_str());
    }

    void NavigationWidget::findAndTerminateProcess(std::string name) {
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