// SPDX-License-Identifier: BSL-1.0

namespace neo {

BackgroundProcess::BackgroundProcess(juce::ThreadPool* threadPool) : _threadPool { threadPool } { }

auto BackgroundProcess::startProcess(juce::String const& command) -> void
{
    if (_threadPool != nullptr) {
        _threadPool->addJob([command, this] {
            juce::ChildProcess proc {};
            if (proc.start(command)) {
                this->_processHasStarted.store(true);

                auto buffer = std::vector<std::uint8_t>(static_cast<size_t>(1024 * 16), std::uint8_t {});
                while (proc.isRunning()) {
                    std::ranges::fill(buffer, std::uint8_t {});
                    auto* const data   = static_cast<void*>(buffer.data());
                    auto const maxSize = static_cast<int>(buffer.size());
                    auto num           = proc.readProcessOutput(data, maxSize);
                    if (num != 0) {
                        _queue.push(juce::String::createStringFromData(static_cast<void*>(buffer.data()), num));
                    }
                }

                this->_processExitCode.store(proc.getExitCode());
                this->_processHasFinished.store(true);
            }
        });

        startTimerHz(5);
        return;
    }

    // Currently only thread pools are supported
    jassertfalse;
}

auto BackgroundProcess::addListener(Listener* listener) -> void { _listeners.add(listener); }

auto BackgroundProcess::removeListener(Listener* listener) -> void { _listeners.remove(listener); }

auto BackgroundProcess::timerCallback() -> void
{
    if (_processHasStarted.load()) {
        _processHasStarted.store(false);
        _listeners.call([this](Listener& l) { l.backgroundProcessStarted(this); });
    }

    if (_processHasFinished.load()) {
        _processHasFinished.store(false);
        _listeners.call([this, ec = _processExitCode.load()](Listener& l) { l.backgroundProcessFinished(this, ec); });
        stopTimer();
    }

    auto output = _queue.pop();
    while (output.has_value()) {
        // Probably a bug in clang-tidy. Value is checked in line above.
        // NOLINTNEXTLINE(bugprone-unchecked-optional-access)
        _listeners.call([this, out = *output](Listener& l) { l.backgroundProcessOutputReceived(this, out); });
        output = _queue.pop();
    }
}

} // namespace neo
