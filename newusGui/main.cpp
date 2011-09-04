
#include <QtGui/QApplication>
#include "newusgui.hpp"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	newusGui w;
	w.show();

	return a.exec();
}

