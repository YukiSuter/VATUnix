#include "home_window.h"
#include <iostream>

home_window::home_window()
{
    auto css_provider = Gtk::CssProvider::create();

    try {
        css_provider->load_from_path("style.css");  // Relative to working directory
    } catch (const Glib::Error& ex) {
        std::cerr << "Failed to load CSS: " << ex.what() << std::endl;
    }

    // Window Params
    set_default_size(600, 400);
    set_resizable(false);
    set_title("VATUnix");

    Gtk::StyleContext::add_provider_for_display(
        Gdk::Display::get_default(),
        css_provider,
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );

    main_box.set_orientation(Gtk::Orientation::VERTICAL);

    menu_stack.add(about_page, "About", "About");
    menu_stack.add(software_page, "Software", "Software");
    menu_stack.add(fts_page, "FTS", "FTS");

    button_box.set_orientation(Gtk::Orientation::HORIZONTAL);
    button_box.set_margin(10);
    button_box.add_css_class("segmented-outline");  // add a custom class
    button_box.set_margin_bottom(0);

    btn_about.set_label("About");
    btn_software.set_label("Software");
    btn_regions.set_label("Regions");
    btn_first.set_label("First Time Setup");

    btn_software.set_group(btn_about);
    btn_regions.set_group(btn_about);
    btn_first.set_group(btn_about);
    btn_about.set_active(true);  // Default

    btn_about.add_css_class("linked");
    btn_software.add_css_class("linked");
    btn_regions.add_css_class("linked");
    btn_first.add_css_class("linked");

    btn_about.add_css_class("flat");
    btn_software.add_css_class("flat");
    btn_regions.add_css_class("flat");
    btn_first.add_css_class("flat");

    btn_software.set_visible(false);
    btn_regions.set_visible(false);

    // Only the first and last get special corner rounding
    btn_about.add_css_class("first");
    btn_regions.add_css_class("last");
    btn_first.add_css_class("last");

    button_box.append(btn_about);
    button_box.append(btn_software);
    button_box.append(btn_regions);
    button_box.append(btn_first);
    button_box.set_halign(Gtk::Align::CENTER);

    main_box.prepend(menu_stack);
    main_box.prepend(button_box);
    menu_stack.set_visible_child("About");
    menu_stack.set_valign(Gtk::Align::CENTER); // Center vertically
    menu_stack.set_vexpand(true);

    set_child(main_box);



    btn_about.signal_toggled().connect([&] {
        if (btn_about.get_active()) {
            menu_stack.set_visible_child("About");
        }
    });

    btn_software.signal_toggled().connect([&] {
        if (btn_software.get_active()) {
            menu_stack.set_visible_child("Software");
        }
    });

    btn_first.signal_toggled().connect([&] {
        if (btn_first.get_active()) {
            menu_stack.set_visible_child("FTS");
        }
    });
}