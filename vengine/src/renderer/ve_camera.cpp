#include "ve_pch.h"
#include "ve_camera.h"


#include "common/ve_assert.h"

using namespace VE;


Camera::Camera(float fov, float aspect, float n, float f)
{
   projectionMatrix = GetOrtho(-1.6, 1.6, -0.9, 0.9, 0, 2);
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
   ASSERT(left != right && top != bottom && n != f, "Invalid frustum");
   return Matrix4(
      2.0f / (right - left), 0.0f, 0.0f, 0.0f,
      0.0f, 2.0f / (top - bottom), 0.0f, 0.0f,
      0.0f, 0.0f, -2.0f / (f - n), 0.0f,
      -(right + left) / (right - left), -(top + bottom) / (top - bottom), (-(f + n)) / (f - n), 1);
}


void Camera::RecalculateViewMatrix()
{
   // const Vector3& R = transform.GetAxisX();
   // const Vector3& U = transform.GetAxisY();
   // const Vector3& D = transform.GetAxisZ();
   // const Vector3& P = transform.GetOrigin();
   //
   // viewMatrix = Matrix4(R.x, R.y, R.z, 0, U.x, U.y, U.z, 0, D.x, D.y, D.z, 0, P.x, P.y, P.z, 1).getInversed();

   viewMatrix = Matrix4();
   viewMatrix.GetOrigin() = transform.GetOrigin();
   viewMatrix.inverse();
   viewProjectionMatrix = projectionMatrix * viewMatrix;
}