#include <QApplication>
#include "sejtablak.h"
#include <QDesktopWidget>

/*
fordítása: qmake Sejtauto.pro
           make
majd futtatása:
            ./Sejtauto
*/
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  SejtAblak w(100, 75);
  w.show();
  
  return a.exec();
}
