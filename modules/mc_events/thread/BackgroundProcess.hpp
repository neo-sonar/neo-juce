// SPDX-License-Identifier: BSL-1.0

#pragma once

namespace mc {

struct BackgroundProcess : private juce::Timer {
    struct Listener {
        Listener()          = default;
        virtual ~Listener() = default;

        Listener(Listener const& other)                  = delete;
        Listener(Listener&& other)                       = delete;
        auto operator=(Listener const& rhs) -> Listener& = delete;
        auto operator=(Listener&& rhs) -> Listener&      = delete;

        virtual auto backgroundProcessStarted(BackgroundProcess* process) -> void                             = 0;
        virtual auto backgroundProcessFinished(BackgroundProcess* process, std::uint32_t exitCode) -> void    = 0;
        virtual auto backgroundProcessOutputReceived(BackgroundProcess* process, juce::String output) -> void = 0;
    };

    explicit BackgroundProcess(juce::ThreadPool* threadPool);
    ~BackgroundProcess() override = default;

    BackgroundProcess(BackgroundProcess const& other)                  = delete;
    BackgroundProcess(BackgroundProcess&& other)                       = delete;
    auto operator=(BackgroundProcess const& rhs) -> BackgroundProcess& = delete;
    auto operator=(BackgroundProcess&& rhs) -> BackgroundProcess&      = delete;

    auto startProcess(juce::String const& command) -> void;
    auto addListener(Listener* listener) -> void;
    auto removeListener(Listener* listener) -> void;

private:
    auto timerCallback() -> void override;

    juce::ListenerList<Listener> _listeners {};
    ThreadSafeQueue<juce::String> _queue {};
    juce::ThreadPool* _threadPool { nullptr };
    std::atomic<bool> _processHasStarted { false };
    std::atomic<bool> _processHasFinished { false };
    std::atomic<uint32_t> _processExitCode { 0 };
};

} // namespace mc
