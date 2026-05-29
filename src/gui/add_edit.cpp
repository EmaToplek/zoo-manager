#include "add_edit.hpp"
#include <wx/wx.h>

// creates a wxChoice dropdown and defaults to the first option
static wxChoice* make_choice(wxWindow *parent, const wxArrayString &options)
{
    wxChoice* choice = new wxChoice(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, options);
    choice->SetSelection(0);
    return choice;
}

// adds label and input pair to sizer
static void add_row(wxWindow* parent, wxBoxSizer *sizer, const wxString &label, wxWindow *input)
{
    sizer->Add(new wxStaticText(parent, wxID_ANY, label), 0, wxLEFT | wxTOP, 16);
    sizer->Add(input, 0, wxEXPAND | wxLEFT | wxRIGHT, 16);
}

// Iterate through the dynamic UI inputs and package them back into a map for saving
std::map<std::string, std::string> AddEditDialog::get_special_info() const
{
    std::map<std::string, std::string> current_info;
    for (const auto& [key, input_ctrl] : dynamic_inputs_) 
    {
        current_info[key] = input_ctrl->GetValue().ToStdString();
    }
    return current_info;
}

// Rebuilds the UI based entirely on the keys in the map
void AddEditDialog::build_dynamic_fields(const std::map<std::string, std::string>& info)
{
    dynamic_sizer_->Clear(true);
    dynamic_inputs_.clear();

    for (const auto& [key, value] : info) 
    {
        wxTextCtrl* input = new wxTextCtrl(this, wxID_ANY, value);
        
        add_row(this, dynamic_sizer_, key + ":", input);
        dynamic_inputs_[key] = input;
    }

    Layout();
   }

