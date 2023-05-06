project(mc-juce VERSION 0.1.0)

juce_add_modules(ALIAS_NAMESPACE mc
    mc_audio_basics
    mc_audio_formats
    mc_audio_processors
    mc_core
    mc_data_structures
    mc_dsp
    mc_events
    mc_extension_pack
    mc_graphics
    mc_gui_basics
    mc_gui_extra
    mc_meters
    mc_synth
)
