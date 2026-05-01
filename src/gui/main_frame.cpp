#include "main_frame.hpp"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title){


    panel_ = new wxPanel(this);
}
