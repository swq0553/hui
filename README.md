## HUI (HTML-User-Interface)

**Note: This code is loosely base on https://github.com/andmcgregor/cefgui**

This is a simple abstraction layer on top of CEF3. It is designed to provide an easy to create
GUI based on HTML5 for games.

After building CEF3, it gives something like this, which needs adapted for samples here...
```
EXE="/path/to/this/file/in/project/hui_simple/build/dir/chrome-sandbox" && sudo -- chown root:root $EXE && sudo -- chmod 4755 $EXE
sudo cp libcef.so /lib/x86_64-linux-gnu/
sudo cp libffmpegsumo.so /lib/x86_64-linux-gnu/
```

Files Needed from CEF3 Build:
- locales/
- cef.pak
- cef_100_percent.pak
- cef_200_percent.pak
- chrome-sandbox (mentioned above)
- devtools_resources.pak
- icudtl.dat
- libcef.so (mentioned above)
- libffmpegsumo.so (mentioned above)
- natives_blob.bin
- snapshot_blob.bin

TODO:
- [x] Custom Routed Requset Handlers (Route, RESTRoute, JSONRESTRoute)
- [x] Injected Javascript Objects - https://bitbucket.org/chromiumembedded/cef/wiki/JavaScriptIntegration
- [ ] Websocket Handshake Interface
