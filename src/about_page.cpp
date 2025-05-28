#include "about_page.h"
#include <giomm/file.h>
#include <gdkmm/texture.h>

AboutPage::AboutPage()
: Gtk::Box(Gtk::Orientation::VERTICAL) {
    auto file = Gio::File::create_for_path("assets/VATUNIX_Side_Dark_Small.png");
    auto texture = Gdk::Texture::create_from_file(file);
    m_picture.set_paintable(texture);

    m_picture.set_content_fit(Gtk::ContentFit::SCALE_DOWN);  // never scales up
    m_picture.set_valign(Gtk::Align::CENTER);
    m_picture.set_halign(Gtk::Align::CENTER);

    append(m_picture);

    m_info_text.set_label(
        "Welcome to VATUnix!\n\n"
        "This is software written to streamline the installation and use of software required to control on the VATSIM network on unsupported unix systems (Linux or MacOS) using WINE to place EuroScope and associated software into a windows environment.\n\n"
        "Use the header buttons to get started."
    );
    m_info_text.set_margin(10);
    m_info_text.set_wrap(true);
    m_info_text.set_justify(Gtk::Justification::CENTER);

    m_info_frame.set_margin_top(20);
    m_info_frame.set_child(m_info_text);
    append(m_info_frame);

    set_margin_start(50);
    set_margin_end(50);
    set_margin_top(20);
    set_margin_bottom(20);
}
