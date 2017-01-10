#Documentation

#Properties
These are not implemented yet as traditional properties; you will need to use the listed *Access* function(s) to get the values represented.

##audioAvailable : Boolean

This property holds the audio availabilty status for the current media.

As the life time of the media player can be longer than the playback of the assigned media, this property may change over time, the `onAudioAvailableChanged()` event can be used to monitor it's status.

**Access**:
`isAudioAvailable()`

**Events**:
`onAudioAvailableChanged(boolean)`

##bufferStatus : Integer

This property holds the percentage of the temporary buffer filled before playback begins or resumes, from (empty) to (full).

When the player object is buffering; this property holds the percentage of the temporary buffer that is filled. The buffer will need to reach 100% filled before playback can start or resume, at which time mediaStatus() will return BufferedMedia or BufferingMedia. If the value is anything lower than 100, mediaStatus() will return StalledMedia.

**Access**:
`bufferStatus()`

**Events**:
`onBufferStatusChanged(integer)`

##currentIndex : Integer

This property holds current position of the playlist.

**Access**:
`currentIndex()`, `setCurrentIndex(integer)`

**Events**:
`onCurrentIndexChanged(integer)`

##currentMedia : String

This property holds the path of the current active media content being played by the player object.

**Access**:
`currentMedia()`

**Events**:
`onCurrentMediaChanged(string)`

##duration : Integer

This property holds the duration of the current media.

The value is the total playback time in milliseconds of the current media. The value may change across the life time of the media object and may not be available when initial playback begins, connect to the onDurationChanged() event to receive status notifications.

**Access**:
`duration()`

**Events**:
`onDurationChanged(integer)`

##error : Integer

This property holds the numeric value of the last error condition.

**Access**:
`error()`

**Events**:
`onError(string)`

##errorString : String

This property holds a string describing the last error condition.

**Access**:
`errorString()`

**Events**:
`onError(message)`

##media : String

This property holds the path of the active media source being used by the media player.

**Access**:
`media()`

##mediaStatus : Integer

This property holds the current status of the current media.

**Access**:
`mediaStatus()`

**Events**:
`onMediaStatusChanged(integer)`

##metaData : JSON

Returns a JSON object containing available meta-data for the current media.

**Access**:
`metaData()`, `isMetaDataAvailable()`

**Events**:
`onMetaDataChanged()`, `onMetaDataAvailableChanged(json)`

##muted : Boolean

This property holds the muted state of the current media.

The value will be true if the playback volume is muted; otherwise false.

**Access**:
`isMuted()`, `setMuted(boolean)`

**Events**:
`onMutedChanged(boolean)`

##notifyInterval : Integer

The interval at which notifiable properties will update.
The interval is expressed in milliseconds, the default value is 1000.

**Access**:
`notifyInterval()`, `setNotifyInterval()`

**Events**:
`onNotifyIntervalChanged()`

##playbackMode : Integer

This property defines the order that items in the playlist are played.

**Access**:
`playbackMode()`, `setPlaybackMode(integer)`

**Events**:
`onPlaybackModeChanged(integer)`

##playbackRate : Integer

This property holds the playback rate of the current media.

This value is a multiplier applied to the media's standard play rate. By default this value is 1.0, indicating that the media is playing at the standard pace. Values higher than 1.0 will increase the rate of play. Values less than zero can be set and indicate the media will rewind at the multiplier of the standard pace.

Not all playback services support change of the playback rate. It is framework defined as to the status and quality of audio and video while fast forwarding or rewinding.

**Access**:
`playbackRate()`, `setPlaybackRate()`

**Events**:
`onPlaybackRateChanged(integer)`

##playlist : Array

This property holds the media playlist being used by the player object.

The player object will use the current playlist item for selection of the content to be played.

If the media playlist is used as a source, `currentMedia()` is updated with a current playlist item. The current source should be selected with `setCurrentIndex(integer)` instead of `setMedia()`, otherwise the current playlist will be discarded.

**Access**:
`playlist()`, `setPlaylist(array)`

##position : Integer

This property holds the playback position of the current media.

The value is the current playback position, expressed in milliseconds since the beginning of the media. Periodically changes in the position will be indicated through the `onPositionChanged(integer)` event, the interval between updates can be set with QMediaObject's method `setNotifyInterval()`.

**Access**:
`position()`, `setPosition(integer)`

**Events**:
`onPositionChanged(integer)`

##seekable : Boolean

This property holds the seek-able status of the current media.

If seeking is supported this property will be true; false otherwise. The status of this property may change across the life time of the media player object, use the `onSeekableChanged(boolean)` event to monitor changes.

**Access**:
`isSeekable()`

**Events**:
`onSeekableChanged(boolean)`

##state : Integer

This property holds the media player's playback state.

**Access**:
`state()`

**Events**:
`onStateChanged(integer)`

##volume : Integer

This property holds the current playback volume.

The playback volume is linear in effect and the value can range from 0 - 100 as a percentage, values outside this range will be normalized.

**Access**:
`volume()`, `setVolume(integer)`

**Events**:
`onVolumeChanged(integer)`

#Funtions
##clear()

Remove all the items from the playlist.

##currentIndex() : Integer

Returns position of the current media content in the playlist.

##insertMedia(integer, string) : Boolean

