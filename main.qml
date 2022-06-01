import QtQuick 2.15
import QtQuick.Window 2.15
import OpenGLUnderQML 1.0
import QtQuick.Controls 1.0
GLWindow {
    id:glWindow
    width: 1920
    height: 1080
    visible: true
    antialiasing:true
    property bool sticEnable: false
    property int scrollValue :0
    SequentialAnimation on gw {
        NumberAnimation { to: 0; easing.type: Easing.OutQuad }
        loops: Animation.Infinite
        running: true
    }


    MouseArea {
               id: mouseArea_full_area
               anchors.fill: parent

           }

    Rectangle{
        x:0
        y:glWindow.height*0.67
        width : glWindow.width
        height: glWindow.height*0.33
        color:"#C7C7CC"
    }
    Rectangle{
        x:glWindow.width*0.01
        y:glWindow.height*0.69
        width : glWindow.width*0.15
        Text{
            text:"select shader"
            anchors.centerIn: parent
        }
    }

    ComboBox{
        id:shaderComboBox
        model:["PBR","PHONG","BLINN_PHONG"]
        editable: false
        x:glWindow.width*0.01
        y:glWindow.height*0.72
        width : glWindow.width*0.15
        onActivated: {
            glWindow.setShader(currentIndex)

        }
    }
    Rectangle{
        x:glWindow.width*0.18
        y:glWindow.height*0.69
        width : glWindow.width*0.15
        Text{
            text:"shiness"
            anchors.centerIn: parent
        }
    }
    Slider{
        id:shinessSlder
        activeFocusOnPress:false

        maximumValue: 100
        minimumValue: 1
        value:32
        x:glWindow.width*0.18
        y:glWindow.height*0.72
        width : glWindow.width*0.15
        onValueChanged: {
            glWindow.setShiness(value)
        }
    }
    Rectangle{
        x:glWindow.width*0.36
        y:glWindow.height*0.69
        width : glWindow.width*0.15
        Text{
            text:"modelScale"
            anchors.centerIn: parent
        }
    }
    Slider{
        id:scaleSlder
        activeFocusOnPress:false

        maximumValue: 10
        minimumValue: 1
        value:1
        x:glWindow.width*0.36
        y:glWindow.height*0.72
        width : glWindow.width*0.15
        onValueChanged: {
            glWindow.setModelScale(value)
        }
    }
    Rectangle{
        id:lightRect
        color:"#F2F2F7"
        x:glWindow.width*0.85
        y:glWindow.height*0.72
        width : glWindow.width*0.15
        height:width
        border.color: "black"
        border.width: 2
        radius:width/10
        Rectangle{
            x:parent.width/2
            y:0
            width:1
            height: parent.height
            color:"black"
        }
        Rectangle{
            x:0
            y:parent.height/2
            width:parent.width
            height:1
            color:"black"
        }
        Rectangle{
            id:stic2
            x:stic.x-stic
            width: stic.width

        }

        Rectangle{
            id:stic
            x:parent.width/2-width/2
            y:parent.height/2-height/2
            width:parent.width/4;
            height:width
            radius: width/2
            color:"#5856D6"
            border.color: "black"
            border.width: 3
        }
        MouseArea{
            anchors.fill: parent
            hoverEnabled:true
            onPositionChanged : {
                if(sticEnable){
                    if(mouseX>0&&mouseX<width){
                        stic.x=mouseX-stic.width/2
                    }
                    if(mouseY>0&&mouseY<height){
                        stic.y=mouseY-stic.width/2
                    }
                    glWindow.setLightPositionXY((mouseX-width/2)/width,(mouseY-height/2)/height)

                }
            }
            onPressed: {
                sticEnable=true
            }

            onReleased: {
                //stic.x=parent.width/2-stic.width/2
                //stic.y=parent.height/2-stic.height/2
                sticEnable=false
            }
            onWheel: {
                if(sticEnable){
                    if(wheel.angleDelta.y>0){
                        glWindow.setLightPositionZ(0.02);


                    }else{
                        glWindow.setLightPositionZ(-0.02);



                    }
                }
            }

        }
    }
}
