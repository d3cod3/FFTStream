/*==============================================================================

    Platype. Yet another commissioned custom made live audio-visual performer software.

    Copyright (c) 2020 Emanuele Mazza aka n3m3da <emanuelemazza@d3cod3.org>

    Platype is distributed under the MIT License. This gives everyone the
    freedoms to use Platype in any context: commercial or non-commercial,
    public or private, open or closed source.

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
    OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.

==============================================================================*/

#include "AppTheme.h"

void AppTheme::setup(){

    ofColor col_main_head = ofColor::fromHex(0x404040);
    ofColor col_main_area = ofColor::fromHex(0x222222);
    ofColor col_win_backg = ofColor::fromHex(0x2b2b2b);

    float alpha_ = 0.8f;

    ImGuiStyle* style = &ImGui::GetStyle();

    style->WindowBorderSize = 0.0f;
    style->WindowMinSize = ImVec2(160, 65);
    style->WindowRounding = 0.0f;
    style->FramePadding = ImVec2(4, 6);
    style->ItemSpacing = ImVec2(8, 2);
    style->ItemInnerSpacing = ImVec2(6, 4);
    style->Alpha = 1.0f;
    style->FrameRounding = 0.0f;
    style->IndentSpacing = 6.0f;
    style->ColumnsMinSpacing = 50.0f;
    style->GrabMinSize = 14.0f;
    style->GrabRounding = 0.0f;
    style->ScrollbarSize = 14.0f;
    style->ScrollbarRounding = 0.0f;
    style->TabRounding = 0.0f;
    style->PopupBorderSize = 0.0f;
    style->TabBorderSize = 0.0f;
    style->ChildBorderSize = 0.0f;
    style->FrameBorderSize = 0.0f;
    style->PopupRounding = 0.0f;

    style->Colors[ImGuiCol_Text]                  = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_TextDisabled]          = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    style->Colors[ImGuiCol_WindowBg]              = ImVec4(0.91f, 0.91f, 0.91f, 0.94f);
    style->Colors[ImGuiCol_ChildBg]               = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style->Colors[ImGuiCol_PopupBg]               = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);

    style->Colors[ImGuiCol_Border]                = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
    style->Colors[ImGuiCol_BorderShadow]          = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
    style->Colors[ImGuiCol_FrameBg]               = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
    style->Colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
    style->Colors[ImGuiCol_FrameBgActive]         = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    style->Colors[ImGuiCol_TitleBg]               = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
    style->Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
    style->Colors[ImGuiCol_TitleBgActive]         = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
    style->Colors[ImGuiCol_MenuBarBg]             = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
    style->Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);

    style->Colors[ImGuiCol_CheckMark]             = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style->Colors[ImGuiCol_SliderGrab]            = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
    style->Colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style->Colors[ImGuiCol_Button]                = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
    style->Colors[ImGuiCol_ButtonHovered]         = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style->Colors[ImGuiCol_ButtonActive]          = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
    style->Colors[ImGuiCol_Header]                = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
    style->Colors[ImGuiCol_HeaderHovered]         = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
    style->Colors[ImGuiCol_HeaderActive]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);


    style->Colors[ImGuiCol_ResizeGrip]            = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
    style->Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    style->Colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);

    style->Colors[ImGuiCol_PlotLines]             = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    style->Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    style->Colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    style->Colors[ImGuiCol_ModalWindowDarkening]  = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

    style->Colors[ImGuiCol_Separator]            = ImVec4(col_main_head, 0.73f);
    style->Colors[ImGuiCol_SeparatorHovered]     = ImVec4(col_main_head, 0.f);
    style->Colors[ImGuiCol_SeparatorActive]      = ImVec4(col_main_head, 0.f);
    style->Colors[ImGuiCol_DragDropTarget]       = ImVec4(col_main_head, 0.8f);
    style->Colors[ImGuiCol_NavHighlight]         = ImVec4(col_main_head, 0.f);
    style->Colors[ImGuiCol_NavWindowingHighlight]= ImVec4(col_main_head, 0.f);
    style->Colors[ImGuiCol_Tab]                  = ImVec4(col_main_area, 0.9f);
    style->Colors[ImGuiCol_TabHovered]           = ImVec4(col_win_backg, 0.7f);
    style->Colors[ImGuiCol_TabActive]            = ImVec4(col_win_backg, 0.7f);

    for (int i = 0; i <= ImGuiCol_COUNT; i++)
    {
        ImVec4& col = style->Colors[i];
        float H, S, V;
        ImGui::ColorConvertRGBtoHSV( col.x, col.y, col.z, H, S, V );

        if( S < 0.1f )
        {
            V = 1.0f - V;
        }
        ImGui::ColorConvertHSVtoRGB( H, S, V, col.x, col.y, col.z );
        if( col.w < 1.00f )
        {
            col.w *= alpha_;
        }
    }

}

void AppTheme::fixForRetinaScreen(){
    ImGuiStyle* style = &ImGui::GetStyle();

    style->FramePadding = ImVec2(8, 12);
    style->ItemSpacing = ImVec2(16, 4);
    style->ItemInnerSpacing = ImVec2(12, 8);
    style->IndentSpacing = 12.0f;
    style->ColumnsMinSpacing = 100.0f;
    style->GrabMinSize = 28.0f;
    style->ScrollbarSize = 28.0f;

}
