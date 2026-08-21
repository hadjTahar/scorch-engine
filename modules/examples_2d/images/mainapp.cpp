#include "mainapp.h"
#include "mainwindow.h"


MainApp::MainApp():
    Application{60, 30 }
{
    auto win = addItem<MainWindow>();
    win->properties.setSize( { 1200, 700 } );
    win->properties.setPosition( {100, 100 } );
}
