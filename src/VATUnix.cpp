#include "VATUnix.h"

#include "file_utils.h"
#include "home_window.h"

VATUnix::VATUnix() : Gtk::Application("com.yukisuter.vatunix") {}

Glib::RefPtr<VATUnix> VATUnix::create() {
    return Glib::RefPtr<VATUnix>(new VATUnix());
}

void VATUnix::on_activate() {
    auto window = new home_window();
    FileUtils::ensure_vatunix_data_folder();  // ✅ make sure the folder exist
    add_window(*window);
    window->present();
}

void VATUnix::update_prefix_dir(std::string new_dir) {
    prefix_dir = new_dir;
}

std::string VATUnix::get_prefix_dir() {
    return prefix_dir;
}


