/*
 * WebAudio - Container.h
 * Copyright (C) 2017
 * Shaun Landis <slandis@github>
 * Ian Firns <firnsy@github>
 */

#ifndef CONTAINER_H
#define CONTAINER_H

#include "Audio.h"

#include <QtWebKitWidgets>
#include <QKeyEvent>

class Container : public QWebView {
    Q_OBJECT

  public:
    explicit Container(QWidget *parent = 0);

    void load(const QUrl &url);
    void setFixedSize(int width, int height);
    void setScrollBars();

    ~Container();

  private:
    QWidget *splash;
    QUrl    url;
    bool    verbose;

    Audio *audio;

  private slots:
    void loadFinished(bool finished);
    void retry();
    void populateJavaScriptWindowObject();

  protected:
	void keyPressEvent(QKeyEvent *event);
};

#endif
