#ifndef MY_APP_H
#define MY_APP_H

#include <gtkmm.h>

class VATUnix : public Gtk::Application {
public:
    static Glib::RefPtr<VATUnix> create();

protected:
    VATUnix();

    void on_activate() override;
};

#endif // MY_APP_H

