#include "Audio.h"

#include <QtWebKitWidgets>
#include <QMediaService>
#include <QMediaPlaylist>
#include <QMediaMetaData>
#include <QFileInfo>
#include <QJsonObject>
#include <QJsonDocument>

#include <alsa/asoundlib.h>

Audio::Audio(QWidget *parent) : QWidget(parent) {
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

Audio::~Audio() {
  ;
}

/* QMediaPlayer functions */
int Audio::bufferStatus() {
  return _player->bufferStatus();
}

QString Audio::currentMedia() {
  return _player->currentMedia().canonicalUrl().toString();
}

qint64 Audio::duration() {
  return _player->duration();
}

QMediaPlayer::Error Audio::error() {
  return _player->error();
}

QString Audio::errorString() {
  return _player->errorString();
}

bool Audio::isAudioAvailable() {
  return _player->isAudioAvailable();
}

bool Audio::isMetaDataAvailable() {
  return _player->isMetaDataAvailable();
}

bool Audio::isMuted() {
  snd_mixer_t *handle;
  snd_mixer_elem_t *elem;
  snd_mixer_selem_id_t *sid;

  static const char* mix_name = "PCM";
  static const char* card = "default";
  static int mix_index = 0;

  snd_mixer_selem_id_alloca(&sid);
  snd_mixer_selem_id_set_index(sid, mix_index);
  snd_mixer_selem_id_set_name(sid, mix_name);

  if (snd_mixer_open(&handle, 0) < 0)
    return false;

  if (snd_mixer_attach(handle, card) < 0) {
    snd_mixer_close(handle);
    return false;
  }

  if (snd_mixer_selem_register(handle, NULL, NULL) < 0) {
    snd_mixer_close(handle);
    return false;
  }

  if (snd_mixer_load(handle)) {
    snd_mixer_close(handle);
    return false;
  }

  elem = snd_mixer_find_selem(handle, sid);

  if (!elem) {
    snd_mixer_close(handle);
    return false;
  }

  int mute = -1;

  if (snd_mixer_selem_has_playback_switch(elem)) {
    snd_mixer_selem_get_playback_switch(elem, (snd_mixer_selem_channel_id_t)0, &mute);
  }

  snd_mixer_close(handle);
  return (mute > 0) ? true : false;
}

bool Audio::isSeekable() {
  return _player->isSeekable();
}

QString Audio::media() {
  return _player->media().canonicalUrl().toString();
}

QMediaPlayer::MediaStatus Audio::mediaStatus() {
  return _player->mediaStatus();
}

QString Audio::metaData() {
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

qreal Audio::playbackRate() {
  return _player->playbackRate();
}

QStringList Audio::playlist() {
  QStringList list;

  for (int i = 0; i < _playlist->mediaCount(); i++) {
    list.append(_playlist->media(i).canonicalUrl().toString());
  }

  return list;
}

qint64 Audio::position() {
  return _player->position();
}

QMediaPlayer::State Audio::state() {
  return _player->state();
}

int Audio::volume() {
  snd_mixer_t *handle;
  snd_mixer_elem_t *elem;
  snd_mixer_selem_id_t *sid;

  static const char* mix_name = "PCM";
  static const char* card = "default";
  static int mix_index = 0;

  snd_mixer_selem_id_alloca(&sid);
  snd_mixer_selem_id_set_index(sid, mix_index);
  snd_mixer_selem_id_set_name(sid, mix_name);

  if (snd_mixer_open(&handle, 0) < 0)
    return -1;

  if (snd_mixer_attach(handle, card) < 0) {
    snd_mixer_close(handle);
    return -1;
  }

  if (snd_mixer_selem_register(handle, NULL, NULL) < 0) {
    snd_mixer_close(handle);
    return -1;
  }

  if (snd_mixer_load(handle)) {
    snd_mixer_close(handle);
    return -1;
  }

  elem = snd_mixer_find_selem(handle, sid);

  if (!elem) {
    snd_mixer_close(handle);
    return -1;
  }

  long minv, maxv, volume;

  snd_mixer_selem_get_playback_volume_range (elem, &minv, &maxv);

  if (snd_mixer_selem_get_playback_volume(elem, (snd_mixer_selem_channel_id_t)0, &volume) < 0) {
    snd_mixer_close(handle);
    return -1;
  }

  volume -= minv;
  maxv -= minv;
  minv = 0;
  volume = 100 * volume / maxv;

  snd_mixer_close(handle);
  return volume;
}

/* QMediaPlayer Slots */
void Audio::pause() {
  _player->pause();
}

void Audio::play() {
  _player->play();
}

void Audio::setMedia(const QStringList &list) {
  _playlist->clear();

  foreach (const QString &item, list) {
    QFileInfo file(item);

    if (file.exists()) {
      _playlist->addMedia(QUrl::fromLocalFile(file.absoluteFilePath()));
    }
  }
}

void Audio::setMuted(bool muted) {
  snd_mixer_t *handle;
  snd_mixer_elem_t *elem;
  snd_mixer_selem_id_t *sid;

  static const char* mix_name = "PCM";
  static const char* card = "default";
  static int mix_index = 0;

  snd_mixer_selem_id_alloca(&sid);
  snd_mixer_selem_id_set_index(sid, mix_index);
  snd_mixer_selem_id_set_name(sid, mix_name);

  if (snd_mixer_open(&handle, 0) < 0)
    return;

  if (snd_mixer_attach(handle, card) < 0) {
    snd_mixer_close(handle);
    return;
  }

  if (snd_mixer_selem_register(handle, NULL, NULL) < 0) {
    snd_mixer_close(handle);
    return;
  }

  if (snd_mixer_load(handle)) {
    snd_mixer_close(handle);
    return;
  }

  elem = snd_mixer_find_selem(handle, sid);

  if (!elem) {
    snd_mixer_close(handle);
    return;
  }

  if (snd_mixer_selem_has_playback_switch(elem)) {
    snd_mixer_selem_set_playback_switch(elem, (snd_mixer_selem_channel_id_t)0, (muted) ? 0 : 1);
  }

  snd_mixer_close(handle);
  emit onMutedChanged(muted);
}

void Audio::setPlaybackRate(qreal rate) {
  _player->setPlaybackRate(rate);
}

void Audio::setPlaylist(const QStringList &list) {
  setMedia(list);
}

void Audio::setPosition(qint64 position) {
  _player->setPosition(position);
}

bool Audio::setVolume(int volume) {
  snd_mixer_t *handle;
  snd_mixer_elem_t *elem;
  snd_mixer_selem_id_t *sid;

  static const char* mix_name = "PCM";
  static const char* card = "default";
  static int mix_index = 0;

  snd_mixer_selem_id_alloca(&sid);
  snd_mixer_selem_id_set_index(sid, mix_index);
  snd_mixer_selem_id_set_name(sid, mix_name);

  if (snd_mixer_open(&handle, 0) < 0)
    return false;

  if (snd_mixer_attach(handle, card) < 0) {
    snd_mixer_close(handle);
    return false;
  }

  if (snd_mixer_selem_register(handle, NULL, NULL) < 0) {
    snd_mixer_close(handle);
    return false;
  }

  if (snd_mixer_load(handle) < 0) {
    snd_mixer_close(handle);
    return false;
  }

  elem = snd_mixer_find_selem(handle, sid);

  if (!elem) {
    snd_mixer_close(handle);
    return false;
  }

  long minv, maxv, set;

  snd_mixer_selem_get_playback_volume_range(elem, &minv, &maxv);

  if (volume < 0 || volume > 100)
    return false;

  set = (volume * (maxv - minv) / 100) + minv;

  if (snd_mixer_selem_set_playback_volume_all(elem, set) < 0) {
    snd_mixer_close(handle);
    return false;
  }

  snd_mixer_close(handle);
  emit onVolumeChanged(volume);
  return true;
}

void Audio::stop() {
  _player->stop();
}

/* QMediaPlaylist Functions */
bool Audio::addMedia(const QString &media) {
  QFileInfo file(media);

  if (file.exists()) {
    _playlist->addMedia(QUrl::fromLocalFile(file.absoluteFilePath()));
    return true;
  }

  return false;
}

void Audio::clear() {
  _playlist->clear();
}

int Audio::currentIndex() {
  return _playlist->currentIndex();
}

bool Audio::insertMedia(int index, const QString &media) {
  QFileInfo file(media);

  if (file.exists()) {
    return _playlist->insertMedia(index, QUrl::fromLocalFile(file.absoluteFilePath()));
  }

  return false;
}

bool Audio::isEmpty() {
  return _playlist->isEmpty();
}

bool Audio::isReadOnly() {
  return _playlist->isReadOnly();
}

QString Audio::media(int index) {
  return _playlist->media(index).canonicalUrl().toString();
}

int Audio::mediaCount() {
  return _playlist->mediaCount();
}

int Audio::nextIndex(int steps = 1) {
  return _playlist->nextIndex(steps);
}

QMediaPlaylist::PlaybackMode Audio::playbackMode() {
  return _playlist->playbackMode();
}

int Audio::previousIndex(int steps = 1) {
  return _playlist->previousIndex(steps);
}

bool Audio::removeMedia(int index) {
  return _playlist->removeMedia(index);
}

void Audio::setPlaybackMode(QMediaPlaylist::PlaybackMode mode) {
  _playlist->setPlaybackMode(mode);
}

/* QMediaPlaylist Slots */
void Audio::next() {
  _playlist->next();
}

void Audio::previous() {
  _playlist->previous();
}

void Audio::setCurrentIndex(int index) {
  _playlist->setCurrentIndex(index);
}

void Audio::shuffle() {
  _playlist->shuffle();
}

/* Player Events */
void Audio::audioAvailableChanged(bool available) {
  emit onAudioAvailableChanged(available);
}

void Audio::bufferStatusChanged(int percent) {
  emit onBufferStatusChanged(percent);
}

void Audio::currentMediaChanged(const QMediaContent &media) {
  emit onCurrentMediaChanged(QString(media.canonicalUrl().toString()));
}

void Audio::durationChanged(qint64 duration) {
  emit onDurationChanged(duration);
}

void Audio::error(QMediaPlayer::Error error) {
  emit onError(QString("%1: %2").arg(error).arg(_player->errorString()));
}

void Audio::mediaChanged(const QMediaContent &media) {
  emit onMediaChanged(QString(media.canonicalUrl().toString()));
}

void Audio::mediaStatusChanged(QMediaPlayer::MediaStatus status) {
  emit onMediaStatusChanged(status);
}

void Audio::metaDataChanged() {
  emit onMetaDataChanged();
}

void Audio::metaDataAvailableChanged(bool available) {
  emit onMetaDataAvailableChanged(available);
}

void Audio::mutedChanged(bool muted) {
  emit onMutedChanged(muted);
}

void Audio::playbackRateChanged(qreal rate) {
  emit onPlaybackRateChanged(rate);
}

void Audio::positionChanged(qint64 position) {
  emit onPositionChanged(position);
}

void Audio::seekableChanged(bool seekable) {
  emit onSeekableChanged(seekable);
}

void Audio::stateChanged(QMediaPlayer::State state) {
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

void Audio::volumeChanged(int volume) {
  emit onVolumeChanged(volume);
}

/* QMediaPlaylist Slots */
void Audio::currentIndexChanged(int index) {
  emit onCurrentIndexChanged(index);
}

void Audio::mediaAboutToBeInserted(int start, int end) {
  emit onMediaAboutToBeInserted(start, end);
}

void Audio::mediaAboutToBeRemoved(int start, int end) {
  emit onMediaAboutToBeRemoved(start, end);
}

void Audio::mediaInserted(int start, int end) {
  emit onMediaInserted(start, end);
}

void Audio::mediaRemoved(int start, int end) {
  emit onMediaRemoved(start, end);
}

void Audio::playbackModeChanged(QMediaPlaylist::PlaybackMode mode) {
  emit onPlaybackModeChanged(mode);
}
