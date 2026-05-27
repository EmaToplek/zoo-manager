#include "add_edit.hpp"
#include <wx/wx.h>
#include "mammal.hpp"
#include "bird.hpp"
#include "reptile.hpp"
#include "fish.hpp"
#include "amphibian.hpp"

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

//
std::map<std::string, std::string> AddEditDialog::get_special_info() const
{
    std::map<std::string, std::string> special_info;
    std::string cat = category_input_->GetStringSelection().ToStdString();
    if (cat == "Bird") 
    {
        special_info["can_fly"]  = can_fly_input_->IsChecked() ? "true" : "false";
        special_info["wingspan"] = wingspan_input_->GetValue().ToStdString();
    }
    else if (cat == "Reptile")
    {
        special_info["is_venomous"] = is_venomous_input_->IsChecked() ? "true" : "false";
        special_info["body_length"] = body_length_input_->GetValue().ToStdString();
    }
    return special_info;
}

// shows/hides Bird and Reptile specific fields based on selected category
void AddEditDialog::update_special_fields(const std::string& category)
{
    for (auto* w : bird_fields_) 
    {
        w->Show(category == "Bird");
    } 
    for (auto* w : reptile_fields_) 
    {
        w->Show(category == "Reptile");
    }
    Layout();
}

// if animal is nullptr - Add mode (empty fields)
//if animal provided - Edit mode (fields pre-filled with existing data)
AddEditDialog::AddEditDialog(wxWindow* parent, Animal* animal) : wxDialog (parent, wxID_ANY, animal ? "Edit Animal" : "Add Animal", wxDefaultPosition, wxSize(400, 560))
{
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    // CREATE ALL INPUT WIDGETS
    //text inputs
    name_input_ = new wxTextCtrl(this, wxID_ANY);
    age_input_ = new wxTextCtrl(this, wxID_ANY);
    weight_input_ = new wxTextCtrl(this, wxID_ANY);

    //dropdowns
    category_input_ = make_choice(this, {"Mammal", "Bird", "Reptile", "Fish", "Amphibian"});
    enclosure_input_ = make_choice(this, {"Savanna", "Jungle", "Aquarium", "Ocean Tank", "Pond", "Rainforest", "Wetlands", "Aviary", "Terrarium"});
    health_input_  = make_choice(this, {"Healthy", "Sick", "In Treatment"});

    // species dropdown is populated from the Mammal subclass by default
    // each subclass owns its own list of valid species 
    // the GUI does not hardcode species anywhere; it always asks the class
    wxArrayString initial_species;
    for (const auto& s : Mammal::get_available_species())
    {
        initial_species.Add(s);
    };
    
    species_input_ = make_choice(this, initial_species);

    // when category changes, species dropdown is rebuilt from the matching subclass
    category_input_->Bind(wxEVT_CHOICE, &AddEditDialog::on_category_changed, this);
    
    // BUILDS LAYOUT - add all fields to layout
    std::vector<std::pair<wxString, wxWindow*>> fields =
    {
        {"Name:", name_input_},
        {"Category:", category_input_},
        {"Species:", species_input_},
        {"Age:", age_input_},
        {"Weight:", weight_input_},
        {"Enclosure:", enclosure_input_},
        {"Health:", health_input_},
    };
  
    for (auto& [label, input] : fields) 
    {
        add_row(this, sizer, label, input);
    };

     // Bird-specific fields
     auto* wingspan_label = new wxStaticText(this, wxID_ANY, "Wingspan (m):");
     wingspan_input_ = new wxTextCtrl(this, wxID_ANY, "1.0");
     can_fly_input_  = new wxCheckBox(this, wxID_ANY, "Can fly");
     can_fly_input_->SetValue(true);

     sizer->Add(wingspan_label, 0, wxLEFT | wxTOP, 16);
     sizer->Add(wingspan_input_, 0, wxEXPAND | wxLEFT | wxRIGHT, 16);
     sizer->Add(can_fly_input_, 0, wxLEFT | wxTOP | wxRIGHT, 16);

     bird_fields_ = {wingspan_label, wingspan_input_, can_fly_input_};

    // Reptile-specific fields
    auto* body_length_label = new wxStaticText(this, wxID_ANY, "Body length (m):");
    body_length_input_      = new wxTextCtrl(this, wxID_ANY, "1.0");
    is_venomous_input_      = new wxCheckBox(this, wxID_ANY, "Venomous");
    is_venomous_input_->SetValue(false);
 
    sizer->Add(body_length_label,  0, wxLEFT | wxTOP, 16);
    sizer->Add(body_length_input_, 0, wxEXPAND | wxLEFT | wxRIGHT, 16);
    sizer->Add(is_venomous_input_, 0, wxLEFT | wxTOP | wxRIGHT, 16);

     
    reptile_fields_ = {body_length_label, body_length_input_, is_venomous_input_}; 

    // Save/Cancel buttons
    wxBoxSizer* btn_sizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton* ok_btn = new wxButton(this, wxID_ANY, "Save"); 
    wxButton* cancel_btn = new wxButton(this, wxID_CANCEL, "Cancel"); 
    
    btn_sizer->Add(cancel_btn, 0, wxRIGHT, 8);
    btn_sizer->Add(ok_btn, 0);
    sizer->AddSpacer(12);
    sizer->Add(btn_sizer, 0, wxALIGN_RIGHT | wxALL, 16); 

    ok_btn->Bind(wxEVT_BUTTON, &AddEditDialog::on_ok, this);

    //edit mode - pre fill fields with existing animal data 
    if (animal) 
    {
        //fill text fields
        std::vector<std::pair<wxTextCtrl*, wxString>> text_fields = 
        {
            {name_input_, animal->get_name()},
            {age_input_, std::to_string(animal->get_age())}, 
            {weight_input_, wxString::Format("%.2f", animal->get_weight())}
        };
        for (auto& [input, value] : text_fields) 
        {
            input->SetValue(value); 
        };

        //set cat first, then trigger on_category_changed so species dropdown is populated with correct subclass species list
        // before we try to select animals current species
        category_input_->SetStringSelection(animal->get_category_to_string());
        wxCommandEvent fake_event;
        on_category_changed(fake_event);
        species_input_->SetStringSelection(animal->get_species());

        // fill remaining dropdowns
        std::vector<std::pair<wxChoice*, wxString>> choice_fields = 
        {
            {enclosure_input_, animal->get_enclosure()},
            {health_input_, animal->get_health_status_to_string()}
        };
        for (auto& [input, value] : choice_fields) 
        {
            input->SetStringSelection(value);
        };
    }
    SetSizer(sizer);
    update_special_fields("Mammal");
        
}

