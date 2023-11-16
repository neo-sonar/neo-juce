namespace neo {

auto toVector(BufferWithSampleRate<float> const& buffer) -> std::vector<float> { return toVector(buffer.buffer); }

auto toVector(BufferWithSampleRate<double> const& buffer) -> std::vector<double> { return toVector(buffer.buffer); }

} // namespace neo
