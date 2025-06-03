#ifndef MY_APP_H
#define MY_APP_H

#include <gtkmm.h>

class VATUnix : public Gtk::Application {
public:
    static Glib::RefPtr<VATUnix> create();
    void update_prefix_dir(std::string new_dir);
    std::string get_prefix_dir();

private:
    std::string prefix_dir;

protected:
    VATUnix();

    void on_activate() override;
};

#endif // MY_APP_H

