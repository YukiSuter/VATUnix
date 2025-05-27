#ifndef ABOUT_PAGE_H
#define ABOUT_PAGE_H

#include <gtkmm.h>

class AboutPage : public Gtk::Box {
public:
    AboutPage();
private:
    Gtk::Picture m_picture;
    Gtk::Label m_info_text;
    Gtk::Frame m_info_frame;
};

#endif // ABOUT_PAGE_H
