#ifndef astro_control_panel_VISIBILITY_CONTROL_HPP
#define astro_control_panel_VISIBILITY_CONTROL_HPP

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
    #ifdef __GNUC__
        #define astro_control_panel_EXPORT __attribute__((dllexport))
        #define astro_control_panel_IMPORT __attribute__((dllimport))
    #else
        #define astro_control_panel_EXPORT __declspec(dllexport)
        #define astro_control_panel_IMPORT __declspec(dllimport)
    #endif
    #ifdef astro_control_panel_BUILDING_LIBRARY
        #define astro_control_panel_PUBLIC astro_control_panel_EXPORT
    #else
        #define astro_control_panel_PUBLIC astro_control_panel_IMPORT
    #endif
    #define astro_control_panel_PUBLIC_TYPE astro_control_panel_PUBLIC
    #define astro_control_panel_LOCAL
#else
    #define astro_control_panel_EXPORT __attribute__((visibility("default")))
    #define astro_control_panel_IMPORT
    #if __GNUC__ >= 4
        #define astro_control_panel_PUBLIC __attribute__((visibility("default")))
        #define astro_control_panel_LOCAL __attribute__((visibility("hidden")))
    #else
        #define astro_control_panel_PUBLIC
        #define astro_control_panel_LOCAL
    #endif
    #define astro_control_panel_PUBLIC_TYPE
#endif

#endif // astro_control_panel_VISIBILITY_CONTROL_HPP