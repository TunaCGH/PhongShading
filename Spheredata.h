#pragma once
#include <vector>
#include <cmath>
#include <glm/glm/glm.hpp>
#include "Vertex.h"

//
class SphereData {
public:
    // Hàm sinh dữ liệu hình cầu
    // radius: Bán kính
    // sectorCount: Số lát cắt dọc (như múi cam)
    // stackCount: Số lát cắt ngang
    static void Generate(float radius, int sectorCount, int stackCount,
        std::vector<Vertex>& vertices, std::vector<GLuint>& indices)
    {
        vertices.clear();
        indices.clear();

        const float PI = 3.14159265359f;
        float x, y, z, xy;
        float nx, ny, nz, lengthInv = 1.0f / radius;

        float sectorStep = 2 * PI / sectorCount;
        float stackStep = PI / stackCount;
        float sectorAngle, stackAngle;

        // 1. Sinh các đỉnh (Vertices) và Pháp tuyến (Normals)
        for (int i = 0; i <= stackCount; ++i) {
            stackAngle = PI / 2 - i * stackStep; // Từ pi/2 xuống -pi/2
            xy = radius * cosf(stackAngle);
            z = radius * sinf(stackAngle);

            for (int j = 0; j <= sectorCount; ++j) {
                sectorAngle = j * sectorStep; // Từ 0 đến 2pi

                x = xy * cosf(sectorAngle);
                y = xy * sinf(sectorAngle);

                // Đối với hình cầu tâm O, vector pháp tuyến chính là vector tọa độ chuẩn hóa
                nx = x * lengthInv;
                ny = y * lengthInv;
                nz = z * lengthInv;

                vertices.push_back({ glm::vec3(x, y, z), glm::vec3(nx, ny, nz) });
            }
        }

        // 2. Sinh các chỉ số nối tam giác (Indices)
        int k1, k2;
        for (int i = 0; i < stackCount; ++i) {
            k1 = i * (sectorCount + 1);
            k2 = k1 + sectorCount + 1;

            for (int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
                if (i != 0) {
                    indices.push_back(k1);
                    indices.push_back(k2);
                    indices.push_back(k1 + 1);
                }
                if (i != (stackCount - 1)) {
                    indices.push_back(k1 + 1);
                    indices.push_back(k2);
                    indices.push_back(k2 + 1);
                }
            }
        }
    }
};