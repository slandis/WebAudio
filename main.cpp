#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>

#include "container.h"

#define DEFAULT_NAME     "WebKit+Audio"
#define DEFAULT_VERSION  "0.1"

#define DEFAULT_URL      "http://localhost:3000"

#define DEFAULT_WIDTH    800
#define DEFAULT_HEIGHT   480


int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  app.setApplicationName(DEFAULT_NAME);
  app.setApplicationVersion(DEFAULT_VERSION);
  app.setAttribute(Qt::AA_SynthesizeMouseForUnhandledTouchEvents);

  QCursor cursor(Qt::BlankCursor);
  app.setOverrideCursor(cursor);
  app.changeOverrideCursor(cursor);

  int height = DEFAULT_HEIGHT;
  int width = DEFAULT_WIDTH;
  QString url = DEFAULT_URL;

  Container container;

  container.setFixedSize(width, height);
  container.setScrollBars();
  container.load(QUrl(url));
  container.show();

  return app.exec();
}
