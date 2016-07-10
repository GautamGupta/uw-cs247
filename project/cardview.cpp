#include "cardview.h"
#include "model.h"
#include "view.h"
#include "controller.h"
#include <gtkmm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

CardView::CardView(Model* model, Controller* controller, View* view) : model_(model), controller_(controller), view_(view) {
    const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = view_->getNullCardImage();
    cardImage = new Gtk::Image(nullCardPixbuf);
    set_image(*cardImage);
}
