#include "ve_pch.h"
#include "ve_camera.h"


#include "common/ve_assert.h"
#include "common/ve_log.h"

using namespace VE;


Camera::Camera(float fov, float aspect, float n, float f, TPerspectiveCamera)
{
   ASSERT_FAILED("not implemented");
}


Camera::Camera(float left, float right, float bottom, float top, TOrthogonalCamera)
{
   SetOrthogonal(left, right, bottom, top);
}


void Camera::SetOrthogonal(float left, float right, float bottom, float top)
{
   projectionMatrix = GetOrtho(left, right, bottom, top, -1, 1);
   viewProjectionMatrix = projectionMatrix * viewMatrix;
}


void Camera::SetPosition(const Vector3& position)
{
   transform.position.xyz = position;
   RecalculateViewMatrix();
}


const Matrix4& Camera::GetViewProjectionMatrix() const
{
   return viewProjectionMatrix;
}


Matrix4 Camera::GetPerspective(float fov, float aspect, float n, float f)
{
   float ymax = n * tanf(fov * static_cast<float>(PI) / 360.0f);
   float xmax = ymax * aspect;
   return Camera::GetFrustum(-xmax, xmax, -ymax, ymax, n, f);
}


Matrix4 Camera::GetFrustum(float left, float right, float bottom, float top, float n, float f)
{
   ASSERT(left != right && top != bottom && n != f, "Invalid frustum");

   return Matrix4(
      (2.0f * n) / (right - left), 0.0f, 0.0f, 0.0f,
      0.0f, (2.0f * n) / (top - bottom), 0.0f, 0.0f,
      (right + left) / (right - left), (top + bottom) / (top - bottom), (-(f + n)) / (f - n), -1,
      0.0f, 0.0f, (-2.0f * f * n) / (f - n), 0.0f);
}


Matrix4 Camera::GetOrtho(float left, float right, float bottom, float top, float n, float f)
{
   VE_LOG_WARNING("Ortho {} {} {} {}", left, right, bottom, top);
   ASSERT(left != right && top != bottom && n != f, "Invalid frustum");
   return Matrix4(
      2.0f / (right - left), 0.0f, 0.0f, 0.0f,
      0.0f, 2.0f / (top - bottom), 0.0f, 0.0f,
      0.0f, 0.0f, -2.0f / (f - n), 0.0f,
      -(right + left) / (right - left), -(top + bottom) / (top - bottom), (-(f + n)) / (f - n), 1);
}


void Camera::RecalculateViewMatrix()
{
   viewMatrix = Matrix4();
   viewMatrix.GetOrigin() = transform.GetOrigin();
   viewMatrix.inverse();
   viewProjectionMatrix = projectionMatrix * viewMatrix;
}