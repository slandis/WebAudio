#ifndef CONTAINER_H
#define CONTAINER_H

#include "WebAudio.h"

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

    WebAudio *webAudio;

  private slots:
    void loadFinished(bool finished);
    void retry();
    void populateJavaScriptWindowObject();

  protected:
	void keyPressEvent(QKeyEvent *event);
};

#endif
