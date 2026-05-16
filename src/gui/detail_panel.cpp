#include <wx/statline.h>
#include "detail_panel.hpp"


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
    set_font(title, 16, true);
    title->SetForegroundColour(wxColour(60, 100, 50));
    sizer->Add(title, 0, wxALL, 12);
    sizer->Add(new wxStaticLine(this), 0, wxEXPAND | wxLEFT | wxRIGHT, 8);
    sizer->AddSpacer(6);

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
        set_font(field_label, 12, false); 
        field_label->SetForegroundColour(wxColour(120, 85, 45)); 
        sizer->Add(field_label, 0, wxLEFT | wxTOP, 8);

        *val_ptr = new wxStaticText(this, wxID_ANY, ""); //creates new wxStaticText on heap and saves addr directly into name_val
        set_font(*val_ptr, 11, true);
        sizer->Add(*val_ptr, 0, wxLEFT | wxBOTTOM, 2);
    }

    //species details 
    sizer->AddSpacer(12);
    sizer->Add(new wxStaticLine(this), 0, wxEXPAND | wxLEFT | wxRIGHT, 8);
    sizer->AddSpacer(6);

    wxStaticText* sub_title = new wxStaticText(this, wxID_ANY, "Species Details");
    set_font(sub_title, 13, true);
    sub_title->SetForegroundColour(wxColour(60, 100, 50));
    sizer->Add(sub_title, 0, wxALL, 12);

    std::vector<std::pair<std::string, wxStaticText**>> subcalss_fields = 
    {
        {"Feeding type:", &feeding_val_},
        {"Habitat:", &habitat_val_},
        {"Min enclosure size:", &enclosure_size_val_},
        {"Special info:", &special_info_val_},
    };

    for (auto& [label, val_ptr] : subcalss_fields) 
    {
        wxStaticText* subclass_label = new wxStaticText(this,  wxID_ANY, label);
        set_font(subclass_label, 12, false); 
        subclass_label->SetForegroundColour(wxColour(120, 85, 45)); 
        sizer->Add(subclass_label, 0, wxLEFT | wxTOP, 8);

        *val_ptr = new wxStaticText(this, wxID_ANY, ""); 
        set_font(*val_ptr, 11, true);
        sizer->Add(*val_ptr, 0, wxLEFT | wxBOTTOM, 2);
    }


    SetSizer(sizer);

}