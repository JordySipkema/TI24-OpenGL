//
//  Matrix.hpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 31/01/2019.
//  Copyright © 2019 Jordy Sipkema. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#define AsRadian(x) ((x)*(M_PI/180.0f))
#define _USE_MATH_DEFINES

#include <stdio.h>
#include "Vec.hpp"

class Matrix
{
public:
    float values[4][4];
    Matrix();
    Matrix(const Matrix &other);
    
    static Matrix Identity() {
        Matrix* m = new Matrix();
        for (int i = 0; i < 4; i++){
            m->values[i][i] = 1;
        }
        return *m;
    }
    
    static Matrix Rotation(Vec4f v4) {
        Matrix m = Matrix::Identity();
        Vec3f vect = Vec3f(v4.x, v4.y, v4.z);
        vect.normalize();
        
        float t = 1.0f - cos(AsRadian(v4.w));
        float c = cos(AsRadian(v4.w));
        float s = sin(AsRadian(v4.w));
        
        m.values[0][0] = c + (vect.x * vect.x * t);
        m.values[0][1] = (vect.x * vect.y * t) - (vect.z * s);
        m.values[0][2] = (vect.x * vect.z * t) + (vect.y * s);
        
        m.values[1][0] = (vect.y * vect.x * t) + (vect.z * s);
        m.values[1][1] = c + (vect.y * vect.y * t);
        m.values[1][2] = (vect.y * vect.z * t) - (vect.x * s);
        
        m.values[2][0] = (vect.z * vect.x * t) - (vect.y * s);
        m.values[2][1] = (vect.z * vect.y * t) + (vect.x * s);
        m.values[2][2] = c + (vect.z * vect.z * t);
        
        return m;
    }
    
    static Vec3f Rotate(const Vec3f pos, const Vec4f rot){
        Matrix m = Matrix::Rotation(rot);
        
        return pos * m;
    }
    
    friend Vec3f operator*(const Vec3f vect, const Matrix matrix){
        Vec3f result = Vec3f(vect);
        
        for (int i = 0; i < 3; i++){
            result[i] = matrix.values[i][0] * vect.x + matrix.values[i][1] * vect.y + matrix.values[i][2] * vect.z + matrix.values[i][3];
        }
        
        return result;
    }
    
    
};

#endif /* Matrix_hpp */
