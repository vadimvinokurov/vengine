#pragma once

#define VE_DEG2RAD(deg) ((deg) * (PI / 180.f))

namespace VE {
enum class Interpolation {
   Constant,
   Linear,
   Cubic
};


__forceinline float linearInterpolate(float a, float b, float t) noexcept
{
   return a + (b - a) * t;
}


__forceinline Vector3 linearInterpolate(const Vector3& a, const Vector3& b, float t) noexcept
{
   return Vector3::lerp(a, b, t);
}


__forceinline Quaternion linearInterpolate(const Quaternion& a, const Quaternion& b, float t) noexcept
{
   if (a.dot(b) < 0.0f) {
      return Quaternion::mix(a, b * -1.0f, t).normalize();
   } else {
      return Quaternion::mix(a, b, t).normalize();
   }
}


__forceinline float loopclamp(float val, float lo, float hi) noexcept
{
   val = fmodf(val - lo, hi - lo);
   return val < 0.0f ? val + hi : val + lo;
}

} //namespace VE