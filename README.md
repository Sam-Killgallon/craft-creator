# Install

Requires `gdk-pixbuf-2.0` to be installed
Build with `cmake . && make`
May need `PKG_CONFIG_PATH="/usr/local/opt/libffi/lib/pkgconfig" cmake . && make` on macos to find libffi

# Run
`./crossstitch_creator ~/pictures/photo.jpg` => Will process the file and output it as `output.jpg`

# Configure
Generate different colour mappings by using `./tools <step>` ie `./tools 35` to generate a colour chart in increments of 35
