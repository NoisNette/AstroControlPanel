#include "astro_control_panel/command_section.hpp"
#include <iostream>

namespace astro_control_panel {
    CommandSection::CommandSection(
            QWidget *parent
        ) : QGroupBox("⌘ | Commands", parent) {
            // setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);

            QVBoxLayout* mainLayout_ = new QVBoxLayout;

            commandPicker_ = new QComboBox(this);
            commandPicker_->addItem("Mapping");
            commandPicker_->addItem("Localization");
            commandPicker_->addItem("Navigation");
            mainLayout_->addWidget(commandPicker_);

            mappingWidget = new MappingWidget(this);
            localizationWidget = new LocalizationWidget(this);
            navigationWidget = new NavigationWidget(this);

            mainLayout_->addWidget(mappingWidget);
            mainLayout_->addWidget(localizationWidget);
            mainLayout_->addWidget(navigationWidget);

            localizationWidget->hide();
            navigationWidget->hide();

            setLayout(mainLayout_);

            connect(commandPicker_, QOverload<int>::of(&QComboBox::activated), [=](int index) { changeCommand_(index); });
    }

    void CommandSection::changeCommand_(int index) {
        if (index == selectedCommandIndex)
            return;

        mappingWidget->hide();
        localizationWidget->hide();
        navigationWidget->hide();

        if (index == 0) { // Mapping
            mappingWidget->show();
        }
        else if (index == 1) { // Localization
            localizationWidget->show();
        }
        else if (index == 2) { // Navigation
            navigationWidget->show();
        }

        selectedCommandIndex = index;
    }
}