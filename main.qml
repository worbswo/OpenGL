import QtQuick 2.15
import QtQuick.Window 2.15
import OpenGLUnderQML 1.0
import QtQuick.Controls 1.0
GLWindow {
    id:glWindow
    width: 857
    height: 720
    visible: true
    antialiasing:true
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
    ComboBox{
        id:shaderComboBox
        model:["PBR","PHONG","BLINN_PHONG"]
        editable: false
        x:glWindow.height*0.01
        y:glWindow.height*0.69
        width : glWindow.width*0.15
        onActivated: {
            glWindow.setShader(currentIndex)
        }
    }

}
