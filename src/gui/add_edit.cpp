#include "add_edit.hpp"
#include <wx/wx.h>

// creates a wxChoice dropdown and defaults to the first option
static wxChoice* make_choice(wxWindow* parent, const wxArrayString& options) 
{
    wxChoice* choice = new wxChoice(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, options);
    choice->SetSelection(0);
    return choice;
}

// adds label and input pair to sizer
static void add_row(wxWindow* parent, wxBoxSizer* sizer, const wxString& label, wxWindow* input)
{
    sizer->Add(new wxStaticText(parent, wxID_ANY, label), 0, wxLEFT | wxTOP, 16);
    sizer->Add(input, 0, wxEXPAND | wxLEFT | wxRIGHT, 16);
}

AddEditDialog::AddEditDialog(wxWindow* parent, Animal* animal) : wxDialog (parent, wxID_ANY, animal ? "Edit Animal" : "Add Animal", wxDefaultPosition, wxSize(400, 460))
{
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    // CREATE ALL INPUT WIDGETS
    //text inputs
    name_input_ = new wxTextCtrl(this, wxID_ANY);
    species_input_ = new wxTextCtrl(this, wxID_ANY);
    age_input_ = new wxTextCtrl(this, wxID_ANY);
    weight_input_ = new wxTextCtrl(this, wxID_ANY);

    //dropdowns
    category_input_ = make_choice(this, {"Mammal", "Bird", "Reptile", "Fish", "Amphibian"});
    enclosure_input_ = make_choice(this, {"Savanna", "Jungle", "Aquarium", "Ocean Tank", "Pond", "Rainforest", "Wetlands", "Aviary", "Terrarium"});
    health_input_  = make_choice(this, {"Healthy", "Sick", "In Treatment"});

    // BUILDS LAYOUT
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


    wxBoxSizer* btn_sizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton* ok_btn = new wxButton(this, wxID_ANY, "Save"); 
    wxButton* cancel_btn = new wxButton(this, wxID_CANCEL, "Cancel"); 
    
    btn_sizer->Add(cancel_btn, 0, wxRIGHT, 8);
    btn_sizer->Add(ok_btn, 0);
    sizer->AddSpacer(12);
    sizer->Add(btn_sizer, 0, wxALIGN_RIGHT | wxALL, 16); 

    ok_btn->Bind(wxEVT_BUTTON, &AddEditDialog::on_ok, this);
    SetSizer(sizer);
        
}

//getters 
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
    if(name_input_->GetValue().IsEmpty() || species_input_->GetValue().IsEmpty()) 
    {
        wxMessageBox("Name and Species cannot be empty.", "Validation Error", wxICON_WARNING);
        return;
    }
    long age_val; 
    if(!age_input_->GetValue().ToLong(&age_val) || age_val <= 0)  
    {
        wxMessageBox("Age must be positive number.", "Validation Error", wxICON_WARNING);
        return;
    }
    double weight_val;
    if(!weight_input_->GetValue().ToDouble(&weight_val) || weight_val <= 0) 
    {
        wxMessageBox("Weight must be positive number.", "Validation Error", wxICON_WARNING);
        return;
    }
    EndModal(wxID_OK);
}
