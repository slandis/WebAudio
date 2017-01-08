#include "WebAudio.h"

#include <QtWebKitWidgets>
#include <QMediaService>
#include <QMediaPlaylist>
#include <QMediaMetaData>
#include <QFileInfo>
#include <QJsonObject>
#include <QJsonDocument>

WebAudio::WebAudio(QWidget *parent) : QWidget(parent) {
  _player = new QMediaPlayer(this);
  _playlist = new QMediaPlaylist();
  _player->setPlaylist(_playlist);

  /* QMediaPlayer */
  connect(_player, SIGNAL(audioAvailableChanged(bool)), SLOT(audioAvailableChanged(bool)));
  connect(_player, SIGNAL(bufferStatusChanged(int)), SLOT(bufferStatusChanged(int)));
  connect(_player, SIGNAL(currentMediaChanged(const QMediaContent)), SLOT(currentMediaChanged(const QMediaContent)));
  connect(_player, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));
  connect(_player, SIGNAL(error(QMediaPlayer::Error)), SLOT(error(QMediaPlayer::Error)));
  connect(_player, SIGNAL(mediaChanged(const QMediaContent)), SLOT(mediaChanged(const QMediaContent)));
  connect(_player, SIGNAL(metaDataChanged()), SLOT(metaDataChanged()));
  connect(_player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), SLOT(mediaStatusChanged(QMediaPlayer::MediaStatus)));
  connect(_player, SIGNAL(metaDataAvailableChanged(bool)), SLOT(metaDataAvailableChanged(bool)));
  connect(_player, SIGNAL(mutedChanged(bool)), SLOT(mutedChanged(bool)));
  connect(_player, SIGNAL(notifyIntervalChanged(int)), SLOT(notifyIntervalChanged(int)));
  connect(_player, SIGNAL(playbackRateChanged(qreal)), SLOT(playbackRateChanged(qreal)));
  connect(_player, SIGNAL(positionChanged(qint64)), SLOT(positionChanged(qint64)));
  connect(_player, SIGNAL(seekableChanged(bool)), SLOT(seekableChanged(bool)));
  connect(_player, SIGNAL(stateChanged(QMediaPlayer::State)), SLOT(stateChanged(QMediaPlayer::State)));
  connect(_player, SIGNAL(volumeChanged(int)), SLOT(volumeChanged(int)));

  /* QMediaPlaylist */
  connect(_playlist, SIGNAL(currentIndexChanged(int)), SLOT(currentIndexChanged(int)));
  connect(_playlist, SIGNAL(mediaAboutToBeInserted(int, int)), SLOT(mediaAboutToBeInserted(int, int)));
  connect(_playlist, SIGNAL(mediaAboutToBeRemoved(int, int)), SLOT(mediaAboutToBeRemoved(int, int)));
  connect(_playlist, SIGNAL(mediaInserted(int, int)), SLOT(mediaInserted(int, int)));
  connect(_playlist, SIGNAL(mediaRemoved(int, int)), SLOT(mediaRemoved(int, int)));
  connect(_playlist, SIGNAL(playbackModeChanged(QMediaPlaylist::PlaybackMode)), SLOT(playbackModeChanged(QMediaPlaylist::PlaybackMode)));
}

WebAudio::~WebAudio() {
  ;
}

/* QMediaPlayer functions */
int WebAudio::bufferStatus() {
  return _player->bufferStatus();
}

QString WebAudio::currentMedia() {
  return _player->currentMedia().canonicalUrl().toString();
}

qint64 WebAudio::duration() {
  return _player->duration();
}

QMediaPlayer::Error WebAudio::error() {
  return _player->error();
}

QString WebAudio::errorString() {
  return _player->errorString();
}

bool WebAudio::isAudioAvailable() {
  return _player->isAudioAvailable();
}

bool WebAudio::isMetaDataAvailable() {
  return _player->isMetaDataAvailable();
}

bool WebAudio::isMuted() {
  return _player->isMuted();
}

bool WebAudio::isSeekable() {
  return _player->isSeekable();
}

QString WebAudio::media() {
  return _player->media().canonicalUrl().toString();
}

QMediaPlayer::MediaStatus WebAudio::mediaStatus() {
  return _player->mediaStatus();
}

QString WebAudio::metaData() {
  QJsonObject data;

  if (_player->isMetaDataAvailable()) {
    if (_player->availableMetaData().contains(QString("ContributingArtist"))) {
      data["artist"] = _player->metaData(QMediaMetaData::ContributingArtist).toStringList().at(0);
    }

    if (_player->availableMetaData().contains(QString("AlbumTitle"))) {
      data["album"] = _player->metaData(QMediaMetaData::AlbumTitle).toString();
    }

    if (_player->availableMetaData().contains(QString("Title"))) {
      data["title"] = _player->metaData(QMediaMetaData::Title).toString();
    }

    if (_player->availableMetaData().contains(QString("Year"))) {
      data["year"] = _player->metaData(QMediaMetaData::Year).toInt();
    }
  }

  QJsonDocument doc(data);
  return QString(doc.toJson(QJsonDocument::Compact));
}

int WebAudio::notifyInterval() {
  return _player->notifyInterval();
}

qreal WebAudio::playbackRate() {
  return _player->playbackRate();
}

QStringList WebAudio::playlist() {
  QStringList list;

  for (int i = 0; i < _playlist->mediaCount(); i++) {
    list.append(_playlist->media(i).canonicalUrl().toString());
  }

  return list;
}

qint64 WebAudio::position() {
  return _player->position();
}

QMediaPlayer::State WebAudio::state() {
  return _player->state();
}

int WebAudio::volume() {
  return _player->volume();
}

/* QMediaPlayer Slots */
void WebAudio::pause() {
  _player->pause();
}

