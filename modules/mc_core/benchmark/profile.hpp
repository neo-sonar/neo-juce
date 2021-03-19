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

namespace mc
{

using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

struct ProfileResult
{
    std::string Name;

    FloatingPointMicroseconds Start;
    std::chrono::microseconds ElapsedTime;
    std::thread::id ThreadID;
};

struct InstrumentationSession
{
    std::string Name;
};

class Instrumentor
{
private:
    std::mutex mutex_;
    std::unique_ptr<InstrumentationSession> currentSession_ {nullptr};
    std::ofstream outputStream_;
    std::vector<std::string> buffer_;

public:
    Instrumentor() = default;

    void BeginSession(std::string const& name, std::string const& filepath = "results.json")
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (currentSession_ != nullptr) { InternalEndSession(); }

        buffer_.reserve(1'000'000);

        outputStream_.open(filepath);
        if (outputStream_.is_open())
        {
            currentSession_       = std::make_unique<InstrumentationSession>();
            currentSession_->Name = name;
            WriteHeader();
        }
        else
        {
            DBG(mc::format("Instrumentor could not open results file '{0}'.", filepath));
        }
    }

    void EndSession()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        InternalEndSession();
    }

    void WriteProfile(const ProfileResult& result)
    {
        auto name = result.Name;
        std::replace(name.begin(), name.end(), '"', '\'');

        auto const json = fmt::format(                                                                    //
            R"(,{{"cat":"function","dur": {0},"name": "{1}","ph":"X","pid":0,"tid": "{2}","ts": {3}}})",  //
            result.ElapsedTime.count(),                                                                   //
            name,                                                                                         //
            result.ThreadID,                                                                              //
            result.Start.count()                                                                          //
        );

        std::lock_guard<std::mutex> lock(mutex_);
        if (currentSession_ != nullptr) { buffer_.push_back(json); }
    }

    static auto Get() -> Instrumentor&
    {
        static Instrumentor instance;
        return instance;
    }

private:
    void WriteHeader()
    {
        outputStream_ << R"({"otherData": {},"traceEvents":[{})";
        outputStream_.flush();
    }

    void WriteFooter()
    {
        outputStream_ << "]}";
        outputStream_.flush();
    }

    // Note: you must already own lock on mutex_ before
    // calling InternalEndSession()
    void InternalEndSession()
    {

        if (currentSession_ != nullptr)
        {
            for (auto const& item : buffer_) { outputStream_ << item; }

            outputStream_.flush();
            WriteFooter();
            outputStream_.close();
            currentSession_.reset(nullptr);
            currentSession_ = nullptr;
        }
    }
};

class InstrumentationTimer
{
public:
    InstrumentationTimer(const char* name) : name_(name), stopped_(false)
    {
        startTimepoint_ = std::chrono::steady_clock::now();
    }

    ~InstrumentationTimer()
    {
        if (!stopped_) { Stop(); }
    }

    void Stop()
    {
        auto endTimepoint = std::chrono::steady_clock::now();
        auto highResStart = FloatingPointMicroseconds {startTimepoint_.time_since_epoch()};
        auto elapsedTime
            = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch()
              - std::chrono::time_point_cast<std::chrono::microseconds>(startTimepoint_).time_since_epoch();

        Instrumentor::Get().WriteProfile({name_, highResStart, elapsedTime, std::this_thread::get_id()});

        stopped_ = true;
    }

private:
    const char* name_;
    std::chrono::time_point<std::chrono::steady_clock> startTimepoint_;
    bool stopped_;
};
}  // namespace mc

#if MOCI_PROFILE
#define MOCI_PROFILE_BEGIN_SESSION(name, filepath) ::mc::Instrumentor::Get().BeginSession(name, filepath)
#define MOCI_PROFILE_END_SESSION() ::mc::Instrumentor::Get().EndSession()
#define MOCI_PROFILE_SCOPE(name) ::mc::InstrumentationTimer MOCI_ANONYMOUS_VARIABLE(timer)(name);
#define MOCI_PROFILE_FUNCTION() MOCI_PROFILE_SCOPE(MOCI_FUNC_SIG)
#else
#define MOCI_PROFILE_BEGIN_SESSION(name, filepath)
#define MOCI_PROFILE_END_SESSION()
#define MOCI_PROFILE_SCOPE(name)
#define MOCI_PROFILE_FUNCTION()
#endif

#endif  // MODERN_CIRCUITS_JUCE_MODULES_PROFILE_HPP