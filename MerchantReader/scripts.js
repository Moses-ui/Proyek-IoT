var api_key = "YJMP9RMTL8LL3KKS";
var url = "https://api.thingspeak.com/channels/2498284/feeds.json?api_key=" + api_key + "&results=2";

function httpGetAsync(url, callback)
{
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.onreadystatechange = function() { 
        if (xmlHttp.readyState == 4 && xmlHttp.status == 200)
            callback(xmlHttp.responseText);
    }
    xmlHttp.open("GET", url, true); // true for asynchronous 
    xmlHttp.send(null);
}

var saldo = document.getElementById("saldo");
var pesan_transaksi = document.getElementById("pesan_transaksi")
setInterval(() => {
    httpGetAsync(url, (response) => {
        let saldoValue = JSON.parse(response)["feeds"][0]["field1"];
        if (JSON.parse(response)["feeds"][1]["field2"] == 1) {
            pesan_transaksi.innerText = "SALDO AWAL: " + saldoValue;    
        } else if (JSON.parse(response)["feeds"][1]["field2"] == 2) {
            pesan_transaksi.innerText = "TRANSAKSI BERHASIL, SISA SALDO " + saldoValue;
        } else if (JSON.parse(response)["feeds"][1]["field2"] == 3){
            pesan_transaksi.innerText = "SALDO TIDAK MENCUKUPI";
        }
    });
}, 1000);
