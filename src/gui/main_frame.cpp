#include "main_frame.hpp"
#include "add_edit.hpp"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) 
{
    //creates animal manager and loads animals from data.json on startup
    animal_manager_ = new Animal_Manager();
    animal_manager_->load();

    //main panel that fills the entire window
    panel_ = new wxPanel(this);
    left_panel_ = new wxPanel(panel_);
    detail_panel_ = new DetailPanel(panel_);

    //aranges left and right panels side by side 
    wxBoxSizer* panel_sizer = new wxBoxSizer(wxHORIZONTAL);
        panel_sizer->Add(left_panel_, 2, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
        panel_sizer->Add(detail_panel_, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
        panel_->SetSizer(panel_sizer);
    
    //search field for filtering animals 
    wxTextCtrl* search_ = new wxTextCtrl(left_panel_, wxID_ANY);
    search_->SetHint("Search by name or species...");  

    //dropdown for categories
    wxArrayString category_choices;
    category_choices.Add("All categories");
    category_choices.Add("Mammal");
    category_choices.Add("Fish");
    category_choices.Add("Bird");
    category_choices.Add("Reptile");
    category_choices.Add("Amphibian");

    wxChoice* category_dropdown_ = new wxChoice(left_panel_, wxID_ANY, wxPoint(50, 50), wxSize(200, 30), category_choices);
    category_dropdown_->SetSelection(0);

    //dropdown for statuses
    wxArrayString status_choices;
    status_choices.Add("All statuses");
    status_choices.Add("Healthy");
    status_choices.Add("In Treatment");
    status_choices.Add("Sick");

    wxChoice* status_dropdown_ = new wxChoice(left_panel_, wxID_ANY, wxPoint(50, 50), wxSize(200, 30), status_choices);
    status_dropdown_->SetSelection(0);

    //panel holding add, edit,remove btns in row
    wxPanel* button_panel_ = new wxPanel(left_panel_);
    
    add_button_ = new wxButton(button_panel_, wxID_ANY, "+Add animal", wxDefaultPosition, wxDefaultSize);
    edit_button_ = new wxButton(button_panel_, wxID_ANY, "Edit",  wxDefaultPosition, wxDefaultSize);
    edit_button_->Disable();

    remove_button_ = new wxButton(button_panel_, wxID_ANY, "Remove", wxDefaultPosition, wxDefaultSize);
    remove_button_->Disable();

    wxBoxSizer* button_panel_sizer = new wxBoxSizer(wxHORIZONTAL);
    button_panel_sizer->Add(add_button_, 0,wxLEFT, 10);
    button_panel_sizer->Add(edit_button_, 0,wxLEFT, 10);
    button_panel_sizer->Add(remove_button_, 0,wxLEFT, 10);
    button_panel_->SetSizer(button_panel_sizer);

    //table showing all animals with columns
    table_ = new wxListCtrl(left_panel_,wxID_ANY, wxDefaultPosition, wxSize(700, 400), wxLC_REPORT);
    table_->AppendColumn("Name", wxLIST_FORMAT_LEFT, 100);
    table_->AppendColumn("Species", wxLIST_FORMAT_LEFT, 100);
    table_->AppendColumn("Category", wxLIST_FORMAT_LEFT, 100);
    table_->AppendColumn("Age", wxLIST_FORMAT_LEFT, 100);
    table_->AppendColumn("Weight", wxLIST_FORMAT_LEFT, 100);
    table_->AppendColumn("Enclosure", wxLIST_FORMAT_LEFT, 100);
    table_->AppendColumn("Health", wxLIST_FORMAT_LEFT, 100);
    
    //fetches all animals from the manager and populates the table
    const std::vector<Animal*> animals = animal_manager_->get_all_animals();
    fill_table(animals);

    // bind list row click to detail panel update
    table_->Bind(wxEVT_LIST_ITEM_SELECTED, &MainFrame::on_animal_selected, this);

    // bind deselect to clear detail panel
    table_->Bind(wxEVT_LIST_ITEM_DESELECTED, &MainFrame::on_animal_deselected, this);
    
    remove_button_->Bind(wxEVT_BUTTON, &MainFrame::on_remove_animal, this);
    edit_button_->Bind(wxEVT_BUTTON, &MainFrame::on_edit_animal, this); 
    add_button_->Bind(wxEVT_BUTTON, &MainFrame::on_add_animal, this); 

    
    //stacks all left animals from the manager and populates the table
    wxBoxSizer* left_panel_sizer = new wxBoxSizer(wxVERTICAL);
        left_panel_sizer->Add(search_, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
        left_panel_sizer->Add(category_dropdown_, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
        left_panel_sizer->Add(status_dropdown_, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
        left_panel_sizer->Add(button_panel_, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
        left_panel_sizer->Add(table_, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
        left_panel_->SetSizer(left_panel_sizer);
    
    //status bar at the bottom of the window
    CreateStatusBar();
    SetStatusText("Hello");
        
}


//reads from animal_manager and draw table
void MainFrame::fill_table(const std::vector<Animal*> animals)
{

    table_->DeleteAllItems();

    for(Animal* animal : animals){
        long index = table_->InsertItem(table_->GetItemCount(), animal->get_name());
        table_->SetItem(index, 1, animal->get_species());
        table_->SetItem(index, 2, animal->get_category_to_string());
        table_->SetItem(index, 3, std::to_string(animal->get_age()));
        table_->SetItem(index, 4, std::to_string(animal->get_weight()));
        table_->SetItem(index, 5, animal->get_enclosure());
        table_->SetItem(index, 6, animal->get_health_status_to_string());
    }
    table_->Refresh();
     
}

// called when user clicks a row in the animal list
// fetches the corresponding animal from the manager and updates the detail panel
void MainFrame::on_animal_selected(wxListEvent& event)
{
    long index = event.GetIndex(); //getIndex() returns clicked row
    Animal* selected = animal_manager_->get_all_animals()[index];
    detail_panel_->show_animal(selected);

    selected_index_ = event.GetIndex();
    edit_button_->Enable();
    remove_button_->Enable();
}

// called when user clicks empty space in the list — clears the detail panel
void MainFrame::on_animal_deselected(wxListEvent& event)
{
    selected_index_ = -1;
    edit_button_->Disable();
    remove_button_->Disable();

    detail_panel_->clear();
}

void MainFrame::on_remove_animal(wxCommandEvent& event) 
{
    //get animal on remembered index
    Animal* selected = animal_manager_->get_all_animals()[selected_index_];

    // show confirmation dialog
    wxString msg = wxString::Format("Are you sure you want to remove %s?", selected->get_name());
    wxMessageDialog dialog(this, msg, "Confirm Remove", wxYES_NO | wxNO_DEFAULT | wxICON_WARNING);
    
    //if confirmed delete
    if(dialog.ShowModal() == wxID_YES) 
    {
        animal_manager_->remove_animal(selected->get_id());
        animal_manager_->save();
        fill_table(animal_manager_->get_all_animals());
        detail_panel_->clear();
        remove_button_->Disable();
        selected_index_ = -1;
    }
}

// called when user clicks Add animal 
// opens emty dialog and creates new animal on save
void MainFrame::on_add_animal(wxCommandEvent& event) 
{ 
    AddEditDialog dialog(this, nullptr); 

    if(dialog.ShowModal() == wxID_OK) 
    {
        uint64_t new_id = animal_manager_->get_all_animals().size() + 1;
        animal_manager_->add_animal(new_id, dialog.get_name().ToStdString(), dialog.get_species().ToStdString(), dialog.get_category().ToStdString(),
                                    dialog.get_age(), dialog.get_weight(), dialog.get_enclosure().ToStdString(), dialog.get_health().ToStdString()); 
        
        animal_manager_->save();
        fill_table(animal_manager_->get_all_animals());
    }
}

// called when user clicks edit
// opens dialog pre-filled with selected animals data and updates it on save
void MainFrame::on_edit_animal(wxCommandEvent& event) 
{
    Animal* selected = animal_manager_->get_all_animals()[selected_index_];
    AddEditDialog dialog(this, selected);

    if(dialog.ShowModal() == wxID_OK)
    {
        selected->set_name(dialog.get_name().ToStdString());
        selected->set_species(dialog.get_species().ToStdString());
        selected->set_age(dialog.get_age());
        selected->set_weight(dialog.get_weight());
        selected->set_enclosure(dialog.get_enclosure().ToStdString());

        std::string h = dialog.get_health().ToStdString();
        if (h == "Healthy") 
        {
            selected->set_health_status(HealthStatus::Healthy);
        }
        else if (h == "Sick") 
        {
            selected->set_health_status(HealthStatus::Sick);
        } 
        else 
        {
            selected->set_health_status(HealthStatus::In_Treatment);
        }

        animal_manager_->save();
        fill_table(animal_manager_->get_all_animals());
        detail_panel_->show_animal(selected);
    }
}