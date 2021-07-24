#ifndef MODERN_CIRCUITS_JUCE_MODULES_PROFILE_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_PROFILE_HPP

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>

namespace mc {

using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

struct ProfileResult {
    std::string Name;

    FloatingPointMicroseconds Start;
    std::chrono::microseconds ElapsedTime;
    std::thread::id ThreadID;
};

struct InstrumentationSession {
    std::string Name;
};

class Profiler {
private:
    std::mutex mutex_;
    std::unique_ptr<InstrumentationSession> currentSession_ { nullptr };
    std::ofstream outputStream_;
    std::vector<std::string> buffer_;

public:
    Profiler() = default;

    void beginSession(std::string const& name, std::string const& filepath = "results.json")
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (currentSession_ != nullptr) {
            internalEndSession();
        }

        buffer_.reserve(1'000'000);

        outputStream_.open(filepath);
        if (outputStream_.is_open()) {
            currentSession_       = std::make_unique<InstrumentationSession>();
            currentSession_->Name = name;
            writeHeader();
        } else {
            DBG(mc::format("Profiler could not open results file '{0}'.", filepath));
        }
    }

    void endSession()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        internalEndSession();
    }

    void writeProfile(const ProfileResult& result)
    {
        auto name = result.Name;
        std::replace(name.begin(), name.end(), '"', '\'');

        auto const json = fmt::format(                                                                   //
            R"(,{{"cat":"function","dur": {0},"name": "{1}","ph":"X","pid":0,"tid": "{2}","ts": {3}}})", //
            result.ElapsedTime.count(),                                                                  //
            name,                                                                                        //
            result.ThreadID,                                                                             //
            result.Start.count()                                                                         //
        );

        std::lock_guard<std::mutex> lock(mutex_);
        if (currentSession_ != nullptr) {
            buffer_.push_back(json);
        }
    }

    static auto get() -> Profiler&
    {
        static Profiler instance;
        return instance;
    }

private:
    void writeHeader()
    {
        outputStream_ << R"({"otherData": {},"traceEvents":[{})";
        outputStream_.flush();
    }

    void writeFooter()
    {
        outputStream_ << "]}";
        outputStream_.flush();
    }

    // Note: you must already own lock on mutex_ before
    // calling InternalEndSession()
    void internalEndSession()
    {

        if (currentSession_ != nullptr) {
            for (auto const& item : buffer_) {
                outputStream_ << item;
            }

            outputStream_.flush();
            writeFooter();
            outputStream_.close();
            currentSession_.reset(nullptr);
            currentSession_ = nullptr;
        }
    }
};

class ProfileTimer {
public:
    explicit ProfileTimer(const char* name)
        : name_(name), stopped_(false)
    {
        startTimepoint_ = std::chrono::steady_clock::now();
    }

    ~ProfileTimer() // NOLINT(bugprone-exception-escape)
    {
        if (!stopped_) {
            stop();
        }
    }

    ProfileTimer(const ProfileTimer& other) = delete;
    ProfileTimer(ProfileTimer&& other)      = delete;
    auto operator=(const ProfileTimer& rhs) -> ProfileTimer& = delete;
    auto operator=(ProfileTimer&& rhs) -> ProfileTimer& = delete;

    void stop()
    {
        auto endTimepoint = std::chrono::steady_clock::now();
        auto highResStart = FloatingPointMicroseconds { startTimepoint_.time_since_epoch() };
        auto elapsedTime
            = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch()
              - std::chrono::time_point_cast<std::chrono::microseconds>(startTimepoint_).time_since_epoch();

        Profiler::get().writeProfile({ name_, highResStart, elapsedTime, std::this_thread::get_id() });

        stopped_ = true;
    }

private:
    const char* name_;
    std::chrono::time_point<std::chrono::steady_clock> startTimepoint_;
    bool stopped_;
};
} // namespace mc

#if MC_PROFILE
#define MC_PROFILE_BEGIN_SESSION(name, filepath) ::mc::Profiler::get().beginSession(name, filepath)
#define MC_PROFILE_END_SESSION() ::mc::Profiler::get().endSession()
#define MC_PROFILE_SCOPE(name) ::mc::ProfileTimer MC_ANONYMOUS_VARIABLE(timer)(name);
#define MC_PROFILE_FUNCTION() MC_PROFILE_SCOPE(MC_FUNC_SIG)
#else
/// \brief Must be called as early as possible to start a new profiling session.
#define MC_PROFILE_BEGIN_SESSION(name, filepath)
/// \brief Close and saves the profiling run to disk.
#define MC_PROFILE_END_SESSION()
/// \brief Profile a scope
#define MC_PROFILE_SCOPE(name)
/// \brief Profile a function
#define MC_PROFILE_FUNCTION()
#endif

#endif // MODERN_CIRCUITS_JUCE_MODULES_PROFILE_HPP
