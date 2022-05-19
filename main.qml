import QtQuick 2.15
import QtQuick.Window 2.15
import OpenGLUnderQML 1.0


GLWindow {
    width: 640
    height: 480
    visible: true
    antialiasing:true
    SequentialAnimation on gw {
        NumberAnimation { to: 0; easing.type: Easing.OutQuad }
        loops: Animation.Infinite
        running: true
    }
    function setWindowSize(displayWidth, displayHeight) {
            x = 0
            y = 0
            width = displayWidth
            height = displayHeight
            console.log(width, "x", height)

        }


}
