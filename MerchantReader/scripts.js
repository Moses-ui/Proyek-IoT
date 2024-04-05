var api_key = "4HUPWPTBRAS5HQ0C";
var url = "https://api.thingspeak.com/channels/2497964/fields/1.json?api_key=" + api_key + "&results=1";

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
setInterval(() => {
    httpGetAsync(url, (response) => {
        saldo.innerText = JSON.parse(response)["feeds"][0]["field1"];
    });
}, 1000);