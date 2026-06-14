#ifndef DETAIL_PANEL_HPP
#define DETAIL_PANEL_HPP

#include <wx/scrolwin.h>
#include <wx/wx.h>
#include "../animals/animal.hpp"

class DetailPanel : public wxScrolledWindow 
{
public:
    DetailPanel(wxWindow* parent); 
    void show_animal(Animal* animal);
    void clear();
    void update_stats(uint64_t total, uint64_t healthy, uint64_t sick, uint64_t in_treatment);

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

     
    // overview stat boxes
    wxStaticText* stat_total_val_;
    wxStaticText* stat_healthy_val_;
    wxStaticText* stat_sick_val_;
    wxStaticText* stat_treatment_val_;

    void set_font(wxStaticText* widget, int size, bool bold); 
    wxPanel* make_stat_box(const wxString& label, wxStaticText** out_val, const wxColour& bg, const wxColour& fg);
    wxStaticText* placeholder_;

};

#endif