// if animal is nullptr - Add mode (empty fields)
// if animal provided - Edit mode (fields pre-filled with existing data)
AddEditDialog::AddEditDialog(wxWindow *parent, Animal_Manager *manager, Animal *animal)
    : wxDialog(parent, wxID_ANY, animal ? "Edit Animal" : "Add Animal", wxDefaultPosition, wxSize(420, 650)),
      manager_(manager), animal_editing_(animal)
{
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    // CREATE ALL INPUT WIDGETS
    // text inputs
    name_input_ = new wxTextCtrl(this, wxID_ANY);
    age_input_ = new wxTextCtrl(this, wxID_ANY);
    weight_input_ = new wxTextCtrl(this, wxID_ANY);

    // dropdowns
    category_input_ = make_choice(this, {"Mammal", "Bird", "Reptile", "Fish", "Amphibian"});
    enclosure_input_ = make_choice(this, {"Savanna", "Jungle", "Aquarium", "Ocean Tank", "Pond", "Rainforest", "Wetlands", "Aviary", "Terrarium"});
    health_input_  = make_choice(this, {"Healthy", "Sick", "In Treatment"});
    

    /*wxArrayString categories, enclosures, health_states;

    categories.Add("Mammal");
    categories.Add("Bird");
    categories.Add("Reptile");
    categories.Add("Fish");
    categories.Add("Amphibian");

    enclosures.Add("Savanna");
    enclosures.Add("Jungle");
    enclosures.Add("Aquarium");
    enclosures.Add("Ocean Tank");
    enclosures.Add("Pond");
    enclosures.Add("Rainforest");
    enclosures.Add("Wetlands");
    enclosures.Add("Aviary");
    enclosures.Add("Terrarium");

    health_states.Add("Healthy");
    health_states.Add("Sick");
    health_states.Add("In Treatment");

    category_input_ = make_choice(this, categories);
    enclosure_input_ = make_choice(this, enclosures);
    health_input_ = make_choice(this, health_states);
    
    */


    // species dropdown is populated from Animal_Manager on startup (defaults to Mammal)
    // manager reads species.json — subclasses have no knowledge of the species list
    // GUI never hardcodes species; it always queries the manager
    wxArrayString initial_species;
    for (const auto &s : manager_->get_species_for_category("Mammal"))
    {
        initial_species.Add(s);
    };

    species_input_ = make_choice(this, initial_species);

    // when category changes, species dropdown is rebuilt from the matching subclass
    category_input_->Bind(wxEVT_CHOICE, &AddEditDialog::on_category_changed, this);

    // BUILDS LAYOUT - add all fields to layout
    std::vector<std::pair<wxString, wxWindow *>> fields =
        {
            {"Name:", name_input_},
            {"Category:", category_input_},
            {"Species:", species_input_},
            {"Age:", age_input_},
            {"Weight:", weight_input_},
            {"Enclosure:", enclosure_input_},
            {"Health:", health_input_},
        };

    for (auto &[label, input] : fields)
    {
        add_row(this, sizer, label, input);
    };

    // This empty sizer will hold our dynamically generated map fields, cleared and rebuilt whenever category changes
    dynamic_sizer_ = new wxBoxSizer(wxVERTICAL);
    sizer->Add(dynamic_sizer_, 1, wxEXPAND | wxALL, 0);

    // save/cancle btns
    wxButton* ok_btn = new wxButton(this, wxID_ANY, "Save");
    wxButton* cancel_btn = new wxButton(this, wxID_CANCEL, "Cancel");
    ok_btn->Bind(wxEVT_BUTTON, &AddEditDialog::on_ok, this);

    wxBoxSizer* btn_sizer = new wxBoxSizer(wxHORIZONTAL);
    btn_sizer->Add(cancel_btn, 0, wxRIGHT, 8);
    btn_sizer->Add(ok_btn, 0);
    sizer->AddSpacer(12);
    sizer->Add(btn_sizer, 0, wxALIGN_RIGHT | wxALL, 16);

    // edit mode - pre fill fields with existing animal data
    if (animal) 
    {
        name_input_->SetValue(animal->get_name());
        age_input_->SetValue(std::to_string(animal->get_age()));
        weight_input_->SetValue(wxString::Format("%.2f", animal->get_weight()));
        
        // set category first, then rebuild species list for that category
        category_input_->SetStringSelection(animal->get_category_to_string());
        wxCommandEvent fake_event;
        on_category_changed(fake_event); 
        species_input_->SetStringSelection(animal->get_species());
        
        enclosure_input_->SetStringSelection(animal->get_enclosure());
        health_input_->SetStringSelection(animal->get_health_status_to_string());
        
        // Build dynamic fields from the existing animal's map
        build_dynamic_fields(animal->get_special_info_map());
    } 
    else 
    {
        // Build dynamic fields using default template for a new Mammal
        build_dynamic_fields(manager_->get_default_traits("Mammal"));
    }

    SetSizer(sizer);
    Layout();
}

// getters
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

// VALIDATION 

// called when user clicks Save - validates input and closes dialog with wxID_OK
void AddEditDialog::on_ok(wxCommandEvent &event)
{
    if (name_input_->GetValue().IsEmpty())
    {
        wxMessageBox("Name and Species cannot be empty.", "Validation Error", wxICON_WARNING);
        return;
    }
    long age_val;
    if (!age_input_->GetValue().ToLong(&age_val) || age_val <= 0)
    {
        wxMessageBox("Age must be positive number.", "Validation Error", wxICON_WARNING);
        return;
    }
    double weight_val;
    if (!weight_input_->GetValue().ToDouble(&weight_val) || weight_val <= 0)
    {
        wxMessageBox("Weight must be positive number.", "Validation Error", wxICON_WARNING);
        return;
    }
    EndModal(wxID_OK);
}

// rebuilds the species dropdown by querying Animal_Manager for the selected category
void AddEditDialog::on_category_changed(wxCommandEvent &event)
{
    species_input_->Clear();
    std::string cat = category_input_->GetStringSelection().ToStdString();

    std::vector<std::string> species = manager_->get_species_for_category(cat);

    for (const auto &s : manager_->get_species_for_category(cat))
    {
        species_input_->Append(s);
    }

    // Safety check: only select 0 if the list isn't empty
    if (!manager_->get_species_for_category(cat).empty())
    {
        species_input_->SetSelection(0);
    }

    // Update dynamic fields ONLY if we are adding a NEW animal.
    // If editing, we keep the animal's existing map.
    if (!animal_editing_) 
    {
        build_dynamic_fields(manager_->get_default_traits(cat));
    }
}