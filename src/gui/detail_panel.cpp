#include <wx/statline.h>
#include "detail_panel.hpp"

// Sets the font size and weight on a given wxStaticText widget
void DetailPanel::set_font(wxStaticText* widget, int size, bool bold) 
{
    wxFont font = widget->GetFont();
    font.SetPointSize(size);
    font.SetWeight(bold ? wxFONTWEIGHT_BOLD : wxFONTWEIGHT_NORMAL);
    widget->SetFont(font);
}

DetailPanel::DetailPanel(wxPanel* parent) : wxPanel(parent) 
{
    SetBackgroundColour(wxColour(240, 230, 210));

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    //basic info section
    wxStaticText* title = new wxStaticText(this, wxID_ANY, "Animal Info");
    set_font(title, 18, true);
    title->SetForegroundColour(wxColour(60, 100, 50));
    sizer->Add(title, 0, wxALL, 12);
    sizer->Add(new wxStaticLine(this), 0, wxEXPAND | wxLEFT | wxRIGHT, 16);
    sizer->AddSpacer(6);

    //info message if no animal is selected
    placeholder_ = new wxStaticText(this, wxID_ANY, "Select an animal to view details");
    set_font(placeholder_, 13, false);
    placeholder_->SetForegroundColour(wxColour(150, 120, 80));
    sizer->Add(placeholder_, 0, wxALL, 12); 

    std::vector<std::pair<std::string, wxStaticText**>> fields = 
    {
      {"Name:", &name_val_},
      {"Species:", &species_val_},
      {"Category:", &category_val_},
      {"Age:", &age_val_},
      {"Weight:", &weight_val_},
      {"Enclosure:",&enclosure_val_},
      {"Health:", &health_val_},
    };

    for (auto& [label, val_ptr] : fields ) 
    {
        wxStaticText* field_label = new wxStaticText(this,  wxID_ANY, label);
        set_font(field_label, 13, true); 
        field_label->SetForegroundColour(wxColour(120, 85, 45)); 
        sizer->Add(field_label, 0, wxLEFT | wxTOP, 16);

        *val_ptr = new wxStaticText(this, wxID_ANY, ""); //creates new wxStaticText on heap and saves addr directly into name_val
        set_font(*val_ptr, 13, false);
        sizer->Add(*val_ptr, 0, wxLEFT | wxBOTTOM, 16);
    }

    //species details 
    sizer->AddSpacer(12);
    sizer->Add(new wxStaticLine(this), 0, wxEXPAND | wxLEFT | wxRIGHT, 16);
    sizer->AddSpacer(6);

    wxStaticText* sub_title = new wxStaticText(this, wxID_ANY, "Species Details");
    set_font(sub_title, 15, true);
    sub_title->SetForegroundColour(wxColour(60, 100, 50));
    sizer->Add(sub_title, 0, wxALL, 12);

    std::vector<std::pair<std::string, wxStaticText**>> subclass_fields = 
    {
        {"Feeding type:", &feeding_val_},
        {"Habitat:", &habitat_val_},
        {"Min enclosure size:", &enclosure_size_val_},
        {"Special info:", &special_info_val_},
    };

    for (auto& [label, val_ptr] : subclass_fields) 
    {
        wxStaticText* subclass_label = new wxStaticText(this,  wxID_ANY, label);
        set_font(subclass_label, 13, true); 
        subclass_label->SetForegroundColour(wxColour(120, 85, 45)); 
        sizer->Add(subclass_label, 0, wxLEFT | wxTOP, 16);

        *val_ptr = new wxStaticText(this, wxID_ANY, ""); 
        set_font(*val_ptr, 13, false);
        sizer->Add(*val_ptr, 0, wxLEFT | wxBOTTOM, 16);
    }


    SetSizer(sizer);
    clear();
}

// Populates the detail panel with data from the selected animal
// Calls virtual methods so the correct subclass version is always used
void DetailPanel::show_animal(Animal* animal) 
{
    placeholder_->Hide();

    //widget, value pair
    std::vector<std::pair<wxStaticText*, wxString>> values = 
    {
        {name_val_, animal->get_name()},
        {species_val_, animal->get_species()},
        {category_val_, animal->get_category_to_string()},
        {age_val_, std::to_string(animal->get_age()) + " years"},
        {weight_val_, wxString::Format("%.2f kg", animal->get_weight())},
        {enclosure_val_, animal->get_enclosure()},
        {health_val_, animal->get_health_status_to_string()},
        {feeding_val_, animal->get_feeding_type()},
        {habitat_val_, animal->get_habitat()},
        {enclosure_size_val_, wxString::Format("%.1f m²", animal->get_min_enclosure_size())},
        {special_info_val_, animal->get_special_info()},
    };

    for (auto& [widget, value] : values)
    widget->SetLabel(value);
}

//TO-DO  HEALTH STATUS WITH COLORS

void DetailPanel::clear()
{
    placeholder_->Show();

    std::vector<wxStaticText*> all_vals = 
    {
        name_val_, species_val_, category_val_, age_val_,
        weight_val_, enclosure_val_, health_val_, feeding_val_,
        habitat_val_, enclosure_size_val_, special_info_val_
    };

    for (auto* val : all_vals)
        val->SetLabel("");

    Layout();
}
