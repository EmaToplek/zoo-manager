#include "add_edit.hpp"
#include <wx/wx.h>
#include "./animal.hpp"

AddEditDialog::AddEditDialog(wxWindow* parent, Animal* animal) : wxDialog (parent, wxID_ANY, animal ? "Edit Animal" : "Add Animal", wxDefaultPosition, wxSize(400, 460))
{
    
}

wxString AddEditDialog::get_name() const 
{
    return name_input_->GetValue();
}

wxString AddEditDialog::get_species() const 
{
    return species_input_->GetValue();
}

wxString AddEditDialog::get_category() const
{
    return category_input_->GetStringSelection();
}

int AddEditDialog::get_age() const 
{
    long val;
    age_input_->GetValue().ToLong(&val);
    return static_cast<int>(val);
}

double AddEditDialog::get_weight() const 
{
    double val;
    weight_input_->GetValue().ToDouble(&val);
    return val;
}

wxString AddEditDialog::get_enclosure() const
{
    return enclosure_input_->GetStringSelection();
}

wxString AddEditDialog::get_health() const 
{
    return health_input_->GetStringSelection();
}