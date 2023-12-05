#include<orbitControl.h>

OribitControl::OribitControl(Camera &iCamera): camera(&iCamera) {};


void OribitControl::lock(bool locking) {
    isLocking = locking;
}

bool OribitControl::lock() {
    return isLocking;
}

void OribitControl::setPosition(const Vector2f position) {
    prePosition = position;
}

// Rotate camera position and up vector
void OribitControl::rotate(const Vector2f curPosition, const Vector2i &screeSize) {
    // Get previous and current vector
    Vector3f currentVector = calculatePositionVector(curPosition, screeSize);
    Vector3f preVector = calculatePositionVector(prePosition, screeSize);

    // Calculate angle
    float angle = std::acos(std::min(1.0f, currentVector.dot(preVector)));
    float cos = std::cos(angle / 2);
    float sin = std::sin(angle / 2);

    // Calculate axis
    Vector3f axis = preVector.cross(currentVector);
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

    // Update previous position
    setPosition(curPosition);
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

// Zoom camera
void OribitControl::zoom(float deltaIntensity) {
    float ratio = 0.0;

    // For intensity >=0, ratio = 1 / (1 + e^(-0.1 * t)) - 0.5, which is a sigmoid function
    // For intensity < 0, ratio = kt, where k < 1, here we choose k = 0.01
    if (deltaIntensity >= 0.0) {
        ratio = 1 / (1 + std::exp(-0.1 * deltaIntensity)) - 0.5;
    } else {
        ratio = 0.01 * deltaIntensity;
    }

    // Update camera new position
    Vector3f newPosition = camera->position() * (1 - ratio) + camera->lookat() * ratio;
    camera->position(newPosition);
}