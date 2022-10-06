namespace mc {

auto toVector(BufferWithSampleRate<float> const& buffer) -> Vector<float> { return toVector(buffer.buffer); }

auto toVector(BufferWithSampleRate<double> const& buffer) -> Vector<double> { return toVector(buffer.buffer); }

} // namespace mc
