/*
 * WebAudio.js
 * (C) Copyright 2017
 * Shaun Landis <slandis@github>
 */
var audio = new WebAudio();

function WebAudio() {
  if (Audio === undefined) {
    return undefined;
  }

  this._autoplay = true;
  this._basepath = "";
}

WebAudio.prototype.play = function() {
  Audio.play();
};

WebAudio.prototype.pause = function() {
  Audio.pause();
};

WebAudio.prototype.stop = function() {
  Audio.stop();
};

WebAudio.prototype.next = function() {
  Audio.next();
};

WebAudio.prototype.previous = function() {
  Audio.previous();
};

WebAudio.prototype.seekForward = function() {
  var position = Audio.position();
  position += 1000;
  Audio.setPosition(position);
};

WebAudio.prototype.seekBackward = function() {
  var position = Audio.position();
  position -= 1000;
  Audio.setPosition(position);
};

WebAudio.prototype.setMute = function(mute) {
  Audio.setMuted(mute);
};

WebAudio.prototype.setPlaylist = function(list) {
  Audio.setMedia(list);
};

WebAudio.prototype.clearPlaylist = function() {
  Audio.clear();
};

WebAudio.prototype.addPlaylistItem = function(file) {
  return Audio.addMedia(file);
};

WebAudio.prototype.insertPlaylistItem = function(file, index) {
  if (typeof(file) === "string") {
    return Audio.insertMedia(index, file);
  } else {
    file.forEach(function(item) {
      if (!Audio.insertMedia(index++, file)) {
        return false;
      }
    });

    return true;
  }

  return false;
};

WebAudio.prototype.removePlaylistItem = function(index) {
  return Audio.removeMedia(index);
};

WebAudio.prototype.addEventListener = function(evt, callback) {
  switch (evt) {
    case 'playing':
      Audio.onPlay.connect(callback);
      break;

    case 'stopped':
      Audio.onStop.connect(callback);
      break;

    case 'paused':
      Audio.onPause.connect(callback);
      break;

    case 'position':
      Audio.onPositionChanged.connect(callback);
      break;

    case 'volume':
      Audio.onVolumeChanged.connect(callback);
      break;

    case 'error':
      Audio.onError.connect(callback);
      break;

    case 'mode':
      Audio.onPlaybackModeChanged.connect(callback);
      break;

    case 'mediachanged':
      Audio.onMediaChanged.connect(callback);
      break;

    case 'mediaremoved':
      Audio.onMediaRemoved.connect(callback);
      break;

    case 'mediainserted':
      Audio.onMediaInserted.connect(callback);
      break;

    case 'metadata':
      Audio.onMetaDataAvailableChanged.connect(callback);
      break;

    case 'muted':
      Audio.onMutedChanged.connect(callback);
      break;

    case 'status':
      Audio.onMediaStatusChanged.connect(callback);
      break;
  }
};
