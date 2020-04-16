#include "mainwindow.h"

int main(int argc, char *argv[]) {
    
  QApplication app(argc, argv);  
    
  MainWindow window;

//  window.resize(350, 250);
  window.setWindowTitle("Main window");
  window.show();

  return app.exec();
}
