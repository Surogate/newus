
#include <QtGui/QApplication>
#include "Newusgui.hpp"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	NewusGui w;
	w.show();

	return a.exec();
}

