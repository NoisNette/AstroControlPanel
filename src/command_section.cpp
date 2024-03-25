#include "astro_control_panel/command_section.hpp"

namespace astro_control_panel {
    CommandSection::CommandSection(
            QWidget *parent
        ) : QGroupBox("⌘ | Commands", parent) {

            QVBoxLayout* mainLayout_ = new QVBoxLayout;

            commandPicker_ = new QComboBox(this);
            commandPicker_->addItem("Mapping");
            commandPicker_->addItem("Localization");
            commandPicker_->addItem("Navigation");
            mainLayout_->addWidget(commandPicker_);

            mappingWidget_ = new MappingWidget(this);
            localizationWidget_ = new LocalizationWidget(this);
            navigationWidget_ = new NavigationWidget(this);

            mainLayout_->addWidget(mappingWidget_);
            mainLayout_->addWidget(localizationWidget_);
            mainLayout_->addWidget(navigationWidget_);

            localizationWidget_->hide();
            navigationWidget_->hide();

            setLayout(mainLayout_);

            connect(commandPicker_, QOverload<int>::of(&QComboBox::activated), [=](int index) { changeCommand_(index); });
    }

    void CommandSection::changeCommand_(int index) {
        if (index == selectedCommandIndex)
            return;

        mappingWidget_->hide();
        localizationWidget_->hide();
        navigationWidget_->hide();

        if (index == 0) { // Mapping
            mappingWidget_->show();
        }
        else if (index == 1) { // Localization
            localizationWidget_->show();
        }
        else if (index == 2) { // Navigation
            navigationWidget_->show();
        }

        selectedCommandIndex = index;
    }
}