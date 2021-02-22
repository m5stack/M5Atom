const char html[] = R"=====(
<!DOCTYPE html><html lang="en"><head><meta charset="UTF-8"><meta name="viewport" content="width=device-width, initial-scale=1.0"><meta http-equiv="refresh" content="3"><title>ATOM Socket</title><style id="CSSstyle" data-color="#f8be00">body{margin:0;padding:0;display:flex;flex-direction:column;justify-content:center;align-items:center;min-height:100vh;}.header{background-color:#ffe600;font-family:emoji;display:flex;flex-direction:column;align-items:center;justify-content:space-between;padding:30px;z-index:2;height:200px;margin-bottom:30px;}.body{height:400px;background-color:white;z-index:2;width:300px;border-radius:40px 40px 0 0;display:flex;flex-direction:column;justify-content:center;align-items:center;}.controlBtn{outline-style:none;border-radius:10px;width:180px;height:30px;background-color:white;}.progressBox{width:100%;height:30px;border-radius:10px;overflow:hidden;position:relative;}.progressBar{position:absolute;height:100%;background-color:#f8be00;width:0;}.progressContainer{width:100%;height:100%;z-index:21;background-color:#343934393439;}</style></head><body><div class="header"><div><h1>ATOM Socket</h1></div><button id="btn" class="controlBtn" onclick="changeRelayState()"> Current Power State: ON </button></div><div class="body"><h3 id="vol">Voltage: </h3><h3 id="current">Current: </h3><h3 id="power">InspectingPower: </h3></div><script>var httpRequest;var stateChange="/on";function res_handle(){var data=httpRequest.responseText;if(data.indexOf("on")!=-1){stateChange="/off";}else if(data.indexOf("off")!=-1){stateChange="/on";}
list=data.split('#');document.getElementById("vol").innerHTML=list[0];document.getElementById("current").innerHTML=list[1];document.getElementById("power").innerHTML=list[2];document.getElementById("btn").innerHTML=list[3];}
function changeRelayState(){if(window.XMLHttpRequest){httpRequest=new XMLHttpRequest()}else if(window.ActiveXObject){httpRequest=new ActiveXObject()}
httpRequest.open("GET",stateChange,true);httpRequest.onreadystatechange=res_handle;httpRequest.send();}
function GetData(){if(window.XMLHttpRequest){httpRequest=new XMLHttpRequest()}else if(window.ActiveXObject){httpRequest=new ActiveXObject()}
httpRequest.open("GET","/data",true);httpRequest.onreadystatechange=res_handle;httpRequest.send();}
GetData();</script></body></html>
)=====";




