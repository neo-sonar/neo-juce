
namespace mc {

BackgroundProcess::BackgroundProcess(juce::ThreadPool* threadPool) : threadPool_ { threadPool } { }

auto BackgroundProcess::startProcess(const juce::String& command) -> void
{
    if (threadPool_ != nullptr) {
        threadPool_->addJob([command, this] {
            juce::ChildProcess proc {};
            if (proc.start(command)) {
                this->processHasStarted_.store(true);

                auto buffer = std::vector<std::uint8_t>(1024 * 16, std::uint8_t {});
                while (proc.isRunning()) {
                    std::fill(std::begin(buffer), std::end(buffer), std::uint8_t {});
                    auto* const data   = static_cast<void*>(buffer.data());
                    auto const maxSize = static_cast<int>(buffer.size());
                    auto num           = proc.readProcessOutput(data, maxSize);
                    if (num != 0) {
                        queue_.push(juce::String::createStringFromData(static_cast<void*>(buffer.data()), num));
                    }
                }

                this->processExitCode_.store(proc.getExitCode());
                this->processHasFinished_.store(true);
            }
        });

        startTimerHz(5);
        return;
    }

    // Currently only thread pools are supported
    jassertfalse;
}

auto BackgroundProcess::addListener(Listener* listener) -> void { listeners_.add(listener); }

auto BackgroundProcess::removeListener(Listener* listener) -> void { listeners_.remove(listener); }

auto BackgroundProcess::timerCallback() -> void
{
    if (processHasStarted_.load()) {
        processHasStarted_.store(false);
        listeners_.call([this](Listener& l) { l.backgroundProcessStarted(this); });
    }

    if (processHasFinished_.load()) {
        processHasFinished_.store(false);
        listeners_.call([this, ec = processExitCode_.load()](Listener& l) { l.backgroundProcessFinished(this, ec); });
        stopTimer();
    }

    auto output = queue_.pop();
    while (output.has_value()) {
        listeners_.call([this, s = output.value()](Listener& l) { l.backgroundProcessOutputReceived(this, s); });
        output = queue_.pop();
    }
}

} // namespace mc