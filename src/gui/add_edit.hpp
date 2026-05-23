#ifndef ADD_EDIT.HPP
#define ADD_EDIT.HPP

#include <wx/wx.h>
#include "../animals/animal.hpp"

class AddEditDialog : public wxDialog 
{
public: 
    wxString get_name() const;
    wxString get_species() const;
    wxString get_category() const;
    int get_age() const;
    double get_weight() const;
    wxString get_enclosure() const;
    wxString get_health() const;

    AddEditDialog(wxWindow* parent, Animal* animal = nullptr);


private: 
    wxTextCtrl* name_input_;
    wxTextCtrl* species_input_;
    wxChoice* category_input_;
    wxTextCtrl* age_input_;
    wxTextCtrl* weight_input_;
    wxChoice* enclosure_input_;
    wxChoice* health_input_;

    void on_ok(wxCommandEvent& event); 
}





#endif