project(neo-juce VERSION 0.1.0)

juce_add_modules(ALIAS_NAMESPACE neo
    neo_audio_basics
    neo_audio_formats
    neo_audio_processors
    neo_core
    neo_data_structures
    neo_dsp
    neo_events
    neo_extension_pack
    neo_graphics
    neo_gui_basics
    neo_gui_extra
    neo_meters
    neo_synth
)
