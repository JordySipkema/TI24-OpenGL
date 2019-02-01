//
//  Matrix.cpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 31/01/2019.
//  Copyright © 2019 Jordy Sipkema. All rights reserved.
//

#include "Matrix.hpp"

Matrix::Matrix(){
    for (int r = 0; r < 4; r++){
        for (int c = 0; c < 4; c++ ){
            values[r][c] = 0.0f;
        }
    }
}

Matrix::Matrix(const Matrix &other)
{
    for (int r = 0; r < 4; r++){
        for (int c = 0; c < 4; c++ ){
            this->values[r][c] = other.values[r][c];
        }
    }
}
