
#include "ListViewer.hpp"


ListViewer::ListViewer(QWidget* parent) 
	: QScrollArea(parent) {
	setup_ui();
}

void ListViewer::setup_ui() {
	setWidget(&_cont);
}
