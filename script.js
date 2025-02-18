// Gem i en variabel for at beholde data ved reload af siden
let weatherData = {
    "temperature": [],
    "timestamp": []
};

const maxLength = 5 / 1440;


let weatherChart;
document.addEventListener('DOMContentLoaded', function() {
    const ctx = document.getElementById('weatherChart').getContext('2d');
    weatherChart = new Chart(ctx, {
        type: 'line',
        data: {
            labels: weatherData.timestamp,
            datasets: [{
                label: 'Temperature (°C)',
                data: weatherData.temperature,
                borderColor: 'rgba(75, 192, 192, 1)',
                borderWidth: 1,
                fill: false
            }]
        },
        options: {
            scales: {
                x: {
                    type: 'time',
                    time: {
                        unit: 'hour'
                    },
                    title: {
                        display: true,
                        text: 'Timestamp'
                    }
                },
                y: {
                    title: {
                        display: true,
                        text: 'Temperature (°C)'
                    }
                }
            }
        }
    });

    window.refreshData = function() {
        fetch('./data.json')
            .then(response => response.json())
            .then(data => {
                const newestData = data[data.length - 1];
                weatherChart.data.labels.push(newestData.timestamp);
                weatherChart.data.datasets[0].data.push(newestData.temperature);
                weatherChart.update();
            });
    };
});

function WebSocket() {
    let ws = new WebSocket("ws://localhost:8080/ws");
    ws.onopen = function () {
        console.log("Connected");
        ws.send("Hello, Server!");
    };

    ws.onmessage = function (evt) {
        console.log(evt.data);
        let data = JSON.parse(evt.data);
        // Append to the weatherData object
        AddData(data.temperature, data.timestamp);
        console.log(weatherData);
    };

    // Startup 
    fetch('./data.json')
        .then(response => response.json())
        .then(data => {
            weatherData = data;
        });
}

function AddData(temp, timestamp) {
    if (!temp || !timestamp) {
        return;
    }

    // Append data to the weatherData object
    weatherData.temperature.push(temp);
    weatherData.timestamp.push(timestamp);



    weatherChart.data.labels.push(timestamp);
    weatherChart.data.datasets[0].data.push(temp);

        // Remove the oldest data points if the arrays exceed the maximum length
        if (weatherData.temperature.length > maxLength) {
            weatherChart.data.labels.shift();
        }
        if (weatherData.timestamp.length > maxLength) {
            weatherChart.data.datasets[0].data.shift();
        }

    weatherChart.update();
}

// Download data.json with weatherData
function DownloadData() {
    const data = "data:text/json;charset=utf-8," + encodeURIComponent(JSON.stringify(weatherData));
    const a = document.createElement('a');
    a.href = data;
    a.download = 'data.json';
    a.click();
}