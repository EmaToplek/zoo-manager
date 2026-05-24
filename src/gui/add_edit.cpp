#include "add_edit.hpp"
#include <wx/wx.h>

//creates wxChoice with options, and sets first option
static wxChoice* make_choice(wxWindow* parent, const wxArrayString& options) 
{
    wxChoice* choice = new wxChoice(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, options);
    choice->SetSelection(0);
    return choice;
}

static void add_row(wxWindow* parent, wxBoxSizer* sizer, const wxString& label, wxWindow* input)
{
    sizer->Add(new wxStaticText(parent, wxID_ANY, label), 0, wxLEFT | wxTOP, 16);
    sizer->Add(input, 0, wxEXPAND | wxLEFT | wxRIGHT, 16);
}

AddEditDialog::AddEditDialog(wxWindow* parent, Animal* animal) : wxDialog (parent, wxID_ANY, animal ? "Edit Animal" : "Add Animal", wxDefaultPosition, wxSize(400, 460))
{
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    //text inputs
    name_input_ = new wxTextCtrl(this, wxID_ANY);
    species_input_ = new wxTextCtrl(this, wxID_ANY);
    age_input_ = new wxTextCtrl(this, wxID_ANY);
    weight_input_ = new wxTextCtrl(this, wxID_ANY);

    //dropdowns
    category_input_ = make_choice(this, {"Mammal", "Bird", "Reptile", "Fish", "Amphibian"});
    enclosure_input_ = make_choice(this, {"Savanna", "Jungle", "Aquarium", "Ocean Tank", "Pond", "Rainforest", "Wetlands", "Aviary", "Terrarium"});
    health_input_  = make_choice(this, {"Healthy", "Sick", "In Treatment"});

    //layout
    std::vector<std::pair<wxString, wxWindow*>> fields =
    {
        {"Name:", name_input_},
        {"Species:", species_input_},
        {"Category:", category_input_},
        {"Age:", age_input_},
        {"Weight:", weight_input_},
        {"Enclosure:", enclosure_input_},
        {"Health:", health_input_},
    };
  
    for (auto& [label, input] : fields) 
    {
        add_row(this, sizer, label, input);
    };

    wxButton* ok_btn = new wxButton(this, wxID_ANY, "Save"); 
    wxButton* cancel_btn = new wxButton(this, wxID_CANCEL, "Cancel"); 

    sizer->Add(ok_btn, 0);
    sizer->Add(cancel_btn, 0, wxRIGHT, 0);
        
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

// called when user clicks Save - validates input and closes dialog with wxID_OK
void AddEditDialog::on_ok(wxCommandEvent& event) 
{
    EndModal(wxID_OK);
}
