/*
 * WebAudio.js
 * (C) Copyright 2017
 * Shaun Landis <slandis@github>
 */
var audio = new WebAudio();

function WebAudio() {
  if (webAudio === undefined) {
    return undefined;
  }

  this._autoplay = true;
  this._basepath = "";
}

WebAudio.prototype.play = function() {
  webAudio.play();
};

WebAudio.prototype.pause = function() {
  webAudio.pause();
};

WebAudio.prototype.stop = function() {
  webAudio.stop();
};

WebAudio.prototype.next = function() {
  webAudio.next();
};

WebAudio.prototype.previous = function() {
  webAudio.previous();
};

WebAudio.prototype.seekForward = function() {
  var position = webAudio.position();
  position += 1000;
  webAudio.setPosition(position);
};

WebAudio.prototype.seekBackward = function() {
  var position = webAudio.position();
  position -= 1000;
  webAudio.setPosition(position);
};

WebAudio.prototype.setMute = function(mute) {
  webAudio.setMuted(mute);
};

WebAudio.prototype.setPlaylist = function(list) {
  webAudio.setMedia(list);
};

WebAudio.prototype.clearPlaylist = function() {
  webAudio.clear();
};

WebAudio.prototype.addPlaylistItem = function(file) {
  return webAudio.addMedia(file);
};

WebAudio.prototype.insertPlaylistItem = function(file, index) {
  if (typeof(file) === "string") {
    return webAudio.insertMedia(index, file);
  } else {
    file.forEach(function(item) {
      if (!webAudio.insertMedia(index++, file)) {
        return false;
      }
    });

    return true;
  }

  return false;
};

WebAudio.prototype.removePlaylistItem = function(index) {
  return webAudio.removeMedia(index);
};

WebAudio.prototype.addEventListener = function(evt, callback) {
  switch (evt) {
    case 'playing':
      webAudio.onPlay.connect(callback);
      break;

    case 'stopped':
      webAudio.onStop.connect(callback);
      break;

    case 'paused':
      webAudio.onPause.connect(callback);
      break;

    case 'position':
      webAudio.onPositionChanged.connect(callback);
      break;

    case 'volume':
      webAudio.onVolumeChanged.connect(callback);
      break;

    case 'error':
      webAudio.onError.connect(callback);
      break;

    case 'mode':
      webAudio.onPlaybackModeChanged.connect(callback);
      break;

    case 'mediachanged':
      webAudio.onMediaChanged.connect(callback);
      break;

    case 'mediaremoved':
      webAudio.onMediaRemoved.connect(callback);
      break;

    case 'mediainserted':
      webAudio.onMediaInserted.connect(callback);
      break;

    case 'metadata':
      webAudio.onMetaDataAvailableChanged.connect(callback);
      break;

    case 'muted':
      webAudio.onMutedChanged.connect(callback);
      break;

    case 'status':
      webAudio.onMediaStatusChanged.connect(callback);
      break;
  }
};
