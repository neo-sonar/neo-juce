#ifndef MODERN_CIRCUITS_APP_ZENTRALE_BACKGROUND_PROCESS_HPP
#define MODERN_CIRCUITS_APP_ZENTRALE_BACKGROUND_PROCESS_HPP

namespace mc
{

class BackgroundProcess : private juce::Timer
{
public:
    struct Listener
    {
        virtual ~Listener() = default;

        virtual auto backgroundProcessStarted(BackgroundProcess* process) -> void                             = 0;
        virtual auto backgroundProcessFinished(BackgroundProcess* process, std::uint32_t exitCode) -> void    = 0;
        virtual auto backgroundProcessOutputReceived(BackgroundProcess* process, juce::String output) -> void = 0;
    };

    explicit BackgroundProcess(juce::ThreadPool* threadPool);
    ~BackgroundProcess() override = default;

    auto startProcess(juce::String command) -> void;
    auto addListener(Listener* listener) -> void;
    auto removeListener(Listener* listener) -> void;

private:
    auto timerCallback() -> void override;

    juce::ListenerList<Listener> listeners_ {};
    ThreadSafeQueue<juce::String> queue_ {};
    juce::ThreadPool* threadPool_ {nullptr};
    std::atomic<bool> processHasStarted_ {false};
    std::atomic<bool> processHasFinished_ {false};
    std::atomic<uint32_t> processExitCode_ {0};
};

}  // namespace mc

#endif  // MODERN_CIRCUITS_APP_ZENTRALE_BACKGROUND_PROCESS_HPP
