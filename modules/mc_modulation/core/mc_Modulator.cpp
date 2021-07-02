namespace mc::modulation
{

Modulator::Modulator(juce::ValueTree valueTree, juce::UndoManager* undoManager)
    : state {std::move(valueTree)}, undoManager_ {undoManager}
{
    color_.referTo(state, "color", undoManager_, juce::Colour {});
}

auto Modulator::getName() const -> juce::String { return {}; }

auto Modulator::prepare(double sampleRate, int maxSamplesPerBlock) -> void
{
    juce::ignoreUnused(sampleRate, maxSamplesPerBlock);
}

auto Modulator::process(juce::AudioBuffer<float>& buffer) -> void { juce::ignoreUnused(buffer); }

auto Modulator::reset() -> void { }

auto Modulator::setColour(juce::Colour newColor) -> void { color_ = newColor; }

auto Modulator::getColour() const -> juce::Colour { return color_; }

/////////////////////////////

ModulatorList::ModulatorList(const juce::ValueTree& parentTree) : ValueTreeObjectListV2<Modulator>(parentTree)
{
    rebuildObjects();
}

ModulatorList::~ModulatorList() { freeObjects(); }

auto ModulatorList::isSuitableType(const juce::ValueTree& v) const -> bool
{
    juce::ignoreUnused(v);
    return false;  // isModulator(v);
}

auto ModulatorList::createNewObject(const juce::ValueTree& v) -> Modulator*
{
    jassertfalse;
    juce::ignoreUnused(v);
    return {};
}

void ModulatorList::deleteObject(Modulator* t)
{
    jassert(t != nullptr);
    juce::ignoreUnused(t);
    delete t;
}

void ModulatorList::newObjectAdded(Modulator* t) { juce::ignoreUnused(t); }

void ModulatorList::objectRemoved(Modulator* /*unused*/) { }

void ModulatorList::objectOrderChanged() { }
}  // namespace mc::modulation
