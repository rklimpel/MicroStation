window.onload = function() {
    // Global parameters:
    // do not resize the chart canvas when its container does (keep at 600x400px)
    Chart.defaults.global.responsive = false;

    // define the chart data
    var chartDataHumidity = {
        labels: labels_list,
        datasets: [{
            label: '{{ humidity_legend }}',
            fill: true,
            lineTension: 0.5,
            backgroundColor: "rgba(75,192,192,0.4)",
            borderColor: "rgba(75,192,192,1)",
            borderCapStyle: 'butt',
            borderDash: [],
            borderDashOffset: 0.0,
            borderJoinStyle: 'miter',
            pointBorderColor: "rgba(75,192,192,1)",
            pointBackgroundColor: "#fff",
            pointBorderWidth: 1,
            pointHoverRadius: 5,
            pointHoverBackgroundColor: "rgba(75,192,192,1)",
            pointHoverBorderColor: "rgba(220,220,220,1)",
            pointHoverBorderWidth: 2,
            pointRadius: 1,
            pointHitRadius: 10,
            data: values_list,
            spanGaps: false
        }]
    }

    // get chart canvas
    var ctx_humidity = document.getElementById("humidity_chart").getContext("2d");

    // create the chart using the chart canvas
    var myChartHumidity = new Chart(ctx_humidity, {
        type: 'line',
        data: chartDataHumidity,
    });
};