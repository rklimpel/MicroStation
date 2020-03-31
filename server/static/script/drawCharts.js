window.onload = function() {

    var chartDataHumidity = {
        labels: humidity_labels_list,
        datasets: [{
            fill: false,
            lineTension: 0.5,
            backgroundColor: "rgba(0,0,0,0.0)",
            borderColor: "rgba(256,256,256,1)",
            borderCapStyle: 'round',
            borderDash: [],
            borderDashOffset: 0.0,
            borderJoinStyle: 'round',
            borderWidth: 1.5,
            pointBackgroundColor: "#fff",
            pointBorderWidth: 0.4,
            pointHoverRadius: 10,
            pointHoverBackgroundColor: "rgba(75,192,192,1)",
            pointHoverBorderColor: "rgba(220,220,220,1)",
            pointHoverBorderWidth: 2,
            pointRadius: 0,
            pointHitRadius: 10,
            data: humidity_values_list,
            spanGaps: false
        }],
    }

    var chartDataTemperature = {
        labels: temperature_labels_list,
        datasets: [{
            fill: false,
            lineTension: 0.5,
            backgroundColor: "rgba(0,0,0,0.0)",
            borderColor: "rgba(256,256,256,1)",
            borderCapStyle: 'round',
            borderDash: [],
            borderDashOffset: 0.0,
            borderJoinStyle: 'round',
            borderWidth: 1.5,
            pointBackgroundColor: "#fff",
            pointBorderWidth: 0.4,
            pointHoverRadius: 10,
            pointHoverBackgroundColor: "rgba(75,192,192,1)",
            pointHoverBorderColor: "rgba(220,220,220,1)",
            pointHoverBorderWidth: 2,
            pointRadius: 0,
            pointHitRadius: 10,
            data: temperature_values_list,
            spanGaps: false
        }],
    }

    var chartOptions = {
        responsive: true,
        title: {
            display: false,
        },
        scales: {
            xAxes: [{
                gridLines: {
                    display: false,
                    drawBorder: false
                },
                ticks: {
                    display: false
                }
            }],
            yAxes: [{
                gridLines: {
                    display: false,
                    drawBorder: false
                },
                ticks: {
                    display: false
                },
            }]
        },
        legend: {
            display: false
        },
        tooltips: {
            enabled: true
        },
        labels: {
            enabled: false
        },
        animation: {
            duration: 4000,
        }
        
    }

    var ctx_humidity = document.getElementById("humidity_chart").getContext("2d");
    var ctx_temperature = document.getElementById("temperature_chart").getContext("2d");

    var myChartHumidity = new Chart(ctx_humidity, {
        type: 'line',
        data: chartDataHumidity,
        options: chartOptions,
    });

    var myChartTemperature = new Chart(ctx_temperature, {
        type: 'line',
        data: chartDataTemperature,
        options: chartOptions,
    });
};