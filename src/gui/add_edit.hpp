#ifndef ADD_EDIT_HPP
#define ADD_EDIT_HPP

#include <wx/wx.h>
#include "../animals/animal.hpp"
#include "../app/animal_manager.hpp"
#include <map>
#include <string>
#include <vector>

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

    AddEditDialog(wxWindow* parent, Animal_Manager* manager,  Animal* animal = nullptr);

     // Bird-specific getters
     bool get_can_fly() const;
     double get_wingspan() const;
 
     // Reptile-specific getters
     bool get_is_venomous() const;
     double get_body_length() const;

     std::map<std::string, std::string> get_special_info() const;


private: 

    Animal_Manager* manager_;

    wxTextCtrl* name_input_;
    wxChoice* species_input_;
    wxChoice* category_input_;
    wxTextCtrl* age_input_;
    wxTextCtrl* weight_input_;
    wxChoice* enclosure_input_;
    wxChoice* health_input_;

    // Bird-specific fields
    wxCheckBox* can_fly_input_;
    wxTextCtrl* wingspan_input_;

    // Reptile-specific fields
    wxCheckBox* is_venomous_input_;
    wxTextCtrl* body_length_input_;

    void on_ok(wxCommandEvent& event); 
    void on_category_changed(wxCommandEvent& event);
    void update_special_fields(const std::string& category);

    wxButton* ok_btn_;
    wxButton* cancel_btn_;

    // groups for show/hide
    std::vector<wxWindow*> bird_fields_;
    std::vector<wxWindow*> reptile_fields_;
};





#endif