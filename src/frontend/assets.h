#pragma once

//<헤더>
#include "imgui.h" //imgui 핵심 기능
#include "imgui_impl_sdl2.h" //SDL이벤트를 imgui가 이해 가능하게
#include "imgui_impl_opengl3.h"//imgui가 만든 UI를 OpenGL로 화면에 그리게 해준다
/*
ImGUI: 즉시 모드 GUI라이브러리. 버튼, 슬라이더 등을 매 프레임 그려낸다
OpenGL: 3D그래픽 API이다. GPU를 통해 화면에 실제로 픽셀을 랜더링 한다
SDL2: 크로스 플랫폼 가능하게, 운영체제 API를 알아서 호출하여 윈도우 생성, 마우스/키보드 입력, 그래픽(OpenGL)와 오디어 하드웨어에 접근 제어
*/

#include <SDL.h>//SDL이다. 창 생성, 이벤트 처리
#include <SDL_opengl.h>//OpenGL관련 기능을 쓰기 위해 필요

#include<vector>


#define BASIC_LOC_X 0
#define BASIC_LOC_Y 0

#define BASIC_SIZE_W 10
#define BASIC_SIZE_H 10

#define BASIC_ACTIVATE true

#define BASIC_GAP true



using namespace std;
//in components

class Transform{};

//위치 이동 전반에 관한 class
class Transform2: Transform{
    private:
        vector<int> location = {BASIC_LOC_X,BASIC_LOC_Y};
        vector<int> size = {BASIC_SIZE_W,BASIC_SIZE_H};
        bool active = true;
    public:
    //
        Transform2(int x=BASIC_LOC_X, int y=BASIC_LOC_Y, int w=BASIC_SIZE_W, int h=BASIC_SIZE_H, bool a=BASIC_ACTIVATE){
            location[0]=x;
            location[1]=y;
            size[0]=w;
            size[1]=h;
            active=a;
        }

        //XY
        void setX(int x){
            location[0]=x;
        }
        void setY(int y){
            location[0]=y;
        }
        void setXY(int x, int y){
            setX(x);
            setY(y);
        } 

        int getX() const{
            return location[0];
        }
        int getY() const{
            return location[1];
        }

        int& operator[](int index){
            return location[index];
        }
        const int& operator[](int index) const{
            return location[index];
        }

        //size
        void setW(int w){
            size[0]=w;
        }
        void setH(int h){
            size[0]=h;
        }
        void setWH(int w, int h){
            setW(w);
            setH(h);
        } 

        int getW() const{
            return size[0];
        }
        int getH() const{
            return size[1];
        }

        //active
        void deactive(){
            active=false;
        }
        void active(){
            active=true;
        }
        bool getactive() const{
            return active;
        }
};

//입력처리
class Manager{};

class InputManager:Manager{
    private:
        bool hovered = false;
        bool clicked = false;
        bool r_clicked = false;
        bool active = false;
        bool activated = false;
        bool deactivated = false;
        bool edited = false;
        bool visible = false;
        bool focused = false;
        
    public:
        virtual void updateHovered()=0;
        virtual void updateClicked()=0;
        virtual void updateRClicked()=0;
        virtual void updateActive()=0;
        virtual void updateActivated()=0;
        virtual void updateDeactivated()=0;
        virtual void updateEdited()=0;
        virtual void updateVisible()=0;
        virtual void updateFocused()=0;
       
        void setHovered(bool h){
            hovered = h;
        }
        void setClicked(bool c){
            clicked = c;
        }
        void setRClicked(bool rc){
            r_clicked = rc;
        }
        void setActive(bool a){
            active = a;
        }
        void setActivated(bool a){
            activated = a;
        }
        void setDeactivated(bool d){
            deactivated = d;
        }
        void setEdited(bool e){
            edited = e;
        }
        void setVisible(bool v){
            visible = v;
        }
        void setFocused(bool f){
            focused = f;
        }

