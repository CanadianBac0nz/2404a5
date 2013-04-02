///////////////////////////////////////////////////////////////////////////////////////
// ONE ASSIGNED APPLICATION WINDOW
// Shows a list of assigned applications for one course, sorted by course

#include <fstream>

#include "OneAssignedUI.h"
#include "SelectCrsUI.h"
#include "UGradApp.h"
#include "GradApp.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
OneAssignedUI::OneAssignedUI(Manager* aManager, string crs) 
: OneReportUI(aManager, crs),
  aTable(3, 3, false),
  aLabel("List of assigned applications sorted by Research Area and Major GPA for " + crs),
  backButton("Back"),
  cancelButton("Cancel"),
  saveButton("Save")
{
  manager = aManager;
  course = crs;

  // Scrolled window settings
  scrolledWindow.set_border_width(5);
  scrolledWindow.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS); 

  fillSummary(ASSIGNED);

  scrolledWindow.add(summary);

  aTable.attach(aLabel, 0, 2, 0, 1,Gtk::EXPAND,Gtk::FILL,0,10);
  aTable.attach(scrolledWindow, 0, 3, 1, 2);
  aTable.attach(backButton, 0, 1, 2, 3,Gtk::FILL,Gtk::FILL,40,50);
  aTable.attach(cancelButton, 2, 3, 2, 3,Gtk::FILL,Gtk::FILL,40,50);
  aTable.attach(saveButton, 1, 2, 2, 3,Gtk::FILL,Gtk::FILL,40,50);

  add(aTable);

  backButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &OneAssignedUI::on_backButton), "Back") );
  cancelButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &OneAssignedUI::on_cancelButton), "Cancel") );
  saveButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &OneAssignedUI::on_saveButton), "Save") );

  show_all_children();

  //cout << "CONSTRUCT OneAssignedUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
OneAssignedUI::~OneAssignedUI() {
  //cout << "DESTRUCT OneAssignedUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Event handler for the back button
void OneAssignedUI::on_backButton(const Glib::ustring& data){
  SelectCrsUI* selectWin = new SelectCrsUI(manager, 1); 
  selectWin->show();
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Event handler for the save button
void OneAssignedUI::on_saveButton(const Glib::ustring& data){
  string cn = "./AppSummaries/AssignedByCrs/" + course;
  int i =0;

  // Create an output file
  ofstream outFile(cn.c_str(), ios::out); 
  if (!outFile)
    cout << "Could not open file" << endl;

  // Output application information to permanent storage
  outFile << "*NEW SUMMARY OF ASSIGNED APPLICATIONS FOR "<< course << "*" << endl;
  for ( i =0; i< summary.size(); i++){
    if (summary.get_text(i,0) == "UNDERGRADS") {
      outFile << endl;
      outFile << "-------- UNDERGRADS --------";
      outFile << endl;
      continue;
    }
    if (summary.get_text(i,0) == "GRADS") {
      outFile << endl;
      outFile << "---------- GRADS -----------";
      outFile << endl;
      continue;
    }
    if (summary.get_text(i,0) == "No Undergrad applications for this course." ||
        summary.get_text(i,0) == "No Grad applications for this course." ) {
      outFile << endl;
      outFile << summary.get_text(i,0) << endl;
      outFile << endl;
      continue;
    }
    outFile << endl;
    outFile << summary.get_text(i,0) << endl;
    outFile << summary.get_text(i,1) << endl;
    outFile << summary.get_text(i,2) << endl;
    outFile << summary.get_text(i,3) << endl;
    outFile << summary.get_text(i,4) << endl;
    outFile << summary.get_text(i,5) << endl;
    outFile << summary.get_text(i,6) << endl;
    outFile << summary.get_text(i,7) << endl;
  }
  outFile << endl;
  saveDialog();
}

