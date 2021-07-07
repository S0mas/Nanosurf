import QtQuick 2.15
import QtCharts 2.15

Item {
    ChartView {
       anchors.fill: parent
       theme: ChartView.ChartThemeDark
       animationOptions: ChartView.SeriesAnimations
       antialiasing: true
       ValueAxis {
           id: axisX
           titleText: "Z movement[m]"
           min: chartData.minMovement
           max: chartData.maxMovement
           labelFormat: "%1.5e"
       }
       ValueAxis {
           id: axisY
           titleText: "force[N]"
           min: chartData.minForce
           max: chartData.maxForce
           labelFormat: "%1.5e"
       }
       LineSeries {
           id: lineSeries
           name: "Force Curve Display"
           axisX: axisX
           axisY: axisY
           color: colors.mainOrange
       }
    }
    Component.onCompleted: {
        chartData.series = lineSeries
    }
}
