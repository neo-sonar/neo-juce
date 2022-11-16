#pragma once

namespace mc {

struct ValueTreeObject {
    explicit ValueTreeObject(juce::ValueTree tree);

    [[nodiscard]] auto valueTree() -> juce::ValueTree& { return _valueTree; }

    [[nodiscard]] auto valueTree() const -> juce::ValueTree const& { return _valueTree; }

private:
    juce::ValueTree _valueTree;
};

inline ValueTreeObject::ValueTreeObject(juce::ValueTree valueTree) : _valueTree { std::move(valueTree) } { }

} // namespace mc
