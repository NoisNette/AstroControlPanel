#include "astro_control_panel/command_section.hpp"
#include <iostream>

namespace astro_control_panel {
    CommandSection::CommandSection(
            QWidget *parent
        ) : QGroupBox("⌘ | Commands", parent) {
    }
}