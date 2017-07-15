/*
 * WebAudio - Container.cpp
 * Copyright (C) 2017
 * Shaun Landis <slandis@github>
 * Ian Firns <firnsy@github>
 */

#include "Container.h"
#include "Audio.h"

#include <QScroller>

Container::Container(QWidget *parent) : QWebView(parent) {
  audio = new Audio(this);
  connect(this, SIGNAL(loadFinished(bool)), this, SLOT(loadFinished(bool)));
  connect(this->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(populateJavaScriptWindowObject()));

  QScroller::grabGesture(this, QScroller::LeftMouseButtonGesture);
  QScroller::grabGesture(this, QScroller::TouchGesture);

  splash = new QWidget(this);
  splash->setStyleSheet("background-color: #000");
  splash->setFixedSize(this->size());

  this->setWindowFlags(Qt::FramelessWindowHint);
  this->setAttribute(Qt::WA_AcceptTouchEvents, true);
  this->setScrollBars();
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
  this->page()->mainFrame()->addToJavaScriptWindowObject(QString("Audio"), audio);
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
