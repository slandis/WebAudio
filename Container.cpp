/*
 * WebAudio - Container.cpp
 * Copyright (C) 2017
 * Shaun Landis <slandis@github>
 * Ian Firns <firnsy@github>
 */

#include "Container.h"
#include "Audio.h"

#include <QScroller>
#include <QVBoxLayout>

Container::Container(QWidget *parent) : QWebView(parent) {
  audio = new Audio(this);
  connect(this, SIGNAL(loadFinished(bool)), this, SLOT(loadFinished(bool)));
  connect(this->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(populateJavaScriptWindowObject()));

  QScroller::grabGesture(this, QScroller::LeftMouseButtonGesture);
  QScroller::grabGesture(this, QScroller::TouchGesture);

  QWebSettings::globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);

  splash = new QWidget(this);
  splash->setStyleSheet("background-color: #000");
  splash->setFixedSize(this->size());

  this->setWindowFlags(Qt::FramelessWindowHint);
  this->setAttribute(Qt::WA_AcceptTouchEvents, true);
  this->setScrollBars();

  /* The following is mostly broken. It steals the input and you can't return. Handy for debug though */
  inspector = new QWebInspector();
  inspector->hide();
  inspector->setPage(this->page());

  QShortcut *ins = new QShortcut(QKeySequence(Qt::Key_F7), this);
  connect(ins, SIGNAL(activated()), this, SLOT(showHideInspector()));
}

void Container::load(const QUrl &url) {
  this->url = url;
  QWebView::load(this->url);
}

void Container::setFixedSize(int width, int height) {
  QWebView::setFixedSize(width, height);
  splash->setFixedSize(width, height);
}

void Container::populateJavaScriptWindowObject() {
  this->page()->mainFrame()->addToJavaScriptWindowObject(QString("audio"), audio);
}

void Container::setScrollBars() {
  this->page()->mainFrame()->setScrollBarPolicy(Qt::Vertical,   Qt::ScrollBarAlwaysOff);
  this->page()->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
}

void Container::loadFinished(bool finished) {
  if (finished) {
    splash->hide();
  } else {
    QTimer::singleShot(1000, this, SLOT(retry()));
  }
}

void Container::retry() {
  QWebView::load(this->url);
}

void Container::showHideInspector() {
  inspector->setVisible(inspector->isHidden());
}

Container::~Container() {
  delete splash;
}

void Container::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
    case Qt::Key_X:
      close();
      break;

    case Qt::Key_R:
      reload();
      break;

    case Qt::Key_Left:
      back();
      break;
  }
}
