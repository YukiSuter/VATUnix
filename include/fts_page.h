#ifndef FTS_PAGE_H
#define FTS_PAGE_H

#include <gtkmm.h>

class FTSPage : public Gtk::Box {
public:
    FTSPage();
private:
    Gtk::Stack wizard_stack;
};

#endif //FTS_PAGE_H
