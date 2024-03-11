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

        setLayout(layout);

        connect(startNavigationButton_, &QPushButton::clicked, [this](void) { startNavigation_(); });
        connect(stopNavigationButton_, &QPushButton::clicked, [this](void) { stopNavigation_(); });
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