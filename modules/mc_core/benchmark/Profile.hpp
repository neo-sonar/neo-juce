#pragma once

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

struct Profiler {
    Profiler() = default;

    void beginSession(std::string const& name, std::string const& filepath = "results.json")
    {
        std::lock_guard<std::mutex> lock(_mutex);
        if (_currentSession != nullptr) { internalEndSession(); }

        _buffer.reserve(1'000'000);

        _outputStream.open(filepath);
        if (_outputStream.is_open()) {
            _currentSession       = std::make_unique<InstrumentationSession>();
            _currentSession->Name = name;
            writeHeader();
        } else {
            DBG(mc::jformat("Profiler could not open results file '{0}'.", filepath));
        }
    }

    void endSession()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        internalEndSession();
    }

    void writeProfile(const ProfileResult& result)
    {
        auto name = result.Name;
        std::replace(name.begin(), name.end(), '"', '\'');

        auto const json = mc::format(                                                                    //
            R"(,{{"cat":"function","dur": {0},"name": "{1}","ph":"X","pid":0,"tid": "{2}","ts": {3}}})", //
            result.ElapsedTime.count(),                                                                  //
            name,                                                                                        //
            fmt::streamed(result.ThreadID),                                                              //
            result.Start.count()                                                                         //
        );

        std::lock_guard<std::mutex> lock(_mutex);
        if (_currentSession != nullptr) { _buffer.push_back(json); }
    }

    static auto get() -> Profiler&
    {
        static Profiler instance;
        return instance;
    }

private:
    void writeHeader()
    {
        _outputStream << R"({"otherData": {},"traceEvents":[{})";
        _outputStream.flush();
    }

    void writeFooter()
    {
        _outputStream << "]}";
        _outputStream.flush();
    }

    // Note: you must already own lock on mutex_ before
    // calling InternalEndSession()
    void internalEndSession()
    {

        if (_currentSession != nullptr) {
            for (auto const& item : _buffer) { _outputStream << item; }

            _outputStream.flush();
            writeFooter();
            _outputStream.close();
            _currentSession.reset(nullptr);
            _currentSession = nullptr;
        }
    }

    std::mutex _mutex;
    std::unique_ptr<InstrumentationSession> _currentSession { nullptr };
    std::ofstream _outputStream;
    Vector<std::string> _buffer;
};

struct ProfileTimer {
    explicit ProfileTimer(const char* name) : _name(name) { _startTimepoint = std::chrono::steady_clock::now(); }

    ~ProfileTimer() // NOLINT(bugprone-exception-escape)
    {
        if (!_stopped) { stop(); }
    }

    ProfileTimer(const ProfileTimer& other)                  = delete;
    ProfileTimer(ProfileTimer&& other)                       = delete;
    auto operator=(const ProfileTimer& rhs) -> ProfileTimer& = delete;
    auto operator=(ProfileTimer&& rhs) -> ProfileTimer&      = delete;

    void stop()
    {
        auto endTimepoint = std::chrono::steady_clock::now();
        auto highResStart = FloatingPointMicroseconds { _startTimepoint.time_since_epoch() };
        auto elapsedTime
            = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch()
              - std::chrono::time_point_cast<std::chrono::microseconds>(_startTimepoint).time_since_epoch();

        Profiler::get().writeProfile({ _name, highResStart, elapsedTime, std::this_thread::get_id() });

        _stopped = true;
    }

private:
    const char* _name;
    std::chrono::time_point<std::chrono::steady_clock> _startTimepoint;
    bool _stopped { false };
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
