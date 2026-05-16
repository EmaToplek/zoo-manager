#include "detail_panel.hpp"

DetailPanel::DetailPanel(wxPanel* parent) : wxPanel(parent) 
{
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    //basic info section
    sizer->Add(new wxStaticText(this, wxID_ANY, "ANIMAL INFO"), 0, wxALL, 8);

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
        sizer->Add(new wxStaticText(this, wxID_ANY, label), 0, wxLEFT | wxTOP, 8);
        *val_ptr = new wxStaticText(this, wxID_ANY, ""); //creates new wxStaticText on heap and saves addr directly into name_val
        sizer->Add(*val_ptr, 0, wxLEFT | wxBOTTOM, 16);
    }
}