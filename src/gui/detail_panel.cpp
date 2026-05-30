#include <wx/statline.h>
#include "detail_panel.hpp"

#include <sstream>
#include <iomanip>

// Sets the font size and weight on a given wxStaticText widget
void DetailPanel::set_font(wxStaticText* widget, int size, bool bold) 
{
    wxFont font = widget->GetFont();
    font.SetPointSize(size);
    font.SetWeight(bold ? wxFONTWEIGHT_BOLD : wxFONTWEIGHT_NORMAL);
    widget->SetFont(font);
}

// builds a coloured stat box: label on top, big number below
wxPanel* DetailPanel::make_stat_box(const wxString& label, wxStaticText** out_val, const wxColour& bg, const wxColour& fg)
{
    wxPanel* box = new wxPanel(this);
    box->SetBackgroundColour(bg);
 
    wxStaticText* lbl = new wxStaticText(box, wxID_ANY, label, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
    set_font(lbl, 9, false);
    lbl->SetForegroundColour(fg);
 
    *out_val = new wxStaticText(box, wxID_ANY, "0", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
    set_font(*out_val, 20, true);
    (*out_val)->SetForegroundColour(fg);
 
    wxBoxSizer* s = new wxBoxSizer(wxVERTICAL);
    s->AddStretchSpacer(1);
    s->Add(lbl, 0, wxEXPAND | wxLEFT | wxRIGHT, 4);
    s->Add(*out_val, 0, wxEXPAND | wxLEFT | wxRIGHT, 4);
    s->AddStretchSpacer(1);
    box->SetSizer(s);
    box->SetMinSize(wxSize(70, 64));
    return box;
}

DetailPanel::DetailPanel(wxWindow* parent) : wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL)
{
    SetBackgroundColour(wxColour(240, 230, 210));
    SetScrollRate(0, 12);

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

    for (auto& [label, val_ptr] : fields) 
    {
        wxStaticText* field_label = new wxStaticText(this,  wxID_ANY, label);
        set_font(field_label, 13, true); 
        field_label->SetForegroundColour(wxColour(120, 85, 45)); 
        sizer->Add(field_label, 0, wxLEFT | wxTOP, 16);

        *val_ptr = new wxStaticText(this, wxID_ANY, ""); //creates new wxStaticText on heap and saves addr directly into name_val
        set_font(*val_ptr, 13, false);
        (*val_ptr)->SetForegroundColour(wxColour(80, 60, 30));
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
        (*val_ptr)->SetForegroundColour(wxColour(80, 60, 30));  
        sizer->Add(*val_ptr, 0, wxLEFT | wxBOTTOM, 16);
    }

    // overview section 
    sizer->AddSpacer(12);
    sizer->Add(new wxStaticLine(this), 0, wxEXPAND | wxLEFT | wxRIGHT, 16);
    sizer->AddSpacer(6);

    wxStaticText* overview_title = new wxStaticText(this, wxID_ANY, "Overview");
    set_font(overview_title, 15, true);
    overview_title->SetForegroundColour(wxColour(60, 100, 50));
    sizer->Add(overview_title, 0, wxALL, 12);
 
    // 2x2 grid of stat boxes
    wxGridSizer* grid = new wxGridSizer(2, 2, 8, 8);
    grid->Add(make_stat_box("Total", &stat_total_val_, wxColour(200, 190, 170), wxColour(60, 40, 20)), 0, wxEXPAND);
    grid->Add(make_stat_box("Healthy", &stat_healthy_val_, wxColour(173, 247, 180), wxColour(8, 45, 12)), 0, wxEXPAND);
    grid->Add(make_stat_box("Sick", &stat_sick_val_, wxColour(239, 93, 132), wxColour(63,  13,  26)), 0, wxEXPAND);
    grid->Add(make_stat_box("In Treatment", &stat_treatment_val_, wxColour(237, 221, 45), wxColour(63, 59, 12)), 0, wxEXPAND);
 
    sizer->Add(grid, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 16);
  
    SetSizer(sizer);
    clear();
}

// Populates the detail panel with data from the selected animal
// Calls virtual methods so the correct subclass version is always used
void DetailPanel::show_animal(Animal* animal) 
{
    placeholder_->Hide();

    std::ostringstream weight_oss;
    weight_oss << std::fixed << std::setprecision(2) << animal->get_weight();

    std::ostringstream enclosure_oss;
    enclosure_oss << std::fixed << std::setprecision(1) << animal->get_min_enclosure_size();

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
        {enclosure_size_val_, wxString::Format("%.1f m2", animal->get_min_enclosure_size())},
        {special_info_val_, animal->get_special_info()},
    };

    for (auto& [widget, value] : values) 
    {
        widget->SetLabel(value);
    }
   
    if (animal->get_health_status() == HealthStatus::Healthy) 
    {
        health_val_->SetForegroundColour(wxColour(34, 139, 34));
    }
    else if (animal->get_health_status() == HealthStatus::Sick) 
    {
        health_val_->SetForegroundColour(wxColour(180, 0, 0));
    }
    else 
    {
        health_val_->SetForegroundColour(wxColour(200, 120, 0));
    }

    health_val_->Refresh();

    FitInside();
    Layout();
}

void DetailPanel::update_stats(uint64_t total, uint64_t healthy, uint64_t sick, uint64_t in_treatment)
{
    stat_total_val_->SetLabel(std::to_string(total));
    stat_healthy_val_->SetLabel(std::to_string(healthy));
    stat_sick_val_->SetLabel(std::to_string(sick));
    stat_treatment_val_->SetLabel(std::to_string(in_treatment));
    Layout();
}



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
    {
        val->SetLabel("");
    }

    FitInside();
    Layout();
}