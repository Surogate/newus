
#ifndef LISTVIEWER_HPP
#define LISTVIEWER_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>

class Container : public QWidget 
{
	Q_OBJECT

public:
	Container() : QWidget(0) {
		setup_ui();
	}

	void push(QWidget* widget) {
		_layout.addWidget(widget);
	}

	void pop() {
		_layout.takeAt(_layout.count() - 1);
	}

	void clear() {
		while (_layout.count())
			_layout.takeAt(0);
	}

private:
	QVBoxLayout _layout;

	void setup_ui() {
		setLayout(&_layout);
	}
};

class ListViewer : public QScrollArea {
	Q_OBJECT

public:
	ListViewer(QWidget* parent = 0);

	template <typename T>
	void operator()(QList< T >& data) {
		typename QList< T >::iterator it = data.begin();
		typename QList< T >::iterator ite = data.end();

		while (it != ite) {
			_cont.push(&(*it));
			++it;
		}
	}
private:
	Container _cont;

	void setup_ui();
};

#endif /* LISTVIEWER_HPP */