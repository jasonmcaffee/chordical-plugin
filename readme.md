## Building vst/component
To build new component/vst3/etc choose Build->Rebuild Project, which will send new copies of the plugin to the dir: ~/Library/Audio/Plug-Ins/VST

copy that file into the /Library/audio/plugins/components folder, and rescan in ableton.

## Adding 3rd party libraries
### Header only
for header file libraries, like cereal, 
- create a folder in the project called cereal-include
- open projucer, click gear icon at top left, paste this in Header Search Paths "../../cereal-include"
- now you can #include <cereal/archives/json.hpp>