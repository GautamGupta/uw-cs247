#ifndef PLAYER_VIEW_H
#define PLAYER_VIEW_H

#include <gtkmm.h>
#include <string>

/** Documentation of methods in .cpp file */

class Model;
class Controller;
class View;

class PlayerView : public Gtk::Frame {
public:
    static const std::string TXT_HUMAN;
    static const std::string TXT_COMPUTER;
    static const std::string TXT_RAGE;
    static const std::string TXT_SCORE;
    static const std::string TXT_DISCARDS;
    static const std::string TXT_PLAYER;

    PlayerView(Model*, Controller*, View*, int);
    virtual ~PlayerView();
    void setToggleButton(std::string, bool);
    void setLabels(int = 0, int = 0);
    void update();

private:
    Model* model_;
    Controller* controller_;
    View* view_;
    int playerNum_;

    Gtk::VBox container;
    Gtk::Button toggleBtn;
    Gtk::Label scoreTxt;
    Gtk::Label discardsTxt;

    void onBtnClick();
};

#endif
