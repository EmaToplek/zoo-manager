#ifndef DETAIL_PANEL_HPP
#define DETAIL_PANEL_HPP

#include <wx/wx.h>
#include "../animals/animal.hpp"

class DetailPanel : public wxPanel 
{
public:
    DetailPanel(wxPanel* parent); 
    void show_animal(Animal* animal);
    void clear();

private:
    wxStaticText* name_val_;
    wxStaticText* category_val_;
    wxStaticText* species_val_;
    wxStaticText* age_val_;
    wxStaticText* weight_val_;
    wxStaticText* enclosure_val_;
    wxStaticText* health_val_;

    wxStaticText* feeding_val_;
    wxStaticText* habitat_val_;
    wxStaticText* enclosure_size_val_;
    wxStaticText* special_info_val_;

    void set_font(wxStaticText* widget, int size, bool bold); 
    wxStaticText* placeholder_;

};

#endif