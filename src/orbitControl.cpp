#include<orbitControl.h>

OribitControl::OribitControl(Camera &iCamera): camera(&iCamera) {};

// Rotate camera position and up vector
void OribitControl::rotate(const Vector2f &curPosition, const Vector2i &screeSize) {
    // Get previous and current vector
    Vector3f currentVector = calculatePositionVector(curPosition, screeSize);
    Vector3f preVector = calculatePositionVector(prePosition, screeSize);

    // Calculate angle
    float angle = std::acos(std::min(1.0f, currentVector.dot(preVector)));
    float cos = std::cos(angle / 2);
    float sin = std::sin(angle / 2);

    // Calculate axis
    Vector3f axis = preVector.cross(preVector);
    Vector4f wordAxis = camera->getViewMatrix().inverse() * Vector4f(axis, 0.0);

    // rotate by quaternion
    wordAxis.x = wordAxis.x * sin;
    wordAxis.y = wordAxis.y * sin;
    wordAxis.z = wordAxis.z * sin;
    wordAxis.w = cos;
    Matrix4f rotationMatrix = Matrix4f::quaternionRotation(wordAxis);

    // update camera
    Vector4f newPosition = rotationMatrix * Vector4f(camera->position(), 0.0);
    Vector4f newUp = rotationMatrix * Vector4f(camera->up(), 0.0);
    camera->position(Vector3f(newPosition.x, newPosition.y, newPosition.z));
    camera->up(Vector3f(newUp.x, newUp.y, newUp.z));
};

Vector3f OribitControl::calculatePositionVector(const Vector2f &position, const Vector2i &screeSize) {
    Vector3f res(
        2.0 * position.x / screeSize.x - 1.0,
        2.0 * position.y / screeSize.y - 1.0,
        0.0
    );
    float z = 1 - res.x * res.x - res.y * res.y;
    if (z < 0.0) {
        return res.normalized();
    } else {
        res.z = std::sqrt(z);
        return res;
    }
};