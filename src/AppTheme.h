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

#pragma once

#include "BaseTheme.h"
#include "ofMain.h"

// ImGui colors
#define C64_BLACK 	ImVec4(0,0,0,1)
#define C64_WHITE 	ImVec4(1,1,1,1)
#define C64_RED     ImVec4(136/255.0f,57/255.0f,50/255.0f,1.0f)
#define C64_CYAN 	ImVec4(103/255.0f,182/255.0f,189/255.0f,1.0f)
#define C64_PURPLE	ImVec4(139/255.0f,63/255.0f,150/255.0f,1.0f)
#define C64_GREEN	ImVec4(85/255.0f,160/255.0f,73/255.0f,1.0f)
#define C64_BLUE	ImVec4(64/255.0f,49/255.0f,141/255.0f,1.0f)
#define C64_YELLOW	ImVec4(191/255.0f,206/255.0f,114/255.0f,1.0f)
#define C64_ORANGE	ImVec4(139/255.0f,84/255.0f,41/255.0f,1.0f)
#define C64_BROWN	ImVec4(87/255.0f,66/255.0f,0/255.0f,1.0f)
#define C64_PINK	ImVec4(184/255.0f,105/255.0f,98/255.0f,1.0f)
#define C64_DGRAY	ImVec4(80/255.0f,80/255.0f,80/255.0f,1.0f)
#define C64_MGRAY	ImVec4(120/255.0f,120/255.0f,120/255.0f,1.0f)
#define C64_LGREEN	ImVec4(148/255.0f,224/255.0f,137/255.0f,1.0f)
#define C64_LBLUE 	ImVec4(120/255.0f,105/255.0f,196/255.0f,1.0f)
#define C64_LGRAY 	ImVec4(159/255.0f,159/255.0f,159/255.0f,1.0f)

#define VHS_DGRAY       ImVec4(58/255.0f,58/255.0f,58/255.0f,1.0f)
#define VHS_DGRAY_OVER  ImVec4(58/255.0f,58/255.0f,58/255.0f,0.7f)
#define VHS_GRAY        ImVec4(82/255.0f,99/255.0f,106/255.0f,1.0f)
#define VHS_GRAY_OVER   ImVec4(82/255.0f,99/255.0f,106/255.0f,0.7f)
#define VHS_LGRAY       ImVec4(121/255.0f,135/255.0f,140/255.0f,1.0f)
#define VHS_LGRAY_OVER  ImVec4(121/255.0f,135/255.0f,140/255.0f,0.7f)
#define VHS_RED         ImVec4(182/255.0f,30/255.0f,41/255.0f,1.0f)
#define VHS_RED_OVER    ImVec4(182/255.0f,30/255.0f,41/255.0f,0.7f)
#define VHS_BLUE        ImVec4(35/255.0f,81/255.0f,140/255.0f,1.0f)
#define VHS_BLUE_OVER   ImVec4(35/255.0f,81/255.0f,140/255.0f,0.7f)
#define VHS_YELLOW      ImVec4(190/255.0f,134/255.0f,60/255.0f,1.0f)
#define VHS_YELLOW_OVER ImVec4(190/255.0f,134/255.0f,60/255.0f,0.7f)

class AppTheme : public ofxImGui::BaseTheme{

public:

    void setup() override;

    void fixForRetinaScreen();

};

class AppLoggerChannel : public ofBaseLoggerChannel
{
public:

    ImVector<char*>     Items;
    bool                scrollToBottom;

    AppLoggerChannel() {
        scrollToBottom = true;
    }

    void log( ofLogLevel level, const std::string & module, const std::string & message ){
        std::ostringstream oss;
        oss << ofGetTimestampString("%H:%M:%S:%i") << " ";
        oss << "[" << ofGetLogLevelName(level, true) << "] ";
        if (module != "") {
            oss << module << ": ";
        }
        oss << message << endl;

        this->AddLog("%s\n", oss.str().c_str());
    }
    void log( ofLogLevel level, const std::string & module, const char* format, ... ) OF_PRINTF_ATTR( 4, 5 ){
        va_list args;
        va_start(args, format);
        if(level != OF_LOG_WARNING && level != OF_LOG_ERROR && level != OF_LOG_FATAL_ERROR){
            log(level, module, format, args);
        }
        va_end(args);
    }
    void log( ofLogLevel level, const std::string & module, const char* format, va_list args ){
        // Compose the message.
        std::ostringstream oss;
        oss << ofGetTimestampString("%H:%M:%S:%i") << " ";
        oss << "[" << ofGetLogLevelName(level, true) << "] ";
        if (module != "") {
            oss << module << ": ";
        }

        oss << ofVAArgsToString(format, args) << endl;

        this->AddLog("%s\n", oss.str().c_str());
    }

    void Clear()     {
        for (int i = 0; i < Items.Size; i++){
            free(Items[i]);
        }
        Items.clear();
    }

    void AddLog(const char* fmt, ...) IM_FMTARGS(2){
        char buf[1024];
        va_list args;
        va_start(args, fmt);
        vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
        buf[IM_ARRAYSIZE(buf)-1] = 0;
        va_end(args);
        Items.push_back(strdup(buf));
        scrollToBottom = true;
    }

    string GetLastLog() {
        if(Items.empty()) return std::string("");

        std::string str(Items.back());
        return str;
    }

    void Draw(const char* title){

        if (!ImGui::Begin(title,nullptr,ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoResize))
        {
            ImGui::End();
            return;
        }
        if (ImGui::Button("Clear")) Clear();

        ImGui::Separator();
        if (ImGui::BeginChild("scrolling", ImVec2(0,0), false, ImGuiWindowFlags_HorizontalScrollbar) ){

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4,1)); // Tighten spacing

            ImVec4 col_default_text = ImGui::GetStyleColorVec4(ImGuiCol_Text);
            for (int i = 0; i < Items.Size; i++){
                const char* item = Items[i];
                ImVec4 col = col_default_text;
                if (strstr(item, "[notice")) col = ImGui::GetStyleColorVec4(ImGuiCol_Text);
                else if (strstr(item, "[warning")) col = ImColor(1.0f,0.5f,0.0f,1.0f);
                else if (strstr(item, "[ error")) col = ImColor(1.0f,0.176f,0.176f,1.0f);
                else if (strstr(item, "[silent")) col = ImColor(1.0f,0.78f,0.58f,1.0f);
                else if (strncmp(item, "# ", 2) == 0) col = ImColor(1.0f,0.78f,0.58f,1.0f);

                // force verbose
                if(strstr(item, "[verbose]")){
                    col = ImColor(0.235f,1.0f,0.235f,1.0f);
                }

                ImGui::PushStyleColor(ImGuiCol_Text, col);
                ImGui::TextUnformatted(item);
                ImGui::PopStyleColor();
            }

            if(scrollToBottom){
                scrollToBottom = false;
                ImGui::SetScrollHere(1.0f);
            }

            ImGui::PopStyleVar(1);

            ImGui::EndChild();
        }
        ImGui::End();
    }

};
