namespace mc::modulation
{

ModulatorList::ModulatorList(juce::ValueTree const& parentTree, juce::UndoManager* undoManager)
    : ValueTreeObjectListV2<Modulator>(parentTree), undoManager_ {undoManager}
{
    rebuildObjects();
}

ModulatorList::~ModulatorList() { freeObjects(); }

auto ModulatorList::getModulatorFor(juce::ValueTree const& v) const -> Modulator*
{
    for (auto* const m : objects)
    {
        if (m->state == v) { return m; }
    }

    return nullptr;
}

auto ModulatorList::isSuitableType(juce::ValueTree const& v) const -> bool
{
    return v.hasType(ModulatorMacroIDs::type);
}

auto ModulatorList::createNewObject(juce::ValueTree const& v) -> Modulator*
{
    if (v.hasType(ModulatorMacroIDs::type))
    {
        auto* m = new ModulatorMacro(v, undoManager_);
        modulators_.add(m);
        return m;
    }

    jassertfalse;
    return nullptr;
}

void ModulatorList::deleteObject(Modulator* m) { modulators_.removeObject(m); }

void ModulatorList::newObjectAdded(Modulator* m) { juce::ignoreUnused(m); }

void ModulatorList::objectRemoved(Modulator* m) { juce::ignoreUnused(m); }

void ModulatorList::objectOrderChanged() { }

}  // namespace mc::modulation