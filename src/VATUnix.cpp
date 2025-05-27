#include "VATUnix.h"
#include "home_window.h"

VATUnix::VATUnix() : Gtk::Application("com.yukisuter.vatunix") {}

Glib::RefPtr<VATUnix> VATUnix::create() {
    return Glib::RefPtr<VATUnix>(new VATUnix());
}

void VATUnix::on_activate() {
    auto window = new home_window();
    add_window(*window);
    window->present();
}