        bool isHovered() const{
            return hovered;
        }
        bool isClicked() const{
            return clicked;
        }
        bool isRClicked() const{
            return r_clicked;
        }
        bool isActive() const{
            return active;
        }
        bool isActivated() const{
            return activated;
        }
        bool isDeactivated() const{
            return deactivated;
        }
        bool isEdited() const{
            return edited;
        }
        bool isVisible() const{
            return visible;
        }
        bool isFocused() const{
            return focused;
        }
};

class ElementInputManager : public InputManager {

public:
    void updateHovered() override{
    setHovered(ImGui::IsItemHovered());
    }
    void updateClicked() override{
        setClicked(ImGui::IsItemClicked());
    }
    void updateRClicked() override{
        setRClicked(ImGui::IsItemClicked(ImGuiMouseButton_Right));
    }
    void updateActive() override{
        setActive(ImGui::IsItemActive());
    }
    void updateActivated() override{
        setActivated(ImGui::IsItemActivated());
    }
    void updateDeactivated() override{
        setDeactivated(ImGui::IsItemDeactivated());
    }
    void updateEdited() override{
        setEdited(ImGui::IsItemEdited());
    }
    void updateVisible() override{
        setVisible(ImGui::IsItemVisible());
    }
    void updateFocused() override{
        setFocused(ImGui::IsItemFocused());
    }
};

class WindowInputManager : public InputManager {

public:
    void updateHovered() override{
        setHovered(ImGui::IsWindowHovered());
    }

    void updateClicked() override{
        setClicked(ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left));
    }

    void updateRClicked() override{
        setRClicked(ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right));
    }

    void updateActive() override{
        setActive(ImGui::IsWindowFocused());
    }

    void updateActivated() override{
        setActivated(ImGui::IsWindowAppearing());
    }

    void updateDeactivated() override{
        setDeactivated(false);
    }

    void updateEdited() override{
        setEdited(false);
    }

    void updateVisible() override{
        setVisible(!ImGui::IsWindowCollapsed());
    }

    void updateFocused() override{
        setFocused(ImGui::IsWindowFocused());
    }
};

class ButtonInputManager:public ElementInputManager{
    
};

class SliderInputManager:public ElementInputManager{
    
};

class TextBox:public ElementInputManager{
    
};

//assets
class Asset{};

class Object: public Asset{
    private:
        Transform2 transform;
    
    public:
        Object(int x=BASIC_LOC_X, 
            int y=BASIC_LOC_Y, 
            int w=BASIC_SIZE_W, 
            int h=BASIC_SIZE_H, 
            int a=BASIC_ACTIVATE):transform(x,y,w,h){}
        virtual void inputCall()=0;
        virtual void render()=0;
        virtual void update()=0;
                
};

//enum class Arrange{HORIZONTAL, VERTICAL};

class Layout:public Object{
    private:
        int gap;
        vector<Object*> elements;
        //이벤트 처리
    public:
        Layout(
            int x=BASIC_LOC_X, 
            int y=BASIC_LOC_Y, 
            int w=BASIC_SIZE_W, 
            int h=BASIC_SIZE_H, 
            int a=BASIC_ACTIVATE,
            int g=BASIC_GAP    
        ):Object(x,y,w,h,a),gap(g){}

        void setGap(int g){
            gap = g;
        }
        int getGap() const{
            return gap;
        }

        vector<Object*> getElements()const{
            return elements;
        }
        
};

class HorizontalLayout:public Layout{
    private:
        WindowInputManager inputmanager;        

    public:
        HorizontalLayout(
            int x=BASIC_LOC_X, 
            int y=BASIC_LOC_Y, 
            int w=BASIC_SIZE_W, 
            int h=BASIC_SIZE_H, 
            int a=BASIC_ACTIVATE,
            int g=BASIC_GAP
        ):Layout(x,y,w,h,a,g){};

        void render()override{
            vector<Object*> elements = getElements();
            for(auto &i:elements){
                ImGui::BeginChild;
                i->render();
            }
        }
};

