#ifndef ADD_EDIT_HPP
#define ADD_EDIT_HPP

#include <wx/wx.h>
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

    std::map<std::string, std::string> get_special_info() const;


private: 

    Animal_Manager* manager_;
    Animal* animal_editing_;

    wxTextCtrl* name_input_;
    wxChoice* species_input_;
    wxChoice* category_input_;
    wxTextCtrl* age_input_;
    wxTextCtrl* weight_input_;
    wxChoice* enclosure_input_;
    wxChoice* health_input_;

    wxBoxSizer* dynamic_sizer_; // Sizer dedicated just to special info
    std::  map<std::string, wxTextCtrl*> dynamic_inputs_; // Maps the trait key to the UI text box

    void on_ok(wxCommandEvent& event); 
    void on_category_changed(wxCommandEvent& event);

    wxButton* ok_btn_;
    wxButton* cancel_btn_;

    // Generates UI fields dynamically based on a map
    void build_dynamic_fields(const std::map<std::string, std::string>& info);
};





#endif