//getters 
wxString AddEditDialog::get_name() const 
{
    return name_input_->GetValue();
}

wxString AddEditDialog::get_species() const 
{
    return species_input_->GetStringSelection();
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

double AddEditDialog::get_wingspan() const 
{
    double val = 1.0;
    wingspan_input_->GetValue().ToDouble(&val);
    return val;
}

bool AddEditDialog::get_can_fly() const
{ 
    return can_fly_input_->IsChecked();
}

bool AddEditDialog::get_is_venomous() const
{ 
    return is_venomous_input_->IsChecked(); 
}

double AddEditDialog::get_body_length() const 
{
    double val = 1.0;
    body_length_input_->GetValue().ToDouble(&val);
    return val;
}

// called when user clicks Save - validates input and closes dialog with wxID_OK
void AddEditDialog::on_ok(wxCommandEvent& event) 
{
    if(name_input_->GetValue().IsEmpty()) 
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

// rebuilds the species dropdown by querying the appropriate subclass
// each subclass owns its own static list of valid species — the GUI never hardcodes species directly
void AddEditDialog::on_category_changed(wxCommandEvent& event)
{
    species_input_->Clear();
    std::string cat = category_input_->GetStringSelection().ToStdString();

    std::vector<std::string> species;
    if (cat == "Mammal") 
    {
        species = Mammal::get_available_species();
    }
    else if (cat == "Bird")  
    {
        species = Bird::get_available_species();
    }    
    else if (cat == "Reptile") 
    {
        species = Reptile::get_available_species();
    }  
    else if (cat == "Fish")  
    {
        species = Fish::get_available_species();
    }    
    else if (cat == "Amphibian") 
    {
         species = Amphibian::get_available_species();
    }
   
    for (const auto& s : species) 
    {
         species_input_->Append(s);
    }
    
    species_input_->SetSelection(0);

    update_special_fields(cat);
}