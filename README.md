## HUIOS (HTML-User-Interface-OpenSource)

**Note: This code is loosely base on https://github.com/andmcgregor/cefgui**

After building CEF3, it gives something like this, which needs adapted for samples here...
EXE="/path/to/this/file/in/project/huios_simple/build/dir/chrome-sandbox" && sudo -- chown root:root $EXE && sudo -- chmod 4755 $EXE
sudo cp libcef.so /lib/x86_64-linux-gnu/
sudo cp libffmpegsumo.so /lib/x86_64-linux-gnu/
