
#include "../NeoCrowdLib/NeoCrowdLib.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    RunRecongizeService("/home/yy/Browse1.mpg","300,150,450,150,450,50,300,50","/home/yy/1.mpg");
    cout << "mainfninish"<<endl;
    return 0;
    //return a.exec();
}
