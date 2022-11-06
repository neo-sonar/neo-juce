#pragma once

#include <variant>

namespace mc {

using LottieLayer = std::variant<LottieNullLayer, LottieShapeLayer>;

[[nodiscard]] auto parseLottieLayer(juce::var const& layer) -> Expected<LottieLayer, String>;

[[nodiscard]] auto name(LottieLayer const& layer) -> Optional<String>;
[[nodiscard]] auto inPoint(LottieLayer const& layer) -> double;
[[nodiscard]] auto outPoint(LottieLayer const& layer) -> double;
[[nodiscard]] auto transform(LottieLayer const& layer) -> LottieTransform;

} // namespace mc