void WebAudio::play() {
  _player->play();
}

void WebAudio::setMedia(const QStringList &list) {
  _playlist->clear();

  foreach (const QString &item, list) {
    QFileInfo file(item);

    if (file.exists()) {
      _playlist->addMedia(QUrl::fromLocalFile(file.absoluteFilePath()));
    }
  }
}

void WebAudio::setMuted(bool muted) {
  _player->setMuted(muted);
}

void WebAudio::setNotifyInterval(int millis) {
  _player->setNotifyInterval(millis);
}

void WebAudio::setPlaybackRate(qreal rate) {
  _player->setPlaybackRate(rate);
}

void WebAudio::setPlaylist(const QStringList &list) {
  setMedia(list);
}

void WebAudio::setPosition(qint64 position) {
  _player->setPosition(position);
}

void WebAudio::setVolume(int volume) {
  _player->setVolume(volume);
}

void WebAudio::stop() {
  _player->stop();
}

/* QMediaPlaylist Functions */
bool WebAudio::addMedia(const QString &media) {
  QFileInfo file(media);

  if (file.exists()) {
    _playlist->addMedia(QUrl::fromLocalFile(file.absoluteFilePath()));
    return true;
  }

  return false;
}

void WebAudio::clear() {
  _playlist->clear();
}

int WebAudio::currentIndex() {
  return _playlist->currentIndex();
}

bool WebAudio::insertMedia(int index, const QString &media) {
  QFileInfo file(media);

  if (file.exists()) {
    return _playlist->insertMedia(index, QUrl::fromLocalFile(file.absoluteFilePath()));
  }

  return false;
}

bool WebAudio::isEmpty() {
  return _playlist->isEmpty();
}

bool WebAudio::isReadOnly() {
  return _playlist->isReadOnly();
}

QString WebAudio::media(int index) {
  return _playlist->media(index).canonicalUrl().toString();
}

int WebAudio::mediaCount() {
  return _playlist->mediaCount();
}

int WebAudio::nextIndex(int steps = 1) {
  return _playlist->nextIndex(steps);
}

QMediaPlaylist::PlaybackMode WebAudio::playbackMode() {
  return _playlist->playbackMode();
}

int WebAudio::previousIndex(int steps = 1) {
  return _playlist->previousIndex(steps);
}

bool WebAudio::removeMedia(int index) {
  return _playlist->removeMedia(index);
}

void WebAudio::setPlaybackMode(QMediaPlaylist::PlaybackMode mode) {
  _playlist->setPlaybackMode(mode);
}

/* QMediaPlaylist Slots */
void WebAudio::next() {
  _playlist->next();
}

void WebAudio::previous() {
  _playlist->previous();
}

void WebAudio::setCurrentIndex(int index) {
  _playlist->setCurrentIndex(index);
}

void WebAudio::shuffle() {
  _playlist->shuffle();
}

/* Player Events */
void WebAudio::audioAvailableChanged(bool available) {
  emit onAudioAvailableChanged(available);
}

void WebAudio::bufferStatusChanged(int percent) {
  emit onBufferStatusChanged(percent);
}

void WebAudio::currentMediaChanged(const QMediaContent &media) {
  emit onCurrentMediaChanged(QString(media.canonicalUrl().toString()));
}

void WebAudio::durationChanged(qint64 duration) {
  emit onDurationChanged(duration);
}

void WebAudio::error(QMediaPlayer::Error error) {
  emit onError(QString("%1: %2").arg(error).arg(_player->errorString()));
}

void WebAudio::mediaChanged(const QMediaContent &media) {
  emit onMediaChanged(QString(media.canonicalUrl().toString()));
}

void WebAudio::mediaStatusChanged(QMediaPlayer::MediaStatus status) {
  emit onMediaStatusChanged(status);
}

void WebAudio::metaDataChanged() {
  emit onMetaDataChanged();
}

void WebAudio::metaDataAvailableChanged(bool available) {
  emit onMetaDataAvailableChanged(available);
}

void WebAudio::mutedChanged(bool muted) {
  emit onMutedChanged(muted);
}

void WebAudio::notifyIntervalChanged(int milliseconds) {
  emit onNotifyIntervalChanged(milliseconds);
}

void WebAudio::playbackRateChanged(qreal rate) {
  emit onPlaybackRateChanged(rate);
}

void WebAudio::positionChanged(qint64 position) {
  emit onPositionChanged(position);
}

void WebAudio::seekableChanged(bool seekable) {
  emit onSeekableChanged(seekable);
}

void WebAudio::stateChanged(QMediaPlayer::State state) {
  switch (state) {
    case QMediaPlayer::StoppedState :
      emit onStopped();
      break;

    case QMediaPlayer::PlayingState :
      emit onPlaying();
      break;

    case QMediaPlayer::PausedState :
      emit onPaused();
      break;
  }
}

void WebAudio::volumeChanged(int volume) {
  emit onVolumeChanged(volume);
}

/* QMediaPlaylist Slots */
void WebAudio::currentIndexChanged(int index) {
  emit onCurrentIndexChanged(index);
}

void WebAudio::mediaAboutToBeInserted(int start, int end) {
  emit onMediaAboutToBeInserted(start, end);
}

void WebAudio::mediaAboutToBeRemoved(int start, int end) {
  emit onMediaAboutToBeRemoved(start, end);
}

void WebAudio::mediaInserted(int start, int end) {
  emit onMediaInserted(start, end);
}

void WebAudio::mediaRemoved(int start, int end) {
  emit onMediaRemoved(start, end);
}

void WebAudio::playbackModeChanged(QMediaPlaylist::PlaybackMode mode) {
  emit onPlaybackModeChanged(mode);
}
