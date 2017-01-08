#Raspberry Pi::WebKit+Audio
-
Framebuffer WebKit+Audio for Raspberry Pi (or anything where the overhead of X11 is too much.) This was written as a major part of an embedded touchscreen media+navigation setup. It is highly tailored to my requirements and as such may not be suitable for use without major modification. The project consists of source for a QT application that renders HTML via a WebKit container that emits Touch events and exposes an Audio object to the HTML. Also included is a JavaScript wrapper for the Audio object.

##Requirements
There are far too many dependencies to list but here are the major ones:

- QT5.x (framebuffer support)
- gstreamer1.0 (and associated plugins)
 
##Documentation
Coming soon

##Credits
Ian Firns ([GitHub Project](https://github.com/firnsy/qt5-webkit-container)) whose WebKit container project served as the starting point for my project.

