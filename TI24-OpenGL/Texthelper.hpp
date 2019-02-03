//
//  Texthelper.hpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 02/02/2019.
//  Copyright © 2019 Jordy Sipkema. All rights reserved.
//

#ifndef Texthelper_hpp
#define Texthelper_hpp

#include <stdio.h>
#include <GLUT/glut.h>
#include <FTGL/ftgl.h>

class Texthelper
{
public:
    static void ShowText(std::string text, int fontsize, int x, int y){
        // Create a pixmap font from a TrueType file.
        FTGLPixmapFont font("/Library/Fonts/Verdana.ttf");
        
        // If something went wrong, bail out.
        if(font.Error())
            return;
        
        // Set the font size and render a small text.
        font.FaceSize(fontsize);
        font.Render(text.c_str(), -1, FTPoint(x, y, 0), FTPoint(), FTGL::RENDER_ALL);
    }
};

#endif /* Texthelper_hpp */