Insert the media content to the playlist at given position.

##isEmpty() : Boolean

Returns true if the playlist contains no items, otherwise returns false.

##isReadOnly() : Boolean

Returns true if the playlist can be modified, otherwise returns false.

##mediaCount() : Integer

Returns the number of items in the playlist.


##next()

Advance to the next media content in playlist.

##pause()

Pause playing the current source.

**Events**:
`onPaused()`

##play()

Start or resume playing the current source.

**Events**:
`onPlaying()`

##previous()

Return to the previous media content in playlist.

##removeMedia(integer) : Boolean

Remove the item from the playlist at given position.

Returns true if the operation is successful, otherwise return false.

##setCurrentIndex(integer)

Activate media content from playlist at position playlistPosition.

##setMedia(array)

Sets the current media source, erasing any existing media sources/playlists.

> Note: This function returns immediately after recording the specified source of the media. It does not wait for the media to finish loading and does not check for errors. Listen for the `onMediaStatusChanged(integer)` and `onError(string)` signals to be notified when the media is loaded and when an error occurs during loading.

**Events**:
`onMediaStatusChanged(integer)`

##setNotifyInterval(integer)

Sets the notify interval to the specified value. Listen for the `onNotifyIntervalChanged(integer)` event to catch changes.

**Events**:
`onNotifyIntervalChanged(interger)`

##setPlaybackMode(integer)

Sets the order that items in the playlist are played back.

- (CurrentItemOnce) 0: The current item is played only once.
- (CurrentItemInLoop) 1: The current item is played repeatedly in a loop.
- (Sequential) 2: Playback starts from the current and moves through each successive item until the last is reached and then stops. The next item is a null item when the last one is currently playing.
- (Loop) 3: Playback restarts at the first item after the last has finished playing.
- (Random) 4: Play items in random order.

##shuffle()

Shuffle items in the playlist.

##stop()

Stop playing, and reset the play position to the beginning.

**Events**:
`onStopped()`

#Events

##onAudioAvailableChanged(available) : Boolean

Signals the availability of audio content has changed to `available`.

**Related**:
`isAudioAvailable()`

##onBufferStatusChanged(percent) : Boolean

Signal the amount of the local buffer filled as a percentage by `percent`.

**Related**:
`bufferStatus()`

##onCurrentIndexChanged(position) : Integer

Signal emitted when playlist position changed to `position`.

**Related**:
`currentIndex()`, `setCurrentIndex(integer)`

##onCurrentMediaChanged(media) : String

Signals that the current playing content has been changed to path `media`.

**Related**:
`currentMedia()`

##onDurationChanged(duration) : Integer

Signal the duration of the content has changed to `duration`, expressed in milliseconds.

**Related**:
`duration()`

##onError(error) : String

Signals that an `error` condition has occurred.

**Related**:
`error()`, `errorString()`

##onMediaAboutToBeInserted(start, end) : Integer, Integer

Signal emitted when items are to be inserted at `start` and ending at `end`.

**Related**:
`insertMedia(string)`, `addMedia(string)`

##onMediaAboutToBeRemoved(start, end) : Integer, Integer

Signal emitted when item are to be deleted at `start` and ending at `end`.

**Related**:
`removeMedia(integer)`

##onMediaChanged(media) : String

Signals that the media source has been changed to path `media`.

**Related**:
`media()`, `setMedia(array)`

##onMediaInserted(start, end) : Integer, Integer

This signal is emitted after media has been inserted into the playlist. The new items are those between `start` and `end` inclusive.

**Related**:
`insertMedia(integer, string)`

##onMediaRemoved(start, end) : Integer, Integer

Move the item from position from `start` position to `end`.

**Related**:
`removeMedia(integer)`

##onMediaStatusChanged(status) : Integer

Signals that the `status` of the current media has changed.

**Related**:
`mediaStatus()`

##onMetaDataChanged() :

Signals that the meta data of the current media object have changed.

**Related**:
`metaData()`

##onMetaDataAvailableChanged(available) : Boolean

Signals that the meta data of the current media object is `available`.

**Related**:
`isMetaDataAvailable()`

##onNotifyIntervalChanged(interval) : Integer

Signals that the notifyInterval as changed to `interval`.

**Related**:
`notifyInterval()`, 'setNotifyInterval()`

##onPlaybackRateChanged(rate) : Integer

Signals the playbackRate has changed to `rate`.

**Related**:
`playbackRate()`, `setPlaybackRate(integer)`

##onPaused()

Signals that the media player has been paused.

**Related**:
`pause()`

##onPlaying()

Signals that the media player has begun or resumed playing media.

**Related**:
`play()`

##onPositionChanged(position) : Integer

Signal the position of the content has changed to `position`, expressed in milliseconds.

**Related**:
`position()`, `setPosition()`

##onSeekableChanged(seekable) : Boolean

Signals the seekable status of the media player has changed to `seekable`.

**Related**:
`isSeekable()`

##onStateChanged(state) : Integer

Signals the state of the media player has changed to `state`.

**Related**:
`state()`

##onStopped()
Signals that the media player has stopped playing.

**Related**:
`stop()`

##onVolumeChanged(volume) : Integer

Signal the playback volume has changed to `volume`.

**Related**:
`volume()`, `setVolume(integer)`