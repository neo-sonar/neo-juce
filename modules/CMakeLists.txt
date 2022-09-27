project(mc-juce VERSION 0.1.0)

juce_add_modules(ALIAS_NAMESPACE mc
    mcj_audio_basics
    mcj_audio_formats
    mcj_audio_processors
    mcj_core
    mcj_data_structures
    mcj_dsp
    mcj_events
    mcj_extension_pack
    mcj_graphics
    mcj_gui_basics
    mcj_meters
    mcj_synth
)
