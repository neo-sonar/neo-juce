project(mc-juce VERSION 0.1.0)

juce_add_modules(ALIAS_NAMESPACE mc
    mcj_core
    mcj_events
    mcj_data_structures
    mcj_audio_basics
    mcj_dsp
    mcj_audio_processors
    mcj_graphics
    mcj_gui_basics
    mcj_meters
)
