#pragma once
#include "math/ve_matrix4.h"
#include "math/ve_transform.h"

namespace VE {

struct TPerspectiveCamera {};


struct TOrthogonalCamera {};

constexpr TPerspectiveCamera PerspectiveCamera{};
constexpr TOrthogonalCamera OrthogonalCamera{};


class Camera {
public:
   Camera(float fov, float aspect, float n, float f, TPerspectiveCamera);
   Camera(float left, float right, float bottom, float top, TOrthogonalCamera);

public:
   void SetOrthogonal(float left, float right, float bottom, float top);
   void SetPosition(const Vector3& position);
   const Vector3& GetPosition() const { return transform.position.xyz; }

   const Matrix4& GetProjectionMatrix() const { return projectionMatrix; }
   const Matrix4& GetViewMatrix() const { return viewMatrix; }
   const Matrix4& GetViewProjectionMatrix() const;

   static Matrix4 GetPerspective(float fov, float aspect, float n, float f);
   static Matrix4 GetFrustum(float left, float right, float bottom, float top, float n, float f);
   static Matrix4 GetOrtho(float left, float right, float bottom, float top, float n, float f);

private:
   void RecalculateViewMatrix();

private:
   Matrix4 projectionMatrix;
   Matrix4 viewMatrix;
   Matrix4 viewProjectionMatrix;
   Matrix4 transform;
};

}