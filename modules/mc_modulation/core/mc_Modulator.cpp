namespace mc
{

Modulator::Modulator(juce::ValueTree valueTree, juce::UndoManager* undoManager)
    : state {std::move(valueTree)}, undoManager_ {undoManager}
{
}

auto Modulator::getName() const -> juce::String { return {}; }

auto Modulator::prepare(double sampleRate, int maxSamplesPerBlock) -> void
{
    juce::ignoreUnused(sampleRate, maxSamplesPerBlock);
}

auto Modulator::process(juce::AudioBuffer<float>& buffer) -> void { juce::ignoreUnused(buffer); }

auto Modulator::reset() -> void { }

auto Modulator::getUndoManager() const -> juce::UndoManager* { return undoManager_; }

auto Modulator::setPlayHead(juce::AudioPlayHead* playHead) -> void { playHead_ = playHead; }
auto Modulator::getPlayHead() const noexcept -> juce::AudioPlayHead* { return playHead_; }

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
}  // namespace mc
