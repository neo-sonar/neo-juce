#include <mc_audio_processors/mc_audio_processors.hpp>

#include <catch2/catch_test_macros.hpp>

namespace {
struct TestProcessor final : juce::AudioProcessor {
    explicit TestProcessor(juce::AudioProcessorValueTreeState::ParameterLayout parameters)
        : vts { *this, nullptr, "Test", std::move(parameters) }
    {
    }
    ~TestProcessor() override = default;

    auto getName() const -> const juce::String override { return "Test"; }

    auto prepareToPlay(double /*sampleRate*/, int /*samplesPerBlock*/) -> void override { }
    auto processBlock(juce::AudioBuffer<float>& /*buffer*/, juce::MidiBuffer& /*midiMessages*/) -> void override { }
    using juce::AudioProcessor::processBlock;
    auto releaseResources() -> void override { }

    auto isBusesLayoutSupported(BusesLayout const& /*layouts*/) const -> bool override { return true; }

    auto createEditor() -> juce::AudioProcessorEditor* override { return nullptr; }
    auto hasEditor() const -> bool override { return false; }

    auto acceptsMidi() const -> bool override { return false; }
    auto producesMidi() const -> bool override { return false; }
    auto isMidiEffect() const -> bool override { return false; }
    auto getTailLengthSeconds() const -> double override { return 0.0; }

    auto getNumPrograms() -> int override { return 0; }
    auto getCurrentProgram() -> int override { return 0; }
    void setCurrentProgram(int /*index*/) override { }
    auto getProgramName(int /*index*/) -> const juce::String override { return ""; }
    void changeProgramName(int /*index*/, juce::String const& /*newName*/) override { }

    auto getStateInformation(juce::MemoryBlock& /*destData*/) -> void override { }
    auto setStateInformation(void const* /*data*/, int /*size*/) -> void override { }

    juce::AudioProcessorValueTreeState vts;
};

auto makeTestProcessor()
{
    return TestProcessor { {
        mc::makeFloatParameter("test_float", "Float", juce::NormalisableRange { 0.0F, 1.0F, 0.01F }, 1.0F),
        mc::makeIntParameter("test_int", "Int", 0, 10, 0),
        mc::makeChoiceParameter("test_choice", "Choice", juce::StringArray { "1", "2", "3" }, 0),
        mc::makeBoolParameter("test_bool", "Bool", false),
    } };
}
} // namespace

TEST_CASE("audio_processors/parameter: getFloatParameter", "[audio_processors]")
{
    auto empty = TestProcessor { {} };
    REQUIRE(mc::getFloatParameter(empty.vts, "Unkown") == nullptr);

    auto test = makeTestProcessor();
    REQUIRE(mc::getFloatParameter(test.vts, "test_float") != nullptr);
    REQUIRE(mc::getFloatParameter(test.vts, "test_int") == nullptr);
    REQUIRE(mc::getFloatParameter(test.vts, "test_choice") == nullptr);
    REQUIRE(mc::getFloatParameter(test.vts, "test_bool") == nullptr);
}

TEST_CASE("audio_processors/parameter: getChoiceParameter", "[audio_processors]")
{
    auto empty = TestProcessor { {} };
    REQUIRE(mc::getChoiceParameter(empty.vts, "Unkown") == nullptr);

    auto test = makeTestProcessor();
    REQUIRE(mc::getChoiceParameter(test.vts, "test_choice") != nullptr);
    REQUIRE(mc::getChoiceParameter(test.vts, "test_float") == nullptr);
    REQUIRE(mc::getChoiceParameter(test.vts, "test_int") == nullptr);
    REQUIRE(mc::getChoiceParameter(test.vts, "test_bool") == nullptr);
}

TEST_CASE("audio_processors/parameter: getIntParameter", "[audio_processors]")
{
    auto empty = TestProcessor { {} };
    REQUIRE(mc::getIntParameter(empty.vts, "Unkown") == nullptr);

    auto test = makeTestProcessor();
    REQUIRE(mc::getIntParameter(test.vts, "test_int") != nullptr);
    REQUIRE(mc::getIntParameter(test.vts, "test_choice") == nullptr);
    REQUIRE(mc::getIntParameter(test.vts, "test_float") == nullptr);
    REQUIRE(mc::getIntParameter(test.vts, "test_bool") == nullptr);
}

TEST_CASE("audio_processors/parameter: getBoolParameter", "[audio_processors]")
{
    auto empty = TestProcessor { {} };
    REQUIRE(mc::getBoolParameter(empty.vts, "Unkown") == nullptr);

    auto test = makeTestProcessor();
    REQUIRE(mc::getBoolParameter(test.vts, "test_bool") != nullptr);
    REQUIRE(mc::getBoolParameter(test.vts, "test_int") == nullptr);
    REQUIRE(mc::getBoolParameter(test.vts, "test_choice") == nullptr);
    REQUIRE(mc::getBoolParameter(test.vts, "test_float") == nullptr);
}
